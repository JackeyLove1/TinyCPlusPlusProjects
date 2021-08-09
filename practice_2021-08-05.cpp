//
// Created by Jacky on 2021/8/5.
//

#ifndef CPP_STUDY_TEMP_PRACTICE_H
#define CPP_STUDY_TEMP_PRACTICE_H

#include <cstddef>
#include <iostream>

class CSingleton {
private:
    static CSingleton *m_instance;

    CSingleton() {};
public:
    static CSingleton *GetInstance() {
        if (m_instance == nullptr) {
            m_instance = new CSingleton();
        }
        return m_instance;
    }
};

class String {
private:
    struct StringValue {
        int RefCount;
        char *data;

        StringValue(const char *initValue);

        ~StringValue();
    };

    StringValue *value;

public:

    String(const char *initValue = "");

    String(const String &rhs);

    String &operator=(const String &rhs);

    const char &operator[](size_t size) const;

    ~String() noexcept;

    friend std::ostream &operator<<(std::ostream &os, const String &str);
};

#include <cstring>

String::StringValue::StringValue(const char *initValue) : RefCount(1) {
    int len = strlen(initValue);
    if (len == 0) {
        data = new char[1];
        data[0] = '\0';
    } else {
        data = new char[strlen(initValue) + 1];
        strcpy(data, initValue);
    }
};

String::StringValue::~StringValue() {
    delete[] data;
}

String::String(const char *initValue) : value(new StringValue(initValue)) {

}

String::String(const String &rhs) : value(rhs.value) {
    ++rhs.value->RefCount;
}

String::~String() noexcept {
    if (--value->RefCount == 0) delete value;
}

String &String::operator=(const String &rhs) {
    if (this == &rhs) {
        return *this;
    }

    if (--value->RefCount == 0) delete value;
    value = rhs.value;
    ++rhs.value->RefCount;
    return *this;
}

const char &String::operator[](size_t size) const {
    return value->data[size];
}

std::ostream &operator<<(std::ostream &os, const String &str) {
    os << str.value->data;
    return os;
}

template<typename T>
class SmartPtr;

template<typename T>
class RefPtr {
private:
    friend class SmartPtr<T>;

    T *ptr;
    int count;

    RefPtr(T *_ptr) : ptr(_ptr), count(1) {};

    ~RefPtr() { delete ptr; }
};

template<typename T>
class SmartPtr {
public:
    SmartPtr(T *ptr) : rp(new RefPtr<T>(ptr)) {};

    SmartPtr(const SmartPtr<T> &sp) : rp(sp.rp) { ++rp->count; };

    SmartPtr &operator=(const SmartPtr<T> &rhs) {
        ++rhs.rp->count;
        if (--rp->count == 0) delete rp;
        rp = rhs.rp;
        return *this;
    }

    ~SmartPtr() {
        if (--rp->count == 0) {
            delete rp;
        } else {
            std::cout << "left: " << rp->count << " objects" << std::endl;
        }

    }

    T &operator*() {
        return *(rp->ptr);
    }

    T *operator->() {
        return (rp->ptr);
    }


private:
    RefPtr<T> *rp;
};

#endif //CPP_STUDY_TEMP_PRACTICE_H
