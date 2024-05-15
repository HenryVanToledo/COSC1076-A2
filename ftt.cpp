#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "LinkedList.h"
#include "Coin.h"

using namespace std;

void displayMenu() {
    cout << "Main Menu:" << endl;
    cout << "1. Display Meal Options" << endl;
    cout << "2. Purchase Meal" << endl;
    cout << "3. Save and Exit" << endl;
    cout << "Administrator-Only Menu:" << endl;
    cout << "4. Add Food" << endl;
    cout << "5. Remove Food" << endl;
    cout << "6. Display Balance" << endl;
    cout << "7. Abort Program" << endl;
    cout << "Select your option (1-7): " << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <foodsfile> <coinsfile>" << endl;
        return 1;
    }

    string foodsFile = argv[1];
    string coinsFile = argv[2];

    // Load data from files
    ifstream foods(foodsFile);
    ifstream coins(coinsFile);
    if (!foods.is_open() || !coins.is_open()) {
        cerr << "Error: Could not open files." << endl;
        return 1;
    }

    LinkedList foodList;
    Coin coinArray[10]; // Assuming we have a fixed size for simplicity

    string line;
    // Load food data
    while (getline(foods, line)) {
        stringstream ss(line);
        string id, name, desc, priceStr;
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, desc, '|');
        getline(ss, priceStr);
        // Assuming price is valid here for simplicity, but should validate
        double price = stod(priceStr);
        foodList.insertSorted(id, name, desc, price);
    }

    // Load coin data
    int coinIndex = 0;
    while (getline(coins, line)) {
        stringstream ss(line);
        int denom, quantity;
        ss >> denom;
        ss.ignore(); // ignore the comma
        ss >> quantity;
        coinArray[coinIndex++] = Coin(denom, quantity);
    }

    // Display menu and handle user input
    while (true) {
        displayMenu();
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                foodList.display();
                break;
            case 2:
                // Implement purchase meal
                break;
            case 3:
                // Save data and exit
                break;
            case 4:
                // Add food
                break;
            case 5:
                // Remove food
                break;
            case 6:
                // Display balance
                break;
            case 7:
                // Abort program
                return 0;
            default:
                cerr << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}
