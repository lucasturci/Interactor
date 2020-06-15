#include <cstdio>
#include <unistd.h>
#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>

#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KNRM  "\x1B[0m"

using namespace std;

void print_help() {
	printf("This program in an interactor, created to transmit messages between the judge and the solution of an interactive problem.\n");
	printf("Both programs must be executables in the current directory and must print and read from standard IO.\n");
}

int main(int argc, char * argv[]) {
	
	if(argc != 3) {
		printf("%sUSAGE:%s %s <solution exec name> <judge exec name>\n", KRED, KNRM, argv[0]);
		print_help();
		exit(0);
	}

	/* Creates sockets */
	int sockets[2], judge;

	if( socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) < 0 ) {
		perror("opening stream socket pair");
		exit(1);
	}

	/* Fork processes */
	if ( (judge = fork()) == -1 ) {
		perror("in forking");
		exit(1);
	}

	cout << KGRN << "Running..." << endl << KNRM;

	/* Close stdin and stdout, to be replaced by the sockets */
	close(0); // close stdin
	close(1); // close stdout
		
	if(judge) { // is judge

		// Transforms sockets[0] into stdin and stdout
		dup(sockets[0]);
		dup(sockets[0]);


		string prog_name = "./" + string(argv[2]);
		execl(prog_name.c_str(), prog_name.c_str(), NULL);
	} else { // is solution

		// Transforms sockets[1] into stdin and stdout
		dup(sockets[1]);
		dup(sockets[1]);


		string prog_name = "./" + string(argv[1]);
		execl(prog_name.c_str(), prog_name.c_str(), NULL);
	}
}