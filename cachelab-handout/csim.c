// ZhiYang Wang, liaosong546263@gmail.com
#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>

/* To represent the size of block. */
#define BLOCKSIZE double
#define EMPTY NULL

typedef struct Line {
    int validBit;
    unsigned indexOfLine;
    BLOCKSIZE* blockInLine;
} LineSim;

typedef struct Set {
    unsigned numOfLines;
    LineSim* arrayOfLines;    
} SetSim;

typedef struct Cache {
    unsigned numOfSet;
    SetSim* arrayOfSets;
} CacheSim;

typedef struct Queue {
    PointerQueueToLRU* headOfQueue;
    PointerQueueToLRU* lastOfQueue;
} wrapperOfQueue;

typedef struct QueueNode {
    LineSim* data;
    PointerQueueToLRU* next;
} PointerQueueToLRU;

void insertLine(wrapperOfQueue* queue, LineSim* data) {
    PointerQueueToLRU* LastQue = queue->lastOfQueue;
    PointerQueueToLRU* HeadQue = queue->headOfQueue;
    PointerQueueToLRU* temp = (PointerQueueToLRU*) malloc(sizeof(PointerQueueToLRU));
    temp->data = data;
    temp->next = EMPTY;
    if (HeadQue == EMPTY) {
        queue->headOfQueue = temp;
        queue->lastOfQueue = temp;
    } else {
        LastQue->next = temp;
        queue->lastOfQueue = temp;     
    }
}

LineSim* getFirstElm(wrapperOfQueue* queue) {
    PointerQueueToLRU* firstElm = queue->headOfQueue;
    if (firstElm == EMPTY) {
        return 0;
    }
    LineSim* result = firstElm->data;
    if (firstElm->next == EMPTY) {
        free(firstElm);
        queue->headOfQueue = EMPTY;
        queue->lastOfQueue = EMPTY;
    } else {
        queue->headOfQueue = firstElm->next;
        free(firstElm);
    }
    return result;
}



int main(int argc, char **argv) {
    printSummary(0, 0, 0);
    return 0;
}

