#include "LinkedList.h"
<<<<<<< HEAD

LinkedList::LinkedList() {
   head = nullptr;

   // TODO
}

LinkedList::~LinkedList() {
    // TODO
}
=======
#include <iomanip>

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void LinkedList::display() const {
    Node* current = head;
    cout << "Food Menu" << endl;
    cout << "---------" << endl;
    cout << "ID |Name |Length" << endl;
    cout << "------------------------------------------------------------------" << endl;
    while (current != nullptr) {
        cout << current->id << "|" << current->name << "|$ " << fixed << setprecision(2) << current->price << endl;
        current = current->next;
    }
}

void LinkedList::insertSorted(const string& id, const string& name, const string& desc, double price) {
    Node* newNode = new Node(id, name, desc, price);
    if (head == nullptr || head->name > name) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr && current->next->name < name) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

Node* LinkedList::find(const string& id) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void LinkedList::remove(const string& id) {
    if (head == nullptr) {
        return;
    }
    if (head->id == id) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }
    Node* current = head;
    while (current->next != nullptr && current->next->id != id) {
        current = current->next;
    }
    if (current->next != nullptr) {
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

int LinkedList::getNextID() const {
    Node* current = head;
    int maxID = 0;
    while (current != nullptr) {
        int currentID = stoi(current->id.substr(1));
        if (currentID > maxID) {
            maxID = currentID;
        }
        current = current->next;
    }
    return maxID + 1;
}

Node* LinkedList::getHead() const {
    return head;
}
>>>>>>> 7ffdc51f9656bfc6d7134e12694da43c49a7152b
