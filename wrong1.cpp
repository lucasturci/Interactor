#include <iostream>

using namespace std;

/*
 *	This is a wrong solution, it will perform a sequential search, and the guesses limit will be exceeded.
 */

/* 
 *	Interaction with the judge: prints a position, and the judge returns the element in that position. 
 *	If the judge returns -1, the position was invalid or you exceeded number of moves, you must terminate immediately
 *	If the judge returns 0, you found the element, and your program was accepted. You should also finish the program.
 */
int ask(int pos) {
	cout << pos << endl;
	int ans; cin >> ans;
	if(ans == -1) exit(0);
	return ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	/* Reads the size of the sequence (up to 10^3) and the element to be found (the element is guaranteed to be in the sequence) */
	int n, y;
	cin >> n >> y;

	for(int i = 1; i <= n; ++i) {
		ask(i);
	}
}