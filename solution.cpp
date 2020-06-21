#include <iostream>

using namespace std;

/*
 *	Solution program: finds the position of an element in a *sorted* sequence in less than 11 moves.
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

	/* Binary search is the solution */
	int lo = 1, hi = n;
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

	cout << "Closing SOLUTION" << endl;
}