/**
 * @file matrix.cpp
 * @author Cade Bivens (cbivens5@skyhawks.utm.edu)
 * @brief Something 
 * @version 0.1
 * @date 2026-02-25
 * 
 * @copyright Copyright (c) 2026
 * 
 */

 #include <iomanip>
 #include "matrix.h"
 #include <stdexcept> // for exceptions

 using namespace std;

// Matrix class implementations

Matrix::Matrix(unsigned int rows, unsigned int cols) : m(rows), n(cols) {
    ar = new double*[m];
    for(int i = 0; i < m; i++) {
        ar[i] = new double[n];
        for(int j = 0; j < n; j++) {
            ar[i][j] = 0.0;
        }
    }
}

Matrix::Matrix(const Matrix& rhs) : m(rhs.m), n(rhs.n) {
    ar = new double*[m];
    for(int i = 0; i < m; i++) {
        ar[i] = new double[n];
        for(int j = 0; j < n; j++) {
            ar[i][j] = rhs.ar[i][j];
        }
    }
}

Matrix::~Matrix() {
    for(int i = 0; i < m; i++) {
        delete[] ar[i];
    }
    delete[] ar;
}

int Matrix::getRows() const {
    return m;
}

int Matrix::getCols() const {
    return n;
}

double& Matrix::at(unsigned int row, unsigned int col) {
    if(row >= m || col >= n) {
        throw out_of_range("Index out of range");
    }
    return ar[row][col];
}

const double& Matrix::at(unsigned int row, unsigned int col) const {
    if(row >= m || col >= n) {
        throw out_of_range("Index out of range");
    }
    return ar[row][col];
}

Matrix& Matrix::operator=(const Matrix& rhs) {
    if(this != &rhs) {
        // Deallocate current
        for(int i = 0; i < m; i++) {
            delete[] ar[i];
        }
        delete[] ar;
        // Copy
        m = rhs.m;
        n = rhs.n;
        ar = new double*[m];
        for(int i = 0; i < m; i++) {
            ar[i] = new double[n];
            for(int j = 0; j < n; j++) {
                ar[i][j] = rhs.ar[i][j];
            }
        }
    }
    return *this;
}

// Global operator implementations

Matrix operator+(const Matrix& m1, const Matrix& m2) {
    if(m1.getRows() != m2.getRows() || m1.getCols() != m2.getCols()) {
        throw invalid_argument("Matrices must have the same dimensions for addition");
    }
    Matrix result(m1.getRows(), m1.getCols());
    for(int i = 0; i < m1.getRows(); i++) {
        for(int j = 0; j < m1.getCols(); j++) {
            result.at(i, j) = m1.at(i, j) + m2.at(i, j);
        }
    }
    return result;
}

Matrix operator-(const Matrix& m1, const Matrix& m2) {
    if(m1.getRows() != m2.getRows() || m1.getCols() != m2.getCols()) {
        throw invalid_argument("Matrices must have the same dimensions for subtraction");
    }
    Matrix result(m1.getRows(), m1.getCols());
    for(int i = 0; i < m1.getRows(); i++) {
        for(int j = 0; j < m1.getCols(); j++) {
            result.at(i, j) = m1.at(i, j) - m2.at(i, j);
        }
    }
    return result;
}

Matrix operator*(const Matrix& m1, const Matrix& m2) {
    if(m1.getCols() != m2.getRows()) {
        throw invalid_argument("Incompatible dimensions for matrix multiplication");
    }
    Matrix result(m1.getRows(), m2.getCols());
    for(int i = 0; i < m1.getRows(); i++) {
        for(int j = 0; j < m2.getCols(); j++) {
            double sum = 0.0;
            for(int k = 0; k < m1.getCols(); k++) {
                sum += m1.at(i, k) * m2.at(k, j);
            }
            result.at(i, j) = sum;
        }
    }
    return result;
}

Matrix operator*(double scalar, const Matrix& m) {
    Matrix result(m.getRows(), m.getCols());
    for(int i = 0; i < m.getRows(); i++) {
        for(int j = 0; j < m.getCols(); j++) {
            result.at(i, j) = scalar * m.at(i, j);
        }
    }
    return result;
}

Matrix operator*(const Matrix& m, double scalar) {
    return scalar * m;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for(int i = 0; i < m.getRows(); i++) {
        for(int j = 0; j < m.getCols(); j++) {
            os << m.at(i, j) << " ";
        }
        os << endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& m) {
    for(int i = 0; i < m.getRows(); i++) {
        for(int j = 0; j < m.getCols(); j++) {
            is >> m.at(i, j);
        }
    }
    return is;
}

 