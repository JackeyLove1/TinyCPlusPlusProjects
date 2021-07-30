//
// Created by Jacky on 2021/7/30.
//

#include <iostream>
#include "complex.h"

using namespace std;

ostream &operator<<(ostream &os, const complex &x) {
    return os << '(' << real(x) << " , " << imag(x) << ')';
}

int main() {
    complex c1(1, 2);
    complex c2(0, 1);
    cout << c1 << endl;
    cout << c2 << endl;

    cout << "c1 + c2 " << c1 + c2 << endl;
    cout << "c1 - c2 " << c1 - c2 << endl;
    cout << "c1 * c2 " << c1 * c2 << endl;

    return 0;
}