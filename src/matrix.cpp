#include <random>
#include <iostream>
#include <tgmath.h>
#include "../lib/matrix.hpp"

std::default_random_engine rng;
std::uniform_real_distribution<double> dist(-1,1);

using std::cout;
using std::cin;
using std::endl;

Matrix::Matrix() {
    matrix = vector<vector<double>>();
}   

Matrix::Matrix(unsigned int rows, unsigned int columns, Fill fill) {
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

void Matrix::add(Matrix &other) {
    auto result = Matrix(matrix.size(), matrix.at(0).size());
    for (int i = 0; i < matrix.size(); i++)
        for (int j = 0; j < matrix.at(0).size(); j++)
            result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
    matrix = result.matrix;
}

void Matrix::multiply(Matrix &other) {
    auto result = Matrix(matrix.size(), other.matrix.at(0).size());
    for (int i = 0; i < matrix.size(); i++)
        for (int j = 0; j < other.matrix.at(0).size(); j++)
            for (int k = 0; k < matrix.at(0).size(); k++)
                result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
    matrix = result.matrix;
}

// void Matrix::sigmoid(double x) {
//     auto result = Matrix(matrix.size(), other.matrix.at(0).size());
//     1 / (1 + exp(-x))
//     matrix = result.matrix;
// }

void Matrix::display() {
    cout << "MATRIZ: " << endl;
    for (auto &rows : matrix) {
        for (double &value : rows)
            cout << " | " << value;
        cout << " |" << endl;
    }
    cout << endl;
}
