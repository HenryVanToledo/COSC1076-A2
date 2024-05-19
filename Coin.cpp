#include "Coin.h"

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