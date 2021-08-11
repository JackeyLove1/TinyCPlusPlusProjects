//
// Created by Jacky on 2021/8/11.
//

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

template<typename T>
class matrix {
    friend std::ostream &operator<<(std::ostream &os, const matrix<T> &);

public:
    matrix(int rows = 0, int cols = 0);

    matrix(const matrix<T> &);

    ~matrix() { delete[] element; }

    int row() const { return rows; }

    int col() const { return cols; }

    T &operator()(int i, int j) const;

    matrix<T> &operator=(const matrix<T> &);

    matrix<T> &operator+();

    matrix<T> &operator+(const matrix<T> &);

    matrix<T> &operator-();

    matrix<T> &operator-(const matrix<T> &);

    matrix<T> &operator*();

    matrix<T> &operator*(const matrix<T> &);

    matrix<T> &operator/(const matrix<T> &);

private:
    int rows;
    int cols;
    T *element;
};

#endif //MATRIX_H
