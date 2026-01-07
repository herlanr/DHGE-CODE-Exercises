#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

// Structure for an item
struct Item {
    char name[32];       // If you change length, adjust input format
    double weight;
    double value;
    bool current;        // current solution: true if item is in the knapsack
    bool optimal;        // optimal solution: true if item is in the knapsack
};

// List of all items
Item items[] = {
    { "Apple", 10, 5, false, false },
    { "Cereal Bar", 2.5, 25, false, false },
    { "Gold Ring", 0.5, 1666, false, false },
    { "Heavy Load", 70, 499.99, false, false },
    { "Passport", 0.5, 60, false, false },
    { "Wallet", 5, 123.27, false, false },
    { "Camera", 49.5, 459.99, false, false },
    { "Glasses", 13, 260.50, false, false },
    { "Juice", 30, 30, false, false },
    { "Sweater", 12, 20, false, false },
    { "Raincoat", 3.5, 40, false, false },
    { "Knife", 10, 50, false, false },
    { "Tissue", 0.1, 0.5, false, false },
    { "Toilet Paper", 0.5, 5, false, false },
    { "Banana", 5, 10, false, false },
    { "Map", 1.5, 20, false, false },
    { "Sunscreen", 7.5, 40, false, false }
};

// Number of items
const int itemCount = sizeof(items) / sizeof(items[0]);

// Best solution value so far
double bestValue = 0;
int callCount = 0; // Count recursive calls

void saveSolution(double value);
void tryItem(int i, double remainingWeight, double currentValue);

// Save current solution if it's better than the best so far
void saveSolution(double value) {
    if (value > bestValue) {
        for (int i = 0; i < itemCount; ++i) {
            items[i].optimal = items[i].current;
        }
        bestValue = value;
    }
}

// Try item i
void tryItem(int i, double remainingWeight, double currentValue) {
    ++callCount;
    if (i == itemCount) {
        // No more items to consider -> solution complete
        saveSolution(currentValue);
        return;
    }

    Item* item = &items[i];
    if (item->weight <= remainingWeight) {
        // Item fits -> try including it
        item->current = true;
        tryItem(i + 1, remainingWeight - item->weight, currentValue + item->value);
    }

    // Always try excluding the item
    item->current = false;
    tryItem(i + 1, remainingWeight, currentValue);
}

int main(int argc, const char* argv[]) {
    double maxWeight;
    if ((argc != 2) || ((maxWeight = atof(argv[1])) <= 0)) {
        cerr << "Usage: " << argv[0] << " max_weight" << endl;
        return EXIT_FAILURE;
    }

    /*** Compute solution ***/
    tryItem(0, maxWeight, 0);

    /*** Output ***/
    double totalWeight = 0;
    for (int i = 0; i < itemCount; ++i) {   
        if (items[i].optimal) {
            cout << items[i].name << ": Weight " << items[i].weight
                 << ", Value " << items[i].value << endl;
            totalWeight += items[i].weight;
        }
    }
    cout << "Total: Weight " << totalWeight << ", Value " << bestValue << endl;
    cout << "Number of recursive calls: " << callCount << endl;

    return EXIT_SUCCESS;
}