#include <cstdio>
#include <unistd.h>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>

#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KNRM  "\x1B[0m"
#define KWHT  "\x1B[37m"

using namespace std;

void print_help() {
	printf("This program in an interactor, created to transmit messages between the judge and the solution of an interactive problem.\n");
	printf("Both programs must be executables in the current directory and must print and read from standard IO.\n");
}

int will_not_block(int fd) {
	fd_set rfds;
	struct timeval tv;
	tv.tv_sec = 0, tv.tv_usec = 500000;
    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);
    int ret = select(fd + 1, &rfds, NULL, NULL, &tv);

    if(ret == -1) {
    	perror("in querying select");
    	exit(1);
    }
    return ret;
}

int main(int argc, char * argv[]) {
	
	if(argc != 3) {
		printf("%sUSAGE:%s%s <solution exec name> <judge exec name>\n", KRED, KNRM, argv[0]);
		print_help();
		exit(0);
	}

	/* Creates sockets */
	int jud_sock[2], sol_sock[2];

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, jud_sock) < 0) {
		perror("in creating judge sockets");
	}
	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sol_sock) < 0) {
		perror("in creating solution sockets");
	}

	int super;
	if ( (super = fork()) == -1) {
		perror("in first forking");
		exit(1);
	}

	if(super) {
		while(1) {
			const size_t B = 10024; // buffer big enough to read all at once
			ssize_t sz;
			char buffer[B];

			// -------------- JUDGE ---------------------

			while(will_not_block(jud_sock[0])) {
				cout << KRED << "JUDGE SAYS" << KNRM << endl;
				sz = read(jud_sock[0], (void *) buffer, B);
				if(sz < 0) {
					perror("in reading from judge socket");
					exit(1);
				}

				// Write to stdout and to solution socket
				write(1, buffer, sz);
				write(sol_sock[0], buffer, sz);
			}


			// -------------- SOLUTION ---------------------
			while(will_not_block(sol_sock[0])) {
				cout << KGRN << "SOLUTION SAYS" << KNRM << endl;

				sz = read(sol_sock[0], (void *) buffer, B);
				if(sz < 0) {
					perror("in reading from solution socket");
					exit(1);
				}

				// Write to stdout and to solution socket
				write(1, buffer, sz);
				write(jud_sock[0], buffer, sz);
				cout << endl;
			}

		}

	} else {
		int judge;
		/* Fork processes */
		if ( (judge = fork()) == -1 ) {
			perror("in forking");
			exit(1);
		}

		/* Close stdin and stdout, to be replaced by the sockets */
		close(0); // close stdin
		close(1); // close stdout
			
		if(judge) { // is judge

			// Transforms jud_sock[1] into stdin and stdout
			dup(jud_sock[1]);
			dup(jud_sock[1]);


			string prog_name = "./" + string(argv[2]);
			execl(prog_name.c_str(), prog_name.c_str(), NULL);
		} else { // is solution

			// Transforms sol_sock[1] into stdin and stdout
			dup(sol_sock[1]);
			dup(sol_sock[1]);

			string prog_name = "./" + string(argv[1]);
			execl(prog_name.c_str(), prog_name.c_str(), NULL);
		}
	}



}