#include <iostream>

using namespace std;

/*
 *	This is a wrong solution, it will sometimes ask for a position out of bounds
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

	/* Binary search is the solution, but the lower bound is wrong. */
	/* This bug is a very rare one to find in random tests, but that's when you'll need exhaustive tests, and when this kind of program will come in handy */
	int lo = 0, hi = n;
	while(lo <= hi) {
		int mid = lo + (hi - lo)/2;
		int x = ask(mid);
		if(x == y) break;
		else if(x < y) {
			lo = mid+1;
		} else {
			hi = mid-1;
		}
	}
}