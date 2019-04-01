//
// Created by tharsanan on 3/30/19.
//

#include "LinkedListReadWriteLock.h"

#include <cstdlib>
#include <pthread.h>
#include <iostream>
#include <thread>

LinkedListReadWriteLock::LinkedListReadWriteLock(){
    lockRead = PTHREAD_MUTEX_INITIALIZER;
    lockWrite = PTHREAD_MUTEX_INITIALIZER;
    lockForReduceTimes = PTHREAD_MUTEX_INITIALIZER;
}

void LinkedListReadWriteLock::setLinkedList(LinkedListSerial linkedListSerial1){
    linkedListSerial = linkedListSerial1;
}

int LinkedListReadWriteLock::Member(int value){
    pthread_mutex_lock(&lockRead);
    linkedListSerial.Member(value);
    pthread_mutex_unlock(&lockRead);
}
int LinkedListReadWriteLock::Insert(int value){
    pthread_mutex_lock(&lockRead);
    pthread_mutex_lock(&lockWrite);
    linkedListSerial.Insert(value);
    pthread_mutex_unlock(&lockWrite);
    pthread_mutex_unlock(&lockRead);
}
int LinkedListReadWriteLock::Delete(int value){
    pthread_mutex_lock(&lockRead);
    pthread_mutex_lock(&lockWrite);
    linkedListSerial.Delete(value);
    pthread_mutex_unlock(&lockWrite);
    pthread_mutex_unlock(&lockRead);
}

void* LinkedListReadWriteLock::threadFunc(void *list){
    LinkedListReadWriteLock* linkedListReadWriteLock = (LinkedListReadWriteLock* )list;
    while (true) {
        int toInsert = 0 + (rand() % (65535 - 0 + 1));

        if (linkedListReadWriteLock->opTimesMemInsDel > 0 && !linkedListReadWriteLock->Member(toInsert)) {
            linkedListReadWriteLock->Insert(toInsert);
            linkedListReadWriteLock->Delete(toInsert);
            pthread_mutex_lock(&linkedListReadWriteLock->lockForReduceTimes);
            linkedListReadWriteLock->opTimesMemInsDel = linkedListReadWriteLock->opTimesMemInsDel - 1;
        }
        linkedListReadWriteLock->opTimesMemOnly = linkedListReadWriteLock->opTimesMemOnly - 1;
        pthread_mutex_unlock(&linkedListReadWriteLock->lockForReduceTimes);
        if(linkedListReadWriteLock->opTimesMemInsDel <= 0  && linkedListReadWriteLock->opTimesMemOnly <= 0){
            break;
        }
    }
    pthread_exit(NULL);
}

void LinkedListReadWriteLock::createThreads(){
    srand(14);
    auto start =  std::chrono::high_resolution_clock::now();
    int i = 0;
    int err;
    while(i < 4)
    {
        err = pthread_create(&(tid[i]), NULL, &LinkedListReadWriteLock::threadFunc, this);
        if (err != 0)
            printf("\nThread can't be created :[%s]", strerror(err));
        i++;
    }
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    pthread_join(tid[3], NULL);
    auto stop =  std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << duration.count() << "\n";
}

void LinkedListReadWriteLock::printAll() {
    linkedListSerial.printAll();
}

void LinkedListReadWriteLock::setTimesNFrac(int times, int mem, int ins, int del){
    memberFrac = mem;
    insertFrac = ins;
    deleteFrac = del;
    opTimes = times;
    opTimesMemInsDel = ((opTimes * insertFrac)/(insertFrac + insertFrac + memberFrac));
    opTimesMemOnly = opTimes - opTimesMemInsDel - opTimesMemInsDel;
}