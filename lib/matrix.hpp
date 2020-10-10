#include <vector>

using std::vector;

enum Fill { random, input_values, zero };

class Matrix {
    private:
        vector<vector<double>> matrix;
    
    public:
        Matrix();
        Matrix(unsigned int rows, unsigned int columns, Fill fill);
        Matrix(unsigned int rows, unsigned int columns) : Matrix(rows, columns, Fill::zero){};
        void multiply(Matrix&);
        void display();
};