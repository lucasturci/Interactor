#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

/* Random generator */
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

/* Generates a random sorted sequence */
vector<int> generate_sequence() {
	uniform_int_distribution<int> n_distribution(1, 1000);
	int n = n_distribution(rng); // random sequence size

	uniform_int_distribution<int> values_distribution(1, 1e9); 

	vector<int> seq;
	for(int i = 1; i <= n; ++i) {
		seq.push_back(values_distribution(rng));
	}

	sort(seq.begin(), seq.end());
	return seq;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	vector<int> seq = generate_sequence();

	/* Randomize the position of the value */
	uniform_int_distribution<int> pos_distribution(0, seq.size()-1);
	int pos = pos_distribution(rng);

	// Print problem info
	cout << seq.size() << ' ' << seq[pos] << endl;

	int count_guesses = 0;
	while(1) {
		int guess; cin >> guess;
		guess--;

		// If guessed position is out of bounds
		if(guess < 0 or guess >= seq.size()) {
			cerr << "WA: position out of bounds" << endl;
			break;
		}
		
		// Handle guesses counting
		count_guesses++;
		if(count_guesses == 12) {
			cout << -1 << '\n';
			cerr << "WA: guess limit exceeded" << endl;
			break;
		} else {
			// If got it right, print and terminate program
			if(seq[guess] == seq[pos]) {
				cout << seq[guess] << endl;
				cerr << "SUCCESS" << endl;
				break;
			}
			cout << seq[guess] << endl;
		}
	}
}