//
// Created by Jacky on 2021/7/30.
//

// C++ my string class for studying
#ifndef CPP_STUDY_MYSTRING_H
#define CPP_STUDY_MYSTRING_H

#include <cstring>

class String {
public:
    String(const char *cstr = 0); // C字符串成员
    String(const String &str); // String类
    String &operator=(const String &str); // 赋值运算符
    ~String();

    char *get_c_str() const { return m_data; }

private:
    char *m_data;
};

inline String::String(const char *cstr) {
    if (cstr) {
        m_data = new char[strlen(cstr) + 1];
        strcpy(m_data, cstr);
    } else {
        m_data = new char[1];
        m_data[0] = '\0';
    }
}

inline String::String(const String &str) {
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
}

inline String &String::operator=(const String &str) {
    // 预防自我赋值
    if (this == &str) {
        return *this;
    }
    delete[] m_data;
    m_data = new char[strlen(str.m_data) + 1];
    strcpy(m_data, str.m_data);
    return *this;
}

inline String::~String() {
    delete[] m_data;
}

#include <iostream>

std::ostream &operator<<(std::ostream &os, const String &str) {
    os << str.get_c_str();
    return os;
}

#endif //CPP_STUDY_MYSTRING_H
