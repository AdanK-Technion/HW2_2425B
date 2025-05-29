#include "Matrix.h"

#include <cmath>

#include "Utilities.h"

Matrix::Matrix(int rows, int columns, double value): rows(rows),
    columns(columns),
    value(value) {
    if (columns < 0 || rows < 0) {
        exitWithError(MatamErrorType::OutOfBounds);
    } else {
        this->array = new double[this->rows * this->columns];
    }
    for (int i = 0; i < this->rows * this->columns; i++) {
        this->array[i] = value;
    }
}

Matrix::~Matrix() {
    delete[] array;
}

double &Matrix::operator()(int rows, int columns) {
    if (rows < 0 || rows >= this->rows || columns < 0 || columns >= this->
        columns) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return array[rows * this->columns + columns];
}

double Matrix::operator()(int rows, int columns) const {
    if (rows < 0 || rows >= this->rows || columns < 0 || columns >= this->
        columns) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return array[rows * this->columns + columns];
}

std::ostream &operator<<(std::ostream &os, Matrix const &matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        os << '|';
        for (int j = 0; j < matrix.columns; j++) {
            os << matrix(i, j) << '|';
        }
        os << '\n';
    }
    return os;
}


Matrix &Matrix::operator+=(Matrix const &matrix) {
    if (this->rows != matrix.rows || this->columns != matrix.columns)
        exitWithError(MatamErrorType::UnmatchedSizes);

    for (int i = 0; i < rows * columns; ++i)
        array[i] += matrix.array[i];
    return *this;
}

Matrix &Matrix::operator-=(Matrix const &matrix) {
    *this += (-matrix);
    return *this;
}

Matrix &Matrix::operator*=(Matrix const &matrix) {
    if (this->columns != matrix.rows)
        exitWithError(MatamErrorType::UnmatchedSizes);
    int oldColumns = this->columns, newColumns = matrix.columns;
    double *oldArray = this->array;
    this->array = new double[this->rows * matrix.columns];
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < matrix.columns; j++) {
            double sum = 0;
            for (int k = 0; k < this->columns; k++) {
                sum += oldArray[i * oldColumns + k] * matrix(k, j);
            }
            this->array[i * newColumns + j] = sum;
        }
    }
    delete[] oldArray;
    this->columns = newColumns;
    return *this;
}

Matrix &Matrix::operator*=(double number) {
    for (int i = 0; i < this->columns * this->rows; i++) {
        this->array[i] *= number;
    }
    return *this;
}

Matrix Matrix::operator+(Matrix const &matrix) const {
    Matrix sumMatrix(*this);
    sumMatrix += matrix;
    return sumMatrix;
}

Matrix Matrix::operator-() const {
    Matrix negative(this->rows, this->columns);
    for (int i = 0; i < this->rows * this->columns; i++) {
        negative.array[i] = -this->array[i];
    }
    return negative;
}

Matrix Matrix::operator-(Matrix const &matrix) const {
    Matrix subtractMatrix(*this);
    subtractMatrix -= matrix;
    return subtractMatrix;
}

Matrix Matrix::operator*(Matrix const &matrix) const {
    Matrix multiplyMatrix(*this);
    multiplyMatrix *= matrix;
    return multiplyMatrix;
}

Matrix Matrix::operator*(double number) const {
    Matrix multiplyMatrix(*this);
    multiplyMatrix *= number;
    return multiplyMatrix;
}

bool operator==(Matrix const &matrix1, Matrix const &matrix2) {
    if (matrix1.rows != matrix2.rows || matrix1.columns != matrix2.columns) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    for (int i = 0; i < matrix1.rows * matrix1.columns; i++) {
        if (matrix1.array[i] != matrix2.array[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(Matrix const &matrix1, Matrix const &matrix2) {
    return !(matrix1 == matrix2);
}

void Matrix::rotateClockwise() {
    int oldRows = this->rows, oldColumns = this->columns;
    this->rows = oldColumns;
    this->columns = oldRows;
    double *oldArray = this->array;
    this->array = new double[this->rows * this->columns];
    for (int i = 0; i < oldRows; i++) {
        for (int j = 0; j < oldColumns; j++) {
            this->array[this->columns * j + (this->columns - i - 1)] = oldArray[
                oldColumns * i + j];
        }
    }
    delete[] oldArray;
}

void Matrix::rotateCounterClockwise() {
    this->rotateClockwise();
    this->rotateClockwise();
    this->rotateClockwise();
}

void Matrix::transpose() {
    int oldRows = this->rows, oldColumns = this->columns;
    this->rows = oldColumns;
    this->columns = oldRows;
    double *oldArray = this->array;
    this->array = new double[this->rows * this->columns];
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            this->array[this->columns * i + j] = oldArray[oldColumns * j + i];
        }
    }
    delete[] oldArray;
}

double Matrix::calcFrobeniusNorm() {
    double sum = 0;
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            sum = sum + ((*this)(i, j) * (*this)(i, j));
        }
    }
    sum = pow(sum, 0.5);
    return sum;
}

double helperForDeterminant(Matrix const &matrix) {
    if (matrix.rows == 1) {
        return matrix(0, 0);
    }
    if (matrix.rows == 2) {
        return (matrix(0, 0) * matrix(1, 1)
                - matrix(0, 1) * matrix(1, 0));
    }
    double sum = 0;
    for (int i = 0; i < matrix.columns; i++) {
        Matrix temp(matrix.rows - 1, matrix.columns - 1);
        for (int j = 0; j < temp.rows; j++) {
            for (int k = 0; k < temp.columns; k++) {
                if (k < i) {
                    temp(j, k) = matrix(j + 1, k);
                } else {
                    temp(j, k) = matrix(j + 1, k + 1);
                }
            }
        }
        if (i % 2 == 0) {
            sum += matrix(0, i) * helperForDeterminant(temp);
        } else {
            sum -= matrix(0, i) * helperForDeterminant(temp);
        }
    }
    return sum;
}


double Matrix::calcDeterminant() {
    if (this->rows != this->columns) {
        exitWithError(MatamErrorType::NotSquareMatrix);
    }
    return helperForDeterminant(*this);
}
