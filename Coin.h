#ifndef COIN_H
#define COIN_H

#include <map>
#include <string>

// Coin.h defines the coin structure for managing currency in the system. 
#define DELIM ","  // delimiter 

// enumeration representing the various types of currency available in the system. 
enum Denomination
{
    INVALID = 0, FIVE_CENTS = 5, TEN_CENTS = 10, TWENTY_CENTS = 20, FIFTY_CENTS = 50,
    ONE_DOLLAR = 100, TWO_DOLLARS = 200, FIVE_DOLLARS = 500, TEN_DOLLARS = 1000,
    TWENTY_DOLLARS = 2000, FIFTY_DOLLARS = 5000, HUNDRED_DOLLARS = 10000
};

// represents a coin type stored in the cash register perhaps. Each denomination
// will have exactly one of these in the cash register.
class Coin
{
public:
    // the denomination type
    Denomination denom;
    
    // the count of how many of these are in the cash register
    unsigned count;

    static std::map<int, unsigned> registerCoins;
    static const std::map<Denomination, int> denominationValues;

    // Constructor
    Coin();
    Coin(Denomination denom, unsigned count);

    static int getDenominationValue(Denomination denom);
    // static void printRegister();
    static void displayBalance();
};

//////////////////////////
///////////// COIN TRACKER
//////////////////////////

class CoinTracker
{
public:
    CoinTracker(int productPriceInCents);
    void addPayment(Denomination denom, unsigned count);
    int getTotalPaid() const;
    bool isPaymentComplete() const;
    int getAmountDue() const;
    bool canProvideChange() const;
    void getChange() const;

private:
    int productPriceInCents;
    int totalPaid;
};

#endif
