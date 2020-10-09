#include <iostream>
#include <vector>
#include <random>

using std::cout;
using std::endl;
using std::vector;
using Matrix = vector<vector<double>>;

std::default_random_engine rng;
std::uniform_real_distribution<double> dist(-1,1);

class BrainNetwork {
    public:
        int i_nodes;
        int h_nodes;
        int o_nodes;
        vector<double> bias_ih;
        vector<double> bias_ho;
        Matrix weight_ih;
        Matrix weight_ho;

    BrainNetwork(int input_nodes, int hidden_nodes, int output_nodes) {
        i_nodes = input_nodes;
        h_nodes = hidden_nodes;
        o_nodes = output_nodes;

        for (int i = 0; i < hidden_nodes; i++) {
            bias_ih.push_back(dist(rng));
            bias_ho.push_back(dist(rng));
        }

        for (int i = 0; i < hidden_nodes; i++) {
            weight_ih.push_back(vector<double>());
            weight_ho.push_back(vector<double>());
            for (int j = 0; j < input_nodes; j++) {
                weight_ih.at(i).push_back(dist(rng));
                weight_ho.at(i).push_back(dist(rng));
            }
        }
    }
};

int main(){
    BrainNetwork b = BrainNetwork(3,3,3);
    
    return 0;
}