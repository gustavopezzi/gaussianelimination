#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

void printMatrix(int N, float A[20][21]) {
    cout << "MATRIX:" << endl;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= N; j++) {
            cout << "[" << A[i][j] << "]\t";
        }  
        cout << endl;
    }
    cout << endl;
}

/*
 * param N is the number of unknowns
 * param A is the matrix with coefficients and constants
 */
int gauss(int N, float A[20][21], float r[20]) {
    float multiplier, divider;
    bool fin = false;
    
    printMatrix(N, A);

    // forward substitution
    for (int m = 0; m <= N; m++) {
        for (int i = m + 1; i <= N; i++) {
            multiplier = A[i][m]; 
            divider = A[m][m]; 
            
            if (divider == 0)
                return 1;
            
            for (int j = m; j <= N; j++) {
                if (i == N) {
                    break;
                    fin = true;
                }

                A[i][j] = (A[m][j] * multiplier / divider) - A[i][j];
            }
            
            for (int j = m; j <= N; j++)
                A[i - 1][j] = A[i - 1][j] / divider;
            
            if (fin)
                break;
        }
    }
    
    // back substitution
    float s = 0;
    r[N-1] = A[N-1][N];
    int y = 0;
    for (int i = N - 2; i >= 0; i--) {
        s = 0;
        y++;
        
        for (int x = 0; x < N; x++) {
            s = s + (A[i][N - 1 - x] * r[N - (x + 1)]);
            
            if (y == x + 1)
                break;
        }
        
        r[i] = A[i][N] - s;
    }  
}

int main(int argc, char** argv) {
    float A[20][21];
    float X[20];
    bool err;

    // EXAMPLE 1:
    // |  2x +y -z  =   8 |
    // | -3x -y +2z = -11 |
    // | -2x +y +2z =  -3 |
    A[0][0] =  2;    A[0][1] =  1;   A[0][2] = -1;   A[0][3] =   8;
    A[1][0] = -3;    A[1][1] = -1;   A[1][2] =  2;   A[1][3] = -11; 
    A[2][0] = -2;    A[2][1] =  1;   A[2][2] =  2;   A[2][3] =  -3; 

    // EXAMPLE 2:
    // |  2x  +y -3z =  -1 |
    // |  -x -3y +2z =  12 |
    // | -2x  +y -3z =   0 |
    // A[0][0] =  2;    A[0][1] =  1;   A[0][2] = -3;   A[0][3] =   -1;
    // A[1][0] = -1;    A[1][1] =  3;   A[1][2] =  2;   A[1][3] =   12; 
    // A[2][0] =  3;    A[2][1] =  1;   A[2][2] = -3;   A[2][3] =    0; 


    gauss(3, A, X);
    
    cout << "SOLUTION:" << endl;
    
    for (int i = 0; i < 3; i++)
        cout << "[" << X[i] << "] ";

    return 0;
}