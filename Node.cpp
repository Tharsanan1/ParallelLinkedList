//
// Created by tharsanan on 3/30/19.
//

#include "Node.h"

Node::Node(){
    next = nullptr;
}

void Node::setValue(int i) {
    value = i;
}

void Node::setNext(Node *pNode) {
    next = pNode;
}

int Node::getValue(){
    return value;
}
Node* Node::getNextNode(){
    return next;
}