#include <iostream>
#include <vector>

using namespace std;

void inputMatrix(vector<vector<int>>& matrix, int rows, int cols) {
    cout << "Enter the elements of the matrix:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> matrix[i][j];
        }
    }
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> multiplyMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B, int rowsA, int colsA, int colsB) {
    vector<vector<int>> C(rowsA, vector<int>(colsB, 0));

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

int main() {
    int rowsA, colsA, rowsB, colsB;

    cout << "Enter the number of rows and columns for the first matrix: ";
    cin >> rowsA >> colsA;

    vector<vector<int>> A(rowsA, vector<int>(colsA));
    inputMatrix(A, rowsA, colsA);

    cout << "Enter the number of rows and columns for the second matrix: ";
    cin >> rowsB >> colsB;

    if (colsA != rowsB) {
        cout << "Error: Number of columns in the first matrix must be equal to the number of rows in the second matrix for multiplication." << endl;
        return 1;
    }

    vector<vector<int>> B(rowsB, vector<int>(colsB));
    inputMatrix(B, rowsB, colsB);

    vector<vector<int>> C = multiplyMatrices(A, B, rowsA, colsA, colsB);

    cout << "Product matrix is:" << endl;
    printMatrix(C);

    return 0;
}