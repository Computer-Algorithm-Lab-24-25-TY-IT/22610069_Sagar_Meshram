#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Function to multiply two matrices
vector<vector<int>> multiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int rowsB = B.size();
    int colsB = B[0].size();

    if (colsA != rowsB) {
        throw invalid_argument("Incompatible matrices for multiplication.");
    }

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

// Recursive function to multiply matrices based on the optimal order
vector<vector<int>> recursiveMultiply(const vector<vector<vector<int>>>& matrices, const vector<vector<int>>& splits, int start, int end) {
    if (start == end) {
        return matrices[start];
    }

    vector<vector<int>> leftResult = recursiveMultiply(matrices, splits, start, splits[start][end]);
    vector<vector<int>> rightResult = recursiveMultiply(matrices, splits, splits[start][end] + 1, end);
    return multiply(leftResult, rightResult);
}

// Function to find the minimum number of scalar multiplications needed
pair<vector<vector<int>>, vector<vector<int>>> findOptimalOrder(const vector<int>& dims) {
    int numMatrices = dims.size() - 1;
    vector<vector<int>> minCost(numMatrices, vector<int>(numMatrices, numeric_limits<int>::max()));
    vector<vector<int>> splitPoints(numMatrices, vector<int>(numMatrices, 0));

    for (int i = 0; i < numMatrices; ++i) {
        minCost[i][i] = 0;
    }

    for (int len = 2; len <= numMatrices; ++len) {
        for (int i = 0; i < numMatrices - len + 1; ++i) {
            int j = i + len - 1;
            for (int k = i; k < j; ++k) {
                int cost = minCost[i][k] + minCost[k + 1][j] + dims[i] * dims[k + 1] * dims[j + 1];
                if (cost < minCost[i][j]) {
                    minCost[i][j] = cost;
                    splitPoints[i][j] = k;
                }
            }
        }
    }
    return make_pair(minCost, splitPoints);
}

// Function to print a matrix
void displayMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

// Function to print the optimal parenthesization of the matrix chain
void displayOptimalParenthesization(const vector<vector<int>>& splits, int start, int end, char& matrixName) {
    if (start == end) {
        cout << matrixName++;
        return;
    }
    cout << "(";
    displayOptimalParenthesization(splits, start, splits[start][end], matrixName);
    displayOptimalParenthesization(splits, splits[start][end] + 1, end, matrixName);
    cout << ")";
}

int main() {
    int matrixCount;
    cout << "Enter the number of matrices in the chain: ";
    cin >> matrixCount;

    vector<int> dimensions(matrixCount + 1);
    cout << "Enter the dimensions of the matrices (format: p0 p1 p2 ... pn):" << endl;
    for (int i = 0; i <= matrixCount; ++i) {
        cin >> dimensions[i];
    }

    vector<vector<vector<int>>> matrices(matrixCount);
    for (int i = 0; i < matrixCount; ++i) {
        cout << "Enter the elements of matrix " << i + 1 << " (" << dimensions[i] << "x" << dimensions[i + 1] << "):" << endl;
        matrices[i].resize(dimensions[i], vector<int>(dimensions[i + 1]));
        for (int r = 0; r < dimensions[i]; ++r) {
            for (int c = 0; c < dimensions[i + 1]; ++c) {
                cin >> matrices[i][r][c];
            }
        }
    }

    pair<vector<vector<int>>, vector<vector<int>>> result = findOptimalOrder(dimensions);
    vector<vector<int>> minCost = result.first;
    vector<vector<int>> splitPoints = result.second;

    cout << "\nThe minimum number of multiplications required: " << minCost[0][matrixCount - 1] << endl;

    cout << "Optimal multiplication order: ";
    char matrixName = 'A';
    displayOptimalParenthesization(splitPoints, 0, matrixCount - 1, matrixName);
    cout << endl;

    try {
        vector<vector<int>> resultMatrix = recursiveMultiply(matrices, splitPoints, 0, matrixCount - 1);
        cout << "\nResultant matrix after multiplication:" << endl;
        displayMatrix(resultMatrix);
    } catch (const invalid_argument& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
