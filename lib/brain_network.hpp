#include "../lib/matrix.hpp"

class BrainNetwork {
    public:
        BrainNetwork(int, int, int);
        int i_nodes;
        int h_nodes;
        int o_nodes;
        Matrix bias_ih;
        Matrix bias_ho;
        Matrix weights_ih;
        Matrix weights_ho;
        double learning_rate;
        void train(Matrix, Matrix);
        Matrix predict(Matrix);
};