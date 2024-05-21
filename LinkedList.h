#ifndef LINKEDLIST_H
#define LINKEDLIST_H
<<<<<<< HEAD
#include "Node.h"


class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    // more functions to be added perhaps...

private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


=======

#include <iostream>
#include <string>
using namespace std;

struct Node {
    string id;
    string name;
    string desc;
    double price;
    Node* next;

    Node(const string& id, const string& name, const string& desc, double price)
        : id(id), name(name), desc(desc), price(price), next(nullptr) {}
};

class LinkedList {
public:
    LinkedList();
    ~LinkedList();
    void display() const;
    void insertSorted(const string& id, const string& name, const string& desc, double price);
    Node* find(const string& id) const;
    void remove(const string& id);
    int getNextID() const;
    Node* getHead() const;

private:
    Node* head;
};

#endif // LINKEDLIST_H
>>>>>>> 7ffdc51f9656bfc6d7134e12694da43c49a7152b
