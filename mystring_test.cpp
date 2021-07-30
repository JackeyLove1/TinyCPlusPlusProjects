//
// Created by Jacky on 2021/7/30.
//

#include "mystring.h"
#include <iostream>

using namespace std;

int main_test() {
    String s1("Hello");
    String s2("World");

    String s3(s1);
    cout << s3 << endl;

    s3 = s2;
    cout << s3 << endl;

    return 0;
}