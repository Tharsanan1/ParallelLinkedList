//
// Created by tharsanan on 3/30/19.
//

#ifndef PARALLELLINKEDLIST_LINKEDLISTONEMUTEX_H
#define PARALLELLINKEDLIST_LINKEDLISTONEMUTEX_H


#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include "LinkedListSerial.h"

class LinkedListOneMutex {
private:
    pthread_mutex_t lock;
    pthread_mutex_t lockForReduceTimes;
    pthread_t tid[4];
    int memberFrac, insertFrac, deleteFrac, opTimes;
    int opTimesMemInsDel;
    int opTimesMemOnly;
public:
    LinkedListSerial linkedListSerial;
    LinkedListOneMutex();
    int Member(int value);
    int Insert(int value);
    int Delete(int value);
    static void* threadFunc(void *args);
    void createThreads();
    void setLinkedList(LinkedListSerial linkedListSerial1);
    void printAll();
    void setTimesNFrac(int times, int mem, int ins, int del);
};


#endif //PARALLELLINKEDLIST_LINKEDLISTONEMUTEX_H
