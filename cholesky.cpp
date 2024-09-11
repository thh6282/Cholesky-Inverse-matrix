#include<iostream>
#include<math.h>
#include <fstream>
using namespace std;

struct p {
    double re; // real part
    double im; // imaginary part
};

// Operator overloading for addition of complex numbers
p operator +(p a, p b) {
    p c;
    c.re = a.re + b.re;
    c.im = a.im + b.im;
    return c;
};

// Operator overloading for subtraction of complex numbers
p operator -(p a, p b) {
    p c;
    c.re = a.re - b.re;
    c.im = a.im - b.im;
    return c;
};

// Operator overloading for multiplication of complex numbers
p operator *(p a, p b) {
    p c;
    c.re = a.re * b.re - a.im * b.im;
    c.im = a.re * b.im + a.im * b.re;
    return c;
};

// Operator overloading for division of complex numbers
p operator/(p b, p a) {
    p c;
    c.re = (a.re * b.re + a.im * b.im) / (pow(a.re, 2) + pow(a.im, 2));
    c.im = (a.re * b.im - a.im * b.re) / (pow(a.re, 2) + pow(a.im, 2));
    return c;
}

// Function to check if a matrix is symmetric (with real parts)
bool is_symmetric(p a[15][15], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (a[i][j].re != a[j][i].re)
                return false;
    return true;
}

// Function to convert matrix to upper triangular matrix using Cholesky decomposition
void upper_triangular(p a[15][15], p b[15][15], int n) { 
    int i, j, k;
    b[0][0].re = sqrt(a[0][0].re);
    
    for (i = 1; i < n; i++)
        b[0][i].re = a[0][i].re / b[0][0].re;

    for (i = 1; i < n; i++) {
        p z;
        z.re = 0;
        z.im = 0;

        for (k = 0; k < i; k++) {
            z = z + b[k][i] * b[k][i];
        }

        if ((a[i][i].re - z.re) < 0)
            b[i][i].im = sqrt(z.re - a[i][i].re);
        else
            b[i][i].re = sqrt(a[i][i].re - z.re);

        if (b[i][i].im == 0 && b[i][i].re == 0) {
            cout << "Matrix is not invertible\n\n";
            break;
        }

        for (j = i + 1; j < n; j++) {
            p z;
            z.re = 0;
            z.im = 0;

            for (k = 0; k < i; k++) {
                z = z + b[k][i] * b[k][j];
            }
            b[i][j] = (a[i][j] - z) / b[i][i];
        }
    }
}

// Function to calculate the inverse of the matrix
void inverse_matrix(p b[15][15], p b1[15][15], int n) {
    int i, j, k;

    for (i = 0; i < n; i++) {
        p x;
        x.re = 1;
        b1[i][i] = x / b[i][i];
    }

    for (j = 1; j < n; j++)
        for (i = 0; i < j; i++) {   
            p x;
            x.re = -1;
            p z;
            z.im = 0;
            z.re = 0;

            for (k = 0; k < j; k++) {
                z = z + b1[i][k] * b[k][j];
            }
            b1[i][j] = x * (z / b[j][j]);
        }
}

// Function to transpose the matrix
void transpose(p b1[15][15], p bt[15][15], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            bt[i][j] = b1[j][i];
}

// Function to multiply two matrices
void multiply_matrices(p b1[15][15], p bt[15][15], p c[15][15], int n) {
    for (int h = 0; h < n; h++) {
        for (int k = 0; k < n; k++) { 
            c[h][k].im = 0;
            c[h][k].re = 0;

            for (int i = 0; i < n; i++) {
                c[h][k] = b1[h][i] * bt[i][k] + c[h][k];
            }
        }
    }
}

// Function to print the matrix
void print_matrix(p c[15][15], int n) {
    for (int i = 0; i < n; i++) {    
        for (int j = 0; j < n; j++)
            cout << c[i][j].re << "\t";
        cout << endl;
    }
}

// Function to print a matrix of complex numbers
void print_complex_matrix(p c[15][15], int n) {
    for (int i = 0; i < n; i++) {    
        for (int j = 0; j < n; j++)
            cout << c[i][j].re << "+" << c[i][j].im << "i\t";
        cout << endl;
    }
}

// Function to read matrix from file
void read(int &n, p a[15][15]) {   
    ifstream f("C:/Users/DELL 5584/Desktop/input.txt");
    f >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            f >> a[i][j].re;
    }
    f.close();     
}   

// Main function
int main() {
    p a[15][15];
    int n;
    read(n, a);

    if (is_symmetric(a, n)) {
        p b[15][15], b1[15][15], bt[15][15], a1[15][15];
        upper_triangular(a, b, n);
        inverse_matrix(b, b1, n);
        transpose(b1, bt, n);
        multiply_matrices(b1, bt, a1, n);
        
        cout << "Upper triangular matrix is\n" << endl;
        print_complex_matrix(b, n);
        
        cout << "\nInverse matrix is\n" << endl;
        print_matrix(a1, n);
    } else {
        p at[15][15], b[15][15], b2[15][15], b3[15][15], bt[15][15], b1[15][15], a1[15][15];
        transpose(a, at, n);
        multiply_matrices(at, a, b, n);
        upper_triangular(b, b2, n);
        inverse_matrix(b2, b3, n);
        transpose(b3, bt, n);
        multiply_matrices(b3, bt, b1, n);
        multiply_matrices(b1, at, a1, n);
        
        cout << "Upper triangular matrix is\n" << endl;
        print_complex_matrix(b2, n);
        
        cout << "\nInverse matrix is\n" << endl;
        print_matrix(a1, n);
    }
}
