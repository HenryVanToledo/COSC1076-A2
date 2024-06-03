#include "Coin.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>

// ANSI color codes for terminal text
const std::string RESET = "\033[0m";
const std::string GREEN = "\033[32m";

std::map<int, int> Coin::registerCoins;

std::map<Denomination, int> Coin::denominationValues = {
    {Denomination::FIVE_CENTS, 5},
    {Denomination::TEN_CENTS, 10},
    {Denomination::TWENTY_CENTS, 20},
    {Denomination::FIFTY_CENTS, 50},
    {Denomination::ONE_DOLLAR, 100},
    {Denomination::TWO_DOLLARS, 200},
    {Denomination::FIVE_DOLLARS, 500},
    {Denomination::TEN_DOLLARS, 1000},
    {Denomination::TWENTY_DOLLARS, 2000},
    {Denomination::FIFTY_DOLLARS, 5000}
};


std::map<Denomination, int> Coin::getChange(int totalPriceInCents, int amountPaidInCents) {
    std::map<Denomination, int> change;
    int changeAmount = amountPaidInCents - totalPriceInCents;

    // Calculate change for each denomination
    for (auto denom = registerCoins.rbegin(); denom != registerCoins.rend(); ++denom) {
        int denomValue = denom->first;
        int count = changeAmount / denomValue;
        if (count > 0 && registerCoins[denomValue] >= count) {
            change[static_cast<Denomination>(denomValue)] = count;
            changeAmount -= count * denomValue;
        }
    }

    if (changeAmount > 0) {
        // Not enough change available
        change.clear();
    }

    return change;
}

int Coin::getDenominationValue(Denomination denom) {
    return static_cast<int>(denom);
}

// New function to format and display change amount
std::string Coin::formatChange(const std::map<Denomination, int>& change) {
    int totalChangeInCents = 0;
    std::stringstream changeStream;
    changeStream << "Your change is: ";

    // Calculate total change in cents
    for (auto it = change.begin(); it != change.end(); ++it) {
        totalChangeInCents += Coin::getDenominationValue(it->first) * it->second;
    }

    // Convert total change to dollars and cents
    int dollars = totalChangeInCents / 100;
    int cents = totalChangeInCents % 100;

    // Format the total change amount with colored dollar sign
    changeStream << GREEN << "$" << dollars << '.' << std::setw(2) << std::setfill('0') << cents << RESET;

    changeStream << " "; //empty space when listing denominations , so it looks better
    // Add individual denominations
  bool first = true;
    for (const auto& changePair : change) {
        Denomination denomination = changePair.first;
        int count = changePair.second;

        if (!first) {
            changeStream << ", ";
        }

        changeStream << count << " x ";
        int denomValue = Coin::getDenominationValue(denomination);
        if (denomValue >= 100) {
            changeStream << "$" << denomValue / 100;
        } else {
            changeStream << denomValue << "c";
        }

        first = false;
    }
    return changeStream.str();
}
