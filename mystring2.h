//
// Created by Jacky on 2021/8/3.
//

#ifndef CPP_STUDY_MYSTRING2_H
#define CPP_STUDY_MYSTRING2_H
// 含引用计数的string类

#include <cstdlib>
#include <iostream>

class String {
private:
    struct StringValue {
        int refCount;
        char *data;

        explicit StringValue(const char *initValue);

        ~StringValue();
    };

    StringValue *value;
public:
    String(const char *initValue = "");

    String(const String &rhs);

    String &operator=(const String &rhs);

    const char &operator[](size_t index) const;

    char *get_c_str() const { return value->data; }

    ~String();

    // friend std::ostream &operator<<(std::ostream &os, const String &str);
};

#include <cstring>

String::StringValue::StringValue(const char *initValue) : refCount(1) {
    data = new char[strlen(initValue) + 1];
    strcpy(data, initValue);
}

String::StringValue::~StringValue() {
    delete[] data;
}

String::String(const char *initValue) : value(new StringValue(initValue)) {
    // std::cout << "construct succeed !" << std::endl;
}

String::String(const String &rhs) : value(rhs.value) {
    ++value->refCount;
}

String::~String() {
    if (--value->refCount == 0) delete value;
}

String &String::operator=(const String &rhs) {
    // 预防自我赋值
    if (this->value == rhs.value) {
        return *this;
    }
    // 解绑原有值
    if (--value->refCount == 0) delete value;
    value = rhs.value;
    ++value->refCount;
    return *this;
}

const char &String::operator[](size_t index) const {
    return value->data[index];
}

inline std::ostream &operator<<(std::ostream &os, const String &str) {
    // std::cout << "run ... " << std::endl;
    os << str.get_c_str();
    return os;
}

#endif //CPP_STUDY_MYSTRING2_H
