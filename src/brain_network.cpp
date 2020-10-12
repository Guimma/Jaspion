#include <iostream>
#include <vector>
#include <random>
#include "../lib/brain_network.hpp"

using std::cout;
using std::endl;

BrainNetwork::BrainNetwork(int input_nodes, int hidden_nodes, int output_nodes) {
    // SETTING LEARNING RATE
    learning_rate = 0.1;

    // SETTING QUANTITY OF NODES
    i_nodes = input_nodes;
    h_nodes = hidden_nodes;
    o_nodes = output_nodes;

    // SETTING BIAS
    bias_ih = Matrix(h_nodes, 1, Fill::random_values);
    bias_ho = Matrix(o_nodes, 1, Fill::random_values);

    // SETTING WEIGHTS
    weights_ih = Matrix(h_nodes, i_nodes, Fill::random_values);
    weights_ho = Matrix(o_nodes, h_nodes, Fill::random_values);
}

void BrainNetwork::train(Matrix input, Matrix expected){
    // INPUT TO HIDDEN
    Matrix hidden = weights_ih;
    hidden.multiply(input);
    hidden.add(bias_ih);
    hidden.sigmoid();

    // HIDDEN TO OUTPUT
    Matrix output = weights_ho;
    output.multiply(hidden);
    output.add(bias_ho);
    output.sigmoid();

    // BACKPROPAGATION
    // OUTPUT TO HIDDEN
    Matrix output_error = expected;
    output_error.subtract(output);
    Matrix d_output = output;
    d_output.d_sigmoid();
    Matrix hidden_T = hidden;
    hidden_T.transpose();

    Matrix gradient = d_output;
    gradient.hadamarp(output_error);
    gradient.escalar_multiply(learning_rate);

    // Adjust Bias O_H
    bias_ho.add(gradient);
    // Adjust Weigths O_H
    Matrix weights_ho_deltas = gradient;
    weights_ho_deltas.multiply(hidden_T);
    weights_ho.add(weights_ho_deltas);

    // HIDDEN TO INPUT
    Matrix weights_ho_T = weights_ho;
    weights_ho_T.transpose();
    Matrix hidden_error = weights_ho_T;
    hidden_error.multiply(output_error);
    Matrix d_hidden = hidden;
    d_hidden.d_sigmoid();
    Matrix input_T = input;
    input_T.transpose();

    Matrix gradient_H = d_hidden;
    gradient_H.hadamarp(hidden_error);
    gradient_H.escalar_multiply(learning_rate);

    // Adjust Bias I_H
    bias_ih.add(gradient_H);

    // Adjust Weigths I_H
    Matrix weights_ih_deltas = gradient_H;
    weights_ih_deltas.multiply(input_T);
    weights_ih.add(weights_ih_deltas);
}

Matrix BrainNetwork::predict(Matrix input) {
    // INPUT TO HIDDEN
    Matrix hidden = weights_ih;
    hidden.multiply(input);
    hidden.add(bias_ih);
    hidden.sigmoid();

    // HIDDEN TO OUTPUT
    Matrix output = weights_ho;
    output.multiply(hidden);
    output.add(bias_ho);
    output.sigmoid();

    return output;
}
