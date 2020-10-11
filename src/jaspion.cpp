#include <iostream>
#include <cstdlib>
#include <vector>
#include "../lib/brain_network.hpp"

using std::vector;
using std::endl;
using std::cout;
using raw_matrix = vector<vector<double>>;

const int GENERATIONS = 10000;

int main(){
    // SETUP TRAINING
    // NETWORK
    BrainNetwork b = BrainNetwork(2,3,1);
    bool train = true;

    // INPUTS
    raw_matrix input_0_0 {
	    { 0, 0 }
    };
    Matrix i00 = Matrix(input_0_0);
    raw_matrix input_0_1 {
	    { 0, 1 }
    };
    Matrix i01 = Matrix(input_0_1);
    raw_matrix input_1_0 {
	    { 1, 0 }
    };
    Matrix i10 = Matrix(input_1_0);
    raw_matrix input_1_1 {
	    { 1, 1 }
    };
    Matrix i11 = Matrix(input_1_1);
    Matrix input[4] = {i00, i01, i10, i11};

    // OUTPUTS
    raw_matrix output_0_0 {
	    { 0 }
    };
    Matrix o00 = Matrix(output_0_0);
    raw_matrix output_0_1 {
	    { 1 }
    };
    Matrix o01 = Matrix(output_0_1);
    raw_matrix output_1_0 {
	    { 1 }
    };
    Matrix o10 = Matrix(output_1_0);
    raw_matrix output_1_1 {
	    { 0 }
    };
    Matrix o11 = Matrix(output_1_1);
    Matrix output[4] = {o00, o01, o10, o11};

    // EXECUTE TRAINING
    while (train)
    {
        for (int i = 0; i < GENERATIONS; i++)
        {
            int e = std::rand() % 4;
            b.train(input[e], output[e]);
        }
        if (b.predict(input[0]).get().at(0) < 0.04 && b.predict(input[1]).get().at(0) > 0.98 )
        {
            train = false;
            cout << "FIM DO TREINAMENTO." << endl;
        }
    }

    return 0;
}