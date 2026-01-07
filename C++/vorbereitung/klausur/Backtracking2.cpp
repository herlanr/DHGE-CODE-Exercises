
#include <iostream>
#include <iomanip>
#include <cstdlib>  // std::atoi, EXIT_*
using namespace std;

// Available coin denominations
const int coins[] = {1, 2, 5, 10};
// Number of coin types
const int nCoins = sizeof(coins) / sizeof(coins[0]);

// Limits and state for building combinations
const int MAX_LEN = 64;   // maximum number of coins in one combination
int current[MAX_LEN];     // buffer holding the current combination
int curSize = 0;          // how many entries of 'current' are active
int callCount = 0;        // how many recursive calls we've made
int solutions = 0;        // number of valid combinations found

// Print the current combination [ c0 c1 c2 ... ]
void printCurrent() {
    cout << "[ ";
    for (int i = 0; i < curSize; ++i) {
        cout << current[i] << ' ';
    }
    cout << "]\n";
}

// Backtracking to generate unbounded combinations (order doesn't matter):
// 'index'     -> current coin type we can use (and any later ones)
// 'remaining' -> how much amount we still need to reach
void explore_unbounded(int index, int remaining) {
    ++callCount; // bookkeeping

    // End condition 1: exact target reached -> emit solution
    if (remaining == 0) {
        ++solutions;
        printCurrent();
        return;
    }

    // End condition 2: overshot the target -> dead branch
    if (remaining < 0) {
        return;
    }

    // End condition 3: no more coin types to try -> dead branch
    if (index == nCoins) {
        return;
    }

    // Choice A: include coin[index] and stay on same index (unbounded use)
    if (curSize < MAX_LEN) {
        current[curSize++] = coins[index];                 // push
        explore_unbounded(index, remaining - coins[index]); // recurse
        --curSize;                                         // pop (backtrack)
    }

    // Choice B: exclude this coin type and move to the next type
    explore_unbounded(index + 1, remaining);
}

int main(int argc, const char* argv[]) {
    // Expect exactly one argument: the amount to form
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " amount\n";
        return EXIT_FAILURE;
    }

    // Convert it to integer and validate
    int amount = std::atoi(argv[1]);
    if (amount <= 0) {
        cerr << "Error: amount must be > 0\n";
        return EXIT_FAILURE;
    }

    // Run backtracking
    cout << "Unbounded combinations for amount = " << amount << "\n";
    explore_unbounded(0, amount);

    // Report    // Report totals
    cout << "Total solutions: " << solutions << "\n";
    cout << "Number of recursive calls: " << callCount << "\n";
    return EXIT_SUCCESS;
}