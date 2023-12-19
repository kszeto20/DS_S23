#include <iostream>
#include "Matrix.h"

using std::cout; using std::endl;

int main() {

    std::cout << "My testing -----" << endl;

    // constructor testing
    Matrix x = Matrix(6, 10, 12);
    std::cout << x << std::endl; // print testing 

    Matrix y = Matrix(3, 10, 4);
    std::cout << y << std::endl; // print testing
    
    // == overload testing
    if (x == y) {
        std::cout << "they're equal!" << std::endl;
    }
    else {
        std::cout << "not all matricies are the same" << std::endl;
    }
    
    // != overload testing
    x = y;
    
    if (x != y) {
        std::cout << "every matrix is different!" << std::endl;
    }
    else {
        std::cout << "they're the equal!" << std::endl;
    }

    // << overload testing (printing)
    std::cout << x << "\n" << y << std::endl;
    y = Matrix(5, 15, 6);
    std::cout << x << "\n" << y << std::endl;

    // testing GET
    double testing = 0.0;

    // out of bounds cases -- should output 0 until valid test cases 
    x.get(-1, 5, testing);
    std::cout << testing << " ";
    x.get(0, 15, testing);
    std::cout << testing << " ";

    y.get(0, 30, testing);
    std::cout << testing << " ";
    y.get(-1, 9, testing);
    std::cout << testing << " ";

    std::cout << "\n" << std::endl;

    // in bounds - cases
    x.get(2, 8, testing);
    std::cout << testing << " ";
    y.get(4, 1, testing);
    std::cout << testing << " ";

    std::cout << "\n" << std::endl;

    
    // testing SET
    testing = 8.0;
    bool testBool;
    // out of bounds -- will output 0 (false) until valid test case
    testBool = x.set(20, 5, testing);
    std::cout << testBool << " ";
    testBool = x.set(0, 15, testing);
    std::cout << testBool << " ";

    testBool = y.set(0, 40, testing);
    std::cout << testBool << " ";
    testBool = y.set(-1, 9, testing);
    std::cout << testBool << " ";
    
    std::cout << "\n" << std::endl;

    // in bounds
    testBool = x.set(2, 8, testing);
    std::cout << testBool << " ";
    testBool = y.set(3, 1, testing);
    std::cout << testBool << " ";
 
    std::cout << "\n" << std::endl;

    std::cout << x << std::endl;
    std::cout << y << std::endl;

    // testing mult by coefficient

    std::cout << x << std::endl;
    x.multiply_by_coefficient(2);
    std::cout << x << std::endl;

    std::cout << y << std::endl;
    y.multiply_by_coefficient(0.25);
    std::cout << y << std::endl;
   
  
    
    // swap row testing
    for (unsigned int i = 0; i < x.num_cols(); i++) {
        x.set(2, i, 19);
    }

    // out of bounds case -- will print 0 (false) until valid test case
    testBool = x.swap_row(200, 1);
    std::cout << testBool << " ";

    testBool = x.swap_row(1, 200);
    std::cout << testBool << " ";

    std::cout << "\n" << std::endl;

    // in bounds
    std::cout << x << std::endl;
    testBool = x.swap_row(1, 2);
    std::cout << testBool << "\n" << x << std::endl;
    
    // testing transpose
    std::cout << x << std::endl;
    x.transpose();
    std::cout << x << std::endl;
    
    std::cout << y << std::endl;
    y.transpose();
    std::cout << y << std::endl;
    

    
    // get row testing
    double * type;
    // out of bounds
    type = x.get_row(123); 
    if (type == NULL) { std::cout << "this is null." << endl; }

    // in bounds
    type = x.get_row(4);
    for (unsigned int i = 0; i < x.num_cols(); i++) {
        std::cout << type[i] << " ";
    }
    delete [] type;
    std::cout << std::endl;    

    // get coll testing 
    double * type2;

    type2 = x.get_col(123);
    if (type2 == NULL) { std::cout << "this is null." << endl; }

    type2 = x.get_col(2);
    for (unsigned int i = 0; i < x.num_rows(); i++) {
        std::cout << type2[i] << " ";
    }
    delete [] type2;
    std::cout << std::endl;

    // add testing
    std::cout << x << std::endl;
    x.add(y);
    std::cout << x << std::endl;

    std::cout << y << std::endl;
    y.add(x);
    std::cout << y << std::endl;

    // subtract testing
    std::cout << y << std::endl;
    y.subtract(x);
    std::cout << y << std::endl;

    std::cout << x << std::endl;
    x.subtract(y);
    std::cout << x << std::endl;

    // quarter testing
    double counter = 0;
    Matrix big = Matrix(21, 11, 4);
    for (unsigned int i = 0; i < big.num_rows(); i++) {
        for (unsigned int j = 0; j < big.num_cols(); j++) {
            big.set(i,j, counter);
            counter++;
        }
    }

    Matrix * quarters = big.quarter();
    std::cout << quarters[0] << std::endl;
    std::cout << quarters[1] << std::endl;
    std::cout << quarters[2] << std::endl;
    std::cout << quarters[3] << std::endl;

    delete [] quarters;

    // testing resize
    std::cout << "size up\n" << x << std::endl;
    x.resize(10, 10, 100);
    std::cout << x << std::endl;

    std::cout << "size down\n" << x << std::endl;
    x.resize(0, 0, 100);
    std::cout << x << std::endl;

    
}