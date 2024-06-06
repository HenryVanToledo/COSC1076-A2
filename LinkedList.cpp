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

LinkedList::LinkedList() : head(nullptr), tail(nullptr), count(0) {}

LinkedList::~LinkedList() {
    // Delete all nodes and clear the list
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current->data;
        current = next;
    }
}

void LinkedList::insertSorted(const std::string& foodID, const std::string& foodName, const std::string& foodDesc, double price) {
    // Create a new node
    Node* newNode = new Node();
    newNode->data = new FoodItem();
    newNode->data->id = foodID;
    newNode->data->name = foodName;
    newNode->data->description = foodDesc;
    newNode->data->price.dollars = static_cast<unsigned>(price);
    newNode->data->price.cents = static_cast<unsigned>((price - newNode->data->price.dollars) * 100);

    newNode->next = nullptr;

    // Check if list is empty
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        newNode->prev = nullptr;
    // Check if new node should be the new head
    } else if (head->data->name > foodName) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        newNode->prev = nullptr;
    // else the new node should be inserted in the middle or at the end
    } else {
        Node* current = head;
        while (current->next != nullptr && current->next->data->name < foodName) {
            current = current->next;
        }
        newNode->next = current->next;
        if (current->next != nullptr) {
            current->next->prev = newNode;
        } else {
            tail = newNode;
        }
        current->next = newNode;
        newNode->prev = current;
    }
    count++;
}

void LinkedList::display() const {
    Node* current = head;

    // Display header
    std::cout << "Food Menu" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << BLUE << "ID     "<<RESET<<"| "<<YELLOW<<"Name                           "<<RESET<<"| "<<GREEN<<"Price" << RESET << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    // Display items in each node
    while (current != nullptr) {
        std::cout << BLUE << std::left << std::setw(5) << current->data->id << RESET <<" | "
                  << YELLOW << std::left << std::setw(30) << std::setfill(' ') << current->data->name << RESET << " | " << GREEN << "$"
                  << current->data->price.dollars << '.' << std::setw(2) << std::setfill('0') << current->data->price.cents
                  << RESET << std::setfill(' ') << std::endl;
        current = current->next;
    }

    std::cout << std::endl;
}

void LinkedList::displayReverse() const {
    Node* current = tail;

    std::cout << "Food Menu (Reversed)" << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << BLUE << "ID    " << RESET << "| " << YELLOW << "Name                           " << RESET << "| " << GREEN << "Price" << RESET << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    while (current != nullptr) {
        std::cout << BLUE << std::left << std::setw(5) << current->data->id << RESET << " | "
                  << YELLOW << std::left << std::setw(30) << std::setfill(' ') << current->data->name << RESET << " | " << GREEN << "$"
                  << current->data->price.dollars << '.' << std::setw(2) << std::setfill('0') << current->data->price.cents
                  << RESET << std::setfill(' ') << std::endl;
        current = current->prev;
    }

    std::cout << std::endl;
}

// Clear the list
void LinkedList::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current->data;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
}

// Remove a specific item from the list given an id
bool LinkedList::remove(const std::string& id) {
    // Check if list is empty
    if (head == nullptr) {
        return false;
    }
    // Check if the head is the item to remove
    if (head->data->id == id) {
        Node* temp = head;
        head = head->next;
        if (head != nullptr)
            head->prev = nullptr;
        else
            tail = nullptr;
        delete temp->data;
        count--;
        return true;
    }
    // Check if the item to remove is in the middle or at the end
    Node* current = head;
    while (current->next != nullptr) {
        if (current->next->data->id == id) {
            Node* temp = current->next;
            current->next = current->next->next;
            if (current->next != nullptr)
                current->next->prev = current;
            else
                tail = current;
            delete temp->data;
            count--;
            return true;
        }
        current = current->next;
    }

    return false;
}
