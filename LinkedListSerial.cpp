//
// Created by tharsanan on 3/30/19.
//

//#include <stdatomic.h>
#include <iostream>
#include "LinkedListSerial.h"

LinkedListSerial::LinkedListSerial(){
    head = nullptr;
}

bool LinkedListSerial::Member(int value){
    Node* current = head;
    while(current != nullptr && current->getValue() < value){
        current = current->getNextNode();
    }
    return !(current == nullptr || current->getValue() < value);
}
bool LinkedListSerial::Insert(int value){
    Node* current = head;
    Node* pred = nullptr;
    Node* temp;

    while(current != nullptr && current->getValue() < value){
        pred = current;
        current = current->getNextNode();
    }
    if(current == nullptr || current->getValue() > value){
        Node* newNode = new Node();
        newNode->setValue(value);
        newNode->setNext(current);
        if(pred == nullptr){
            head = newNode;
        }
        else{
            pred->setNext(newNode);
        }
        return true;
    }
    else{
        return false;
    }
}
bool LinkedListSerial::Delete(int value){
    Node* current = head;
    Node* pred = nullptr;
    while(current != nullptr && current->getValue() < value){
        pred = current;
        current = current->getNextNode();
    }
    if(current != nullptr && current->getValue() == value){
        if(pred == nullptr){
            head = current->getNextNode();
            delete (current);
        }
        else{
            pred->setNext(current->getNextNode());
            delete (current);
        }
        return true;
    }
    else{
        return false;
    }
}

void LinkedListSerial::printAll(){
    Node* current = head;
    while (current != nullptr){
        std::cout << current->getValue() << " : value \n";
        current = current->getNextNode();
    }
}