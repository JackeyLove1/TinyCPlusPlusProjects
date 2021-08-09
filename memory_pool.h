//
// Created by Jacky on 2021/8/4.
//

#ifndef CPP_STUDY_MEMORY_POOL_H
#define CPP_STUDY_MEMORY_POOL_H

// 经典内存池实现
#include <iostream>

template<int ObjectSize, int NumOfObjects = 20>
class MemPool {
private:
    // 空闲节点结构体
    struct FreeNode {
        FreeNode *pNext;
        char data[ObjectSize];
    };

    // 内存块结构体
    struct MemBlock {
        MemBlock *pNext;
        FreeNode data[NumOfObjects];
    };

    FreeNode *freeNodeListHeader;
    MemBlock *memBlockHeader;

public:
    MemPool() {
        freeNodeListHeader = nullptr;
        memBlockHeader = nullptr;
    }

    ~MemPool() {
        MemBlock *ptr;
        while (memBlockHeader) {
            ptr = memBlockHeader->pNext;
            delete memBlockHeader;
            memBlockHeader = ptr;
        }
    }

    void *malloc();

    void free(void *);
};

// 分配空闲的节点
template<int ObjectSize, int NumOfObjects>
void *MemPool<ObjectSize, NumOfObjects>::malloc() {
    if (freeNodeListHeader == nullptr) {
        MemBlock *newMemBlock = new MemBlock;
        newMemBlock->pNext = nullptr;
        // 设置内存块的第一个节点为空闲节点链表的首节点
        freeNodeListHeader = &newMemBlock->data[0];

        // 将内存块的其他节点串联起来
        for (int i = 1; i < NumOfObjects; i++) {
            newMemBlock->data[i - 1].pNext = &newMemBlock->data[i];
        }

        newMemBlock->data[NumOfObjects - 1].pNext = nullptr;

        // 首次申请内存块
        if (memBlockHeader == nullptr) {
            memBlockHeader = newMemBlock;
        } else {
            // 将新内存加入内存块链表
            newMemBlock->pNext = memBlockHeader;
            memBlockHeader = newMemBlock;
        }
    }

    // 返回空闲链表的第一个节点
    void* freeNode = freeNodeListHeader;
    freeNodeListHeader = freeNodeListHeader->pNext;
    return freeNode;
}

// 释放已经分配的节点
template<int ObjectSize, int NumOfObjects>
void MemPool<ObjectSize, NumOfObjects>::free(void * p) {
    FreeNode* pNode = static_cast<FreeNode*>(p);
    pNode->pNext = freeNodeListHeader; // 将释放的节点插入空闲链表的头部
    freeNodeListHeader = pNode;
}

#endif //CPP_STUDY_MEMORY_POOL_H
