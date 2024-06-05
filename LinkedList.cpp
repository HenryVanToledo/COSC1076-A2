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
        delete current;
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
    } else if (head->data->name > foodName) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        newNode->prev = nullptr;
    } else {
        Node* current = head;
        while (current->next != nullptr && current->next->data->name < foodName) {
            current = current->next;
        }
        newNode->next = current->next;
        if (current->next != nullptr)
            current->next->prev = newNode;
        current->next = newNode;
        newNode->prev = current;
    }
    count++;
}

void LinkedList::display() const {
    Node* current = head;

    std::cout << "Food Menu" << std::endl;
    std::cout << "---------" << std::endl;
    std::cout << "ID     | Name                           | Price" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    while (current != nullptr) {
        std::cout << std::left << std::setw(5) << current->data->id << " | "
                  << std::left << std::setw(30) << std::setfill(' ') << current->data->name << " | $"
                  << current->data->price.dollars << '.' << std::setw(2) << std::setfill('0') << current->data->price.cents
                  << std::setfill(' ') << std::endl;
        current = current->next;
    }

    std::cout << std::endl;
}

void LinkedList::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current->data;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
}

bool LinkedList::remove(const std::string& id) {
    if (head == nullptr) {
        return false;
    }

    if (head->data->id == id) {
        Node* temp = head;
        head = head->next;
        if (head != nullptr)
            head->prev = nullptr;
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
            if (current->next != nullptr)
                current->next->prev = current;
            delete temp->data;
            delete temp;
            count--;
            return true;
        }
        current = current->next;
    }

    return false;
}
