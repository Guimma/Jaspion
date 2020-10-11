#include <random>
#include <iostream>
#include <tgmath.h>
#include "../lib/matrix.hpp"

std::default_random_engine rng;
std::uniform_real_distribution<double> dist(-1,1);

using std::cout;
using std::cin;
using std::endl;
using std::tuple;

Matrix::Matrix() {
    matrix = vector<vector<double>>();
}   

Matrix::Matrix(vector<vector<double>> data) {
    matrix = data;
}

Matrix::Matrix(uint rows, uint columns, Fill fill) {
    switch (fill) {
        case random:
            for (int i = 0; i < rows; i++) {
                matrix.push_back(vector<double>());
                for (int j = 0; j < columns; j++) 
                    matrix.at(i).push_back(dist(rng));        
            }
            break;
        case input_values:
            for (int i = 0; i < rows; i++) {
                matrix.push_back(vector<double>());
                for (int j = 0; j < columns; j++){
                    double in = 0;
                    cin >> in;
                    matrix.at(i).push_back(in);
                }
            }
            break;
        default:
            for (int i = 0; i < rows; i++) {
                matrix.push_back(vector<double>());
                for (int j = 0; j < columns; j++)
                    matrix.at(i).push_back(0.0);
            } 
            break;
    }
}

vector<vector<double>> Matrix::get(){
    return matrix;
}

void Matrix::add(Matrix &other) {
    for (int i = 0; i < this->rows(); i++)
        for (int j = 0; j < this->cols(); j++)
            matrix[i][j] = matrix[i][j] + other.matrix[i][j];
}

void Matrix::subtract(Matrix &other) {
    for (int i = 0; i < this->rows(); i++)
        for (int j = 0; j < this->cols(); j++)
            matrix[i][j] = matrix[i][j] - other.matrix[i][j];
}

void Matrix::hadamarp(Matrix &other) {
    for (int i = 0; i < this->rows(); i++)
        for (int j = 0; j < this->cols(); j++)
            matrix[i][j] = matrix[i][j] * other.matrix[i][j];
}

void Matrix::multiply(Matrix &other) {
    auto result = Matrix(this->rows(), other.cols());
    for (int i = 0; i < this->rows(); i++)
        for (int j = 0; j < other.cols(); j++)
            for (int k = 0; k < this->cols(); k++)
                result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
    matrix = result.matrix;
}

void Matrix::escalar_multiply(uint escalar) {
    for (int i = 0; i < this->rows(); i++)
        for (int j = 0; j < this->cols(); j++)
            matrix[i][j] *= escalar;
}

void Matrix::sigmoid() {
    for (int i = 0; i < this->rows(); i++)
        for (int j = 0; j < this->cols(); j++)
            matrix[i][j] = 1.0 / (1.0 + exp(-matrix[i][j]));
}

void Matrix::d_sigmoid() {
    for (int i = 0; i < this->rows(); i++)
        for (int j = 0; j < this->cols(); j++)
            matrix[i][j] = matrix[i][j] * (1 - matrix[i][j]);
}

void Matrix::transpose() {
    auto result = Matrix(this->cols(), this->rows());
    for (int i = 0; i < result.rows(); i++)
        for (int j = 0; j < result.cols(); j++)
            result.matrix[i][j] = matrix[j][i];
    matrix = result.matrix;
}

uint Matrix::cols() {
    return this->matrix.at(0).size();
}

uint Matrix::rows() {
    return this->matrix.size();
}


void Matrix::display() {
    cout << "MATRIZ: " << endl;
    for (auto &rows : matrix) {
        for (double &value : rows)
            cout << " | " << value;
        cout << " |" << endl;
    }
    cout << endl;
}
