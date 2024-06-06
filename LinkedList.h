#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    // Functions for LinkedList
    void insertSorted(const std::string& foodID, const std::string& foodName, const std::string& foodDesc, double price);
    void display() const;
    void displayReverse() const;
    void clear();
    bool remove(const std::string& id);

    //Function to get head and tail
    Node* getHead() const { return head; }
    Node* getTail() const { return tail; }

private:
    // Head
    Node* head;
    // Tail
    Node* tail;
    unsigned count;
};

#endif // LINKEDLIST_H
