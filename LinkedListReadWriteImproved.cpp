//
// Created by tharsanan on 4/2/19.
//

#include "LinkedListReadWriteImproved.h"

#include <cstdlib>
#include <pthread.h>
#include <iostream>
#include <thread>

LinkedListReadWriteImproved::LinkedListReadWriteImproved(){
    lockRead = PTHREAD_MUTEX_INITIALIZER;
    lockWrite = PTHREAD_MUTEX_INITIALIZER;
    lockForReduceTimes = PTHREAD_MUTEX_INITIALIZER;
    isReading = 0;
    lockedValue = 0;
}



void LinkedListReadWriteImproved::setLinkedList(LinkedListSerial linkedListSerial1){
    linkedListSerial = linkedListSerial1;
}

int LinkedListReadWriteImproved::Member(int value){

    pthread_mutex_lock(&lockRead);
    if(lockedValue < value) {
        lockedValue = value;
    }
    isReading++;
    if(isReading == 1){
        pthread_mutex_lock(&lockWrite);         // it will also make sure no read when one thread writes.
    }
    pthread_mutex_unlock(&lockRead);
    pthread_t thId = pthread_self();
//    std::cout << thId;
    linkedListSerial.Member(value);
    pthread_mutex_lock(&lockRead);
    isReading--;
    if(isReading == 0){
        pthread_mutex_unlock(&lockWrite);
    }
    pthread_mutex_unlock(&lockRead);
}
int LinkedListReadWriteImproved::Insert(int value){
//    pthread_mutex_lock(&lockRead);
//    if(isReading != 0){
//        pthread_mutex_unlock(&lockRead);
//        while(true){
//            pthread_mutex_lock(&lockRead);
//            if(isReading == 0){
//                int i = linkedListSerial.Insert(value);
//                pthread_mutex_unlock(&lockRead);
//                return i;
//            }
//            pthread_mutex_unlock(&lockRead);
//
//        }
//    }
//    else{
//        linkedListSerial.Insert(value);
//        pthread_mutex_unlock(&lockRead);
//    }
    pthread_mutex_lock(&lockRead);
    if(lockedValue < value){

    }
    pthread_mutex_lock(&lockWrite);
    linkedListSerial.Insert(value);
    pthread_mutex_unlock(&lockWrite);





}
int LinkedListReadWriteImproved::Delete(int value){
//    pthread_mutex_lock(&lockRead);
//    if(isReading == 0) {
//        linkedListSerial.Delete(value);
//        pthread_mutex_unlock(&lockRead);
//    }
//    else{
//        pthread_mutex_unlock(&lockRead);
//        return 0;
//    }
    pthread_mutex_lock(&lockWrite);
    linkedListSerial.Delete(value);
    pthread_mutex_unlock(&lockWrite);

}

void* LinkedListReadWriteImproved::threadFunc(void *list){
    LinkedListReadWriteImproved* linkedListReadWriteLock = (LinkedListReadWriteImproved* )list;
    while (true) {
        int toInsert = 0 + (rand() % (65535 - 0 + 1));

        if (linkedListReadWriteLock->opTimesMemInsDel > 0 /**&& !linkedListReadWriteLock->Member(toInsert)**/) {
            linkedListReadWriteLock->Insert(toInsert);
            linkedListReadWriteLock->Delete(toInsert);
            pthread_mutex_lock(&linkedListReadWriteLock->lockForReduceTimes);
            linkedListReadWriteLock->opTimesMemInsDel = linkedListReadWriteLock->opTimesMemInsDel - 1;
//            linkedListReadWriteLock->opTimesMemOnly = linkedListReadWriteLock->opTimesMemOnly - 1;
            pthread_mutex_unlock(&linkedListReadWriteLock->lockForReduceTimes);
        }
//        else{
        pthread_mutex_lock(&linkedListReadWriteLock->lockForReduceTimes);
        linkedListReadWriteLock->opTimesMemOnly = linkedListReadWriteLock->opTimesMemOnly - 1;
        pthread_mutex_unlock(&linkedListReadWriteLock->lockForReduceTimes);
        linkedListReadWriteLock->Member(toInsert);
//        }

        if(linkedListReadWriteLock->opTimesMemInsDel <= 0  && linkedListReadWriteLock->opTimesMemOnly <= 0){
            break;
        }
    }
    pthread_exit(NULL);
}

void LinkedListReadWriteImproved::createThreads(){
    srand(14);
    auto start =  std::chrono::high_resolution_clock::now();
    int i = 0;
    int err;
    while(i < 4)
    {
        err = pthread_create(&(tid[i]), NULL, &LinkedListReadWriteImproved::threadFunc, this);
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

void LinkedListReadWriteImproved::printAll() {
    linkedListSerial.printAll();
}

void LinkedListReadWriteImproved::setTimesNFrac(int times, int mem, int ins, int del){
    memberFrac = mem;
    insertFrac = ins;
    deleteFrac = del;
    opTimes = times;
    opTimesMemInsDel = ((opTimes * insertFrac)/(insertFrac + insertFrac + memberFrac));
    opTimesMemOnly = opTimes - opTimesMemInsDel - opTimesMemInsDel;
}