//
// Created by Jacky on 2021/8/8.
//

#ifndef TINYWEBSERVER_THREADSAFESTACK_H
#define TINYWEBSERVER_THREADSAFESTACK_H

// 使用互斥锁实现
#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct empty_stack : std::exception{
    const char* what() const throw(){
        return "empty_stack";
    }
};

template<typename T>
class ThreadSafe_stack{
private:
    std::stack<T> data;
    mutable std::mutex mtx;

public:
    ThreadSafe_stack(): data(std::stack<T>()) {}

    ThreadSafe_stack(const ThreadSafe_stack<T>& other){
        std::lock_guard<std::mutex> lock(other.mtx);
        data = other.data;
    }

    ThreadSafe_stack& operator = (const ThreadSafe_stack<T>& other) = delete ;

    void push(T new_value){
        std::lock_guard<std::mutex> lock(mtx);
        data.push(new_value);
    }

    std::shared_ptr<T> pop(){
        std::lock_guard<std::mutex> lock(mtx);
        if(data.empty()) throw empty_stack();

        std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
        data.pop();
        return res;
    }

    void pop(T& value){
        std::lock_guard<std::mutex> lock(mtx);
        if(data.empty()) throw empty_stack();
        
        value = data.top();
        data.pop();
    }
    
    bool empty(){
        std::lock_guard<std::mutex> lock(mtx);
        return data.empty();
    }
    
};

#endif //TINYWEBSERVER_THREADSAFESTACK_H
