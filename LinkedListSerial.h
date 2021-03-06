//
// Created by tharsanan on 3/30/19.
//

#ifndef PARALLELLINKEDLIST_LINKEDLIST_H
#define PARALLELLINKEDLIST_LINKEDLIST_H


#include "Node.h"

class LinkedListSerial {
private:
    Node* head;
public:
    bool Member(int value);
    bool Insert(int value);
    bool Delete(int value);
    void printAll();
    LinkedListSerial();
    void executeOperations(int times, int mem, int ins, int del);
    int count;
};


#endif //PARALLELLINKEDLIST_LINKEDLIST_H
