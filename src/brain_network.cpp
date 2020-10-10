#include <iostream>
#include <vector>
#include <random>
#include "../lib/matrix.hpp"

using std::cout;
using std::endl;
using Vector = std::vector<double>;

class BrainNetwork {
    public:
        int i_nodes;
        int h_nodes;
        int o_nodes;
        Matrix bias_ih;
        Matrix bias_ho;
        Matrix weight_ih;
        Matrix weight_ho;
        BrainNetwork(int, int, int);
        void feed_foward(Matrix);
};

BrainNetwork::BrainNetwork(int input_nodes, int hidden_nodes, int output_nodes) {
    // SETTING QUANTITY OF NODES
    i_nodes = input_nodes;
    h_nodes = hidden_nodes;
    o_nodes = output_nodes;

    // SETTING BIAS
    bias_ih = Matrix(h_nodes, 1, Fill::random);
    bias_ho = Matrix(o_nodes, 1, Fill::random);

    // SETTING WEIGHTS
    weight_ih = Matrix(hidden_nodes, input_nodes, Fill::random);
    weight_ho = Matrix(output_nodes, hidden_nodes, Fill::random);
}

void BrainNetwork::feed_foward(Matrix input){
    // INPUT TO HIDDEN
    input.display();
    weight_ih.display();
    Matrix hidden = input;
    hidden.multiply(weight_ih);
    hidden.add(bias_ih);
    hidden.display();
    // for (int i = 0; i < bias_ih.size(); i++) {
    //     hidden.push_back(bias_ih.at(i));
    // }
    // hidden = sigmoid()

    // HIDDEN TO OUTPUT
    

}

int main(){
    BrainNetwork b = BrainNetwork(3,1,3);
    Matrix input = Matrix(2, 1, Fill::input_values);
    b.feed_foward(input);
    
    return 0;
}