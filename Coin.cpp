#include "Coin.h"
<<<<<<< HEAD
 
 // implement functions for managing coins; this may depend on your design.
=======

Coin::Coin() : denomination(0), quantity(0) {}

Coin::Coin(int denomination, int quantity) : denomination(denomination), quantity(quantity) {}

int Coin::getDenomination() const {
    return denomination;
}

int Coin::getQuantity() const {
    return quantity;
}

void Coin::increaseQuantity() {
    ++quantity;
}

void Coin::decreaseQuantity() {
    if (quantity > 0) {
        --quantity;
    }
}
>>>>>>> 7ffdc51f9656bfc6d7134e12694da43c49a7152b
