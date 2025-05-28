#pragma once

#include <iostream>
#include <ostream>

class Matrix {
private:
    int rows;
    int columns;
    int value;
    int *array;

public:
    Matrix(int rows = 0, int columns = 0, int value = 0);

    ~Matrix();

    int &operator()(int r, int c);

    int operator()(int r, int c) const;

    friend std::ostream &operator<<(std::ostream &os, Matrix const &matrix);

    // 1) binary +, -, *  (return new Matrix)
    Matrix operator+(Matrix const &matrix) const;

    Matrix operator-(Matrix const &matrix) const;

    Matrix operator-() const;

    Matrix operator*(Matrix const &matrix) const;

    Matrix operator*(int number) const;

    Matrix &operator+=(Matrix const &matrix);

    Matrix &operator-=(Matrix const &matrix);

    Matrix &operator*=(Matrix const &matrix);

    Matrix &operator*=(int number);

    friend bool operator==(Matrix const &matrix1, Matrix const &matrix2);

    friend bool operator!=(Matrix const &matrix1, Matrix const &matrix2);
};
