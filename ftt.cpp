#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
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


void purchaseMeal(LinkedList& foodList, Coin* coinArray) {
    string foodID;
    cout << "Purchase Meal" << endl;
    cout << "-------------" << endl;
    cout << "Please enter the ID of the food you wish to purchase: ";
    cin >> foodID;

    Node* foodItem = foodList.find(foodID);
    if (foodItem == nullptr) {
        cerr << "Error: Food item not found." << endl;
        return;
    }

    cout << "You have selected \"" << foodItem->name << " - " << foodItem->desc << "\". This will cost you $ " << fixed << setprecision(2) << foodItem->price << "." << endl;
    cout << "Please hand over the money - type in the value of each note/coin in cents." << endl;
    cout << "Please enter ctrl-D or enter on a new line to cancel this purchase." << endl;

    double amountDue = foodItem->price;
    double amountPaid = 0.0;
    int denomination;
    while (amountPaid < amountDue) {
        cout << "You still need to give us $" << fixed << setprecision(2) << amountDue - amountPaid << ": ";
        if (!(cin >> denomination)) {
            // Cancel purchase
            cout << "Purchase cancelled. Refunding money." << endl;
            return;
        }

        bool validDenom = false;
        for (int i = 0; i < 10; ++i) {
            if (coinArray[i].getDenomination() == denomination) {
                validDenom = true;
                coinArray[i].increaseQuantity();
                amountPaid += denomination / 100.0;
                break;
            }
        }

        if (!validDenom) {
            cerr << "Error: invalid denomination encountered." << endl;
        }
    }

    // Calculate change
    double change = amountPaid - amountDue;
    cout << "Your change is $" << fixed << setprecision(2) << change << endl;
    // Provide change to customer
    // ...

    // Update food item stock
    foodItem->quantity--;

    cout << "Purchase successful. Returning to main menu." << endl;
}

void saveAndExit(const LinkedList& foodList, const Coin* coinArray, const string& foodsFile, const string& coinsFile) {
    ofstream foods(foodsFile);
    ofstream coins(coinsFile);
    
    if (!foods.is_open() || !coins.is_open()) {
        cerr << "Error: Could not open files for saving." << endl;
        return;
    }

    // Save food data
    Node* current = foodList.head;
    while (current != nullptr) {
        foods << current->id << "|" << current->name << "|" << current->desc << "|" << fixed << setprecision(2) << current->price << endl;
        current = current->next;
    }

    // Save coin data
    for (int i = 0; i < 10; ++i) {
        coins << coinArray[i].getDenomination() << "," << coinArray[i].getQuantity() << endl;
    }

    foods.close();
    coins.close();
    cout <<"Data saved successfully. Exiting program." << endl;
}

void addFoodItem(LinkedList& foodList) {
string name, desc, priceStr;
cout <<"Enter the item name: ";
cin.ignore();  // Ignore any remaining input in the buffer
getline(cin, name);
cout << "Enter the item description: ";
getline(cin, desc);
cout << "Enter the price for this item (e.g., 8.50): ";
getline(cin, priceStr);
// Validate price
size_t pos = priceStr.find('.');
if (pos == string::npos || pos == 0 || pos == priceStr.length() - 1) {
    cerr << "Error: Invalid price format." << endl;
    return;
}

double price;
try {
    price = stod(priceStr);
} catch (...) {
    cerr << "Error: Invalid price format." << endl;
    return;
}

// Generate new ID
string id = "F" + to_string(foodList.getNextID());

foodList.insertSorted(id, name, desc, price);
cout << "This item \"" << name << " - " << desc << "\" has now been added to the food menu." << endl;
}

bool validateFoodLine(const string& line) {
stringstream ss(line);
string id, name, desc, priceStr;
getline(ss, id, ‘|’);
getline(ss, name, ‘|’);
getline(ss, desc, ‘|’);
getline(ss, priceStr);
if (id.empty() || name.empty() || desc.empty() || priceStr.empty()) {
return false;
}
size_t pos = priceStr.find(’.’);
if (pos == string::npos || pos == 0 || pos == priceStr.length() - 1) {
return false;
}
try {
stod(priceStr);
} catch (…) {
return false;
}
return true;
}

bool validateCoinLine(const string& line) {
stringstream ss(line);
int denom, quantity;
char comma;
ss >> denom >> comma >> quantity;
if (!ss || comma != ‘,’ || denom <= 0 || quantity < 0) {
return false;
}
return true;
}

void abortProgram() {
cout << "Program aborted. All data will be lost." << endl;
exit(0);
}

void displayBalance(const Coin* coinArray) {
cout << "Balance Summary" << endl;
cout << "———––" << endl;
cout << "Denom | Quantity | Value" << endl;
cout << "—————————" << endl;

double totalValue = 0.0;
for (int i = 0; i < 10; ++i) {
    int denom = coinArray[i].getDenomination();
    int quantity = coinArray[i].getQuantity();
    double value = denom * quantity / 100.0;
    cout << denom << " | " << quantity << " |$ " << fixed << setprecision(2) << value << endl;
    totalValue += value;
}

cout << "---------------------------" << endl;
cout << "$ " << fixed << setprecision(2) << totalValue << endl;
}
void removeFoodItem(LinkedList& foodList) {
string foodID;
cout << "Enter the food id of the food to remove from the menu: ";
cin >> foodID;

Node* foodItem = foodList.find(foodID);
if (foodItem == nullptr) {
    cerr << "Error: Food item not found." << endl;
    return;
}

foodList.remove(foodID);
cout << "\"" << foodID << " - " << foodItem->name << " - " << foodItem->desc << "\" has been removed from the system." << endl;
}


int main(int argc, char* argv[]) {
if (argc != 3) {
cerr << "Usage: " << argv[0] << ""  "" << endl;
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
    if (!validateFoodLine(line)) {
        cerr << "Error: Invalid food data format." << endl;
        return 1;
    }
    stringstream ss(line);
    string id, name, desc, priceStr;
    getline(ss, id, '|');
    getline(ss, name, '|');
    getline(ss, desc, '|');
    getline(ss, priceStr);
    double price = stod(priceStr);
    foodList.insertSorted(id, name, desc, price);
}

// Load coin data
int coinIndex = 0;
while (getline(coins, line)) {
    if (!validateCoinLine(line)) {
        cerr << "Error: Invalid coin data format." << endl;
        return 1;
    }
    stringstream ss(line);
    int denom, quantity;
    char comma;
    ss >> denom >> comma >> quantity;
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
            purchaseMeal(foodList, coinArray);
            break;
        case 3:
            saveAndExit(foodList, coinArray, foodsFile, coinsFile);
            return 0;
        case 4:
            addFoodItem(foodList);
            break;
        case 5:
            removeFoodItem(foodList);
            break;
        case 6:
            displayBalance(coinArray);
            break;
        case 7:
            abortProgram();
            break;
        default:
            cerr << "Invalid option. Please try again." << endl;
    }
}

return 0;
}