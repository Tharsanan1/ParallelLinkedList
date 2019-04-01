#include <iostream>
#include <cstring>
#include "LinkedListSerial.h"
#include "LinkedListOneMutex.h"
#include "LinkedListReadWriteLock.h"

void createLinkedList(int number,int seed, LinkedListSerial* linkedListSerial){
    int count = 0;
    srand(seed);
    while(count < number){
        int output = 0+ (rand() % (65535 - 0 + 1));
        count += linkedListSerial->Insert(output);
    }
}

int main() {

    LinkedListSerial* linkedListSerial = new LinkedListSerial();
    createLinkedList(1000,3,linkedListSerial);

    LinkedListSerial* linkedListSerial1 = new LinkedListSerial();
    createLinkedList(1000,15,linkedListSerial1);

    LinkedListSerial* linkedListSerial2 = new LinkedListSerial();
    createLinkedList(1000,15,linkedListSerial2);

    LinkedListReadWriteLock* linkedListReadWriteLock = new LinkedListReadWriteLock();
    linkedListReadWriteLock->setLinkedList(*linkedListSerial2);
    linkedListReadWriteLock->setTimesNFrac(10000000,500,250,250);
    linkedListReadWriteLock->createThreads();

    LinkedListOneMutex* linkedListOneMutex = new LinkedListOneMutex();
    linkedListOneMutex->setLinkedList(*linkedListSerial1);
    linkedListOneMutex->setTimesNFrac(10000000,500,250,250);
    linkedListOneMutex->createThreads();
//    linkedListOneMutex->printAll();

    pthread_exit(NULL);

}

