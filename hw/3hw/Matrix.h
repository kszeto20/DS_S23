#ifndef __matrix_h
#define __matrix_h

#include <iostream>

class Matrix {
    public:

    Matrix();
    Matrix(const Matrix& n);
    Matrix(unsigned int r, unsigned int c, double fVal);
    ~Matrix();

    // accessors
    double ** get_data() const { return data; }
    unsigned int num_rows() const { return rows; }
    unsigned int num_cols() const { return cols; }
    bool get(unsigned int r, unsigned int c, double& val) const;
    double * get_row(unsigned int r);
    double * get_col(unsigned int c);

    // modifiers
    void clear();
    bool set(unsigned int r, unsigned int c, double val);

    // matrix operations
    void multiply_by_coefficient(double factor);
    bool swap_row(unsigned int source, unsigned int target);
    void transpose();
    bool add(const Matrix& B);
    bool subtract(const Matrix& B);
    Matrix* quarter();
    void resize(unsigned int r, unsigned int c, double fVal);

    // = operator overload
    void operator= (const Matrix& n);

    private:
    unsigned int rows;
    unsigned int cols;
    double ** data;
};

bool operator== (const Matrix& a, const Matrix& b);
bool operator!= (const Matrix& a, const Matrix& b);
std::ostream& operator<< (std::ostream& out, const Matrix& m);

#endif
