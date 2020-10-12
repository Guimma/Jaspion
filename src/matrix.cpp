#include <random>
#include <iostream>
#include <cstdlib>
#include <tgmath.h>
#include <chrono>
#include "../lib/matrix.hpp"

std::default_random_engine rng;
std::uniform_real_distribution<double> dist(-1,1);

using std::cout;
using std::cin;
using std::endl;
using std::tuple;
int NUM_THREADS = 2;

Matrix::Matrix() {
    matrix = vector<vector<double>>();
}

Matrix::Matrix(vector<vector<double>> data) {
    matrix = data;
}

Matrix::Matrix(uint rows, uint columns, Fill fill) {
    rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
    switch (fill) {
        case random_values:
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
    int i,j;
    #pragma omp parallel for schedule(static) private(i,j) num_threads(NUM_THREADS)
    for (i = 0; i < this->rows(); i++)
        for (j = 0; j < this->cols(); j++)
            matrix[i][j] = matrix[i][j] + other.matrix[i][j];
}

void Matrix::subtract(Matrix &other) {
    int i,j;
    #pragma omp parallel for schedule(static) private(i,j) num_threads(NUM_THREADS)
    for (i = 0; i < this->rows(); i++)
        for (j = 0; j < this->cols(); j++)
            matrix[i][j] = matrix[i][j] - other.matrix[i][j];
}

void Matrix::hadamarp(Matrix &other) {
    int i,j;
    #pragma omp parallel for schedule(static) private(i,j) num_threads(NUM_THREADS)
    for (i = 0; i < this->rows(); i++)
        for (j = 0; j < this->cols(); j++)
            matrix[i][j] = matrix[i][j] * other.matrix[i][j];
}

void Matrix::multiply(Matrix &other) {
    int i,j,k;
    auto result = Matrix(this->rows(), other.cols());
    #pragma omp parallel shared(result,matrix,other) private(i,j,k) num_threads(NUM_THREADS)
    {
        #pragma omp for schedule(static)
        for (i= 0; i < this->rows(); i++)
            for (j = 0; j < other.cols(); j++){
                for (k = 0; k < this->cols(); k++)
                    result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
            }
    }

    matrix = result.matrix;
}

void Matrix::escalar_multiply(double escalar) {
    int i,j;
    #pragma omp parallel for schedule(static) private(i,j) num_threads(NUM_THREADS)
    for (i = 0; i < this->rows(); i++)
        for (j = 0; j < this->cols(); j++)
            matrix[i][j] *= escalar;
}

void Matrix::sigmoid() {
    int i,j;
    #pragma omp parallel for schedule(static) private(i,j) num_threads(NUM_THREADS)
    for (i = 0; i < this->rows(); i++)
        for (j = 0; j < this->cols(); j++)
            matrix[i][j] = 1.0 / (1.0 + exp(-matrix[i][j]));
}

void Matrix::d_sigmoid() {
    int i,j;
    #pragma omp parallel for schedule(static) private(i,j) num_threads(NUM_THREADS)
    for (i = 0; i < this->rows(); i++)
        for (j = 0; j < this->cols(); j++)
            matrix[i][j] *= (1 - matrix[i][j]);
}

void Matrix::transpose() {
    int i,j;
    auto result = Matrix(this->cols(), this->rows());
    #pragma omp parallel for schedule(static) private(i,j) num_threads(NUM_THREADS)
    for (i = 0; i < result.rows(); i++)
        for (j = 0; j < result.cols(); j++)
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
