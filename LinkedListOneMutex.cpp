//
// Created by tharsanan on 3/30/19.
//
#include <cstdlib>
#include <pthread.h>
#include <iostream>
#include <thread>
#include "LinkedListOneMutex.h"

LinkedListOneMutex::LinkedListOneMutex(){
    lock = PTHREAD_MUTEX_INITIALIZER;
    lockForReduceTimes = PTHREAD_MUTEX_INITIALIZER;
}

void LinkedListOneMutex::setLinkedList(LinkedListSerial linkedListSerial1){
    linkedListSerial = linkedListSerial1;
}

int LinkedListOneMutex::Member(int value){
    pthread_mutex_lock(&lock);
    linkedListSerial.Member(value);
    pthread_mutex_unlock(&lock);
}
int LinkedListOneMutex::Insert(int value){
    pthread_mutex_lock(&lock);
    linkedListSerial.Insert(value);
    pthread_mutex_unlock(&lock);
}
int LinkedListOneMutex::Delete(int value){
    pthread_mutex_lock(&lock);
    linkedListSerial.Delete(value);
    pthread_mutex_unlock(&lock);
}

void* LinkedListOneMutex::threadFunc(void *list){
    LinkedListOneMutex* linkedListOneMutex = (LinkedListOneMutex* )list;
    while (true) {
        int toInsert = 0 + (rand() % (65535 - 0 + 1));

        if (linkedListOneMutex->opTimesMemInsDel > 0 && !linkedListOneMutex->Member(toInsert)) {
            linkedListOneMutex->Insert(toInsert);
            linkedListOneMutex->Delete(toInsert);
            pthread_mutex_lock(&linkedListOneMutex->lockForReduceTimes);
            linkedListOneMutex->opTimesMemInsDel = linkedListOneMutex->opTimesMemInsDel - 1;
        }
        linkedListOneMutex->opTimesMemOnly = linkedListOneMutex->opTimesMemOnly - 1;
        pthread_mutex_unlock(&linkedListOneMutex->lockForReduceTimes);
        if(linkedListOneMutex->opTimesMemInsDel <= 0  && linkedListOneMutex->opTimesMemOnly <= 0){
            break;
        }
    }
    pthread_exit(NULL);
}

void LinkedListOneMutex::createThreads(){
    srand(14);
    auto start =  std::chrono::high_resolution_clock::now();
    int i = 0;
    int err;
    while(i < 4)
    {
        err = pthread_create(&(tid[i]), NULL, &LinkedListOneMutex::threadFunc, this);
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

void LinkedListOneMutex::printAll() {
    linkedListSerial.printAll();
}

void LinkedListOneMutex::setTimesNFrac(int times, int mem, int ins, int del){
    memberFrac = mem;
    insertFrac = ins;
    deleteFrac = del;
    opTimes = times;
    opTimesMemInsDel = ((opTimes * insertFrac)/(insertFrac + insertFrac + memberFrac));
    opTimesMemOnly = opTimes - opTimesMemInsDel - opTimesMemInsDel;
}