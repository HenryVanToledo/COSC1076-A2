#ifndef COIN_H
#define COIN_H

#include <map>
#include <string>

enum class Denomination {
    FIVE_CENTS = 5,
    TEN_CENTS = 10,
    TWENTY_CENTS = 20,
    FIFTY_CENTS = 50,
    ONE_DOLLAR = 100,
    TWO_DOLLARS = 200,
    FIVE_DOLLARS = 500,
    TEN_DOLLARS = 1000,
    TWENTY_DOLLARS = 2000,
    FIFTY_DOLLARS = 5000,
    INVALID = 0
};

class Coin {
public:
    static std::map<int, int> registerCoins;
    static std::map<Denomination, int> denominationValues;

    static std::map<Denomination, int> getChange(int totalPriceInCents, int amountPaidInCents);
    static int getDenominationValue(Denomination denom);
    static std::string formatChange(const std::map<Denomination, int>& change);
};

#endif // COIN_H
