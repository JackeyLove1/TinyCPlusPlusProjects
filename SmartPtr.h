//
// Created by Jacky on 2021/8/4.
//

#ifndef CPP_STUDY_SMARTPTR_H
#define CPP_STUDY_SMARTPTR_H

template<typename T> class SmartPtr;

template<typename T> class RefPtr{
private:
    // 设置为友元，便于访问private
    friend class SmartPtr<T>;
    // 构造函数
    RefPtr(T* ptr): p(ptr), count(1){}
    // 析构函数
    ~RefPtr(){delete p;}
    // 引用计数
    int count;
    // 基础指针
    T* p;
};

#include <iostream>
template<typename T>
class SmartPtr{
public:
    SmartPtr(T* ptr): rp(new RefPtr<T>(ptr)){}
    SmartPtr(const SmartPtr<T>& sp): rp(sp.rp){++rp->count;}
    SmartPtr& operator = (const SmartPtr<T>& rhs){
        ++rhs.rp->count;
        // 预防自我赋值
        if(--rp->count == 0){
            delete rp;
        }
        rp = rhs.rp;
        return *this;
    }
    T& operator * (){ // 重载*操作符
        return *(rp->p);
    }
    T* operator -> (){ // 重载 -> 操作符
        return rp->p;
    }
    // 析构函数
    ~SmartPtr(){
        if (--rp->count == 0){
            delete rp;
        }else{
            std::cout << "leave " << rp->count << " object" << std::endl;
        }
    }
private:
    RefPtr<T> *rp; // 辅助类对象
};

#endif //CPP_STUDY_SMARTPTR_H
