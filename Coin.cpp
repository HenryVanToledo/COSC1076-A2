#include "Coin.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>

// maps through denom to correspond to value
const std::map<Denomination, int> Coin::denominationValues = {
    {FIVE_CENTS, 5}, {TEN_CENTS, 10}, {TWENTY_CENTS, 20}, {FIFTY_CENTS, 50},
    {ONE_DOLLAR, 100}, {TWO_DOLLARS, 200}, {FIVE_DOLLARS, 500}, {TEN_DOLLARS, 1000},
    {TWENTY_DOLLARS, 2000}, {FIFTY_DOLLARS, 5000}, {HUNDRED_DOLLARS, 10000}
};
// map to store the coins
std::map<int, unsigned> Coin::registerCoins;

// Constructors
Coin::Coin() : denom(FIVE_CENTS), count(0) {}
Coin::Coin(Denomination denom, unsigned count) : denom(denom), count(count) {}

// gets value of denom
int Coin::getDenominationValue(Denomination denom) {
    return denominationValues.at(denom);
}

///////////////////////////////
//////////////////TESTING CODE
///////////////////////////////

// Prints all values in register for testing purposes
// void Coin::printRegister() {
//     std::cout << "Register Contents:" << std::endl;
//     for (const auto& coin : registerCoins) {
//         double denominationValue = coin.first / 100.0;
//         std::cout << "Denomination: $" << std::fixed << std::setprecision(2) << denominationValue << " Quantity: " << coin.second << std::endl;
//     }
//     std::cout << std::endl;
// }

void Coin::displayBalance() {
    // Print header
    std::cout << "Balance Summary" << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << "Denom | Quantity | Value" << std::endl;
    std::cout << "---------------------------" << std::endl;

    double totalValue = 0;

    // Iterate through denominations and quantities
    for (const auto& coin : Coin::registerCoins) {
        Denomination denomination = static_cast<Denomination>(coin.first); // Convert int to Denomination enum
        int quantity = coin.second;
        double value = Coin::getDenominationValue(denomination) * quantity / 100.0; // Calculate total value of each denomination
        totalValue += value;

        // Display denomination, quantity, and value with correct formatting
        std::cout << std::setw(5) << std::left << Coin::getDenominationValue(denomination) << " | " << std::setw(8) << std::left << quantity << " | $" << std::setw(8) << std::right << std::fixed << std::setprecision(2) << value << std::endl;
    }

    // Print footer
    std::cout << "---------------------------" << std::endl;
    std::cout << "$ " << std::setprecision(2) << std::fixed << totalValue << std::endl;
}



//////////////////////
///////// COIN TRACKER
//////////////////////

// Constructor
CoinTracker::CoinTracker(int productPriceInCents) : productPriceInCents(productPriceInCents), totalPaid(0) {}

// Adds payment to total paid
void CoinTracker::addPayment(Denomination denom, unsigned count) {
    totalPaid += Coin::getDenominationValue(denom) * count;
}

// Returns total paid
int CoinTracker::getTotalPaid() const {
    return totalPaid;
}

//checks if the payment is complete
bool CoinTracker::isPaymentComplete() const {
    return totalPaid >= productPriceInCents;
}

// Finds the amount owing
int CoinTracker::getAmountDue() const {
    return productPriceInCents - totalPaid;
}

// Checks whether there is change and if it can be given
bool CoinTracker::canProvideChange() const {
    // checks it total paid is less then the price of the product
    if (totalPaid <= productPriceInCents) {
        return true;
    }

    // Checks change in register
    int changeDue = totalPaid - productPriceInCents;
    std::map<int, unsigned> registerCopy = Coin::registerCoins;

    // sorts through denoms
    std::vector<std::pair<Denomination, int>> denominations(Coin::denominationValues.begin(), Coin::denominationValues.end());
    std::sort(denominations.begin(), denominations.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
    });

    // checks if change can be given
    for (const auto &denomPair : denominations) {
        int value = denomPair.second;
        while (changeDue >= value && registerCopy[value] > 0) {
            changeDue -= value;
            registerCopy[value]--;
        }
    }

    return changeDue == 0;
}

// getChange function to return the change
void CoinTracker::getChange() const {

    // checks if total paid is less then the price of the product
    if (totalPaid <= productPriceInCents) {
        std::cout << "No change due." << std::endl;
        return;
    }

    // checks change in register
    int changeDue = totalPaid - productPriceInCents;
    std::vector<std::pair<Denomination, int>> denominations(Coin::denominationValues.begin(), Coin::denominationValues.end());
    std::sort(denominations.begin(), denominations.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
    });

    std::ostringstream changeStream;
    bool first = true;

    // sorts through denoms
    for (const auto &denomPair : denominations) {
        int value = denomPair.second;
        int count = 0;
        // loops through all change
        while (changeDue >= value && Coin::registerCoins[value] > 0) {
            changeDue -= value;
            Coin::registerCoins[value]--;
            count++;
        }

        // checks if change avaialbe
        if (count > 0) {
            if (!first) {
                changeStream << ", ";
            }
            first = false;

            if (value >= 100) {
                changeStream << count << " x $" << value / 100;
            } else {
                changeStream << count << " x " << value << "c";
            }
        }
    }

    // checks if not enough change
    if (changeDue > 0) {
        std::cerr << "Error: Not enough change in the register." << std::endl;
    // Print statement for change
    } else {
        std::cout << "Your change is: " << changeStream.str() << "\n" << std::endl;
    }
}
