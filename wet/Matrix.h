#pragma once

#include <iostream>
#include <ostream>

class Matrix {
private:
    int rows;
    int columns;
    double value;
    double *array;

public:
    Matrix(int rows = 0, int columns = 0, double value = 0);

    ~Matrix();

    double &operator()(int rows, int columns);

    double operator()(int rows, int columns) const;

    friend std::ostream &operator<<(std::ostream &os, Matrix const &matrix);

    Matrix operator+(Matrix const &matrix) const;

    Matrix operator-(Matrix const &matrix) const;

    Matrix operator-() const;

    Matrix operator*(Matrix const &matrix) const;

    Matrix operator*(double number) const;

    Matrix &operator+=(Matrix const &matrix);

    Matrix &operator-=(Matrix const &matrix);

    Matrix &operator*=(Matrix const &matrix);

    Matrix &operator*=(double number);

    friend bool operator==(Matrix const &matrix1, Matrix const &matrix2);

    friend bool operator!=(Matrix const &matrix1, Matrix const &matrix2);

    void rotateClockwise();

    void rotateCounterClockwise();

    void transpose();

    double calcFrobeniusNorm();

    double calcDeterminant();

    friend double helperForDeterminant(Matrix const &matrix);
};
