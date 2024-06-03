#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cctype>
#include <limits>
#include "LinkedList.h"


// validates input files
void validateFoodData(const std::string& food_file, LinkedList& food_list);
void validateCoinData(const std::string& coin_file);

// save data to files
void saveData(const std::string& food_file, const std::string& coin_file, LinkedList& food_list);

// display menu prompt
void displayMenu();

// Second menu option
bool menuOption(LinkedList& food_list, const std::string& food_file, const std::string& coin_file);

// Option 2, purchaseMeal function
void purchaseMeal(LinkedList& foodList);

// Add Food Function
void addFood(LinkedList& food_list);

// Remove Food Function
void removeFood(LinkedList& food_list);

// Display Balance Function
void displayBalance();

// Terminate Program Function
void terminateProgram(LinkedList& food_list, const std::string& food_file, const std::string& coin_file);

// Function to generate the next food ID
std::string generateFoodID(const LinkedList& food_list);


int main(int argc, char **argv)
{
    // Check if command line has 3 args
    if (argc != 3) {
        std::cout << "Error: " << std::endl;
        std::cout << "Please enter command line as: ./ftt <food_file> <coin_file>" << std::endl;
        return EXIT_FAILURE;
    }

    // Seperate food and coin file from command line
    std::string food_file = argv[1];
    std::string coin_file = argv[2];

    // creating food_list linked list
    LinkedList food_list;

    // Load data from files
    validateFoodData(food_file, food_list);
    validateCoinData(coin_file);

    // Executes menu option on repeat until user exits or program saves
    while(!menuOption(food_list, food_file, coin_file)) {

    }

    return EXIT_SUCCESS;
}

void validateFoodData(const std::string& food_file, LinkedList& food_list) {
    // Validates .dat file
    if (food_file.size() < 4 || food_file.substr(food_file.size() - 4) != ".dat") {
        std::cerr << "Error: Invalid file type. Only .dat files are accepted." << std::endl;
        exit(EXIT_FAILURE);
    }
    // Checks if file can open
    std::ifstream file(food_file);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << food_file << std::endl;
        exit(EXIT_FAILURE);
    }

    // loops through entire file line by line
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string foodID, foodName, foodDesc, priceStr;
        // Validation to see if 3 | seperators are in each line
        if (std::getline(ss, foodID, '|') &&
            std::getline(ss, foodName, '|') &&
            std::getline(ss, foodDesc, '|') &&
            std::getline(ss, priceStr)) {

            // Validation for ID formating
            if (foodID.empty() || foodID[0] != 'F' || foodID.substr(1).find_first_not_of("0123456789") != std::string::npos) {
                std::cerr << "Error: Invalid food ID format in file " << food_file << std::endl;
                exit(EXIT_FAILURE);
            }

            // Validation for Price formatting
            size_t dotPos = priceStr.find('.');
            if (dotPos == std::string::npos || dotPos == 0 || dotPos == priceStr.size() - 1 || priceStr.find_first_not_of("0123456789.", dotPos + 1) != std::string::npos) {
                std::cerr << "Error: Invalid price format in file " << food_file << std::endl;
                exit(EXIT_FAILURE);
            }

            // inserts the values into the LinkedList containing food items
            double price = std::stod(priceStr);
            food_list.insertSorted(foodID, foodName, foodDesc, price);
        // Error in formatting of lines in input food file
        } else {
            std::cerr << "Error: Invalid line format in file " << food_file << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

void validateCoinData(const std::string& coin_file) {

    // Check if the file extension is .dat
    if (coin_file.size() < 4 || coin_file.substr(coin_file.size() - 4) != ".dat") {
        std::cerr << "Error: Invalid file type. Only .dat files are accepted." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Validation to see if file opened
    std::ifstream file(coin_file);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << coin_file << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;

    // loops to read all lines in input coin file
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string denomStr, quantityStr;

        // Check for seperation of ','
        if (std::getline(ss, denomStr, ',') && std::getline(ss, quantityStr)) {
            // Validate and convert denomination and quantity to integers
            try {
                int denomination = std::stoi(denomStr);
                int quantity = std::stoi(quantityStr);

                // check that denom and quant are non-negative
                if (denomination < 0 || quantity < 0) {
                    std::cerr << "Error: Invalid denomination or quantity in file " << coin_file << std::endl;
                    exit(EXIT_FAILURE);
                }
                // Stores the denom in the register with associated quantity
                Coin::registerCoins[denomination] = quantity;
            } catch (const std::exception& e) {
                std::cerr << "Error: Invalid line format in file " << coin_file << std::endl;
                exit(EXIT_FAILURE);
            }
        // Error for line format in input coin file
        } else {
            std::cerr << "Error: Invalid line format in file " << coin_file << std::endl;
            exit(EXIT_FAILURE);
        }
    }


    //////////////////////////////
    //////////// TESTING REGISTER
    //////////////////////////////

    // Print the loaded coin data (for debugging purposes)
    // for (const auto& coin : Coin::registerCoins) {
    //     std::cout << "Denomination: " << coin.first << " Quantity: " << coin.second << std::endl;
    // }
}

// opening menu
void displayMenu() {
    std::cout << "Main Menu:" << std::endl;
    std::cout << "   1. Display Meal Options" << std::endl;
    std::cout << "   2. Purchase Meal" << std::endl;
    std::cout << "   3. Save and Exit" << std::endl;
    std::cout << "Administrator-Only Menu:" << std::endl;
    std::cout << "   4. Add Food" << std::endl;
    std::cout << "   5. Remove Food" << std::endl;
    std::cout << "   6. Display Balance" << std::endl;
    std::cout << "   7. Abort Program" << std::endl;
    std::cout << "\nType: 'help' to display Help Menu:\n";
    std::cout << "\nSelect your option (1-7) : ";
}

// function to display help text (minor improvement)
void displayHelp() {
    std::cout << "\nHelp Menu:\n";
    std::cout << "1. Display Meal Options - Shows the list of available meals.\n";
    std::cout << "2. Purchase Meal - Allows you to purchase a meal by entering its ID.\n";
    std::cout << "3. Save and Exit - Saves current data and exits the program.\n";
    std::cout << "4. Add Food - (Admin) Adds a new food item to the list.\n";
    std::cout << "5. Remove Food - (Admin) Removes a food item from the list.\n";
    std::cout << "6. Display Balance - (Admin) Displays the balance summary.\n";
    std::cout << "7. Abort Program - (Admin) Terminates the program without saving.\n";
    std::cout << "Type 'help' at any prompt to see this help menu again.\n\n";
}




bool menuOption(LinkedList& food_list, const std::string& food_file, const std::string& coin_file) {
    int option;
    std::string input;

    displayMenu();

    // Handle control + d
    if (std::cin.eof()) {
        std::cout << "Exiting program." << std::endl;
        exit(EXIT_SUCCESS);
    }

    std::cin >> input;

    if (input == "help") {
        displayHelp();
        // Clear input buffer to avoid the infinite loop
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false; // Returning false to re-display the menu
    }


    std::stringstream ss(input);
    ss >> option;

    // Check for valid integer input
    if (ss.fail() || !ss.eof()) {
        std::cout << "Invalid option. Please select a valid option (1-7):\n\n";
        return menuOption(food_list, food_file, coin_file);
    }

    // Displays food menu option
    if (option == 1) {
        food_list.display();
        return false;
    }

    // Purchase meal option
    if (option == 2) {
        purchaseMeal(food_list);
        return false;
    }

    // Saves coin and food data to output files
    if (option == 3) {
        saveData(food_file, coin_file, food_list);
        std::cout << "Data saved. Exiting program." << std::endl;
        exit(EXIT_SUCCESS);
    }

    // Add food option to food_list
    if (option == 4) {
        addFood(food_list);
        return false;
    }

    if (option == 5) {
        removeFood(food_list);
        return false;
    }

    if (option == 6) {
        displayBalance();
        return false;
    }

    if (option == 7) {
        terminateProgram(food_list, food_file, coin_file);
    }

    std::cout << "Invalid option. Please select a valid option (1-7)\n\n";
        // If input is not a valid integer, clear error flags
    std::cin.clear();
    return menuOption(food_list, food_file, coin_file);
}




void purchaseMeal(LinkedList& foodList) {
    std::cout << "\nPurchase Meal" << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << "Please enter the ID of the food you wish to purchase:" << std::endl;
    std::string foodID;
    std::cin >> foodID;

    // Check if the food ID is valid
    if (foodID.empty() || foodID[0] != 'F' || foodID.substr(1).find_first_not_of("0123456789") != std::string::npos) {
        std::cerr << "Error: Invalid food ID format.\n" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    // Find the food item in the linked list with the associated ID
    Node* current = foodList.getHead();
    Node* foundNode = nullptr;

    // loops through to match IDs
    while (current != nullptr) {
        if (current->data->id == foodID) {
            foundNode = current;
        }
        current = current->next;
    }

    if (foundNode != nullptr) {

        // calculates in cents for denom enum
        int totalPriceInCents = foundNode->data->price.dollars * 100 + foundNode->data->price.cents;
        CoinTracker coinTracker(totalPriceInCents);

        // menu output
        std::cout << "You have selected: \"" << foundNode->data->name << " - " << foundNode->data->description 
        << "\". This will cost you $" << foundNode->data->price.dollars << '.' << std::setw(2) << std::setfill('0') << foundNode->data->price.cents 
        << std::setfill(' ') << std::endl;

        std::cout << "Please hand over the money - type in the value of each note/coin in cents." << std::endl;
        std::cout << "Please enter ctrl-D or enter a new line to cancel this purchase" << std::endl;

        // loops continuously until either payment is completed or user cancels
        while (!coinTracker.isPaymentComplete()) {
            std::cout << "You still need to give us $" << coinTracker.getAmountDue() / 100 << '.' << std::setw(2) << std::setfill('0') << coinTracker.getAmountDue() % 100 << ": ";
            int payment;
            std::cin >> payment;

                ////////////////////////
                ////// TO DO //////////
                ///////////////////////
                // Add validation for pressing enter that refunds to user

            // Check for EOF (Ctrl-D)
            if (std::cin.eof()) {
                std::cerr << "Purchase canceled.\n" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return;
            }

            // initialisation 
            Denomination denomination = Denomination::INVALID; 
            bool validDenomination = false;

            // check is payment is a valid denom
            for (const auto& denominationValue : Coin::denominationValues) {
                if (payment == denominationValue.second) {
                    validDenomination = true;
                    denomination = denominationValue.first;
                    break; // Exit the loop once a valid denomination is found
                }
            }
            // If denom is valid, add it as a payment
            if (validDenomination) {
                coinTracker.addPayment(denomination, 1);
                Coin::registerCoins[Coin::getDenominationValue(denomination)]++;
                std::cout << "Amount Paid: $" << coinTracker.getTotalPaid() / 100 << '.' << std::setw(2) << std::setfill('0') << coinTracker.getTotalPaid() % 100 << std::endl;
            // Error if denomination not in enumerator
            } else {
                std::cerr << "Error: Invalid denomination. Please enter a valid denomination." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        if (coinTracker.isPaymentComplete()) {
            // Validation for if change available
            if (coinTracker.canProvideChange()) {
                std::cout << "Payment complete. Enjoy your meal!" << std::endl;
                coinTracker.getChange();
                // Below line for TESTING
                // Coin::printRegister();
            // Error if change doesn't have change
            } else {
                std::cerr << "Error: Not enough change in the register. Purchase canceled.\n" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return;
            }
        }
    // Error if invalid ID input
    } else {
        std::cerr << "Error: Food item with ID " << foodID << " not found.\n" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}


void saveData(const std::string& food_file, const std::string& coin_file, LinkedList& food_list) {
    std::ofstream foodFile(food_file);
    // opens foodFile to input food items
    if (foodFile.is_open()) {
        Node* current = food_list.getHead();
        while (current != nullptr) {
            foodFile << current->data->id << "|" << current->data->name << "|" << current->data->description 
                     << "|" << current->data->price.dollars << '.' << std::setw(2) << std::setfill('0') << current->data->price.cents 
                     << std::endl;
            current = current->next;
        }
        foodFile.close();
    // Error if foodFile cant be opened
    } else {
        std::cerr << "Error: Could not open file " << food_file << " for writing." << std::endl;
    }

    // Saving updated info to coinFile
    std::ofstream coinFile(coin_file);
    if (coinFile.is_open()) {
        for (const auto& coin : Coin::registerCoins) {
            coinFile << coin.first << "," << coin.second << std::endl;
        }
        coinFile.close();
        
        // Clear register data
        Coin::registerCoins.clear();
    } else {
        std::cerr << "Error: Could not open file " << coin_file << " for writing." << std::endl;
    }

    // LinkedList deconstructor
    food_list.clear();
}


void addFood(LinkedList& food_list) {

    // ID generation
    std::string foodID = generateFoodID(food_list);

    std::cout << "FOOD ID:" << foodID << std::endl;

    std::cout << "The new meal item will have the Item ID of " << foodID << std::endl;
    std::cout << "-------------" << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Food name
    std::cout << "Enter the item name: ";
    std::string foodName;
    std::getline(std::cin, foodName);

    // Food desc
    std::cout << "Enter the item description: ";
    std::string foodDesc;
    std::getline(std::cin, foodDesc);

    int foodPriceCents = 0;
    bool validPrice = false;

    // loop to get a valid price in cents, minimum 100 cents
    while (!validPrice) {
        std::cout << "Enter the price for this item (in cents): ";
        if (!(std::cin >> foodPriceCents) || foodPriceCents < 100) {
            std::cerr << "Error: Invalid price. Please enter a valid price of at least 100 cents." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            validPrice = true;
        }
    }

    // Converts foodPrice to dollar amount
    double foodPrice;
    foodPrice = foodPriceCents / 100.0;

    // adds to the sorted list
    food_list.insertSorted(foodID, foodName, foodDesc, foodPrice);

    std::cout << "This item \"" << foodName << " - " << foodDesc << "\" has now been added to the food menu" << std::endl;
}



std::string generateFoodID(const LinkedList& food_list) {
    
    std::string highestID = "F0000";

    // iterates through list to find highest id in food_list
    Node* current = food_list.getHead();
    while (current != nullptr) {
        highestID = std::max(highestID, current->data->id);
        current = current->next;
    }

    // once highest ID found, increment by 1
    int idNum = std::stoi(highestID.substr(1)) + 1;
    std::string nextID = "F" + std::to_string(idNum);

    // Adds correct formatting to ID
    std::string formattedID = "F" + std::string(4 - std::to_string(idNum).length(), '0') + std::to_string(idNum);

    return formattedID;
}


void removeFood(LinkedList& food_list) {
    std::cout << "Enter the food ID of the food to remove from the menu: ";
    std::string foodID;
    std::cin >> foodID;

    // Retrieve the food item details before attempting to remove it
    std::string removedFoodName;
    std::string removedFoodDesc;

    // Find the food item in the linked list with the associated ID
    Node* current = food_list.getHead();
    Node* prev = nullptr;
    while (current != nullptr) {
        if (current->data->id == foodID) {
            // Found the food item, retrieve its details
            removedFoodName = current->data->name;
            removedFoodDesc = current->data->description;
            
            // Remove the food item from the list
            if (prev == nullptr) {
                // If the item to be removed is the head
                food_list.remove(foodID);
            } else {
                prev->next = current->next;
                delete current->data;
            }
            
            // Output statement for successful removal
            std::cout << "\'" << foodID << " - " << removedFoodName << " - " << removedFoodDesc << "\' has been removed from the system." << std::endl;
            
            return;
        }
        prev = current;
        current = current->next;
    }

    // If the food item with the specified ID was not found
    std::cerr << "Error: No food item found with ID " << foodID << std::endl;
}

void displayBalance() {
    std::cout << "\nBalance Summary" << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << "Denom | Quantity | Value" << std::endl;
    std::cout << "------------------------------" << std::endl;
    
    double totalValue = 0;

    // Iterate through the registerCoins map
    for (const auto& coin : Coin::registerCoins) {
        int denomination = coin.first;
        int quantity = coin.second;
        double value = denomination / 100 * quantity;
        totalValue += value;

        // formatting for coins table
        std::cout << std::setw(5) << std::left << denomination << " | " << std::setw(8) << std::left << quantity << " | $" << std::setw(8) << std::right << std::fixed << std::setprecision(2) << value << std::endl;
    }

    std::cout << "------------------------------" << std::endl;
    std::cout << "                   $ " << std::fixed << std::setprecision(2) << totalValue << std::endl;
    
}

// Function to free memory then close program without saving
void terminateProgram(LinkedList& food_list, const std::string& food_file, const std::string& coin_file) {
    // Free memory
    food_list.clear();

    std::cout << "Exiting program." << std::endl;
    exit(EXIT_SUCCESS);
}
