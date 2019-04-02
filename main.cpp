#include <iostream>
#include <cstring>
#include "LinkedListSerial.h"
#include "LinkedListOneMutex.h"
#include "LinkedListReadWriteLock.h"

void createLinkedList(int number,int seed, LinkedListSerial* linkedListSerial){
    int count = 0;
    srand(time(NULL));
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
    linkedListSerial2->executeOperations(10000,900,50,50);

    LinkedListOneMutex* linkedListOneMutex = new LinkedListOneMutex();
    linkedListOneMutex->setLinkedList(*linkedListSerial);
    linkedListOneMutex->setTimesNFrac(10000,900,50,50);
    linkedListOneMutex->createThreads();

    LinkedListReadWriteLock* linkedListReadWriteLock = new LinkedListReadWriteLock();
    linkedListReadWriteLock->setLinkedList(*linkedListSerial1);
    linkedListReadWriteLock->setTimesNFrac(10000,900,50,50);
    linkedListReadWriteLock->createThreads();

    std::cout << linkedListSerial2->count << " " << linkedListOneMutex->linkedListSerial.count << " " << linkedListReadWriteLock->linkedListSerial.count;
//    linkedListOneMutex->printAll();

    pthread_exit(NULL);

}

