#include <vector>

using std::vector;

using uint = unsigned int;

enum Fill { random, input_values, zero };

class Matrix {
    private:
        vector<vector<double>> matrix;
    
    public:
        Matrix();
        Matrix(vector<vector<double>>);
        Matrix(uint rows, uint columns, Fill fill);
        Matrix(uint rows, uint columns) : Matrix(rows, columns, Fill::zero){};
        vector<vector<double>> get();
        void multiply(Matrix&);
        void escalar_multiply(double);
        void add(Matrix&);
        void subtract(Matrix&);
        void hadamarp(Matrix&);
        void sigmoid();
        void d_sigmoid();
        void transpose();
        void display();
        uint cols();
        uint rows();
};