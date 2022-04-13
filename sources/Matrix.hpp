#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

namespace zich
{
    class Matrix
    {
    private:
        size_t row, col;
        vector<double> matrix;
        double sum_of_matrix() const;

    public:
        Matrix(const vector<double> &matrix, const int row, const int col);
        ~Matrix();

        // Boolean function that checks if the other mat is good
        bool check_valid_mat(const Matrix &other_matrix) const;

        // Plus operators
        Matrix operator+(const Matrix &other_matrix);
        Matrix &operator+=(const Matrix &other_matrix);
        Matrix &operator++();
        Matrix operator++(const int num);
        friend Matrix operator+(Matrix &mat);

        // Minus operators
        Matrix operator-(const Matrix &other_matrix);
        Matrix &operator-=(const Matrix &other_matrix);
        Matrix &operator--();
        Matrix operator--(const int num);
        friend Matrix operator-(Matrix &mat);

        // Comperations operators
        bool operator>(const Matrix &other_matrix) const;
        bool operator>=(const Matrix &other_matrix) const;
        bool operator<(const Matrix &other_matrix) const;
        bool operator<=(const Matrix &other_matrix) const;
        bool operator!=(const Matrix &other_matrix) const;
        bool operator==(const Matrix &other_matrix) const;

        // Multiplaction operators
        Matrix operator*(const double num);
        Matrix operator*(const Matrix &other_matrix);
        Matrix &operator*=(const Matrix &other_matrix);
        Matrix &operator*=(const double num);
        friend Matrix operator*(const double num, Matrix &mat);

        // Input and Output operators
        friend istream &operator>>(istream &input, Matrix &mat);
        friend ostream &operator<<(ostream &output, const Matrix &mat);
    };
}