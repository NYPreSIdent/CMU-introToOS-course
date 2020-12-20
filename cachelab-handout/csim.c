// ZhiYang Wang, liaosong546263@gmail.com
#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

/* To represent the size of block. */
#define BLOCKSIZE double
#define EMPTY NULL
#define VALID 1 
#define INVALID 0 
#define SUCCSESS 1
#define FALIURE 0

/* The ListOfAction follows the rule: There exits four numbers, each represents for
   1. number of set, 2. E-way associativity, 3. blockNum */
static unsigned int factorOfSets;
static unsigned int factorOfLines;
static unsigned int factorOfBlocks;
static unsigned int missCount;
static unsigned int hitCount;
static unsigned int evictCount;
static char* pathOfFile;

/* To represent the line in cache set. */
typedef struct Line {
    char validBit;
    unsigned int indexOfLine;
    BLOCKSIZE* blockInLine;
} LineSim;


typedef struct QueueNode {
    LineSim* data;
    struct QueueNode* next;
} PointerQueueToLRU;

typedef struct Queue {
    PointerQueueToLRU* headOfQueue;
} wrapperOfQueue;

typedef struct Set {
    unsigned int numOfLines;
    LineSim* arrayOfLines;    
    wrapperOfQueue* LRUque;
} SetSim;

typedef struct Cache {
    unsigned int numOfSet;
    SetSim* arrayOfSets;
} CacheSim;

PointerQueueToLRU* insertHelper(PointerQueueToLRU* queue, LineSim* data) {
    if (queue == EMPTY) {
        PointerQueueToLRU* temp = (PointerQueueToLRU*) malloc(sizeof(PointerQueueToLRU));
        temp->data = data;
        temp->next = NULL;
        return temp;
    }
    PointerQueueToLRU* nextQueue = queue->next;
    if (queue->data == data) {
        free(queue); 
        return insertHelper(nextQueue, data);
    } 
    queue->next = insertHelper(nextQueue, data);
    return queue;
}

void insertLine(wrapperOfQueue* queue, LineSim* data) {
    queue->headOfQueue = insertHelper(queue->headOfQueue, data);
}

LineSim* getFirstElm(wrapperOfQueue* queue) {
    PointerQueueToLRU* head = queue->headOfQueue;
    if (head == EMPTY) {
        return EMPTY;
    }
    LineSim* result = head->data;
    queue->headOfQueue = head->next;
    free(head);
    return result;
}

wrapperOfQueue* initQueue() {
    wrapperOfQueue* result = (wrapperOfQueue*) malloc(sizeof(wrapperOfQueue));
    result->headOfQueue = EMPTY;
    return result;
}

BLOCKSIZE* initBlock(unsigned int numberOfBlock) {
    /* It's just an array of BLOCKSIZE. */ 
    BLOCKSIZE* result = (BLOCKSIZE*) malloc(numberOfBlock * sizeof(BLOCKSIZE));
    return result;
}

LineSim* initLine(unsigned int numberOfBlock, 
                  unsigned int numberOfLines,
                  wrapperOfQueue* localQueue) {
    /* The structure of line: [valid data, tag, block] */
    LineSim* result = (LineSim*) malloc(sizeof(LineSim) * numberOfLines);

    for (unsigned int i = 0; i < numberOfLines; i++) {
        result[i].validBit = INVALID;
        result[i].indexOfLine = 0; 
        result[i].blockInLine = initBlock(numberOfBlock);
    }
    return result;
}

SetSim* initSet(unsigned int numberOfLine,
                unsigned int numberOfBlock, 
                unsigned int numberOfSet) {
    /*
        The Set just look like this way:
            Set -> Line
                   Line
                   ....
    */
    SetSim* pointerToSet = (SetSim*) malloc(sizeof(SetSim) * numberOfSet);

    for (int i = 0; i < numberOfSet; i++) {
        wrapperOfQueue* localQueue = initQueue();
        pointerToSet[i].arrayOfLines = initLine(numberOfBlock, numberOfLine, localQueue);
        pointerToSet[i].numOfLines = numberOfLine;
        pointerToSet[i].LRUque = localQueue;
    }

    return pointerToSet;
}

CacheSim* initCache() {
    /* 
        Cache looks like this way (2-way set associative cache example):

            Cache -> Set
                     Set
                     Set
                     ...
                     (each set can be accessed by using array index)

        The line is just an array of struct Lines, so we can use Cache[index] to represent that set.
    */
    unsigned int numberOfSet = pow(2, factorOfSets);
    unsigned int numberOfBlock = pow(2, factorOfBlocks);
    unsigned int numberOfLines = factorOfLines;

    CacheSim* pointerToCache = (CacheSim*) malloc(sizeof(CacheSim));

    // initialize the Cache struct to point to the start addr of the lines.
    pointerToCache->numOfSet = numberOfSet;
    pointerToCache->arrayOfSets = initSet(numberOfLines, numberOfBlock, numberOfSet); 

    // initialize the set to point to initialize lines.
    return pointerToCache;
}

char isHit(LineSim localLine, unsigned int tag) {
    unsigned int localTag = localLine.indexOfLine;
    unsigned int isValid = localLine.validBit;
    if (!isValid) {
        return 0;
    }
    if (localTag == tag) {
        return 1;
    } else {
        return 0;
    }
}

void store(CacheSim* localCache, 
           unsigned int tag, 
           unsigned int cacheIndex, 
           unsigned int offset,
           char isModified) {
    SetSim localSet = localCache->arrayOfSets[cacheIndex];
    LineSim* localLine = localSet.arrayOfLines;
    int HitStatus = FALIURE;
    wrapperOfQueue* localQueue = localSet.LRUque;

    for (int i = 0; i < factorOfLines; i++) {
        if (localLine[i].validBit != VALID) {
            localLine[i].indexOfLine = tag;
            localLine[i].blockInLine[offset] = 10;
            localLine[i].validBit = VALID;
            HitStatus = SUCCSESS;
            localLine = &localLine[i];
            missCount += 1;
            insertLine(localQueue, localLine);
            break;
        }
        if (isHit(localLine[i], tag)) {
            localLine[i].indexOfLine = tag;
            localLine[i].blockInLine[offset] = 10;
            localLine[i].validBit = VALID;
            HitStatus = SUCCSESS;
            localLine = &localLine[i];
            hitCount += 1;
            insertLine(localQueue, localLine);
            break;
        }
    }

    if (!HitStatus) {
        LineSim* LRULine = getFirstElm(localQueue);
        evictCount += 1;
        missCount += 1;
        LRULine->blockInLine[offset] = 10;
        LRULine->indexOfLine = tag;
        LRULine->validBit = VALID;
        insertLine(localQueue, LRULine);
    }   
}

void load(CacheSim* localCache, unsigned int tag, unsigned int cacheIndex, unsigned int offset) {
    SetSim localSet = localCache->arrayOfSets[cacheIndex];
    LineSim* localLine = localSet.arrayOfLines;
    int HitStatus = FALIURE;
    wrapperOfQueue* localQueue = localSet.LRUque;

    for (int i = 0; i < factorOfLines; i++) {
        if (isHit(localLine[i], tag)) {
            insertLine(localQueue, localLine);
            localLine[i].indexOfLine = tag;
            localLine[i].blockInLine[offset] = 1;
            HitStatus = SUCCSESS;
            hitCount += 1;
            break;
        }
    }
    if (!HitStatus) {
        store(localCache, tag, cacheIndex, offset, FALIURE);
    }
}

int getMaskForAddr(int lenOfMask) {
    /* We make use of the property of binary number:
        Suppose we want to get 0x11, we can calculate the 2 ** 2(the length of mask) - 1 */
    return pow(2, lenOfMask) - 1;
}

void modify(CacheSim* localCache, unsigned int tag, unsigned int cacheIndex, unsigned int offset) {
    load(localCache, tag, cacheIndex, offset);
    store(localCache, tag, cacheIndex, offset, SUCCSESS);
}

int main(int argc, char **argv) {
    char action;
    FILE* fp;
    unsigned int addr;
    char instru[2];
    char* cvalue = NULL;
    int dataSize;
    unsigned int tag;
    unsigned int cacheIndex;
    unsigned int blockOffset;

    while ((action = getopt(argc, argv, "s:E:b:t:")) != -1) {
        switch (action) {
            case 's':
                cvalue = optarg;
                factorOfSets = (unsigned int) atoi(cvalue);
                break;
            case 'E':
                cvalue = optarg;
                factorOfLines = (unsigned int) atoi(cvalue);
                break;
            case 'b':
                cvalue = optarg;
                factorOfBlocks = (unsigned int) atoi(cvalue);
            case 't':
                pathOfFile = optarg; 
                break;
            default:
                abort();
        }
    }

    CacheSim* CacheInstance = initCache();

    fp = fopen(pathOfFile, "r");
    if (fp == NULL) {
        abort();
    }


    while (fscanf(fp, "%s %x,%d", instru, &addr, &dataSize) != EOF) {
        int blockMask = getMaskForAddr(factorOfBlocks);
        int cacheMask = (~blockMask) & getMaskForAddr(factorOfBlocks + factorOfSets);

        blockOffset = blockMask & addr;
        cacheIndex = (cacheMask & addr) >> factorOfBlocks;
        tag = ((~cacheMask) & addr) >> (factorOfBlocks + factorOfSets);

        if (strcmp(instru, "I") == 0) {
            continue;
        } else if (strcmp(instru, "M") == 0) {
            modify(CacheInstance, tag, cacheIndex, blockOffset);
        } else if (strcmp(instru, "L") == 0) {
            load(CacheInstance, tag, cacheIndex, blockOffset);
        } else if (strcmp(instru, "S") == 0) {
            store(CacheInstance, tag, cacheIndex, blockOffset, FALIURE);
        } else {
            continue;
        }
    }
    printSummary(hitCount, missCount, evictCount);

    fclose(fp);
    return 0;
}
