#include <iostream>
#include <iomanip>
#include "LinkedList.h"
#include "Node.h"

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
    std::cout << "ID   |Name                           |Price" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
        // iterates through list to display menu data
    while (current != nullptr) {
        std::cout << current->data->id << "|" 
                  << std::setw(30) << std::left << current->data->name.substr(0, 29) << "|" // Adjusted to show only 29 characters of the name
                  << "$" << std::setw(2) << current->data->price.dollars << "." 
                  << std::setw(2) << std::setfill('0') << current->data->price.cents 
                  << std::setfill(' ') << std::endl;
        current = current->next;
    }
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
    if (head == nullptr) {
        return false;
    }

    if (head->data->id == id) {
        Node* temp = head;
        head = head->next;
        delete temp->data;
        delete temp;
        count--;
        return true;
    }

    Node* current = head;
    while (current->next != nullptr) {
        if (current->next->data->id == id) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp->data;
            return true;
        }
        current = current->next;
    }

    return false;
}






