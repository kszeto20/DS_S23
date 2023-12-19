#include <iostream>
#include<cmath>

using std::cout; using std::endl;

void compute_squares (unsigned int a[], unsigned int b[], const int n) {
    unsigned int * a_ptr;
    unsigned int * b_ptr = b;

    for (a_ptr = a; a_ptr < a + n; a_ptr++, b_ptr++) {
        *b_ptr = pow(*a_ptr, 2);
    }

}

int main() {
    /*
    unsigned int one[5] = {1, 2, 3, 4, 5};
    unsigned int two[5];
    int size = 5;
    */
    
    unsigned int one[10] = {5, 4, 3, 2, 1, 1, 2, 3, 4, 5};
    unsigned int two[10];
    int size = 10;
    
    
    // unsigned int one[6] = {12, 10, 5, 3, 2, 8};
    // unsigned int two[6];
    // int size = 6;
    

    compute_squares (one, two, size);

    for (int i = 0; i < size; i++) {
        cout << two[i] << endl;
    }

    return 0;
}

