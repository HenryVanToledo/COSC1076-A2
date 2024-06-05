#include <iostream>
#include <iomanip>
#include "LinkedList.h"
#include "Node.h"

// Defined colours
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"


LinkedList::LinkedList() : head(nullptr), count(0) {}

LinkedList::~LinkedList() {
    // delete all nodes and clear the list
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current->data;
        delete current;
        current = next;
    }
}

void LinkedList::insertSorted(const std::string& foodID, const std::string& foodName, const std::string& foodDesc, double price) {
    // Create a new node
    Node* newNode = new Node();

    // Create a new FoodItem
    newNode->data = new FoodItem();

    // Set the ID
    newNode->data->id = foodID;

    //set the name
    newNode->data->name = foodName;

    // set the food desc
    newNode->data->description = foodDesc;

    // set the price
    newNode->data->price.dollars = static_cast<unsigned>(price);
    newNode->data->price.cents = static_cast<unsigned>((price - newNode->data->price.dollars) * 100);

    // assign next to nullptr
    newNode->next = nullptr;

    // Validate if list is empty or is the head
    if (head == nullptr || head->data->name > foodName) {
        newNode->next = head;
        head = newNode;
    // new node isnt the head
    } else {
        Node* current = head;
        // iterates through the list to find the correct position
        while (current->next != nullptr && current->next->data->name < foodName) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    // incremetor
    count++;
}

void LinkedList::display() const {
    Node* current = head;

    //display menu
    std::cout << "Food Menu" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << BLUE <<"ID"<<RESET<<"   |"<<YELLOW<<"Name"<<RESET<<"                           |"<<GREEN<<"Price" << RESET<< std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    
    // iterates through list to display menu data
    while (current != nullptr) {
        std::cout << std::left << std::setw(5) << BLUE << current->data->id << RESET << "|" << YELLOW
                  << std::left << std::setw(30) << std::setfill(' ') << current->data->name << RESET << " |" << GREEN <<"$"
                  << current->data->price.dollars << '.'
                  << std::setw(2) << std::setfill('0') << current->data->price.cents
                  << std::setfill(' ') << RESET << std::endl;
        current = current->next;
    }

    std::cout << std::endl;
}

void LinkedList::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current->data;
        current = next;
    }
    head = nullptr;
    count = 0;
}


bool LinkedList::remove(const std::string& id) {
    // Check to see list isnt empty
    if (head == nullptr) {
        return false;
    }

    // Removes the head if it matches the id
    if (head->data->id == id) {
        Node* temp = head;
        head = head->next;
        delete temp->data;
        count--;
        return true;
    }

    // If the node to remove is not the head
    Node* current = head;

    // Traverse from the tail to the head
    while (current->next != nullptr && current->next->next != nullptr) {
        if (current->next->next->data->id == id) {
            Node* temp = current->next->next;
            current->next->next = current->next->next->next;
            delete temp->data;
            count--;
            return true;
        }
        current = current->next;
    }

    return false;
}
