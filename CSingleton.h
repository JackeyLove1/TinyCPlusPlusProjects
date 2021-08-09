//
// Created by Jacky on 2021/8/4.
//

#ifndef CPP_STUDY_CSINGLETON_H
#define CPP_STUDY_CSINGLETON_H

class CSingleton {
private:
    CSingleton() {};
    static CSingleton *m_pInstance;

public:
    static CSingleton *GetInstance() {
        if (m_pInstance == nullptr) {
            m_pInstance = new CSingleton();
        }
        return m_pInstance;
    }
};

#endif //CPP_STUDY_CSINGLETON_H
