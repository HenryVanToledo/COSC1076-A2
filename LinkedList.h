#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"


class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    void insertSorted(const std::string& foodID, const std::string& foodName, const std::string& foodDesc, double price);
    void display() const;

    Node* getHead() const { return head; }

    //Clear function
    void clear();

    bool remove(const std::string& id);

private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H
