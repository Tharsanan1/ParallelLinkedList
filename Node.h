//
// Created by tharsanan on 3/30/19.
//

#ifndef PARALLELLINKEDLIST_NODE_H
#define PARALLELLINKEDLIST_NODE_H
#include "Node.h"


class Node {
private:
    Node* next;
    int value;
public:
    int getValue();
    Node* getNextNode();

    void setValue(int i);

    void setNext(Node *pNode);
    Node();
};


#endif //PARALLELLINKEDLIST_NODE_H
