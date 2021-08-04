//
// Created by Jacky on 2021/8/4.
//

#include <iostream>
#include "SmartPtr.h"

using namespace std;

int main(){
    int* ia = new int(10);
    {
        SmartPtr<int>sptr1(ia);
        cout << "sptr1: " << *sptr1 << endl;
        SmartPtr<int>sptr2(sptr1);
        *sptr2 = 5;
        cout << "sptr2: " << *sptr2 << endl;
        {
            SmartPtr<int>sptr3 = sptr1;
            cout << "sptr3: " << *sptr3 << endl;
        }
    }

    return 0;
}