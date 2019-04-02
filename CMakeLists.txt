cmake_minimum_required(VERSION 3.13)
project(ParallelLinkedList)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(ParallelLinkedList main.cpp LinkedListSerial.cpp Node.cpp LinkedListOneMutex.cpp LinkedListReadWriteLock.cpp)

