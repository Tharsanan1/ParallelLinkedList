//
// Created by tharsanan on 3/30/19.
//

//#include <stdatomic.h>
#include <iostream>
#include <chrono>
#include "LinkedListSerial.h"

LinkedListSerial::LinkedListSerial(){
    head = nullptr;
    count = 0;
}



bool LinkedListSerial::Member(int value){
    count++;
    Node* current = head;
    while(current != nullptr && current->getValue() < value){
        current = current->getNextNode();
    }
    return !(current == nullptr || current->getValue() < value);
}
bool LinkedListSerial::Insert(int value){
    Node* current = head;
    Node* pred = nullptr;

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

void LinkedListSerial::executeOperations(int times, int mem, int ins, int del){
    int memberFrac = mem;
    int insertFrac = ins;
    int deleteFrac = del;
    int opTimes = times;
    int opTimesMemInsDel = ((opTimes * insertFrac)/(insertFrac + insertFrac + memberFrac));
    int opTimesMemOnly = opTimes - opTimesMemInsDel - opTimesMemInsDel;
    auto start =  std::chrono::high_resolution_clock::now();
    while (true) {
        int toInsert = 0 + (rand() % (65535 - 0 + 1));

        if (opTimesMemInsDel > 0 /**&& !Member(toInsert)**/) {
            Insert(toInsert);
            Delete(toInsert);
            opTimesMemInsDel = opTimesMemInsDel - 1;
        }

        opTimesMemOnly = opTimesMemOnly - 1;
        Member(toInsert);
        if(opTimesMemInsDel <= 0  && opTimesMemOnly <= 0){
            break;
        }
    }
    auto stop =  std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << duration.count() << "\n " ;
}