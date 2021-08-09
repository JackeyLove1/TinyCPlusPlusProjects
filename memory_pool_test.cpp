//
// Created by Jacky on 2021/8/4.
//

#include <iostream>
#include "memory_pool.h"

using namespace std;


class A {
    static int count;
    int No;
public:
    A() {
        No = count;
        count++;
    }

    void print() {
        cout << this << " : ";
        cout << "the " << No << " the object" << endl;
    }

    void *operator new(size_t size);

    void operator delete(void *p);
};

// 定义内存池对象
MemPool<sizeof(A), 2> mp;

void *A::operator new(size_t size) {
    return mp.malloc();
}

void A::operator delete(void *p) {
    mp.free(p);
}

int A::count = 0;


int main() {
    A *p1 = new A;
    p1->print();
    A* p2 = new A;
    p2->print();
    delete p1;
    p1 = new A;
    p1->print();
    A* p3 = new A;
    p3->print();
    delete p1;
    delete p2;
    delete p3;
}