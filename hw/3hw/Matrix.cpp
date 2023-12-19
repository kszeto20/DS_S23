#include <iostream>
#include "Matrix.h"

using std::cout; using std::endl;

Matrix::Matrix() { // default constructor
    rows = 0;
    cols = 0;

    data = new double * [rows];

    for (unsigned int i = 0; i < rows; i++) {
        data[i] = new double [cols];
        for (unsigned int j = 0; j < cols; j++) {
            data[i][j] = 0.0;
        }
    }

}

Matrix::Matrix(const Matrix& n) { // copy constructor

    rows = n.num_rows();
    cols = n.num_cols();

    data = new double * [rows];
    double toRep;

    for (unsigned int i = 0; i < rows; i++) {
        data[i] = new double[cols];
        for (unsigned int j = 0; j < cols; j++) {
            n.get(i, j, toRep);
            data[i][j] = toRep;
        }
    }
}


Matrix::Matrix(unsigned int r, unsigned int c, double fVal) { // normal constructor
    rows = r;
    cols = c;
    if (r <= 0 || c <= 0) { // 0 checking 
        rows = 0;
        cols = 0;
    }
    data = new double * [r];

    for (unsigned int i = 0; i < r; i++) {
        data[i] = new double [c];
        for (unsigned int j = 0; j < c; j++) {
            data[i][j] = fVal;
        }
    }
}

Matrix::~Matrix() {
    clear();
}

bool Matrix::get(unsigned int r, unsigned int c, double& val) const {
    if ((r >= rows) || (c >= cols)) { 
        return false;
    }
    val = data[r][c]; // get value and store it back into val
    return true;
}

double* Matrix::get_row(unsigned int r) {
    double* toRet { nullptr };
    if (r >= rows) {
        return toRet;
    }
    toRet = new double [cols];
    for (unsigned int i = 0; i < cols; i++) {
        toRet[i] = data[r][i]; // go through each row; at specified col add value to toRet array
    }
    return toRet;
}

double * Matrix::get_col(unsigned int c) {
    double* toRet { nullptr };
    if (c >= cols) {
        return toRet;
    }

    toRet = new double [rows];
    for (unsigned int i = 0; i < rows; i++) {
        toRet[i] = data[i][c]; // go through each col; at specified row add value to toRet vector
    }
    return toRet;
}

void Matrix::clear() { // all the delete statements for heap variables
    for (unsigned int i = 0; i < rows; i++) {
        delete [] data[i];
    }
    rows = 0;
    cols = 0;
    delete [] data;
}

bool Matrix::set(unsigned int r, unsigned int c, double val) {
    if ((r >= rows) || (c >= cols)) {
        return false;
    }
    data[r][c] = val; // set value at index to provided value
    return true;

}

void Matrix::multiply_by_coefficient(double factor) {
    double toChange = 0.0;
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < cols; j++) { // for each index
            toChange = data[i][j];
            data[i][j] = (toChange * factor); // multiply the value by the given factor
        }
    }
}

bool Matrix::swap_row(unsigned int source, unsigned int target) {
    if ((source >= rows) || (target >= rows)) {
        return false;
    }
    double * temp = data[source]; // temp variable to hold original values of source
    data[source] = data[target]; // switch original to target
    data[target] = temp; // reassign target values to temp values
    return true;
}

void Matrix::transpose() { // flip rows and cols and reassign values
    double ** newM = new double * [cols]; // create new data table with correct dimensions
    for (unsigned int j = 0; j < cols; j++) {
        newM[j] = new double [rows];
        for (unsigned int i = 0; i < rows; i++) {
            newM[j][i] = data[i][j];
        }
    }

    for (unsigned int i = 0; i < rows; i++) { // clear existing data
        delete [] data[i];
    }
    delete [] data;

    // assigned attributes to the new variables
    int oldR = rows;
    rows = cols;
    cols = oldR;

    data = newM;   
    
}

bool Matrix::add(const Matrix& B) {
    if (rows != B.num_rows() || cols != B.num_cols()) {
        return false;
    }

    double ** bData = B.get_data();

    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < cols; j++) {
            data[i][j] += bData[i][j]; // add value at corresponding index to original index
        }
    }
    return true;

}

bool Matrix::subtract(const Matrix& B) {
    if (rows != B.num_rows() || cols != B.num_cols()) {
        return false;
    }

    double ** bData = B.get_data();

    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < cols; j++) {
            data[i][j] -= bData[i][j]; // subtract value at corresponding index to the original index
        }
    }
    return true;   
}


void Matrix::operator= (const Matrix& n) { // = operator (like copy constructor)
    clear();

    rows = n.num_rows();
    cols = n.num_cols();

    double toRep;
    data = new double * [rows];

    for (unsigned int i = 0; i < rows; i++) {
        data[i] = new double[cols];
        for (unsigned int j = 0; j < cols; j++) {
            n.get(i, j, toRep);
            data[i][j] = toRep;
        }
    }   

}


Matrix* Matrix::quarter() { // quarter function
    Matrix * toRet = new Matrix[4];
    unsigned int quadRows, quadCols; // dimensions for quadrants
    quadRows = rows / 2;
    quadCols = cols / 2;

    if (rows % 2 != 0) { // if odd add one to dimension
        quadRows++;
    }

    if (cols % 2 != 0) { // if odd add one to dimension
        quadCols++;
    }

    for (int i = 0; i < 4; i++) {
        // if statement for each case
        Matrix newM = Matrix(quadRows, quadCols, 0.0);
        if (i == 0) { // quadrant one
            for (unsigned int j = 0; j < quadRows; j++) { // (row 0 - quadrows)
                for (unsigned int k = 0; k < quadCols; k++) { //(col 0 to quadcols)
                    newM.set(j, k, data[j][k]);
                }
            }
        } 
        else if (i == 1) { // quadrant two 
            int rowcounter = 0; // row for subquadrant indexing 
            int colcounter = 0; // col for subquadrant indexing 
            for (unsigned int j = 0; j < quadRows; j++) { // (row 0 to quadrows)
                for (unsigned int k = cols -  quadCols; k < cols; k++) { // (col quadCol to maxcol)
                    newM.set(rowcounter, colcounter, data[j][k]);
                    colcounter++;
                }
                rowcounter++;
                colcounter = 0;
            }
        }
        else if (i == 2) {
            int rowcounter = 0; // row for subquadrant indexing 
            int colcounter = 0; // col for subquadrant indexing 
            for (unsigned int j = rows - quadRows; j < rows; j++) { // row (quadrow to maxrow)
                for (unsigned int k = 0; k < quadCols; k++) { // col (0 to quadcol)
                    newM.set(rowcounter, colcounter, data[j][k]);
                    colcounter++;
                }
                rowcounter++;
                colcounter = 0;
            }
        }
        else if (i == 3) {
            int rowcounter = 0; // row for subquadrant indexing 
            int colcounter = 0; // col for subquadrant indexing 
            for (unsigned int j = rows - quadRows; j < rows; j++) { // (row quadrow to maxrow)
                for (unsigned int k = cols -  quadCols; k < cols; k++) { // (col quadcol to maxcol)
                    newM.set(rowcounter, colcounter, data[j][k]);
                    colcounter++;
                }
                rowcounter++;
                colcounter = 0;
            }
        }

        toRet[i] = newM; // assign to new array of matricies
    }
    return toRet; // return new array

}

void Matrix::resize(unsigned int r, unsigned int c, double fVal) {
    unsigned int newRows = r; 
    unsigned newCols = c;

    if (r == 0 || c == 0) { // check for 0 parameters
        newRows = 0;
        newCols = 0;
    }
    double ** tempD = new double * [newRows]; // create temp data table
    double toRep;

    for (unsigned int i = 0; i < newRows; i++) {
        tempD[i] = new double[newCols]; 
        for (unsigned int j = 0; j < newCols; j++) {
            if (i >= rows || j >= cols) { // if desired index is bigger than existing index
                toRep = fVal; // replace toRep (replacement value) with fill value 
            }
            else {
                toRep = data[i][j]; // if within existing index -- toRep val = data at that index
            }
            tempD[i][j] = toRep; // replace data
        }
    }

    for (unsigned int i = 0; i < rows; i++) { // clear existing data
        delete [] data[i];
    }
    delete [] data;

    data = tempD; // reassign data to newly created data table

    rows = newRows; // update row count
    cols = newCols; // update col count
}



bool operator== (const Matrix& a, const Matrix& b) {
    unsigned int aRows = a.num_rows();
    unsigned int aCols = a.num_cols();

    if (aRows != b.num_rows() || aCols != b.num_cols()) {
        return false;
    }

    double ** aData = a.get_data();
    double ** bData = b.get_data();

    for (unsigned int i = 0; i < aRows; i++) {
        for (unsigned int j = 0; j < aCols; j++) {
            if (aData[i][j] != bData[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool operator!= (const Matrix& a, const Matrix& b) {
    unsigned int aRows = a.num_rows();
    unsigned int aCols = a.num_cols();

    if (aRows != b.num_rows() || aCols != b.num_cols()) {
        return true;
    }

    double ** aData = a.get_data();
    double ** bData = b.get_data();

    for (unsigned int i = 0; i < aRows; i++) {
        for (unsigned int j = 0; j < aCols; j++) {
            if (aData[i][j] != bData[i][j]) {
                return true;
            }
        }
    }
    return false;
}

std::ostream& operator<< (std::ostream& out, const Matrix& m) {
    cout << m.num_rows() << " x " << m.num_cols() << " matrix:" << endl;
    double value = 0.0;
    out << "[ ";
    for (unsigned int i = 0; i < m.num_rows(); i++) {
        if (i != 0) {
            out << "  ";
        }
        for (unsigned int j = 0; j < m.num_cols(); j++) {
            m.get(i, j, value);
            
            out << value << " ";
        }
        if (i != m.num_rows() - 1) {
            out << endl;
        }
    }
    out << "]" << endl;
    return out;
}