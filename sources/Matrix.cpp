#include "Matrix.hpp"

using namespace std;

namespace zich
{
    Matrix::Matrix(const vector<double> &matrix, const int row, const int col)
    {
        if (row <= 0 || col <= 0 || matrix.size() != row * col)
        {
            throw invalid_argument("Please make sure that Matrix dimensions are positive and the dimensions match the vector size");
        }
        this->matrix = matrix;
        this->row = (size_t)row;
        this->col = (size_t)col;
    }

    Matrix::~Matrix() {}

    bool Matrix::check_valid_mat(const Matrix &other_matrix) const
    {
        if (this->row != other_matrix.row || this->col != other_matrix.col)
        {
            throw invalid_argument("Please make sure the Matrices have the same dimensions");
        }
        return true;
    }

    double Matrix::sum_of_matrix() const
    {
        double sum = 0;
        for (size_t i = 0; i < this->row * this->col; i++)
        {
            sum += this->matrix[i];
        }
        return sum;
    }

    // Plus operators
    Matrix Matrix::operator+(const Matrix &other_matrix)
    {
        check_valid_mat(other_matrix);

        vector<double> result;

        for (size_t i = 0; i < this->row * this->col; i++)
        {
            result.push_back(this->matrix[i] + other_matrix.matrix[i]);
        }
        return Matrix(result, this->row, this->col);
    }

    Matrix &Matrix::operator+=(const Matrix &other_matrix)
    {
        check_valid_mat(other_matrix);

        for (size_t i = 0; i < this->row * this->col; i++)
        {
            this->matrix[i] += other_matrix.matrix[i];
        }
        return *this;
    }

    Matrix &Matrix::operator++()
    {
        for (size_t i = 0; i < this->row * this->col; i++)
        {
            this->matrix[i]++;
        }
        return *this;
    }

    Matrix Matrix::operator++(int num)
    {
        Matrix result = *this;

        for (size_t i = 0; i < this->row * this->col; i++)
        {
            this->matrix[i]++;
        }
        return result;
    }

    Matrix operator+(Matrix &mat)
    {
        return mat;
    }

    // Minus operators
    Matrix Matrix::operator-(const Matrix &other_matrix)
    {
        check_valid_mat(other_matrix);

        vector<double> result;

        for (size_t i = 0; i < this->row * this->col; i++)
        {
            result.push_back(this->matrix[i] - other_matrix.matrix[i]);
        }
        return Matrix(result, this->row, this->col);
    }

    Matrix &Matrix::operator-=(const Matrix &other_matrix)
    {
        check_valid_mat(other_matrix);

        for (size_t i = 0; i < this->row * this->col; i++)
        {
            this->matrix[i] -= other_matrix.matrix[i];
        }
        return *this;
    }

    Matrix &Matrix::operator--()
    {
        for (size_t i = 0; i < this->row * this->col; i++)
        {
            this->matrix[i]--;
        }
        return *this;
    }

    Matrix Matrix::operator--(int num)
    {
        Matrix result = *this;

        for (size_t i = 0; i < this->row * this->col; i++)
        {
            this->matrix[i]--;
        }
        return result;
    }

    Matrix operator-(Matrix &mat)
    {
        return mat * -1;
    }

    // Comperations operators
    bool Matrix::operator>(const Matrix &other_matrix) const
    {
        check_valid_mat(other_matrix);
        return (*this).sum_of_matrix() > other_matrix.sum_of_matrix();
    }

    bool Matrix::operator>=(const Matrix &other_matrix) const
    {
        check_valid_mat(other_matrix);
        return (*this).sum_of_matrix() >= other_matrix.sum_of_matrix();
    }

    bool Matrix::operator<(const Matrix &other_matrix) const
    {
        check_valid_mat(other_matrix);
        return (*this).sum_of_matrix() < other_matrix.sum_of_matrix();
    }

    bool Matrix::operator<=(const Matrix &other_matrix) const
    {
        check_valid_mat(other_matrix);
        return (*this).sum_of_matrix() <= other_matrix.sum_of_matrix();
    }

    bool Matrix::operator!=(const Matrix &other_matrix) const
    {
        check_valid_mat(other_matrix);

        for (size_t i = 0; i < this->row * this->col; i++)
        {
            if (this->matrix[i] != other_matrix.matrix[i])
            {
                return true;
            }
        }
        return false;
    }

    bool Matrix::operator==(const Matrix &other_matrix) const
    {
        check_valid_mat(other_matrix);

        return !((*this) != other_matrix);
    }

    // Multiplaction operators
    Matrix Matrix::operator*(const double num)
    {
        vector<double> result;

        for (size_t i = 0; i < this->row * this->col; i++)
        {
            result.push_back(this->matrix[i] * num);
        }
        return Matrix(result, this->row, this->col);
    }

    Matrix Matrix::operator*(const Matrix &other_matrix)
    {
        if (this->col != other_matrix.row)
        {
            throw invalid_argument("Make sure that the dimensions are compatible !");
        }

        vector<double> result;

        for (size_t i = 0; i < this->row; i++)
        {
            for (size_t j = 0; j < other_matrix.col; j++)
            {
                double sum = 0;
                for (size_t k = 0; k < this->col; k++)
                {
                    sum += this->matrix[i * this->col + k] * other_matrix.matrix[k * other_matrix.col + j];
                }
                result.push_back(sum);
            }
        }
        return Matrix(result, this->row, other_matrix.col);
    }

    Matrix &Matrix::operator*=(const Matrix &other_matrix)
    {
        *this = (*this) * other_matrix;
        return *this;
    }

    Matrix &Matrix::operator*=(double num)
    {
        *this = (*this) * num;
        return *this;
    }

    Matrix operator*(const double num, Matrix &mat)
    {
        return mat * num;
    }

    // Input and Output operators
    istream &operator>>(istream &input, Matrix &mat)
    {
        vector<double> new_matrix;
        string input_stream;
        int row = 0;
        int col = 0;
        int col_amount = 0;
        int brackets_counter = 0;

        while (getline(input, input_stream))
        {
            for (size_t i = 0; i < input_stream.length(); i++)
            {
                if (input_stream[i] == ']')
                {
                    brackets_counter--;
                    if (brackets_counter < 0)
                    {
                        throw invalid_argument("Check the amount of brackets in the input");
                    }
                }
                else if (input_stream[i] == ' ' || input_stream[i] == ',')
                {
                    if (input_stream[i] == ',')
                    {
                        if (i == 0)
                        {
                            throw invalid_argument("Check the input format");
                        }
                        if (input_stream[i - 1] != ']' || input_stream[i + 1] != ' ')
                        {
                            throw invalid_argument("Check the input format");
                        }
                    }
                    continue;
                }

                else if (input_stream[i] == '[')
                {
                    brackets_counter++;
                    if (brackets_counter > 1)
                    {
                        throw invalid_argument("Check the amount of brackets in the input");
                    }

                    if (col == 0)
                    {
                        col = col_amount;
                    }

                    else if (col != col_amount)
                    {
                        throw invalid_argument("Check the Number of columns because they don't match");
                    }
                    col_amount = 0;

                    row++;
                }

                else if (input_stream[i] >= '0' && input_stream[i] <= '9')
                {
                    string input_number;
                    while (input_stream[i] >= '0' && input_stream[i] <= '9')
                    {
                        input_number += input_stream[i++];
                    }
                    double convert_to_double = stod(input_number);
                    new_matrix.push_back(convert_to_double);

                    col_amount++;
                    i--;
                }
                else
                {
                    throw invalid_argument("Check the input format");
                }
            }
        }
        if (brackets_counter != 0)
        {
            throw invalid_argument("Check the amount of brackets in the input");
        }
        mat = Matrix(new_matrix, row, col);
        return input;
    }

    ostream &operator<<(ostream &output, const Matrix &mat)
    {
        for (size_t i = 0; i < mat.row; i++)
        {
            output << '[';
            for (size_t j = 0; j < mat.col; j++)
            {
                if (j != mat.col - 1)
                {
                    output << mat.matrix[i * mat.col + j] << " ";
                }
                else
                {
                    output << mat.matrix[i * mat.col + j];
                }
            }
            if (i != mat.row - 1)
            {
                output << "]" << endl;
            }
            else
            {
                output << ']';
            }
        }
        return output;
    }
}