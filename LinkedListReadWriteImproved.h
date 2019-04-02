//
// Created by tharsanan on 4/2/19.
//

#ifndef PARALLELLINKEDLIST_LINKEDLISTREADWRITEIMPROVED_H
#define PARALLELLINKEDLIST_LINKEDLISTREADWRITEIMPROVED_H


#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include "LinkedListSerial.h"

class LinkedListReadWriteImproved {
private:
    pthread_mutex_t lockRead;
    pthread_mutex_t lockWrite;
    pthread_mutex_t lockForReduceTimes;
    pthread_t tid[4];
    int memberFrac, insertFrac, deleteFrac, opTimes;
    int opTimesMemInsDel;
    int opTimesMemOnly;
    int isReading;
public:
    LinkedListSerial linkedListSerial;
    LinkedListReadWriteImproved();
    int Member(int value);
    int Insert(int value);
    int Delete(int value);
    static void* threadFunc(void *args);
    void createThreads();
    void setLinkedList(LinkedListSerial linkedListSerial1);
    void printAll();
    void setTimesNFrac(int times, int mem, int ins, int del);
    int lockedValue;
    int maxValue;
    bool type;
};


#endif //PARALLELLINKEDLIST_LINKEDLISTONEMUTEX_H
