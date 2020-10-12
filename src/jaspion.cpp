#include <iostream>
#include <cstdlib>
#include <vector>
#include <chrono>
#include "../lib/brain_network.hpp"

using std::vector;
using std::endl;
using std::cin;
using std::cout;
using raw_matrix = vector<vector<double>>;

const long GENERATIONS = 10'000;
const double MIN_ERROR = 0.01;
const double MAX_ERROR = 0.99;

int main(){
    // SETUP TRAINING
    // NETWORK
    BrainNetwork b = BrainNetwork(2,3,1);
    bool train = true;

    // INPUTS
    raw_matrix input_0_0 {
	    { 0 },
        { 0 }
    };
    Matrix i00 = Matrix(input_0_0);
    raw_matrix input_0_1 {
	    { 0 },
        { 1 }
    };
    Matrix i01 = Matrix(input_0_1);
    raw_matrix input_1_0 {
	    { 1 },
        { 0 }
    };
    Matrix i10 = Matrix(input_1_0);
    raw_matrix input_1_1 {
	    { 1 },
        { 1 }
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

    char opt;
    cout << "INSERIR NUMERO DE GERACOES MANUALMENTE? (s/n): ";
    cin >> opt;

    auto start = std::chrono::high_resolution_clock::now();
    if (opt == 's') {
        long num_generations = 0;
        cout << "NUMERO DE GERACOES: ";
        cin >> num_generations;
        start = std::chrono::high_resolution_clock::now();
        cout << "TREINANDO A REDE NEURAL..." << endl;
        for (int i = 0; i < num_generations; i++) {
            int e = std::rand() % 4;
            b.train(input[e], output[e]);
        }
        cout << "FIM DO TREINAMENTO. (Geracoes: " << num_generations << ")" << endl;
    }
    else if(opt == 'n') {
        start = std::chrono::high_resolution_clock::now();
        cout << "TREINANDO A REDE NEURAL..." << endl;
        int train_count = 0;
        while (train) {
            for (int i = 0; i < GENERATIONS; i++) {
                int e = std::rand() % 4;
                b.train(input[e], output[e]);
            }
            train_count++;

            // BREAK POINT
            auto result1 = b.predict(input[0]).get().at(0).at(0);
            auto result2 = b.predict(input[1]).get().at(0).at(0);
            if (result1 < MIN_ERROR && result2 > MAX_ERROR)
            {
                train = false;
                cout << "FIM DO TREINAMENTO. (Geracoes: " << GENERATIONS * train_count << ")" << endl;
            }

        }
    }
    else {
        return 0;
    }


    // LOG RESULTS
    cout << "--------------OPERACOES XOR--------------" << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << endl;
        cout << "CASO " << i + 1 << ": " << endl;
        input[i].display();
        cout << "ESPERADO: " << output[i].get().at(0).at(0) << endl;
        cout << "RESULTADO: " << b.predict(input[i]).get().at(0).at(0) << endl;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    cout << endl;
    cout << "TEMPO DE EXECUCAO: " << duration.count() << "ms" << endl;

    return 0;
}