#include "Node.h"

// Constructor
Node::Node() : data(nullptr), next(nullptr) {}

// Deconstructor
Node::~Node() {
    delete data;
}
