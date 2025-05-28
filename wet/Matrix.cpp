#include "Matrix.h"

#include "Utilities.h"
#includ "Utilities.h"
Matrix::Matrix(int rows, int columns, int value): rows(rows), columns(columns),
                                                  value(value) {
    if (columns < 0 || rows < 0) {
        exitWithError(MatamErrorType::OutOfBounds);
        this->rows = 0;
        this->columns = 0;
        this->value = 0;
    } else {
        this->array = new int[this->rows * this->columns];
    }
    for (int i = 0; i < this->rows * this->columns; i++) {
        this->array[i] = value;
    }
}

Matrix::~Matrix() {
    delete[] array;
}

int &Matrix::operator()(int rows, int columns) {
    if (rows < 0 || rows >= this->rows || columns < 0 || columns >= this->
        columns) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return array[rows * columns + columns];
}

int Matrix::operator()(int rows, int columns) const {
    if (rows < 0 || rows >= this->rows || columns < 0 || columns >= this->
        columns) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return array[rows * columns + columns];
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
    int *oldArray = this->array;
    this->array = new int[this->rows * matrix.columns];
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < matrix.columns; j++) {
            int sum = 0;
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

Matrix &Matrix::operator*=(int number) {
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

Matrix Matrix::operator*(int number) const {
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
