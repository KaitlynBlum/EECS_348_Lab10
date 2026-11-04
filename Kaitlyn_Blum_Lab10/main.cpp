
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Matrix {
private:
    int N;
    int** data;

public:
    // Constructor
    Matrix(int size = 0) {
        N = size;
        data = new int*[N];

        for (int i = 0; i < N; i++) {
            data[i] = new int[N];
        }
    }

    // Copy constructor
    Matrix(const Matrix& other) {
        N = other.N;
        data = new int*[N];

        for (int i = 0; i < N; i++) {
            data[i] = new int[N];

            for (int j = 0; j < N; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    // Assignment operator
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            for (int i = 0; i < N; i++) {
                delete[] data[i];
            }
            delete[] data;

            N = other.N;
            data = new int*[N];

            for (int i = 0; i < N; i++) {
                data[i] = new int[N];

                for (int j = 0; j < N; j++) {
                    data[i][j] = other.data[i][j];
                }
            }
        }

        return *this;
    }

    // Destructor
    ~Matrix() {
        for (int i = 0; i < N; i++) {
            delete[] data[i];
        }

        delete[] data;
    }

    // Get matrix size
    int getSize() const {
        return N;
    }

    // Get element
    int getElement(int row, int col) const {
        return data[row][col];
    }

    // Set element
    void setElement(int row, int col, int value) {
        data[row][col] = value;
    }

    // Read matrix from file
    void readMatrix(ifstream& fin) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                fin >> data[i][j];
            }
        }
    }

    // Display matrix
    void display(ostream& out) const {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                out << setw(4) << data[i][j];
            }
            out << endl;
        }
    }

    // Addition operator
    Matrix operator+(const Matrix& other) const {
        Matrix result(N);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                result.data[i][j] =
                    data[i][j] + other.data[i][j];
            }
        }

        return result;
    }

    // Multiplication operator
    Matrix operator*(const Matrix& other) const {
        Matrix result(N);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                result.data[i][j] = 0;

                for (int k = 0; k < N; k++) {
                    result.data[i][j] +=
                        data[i][k] * other.data[k][j];
                }
            }
        }

        return result;
    }

    // Main diagonal sum
    int mainDiagonalSum() const {
        int sum = 0;

        for (int i = 0; i < N; i++) {
            sum += data[i][i];
        }

        return sum;
    }

    // Secondary diagonal sum
    int secondaryDiagonalSum() const {
        int sum = 0;

        for (int i = 0; i < N; i++) {
            sum += data[i][N - 1 - i];
        }

        return sum;
    }
};

// Problem 5: Swap rows (pass by value)
void swapRows(Matrix matrix,
              int row1 = 0,
              int row2 = 1,
              ostream& out = cout) {

    int N = matrix.getSize();

    if (row1 < 0 || row1 >= N ||
        row2 < 0 || row2 >= N) {
        out << "Invalid row indices!" << endl;
        return;
    }

    for (int j = 0; j < N; j++) {
        int temp = matrix.getElement(row1, j);

        matrix.setElement(row1, j,
                          matrix.getElement(row2, j));

        matrix.setElement(row2, j, temp);
    }

    matrix.display(out);
}

// Problem 6: Swap columns
void swapColumns(Matrix matrix,
                 int col1 = 0,
                 int col2 = 1,
                 ostream& out = cout) {

    int N = matrix.getSize();

    if (col1 < 0 || col1 >= N ||
        col2 < 0 || col2 >= N) {
        out << "Invalid column indices!" << endl;
        return;
    }

    for (int i = 0; i < N; i++) {
        int temp = matrix.getElement(i, col1);

        matrix.setElement(i, col1,
                          matrix.getElement(i, col2));

        matrix.setElement(i, col2, temp);
    }

    matrix.display(out);
}

// Problem 7: Update matrix element
void updateMatrix(Matrix matrix,
                  int row = 0,
                  int col = 0,
                  int value = 100,
                  ostream& out = cout) {

    int N = matrix.getSize();

    if (row < 0 || row >= N ||
        col < 0 || col >= N) {
        out << "Invalid row or column indices!" << endl;
        return;
    }

    matrix.setElement(row, col, value);

    matrix.display(out);
}

int main() {

    // Open input and output files
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if (!fin) {
        cerr << "Error: Cannot open input.txt!" << endl;
        return 1;
    }

    if (!fout) {
        cerr << "Error: Cannot create output.txt!" << endl;
        return 1;
    }

    int N;
    fin >> N;

    if (!fin || N <= 0) {
        cerr << "Invalid matrix size!" << endl;
        return 1;
    }

    Matrix A(N);
    Matrix B(N);

    // Read matrices
    A.readMatrix(fin);
    B.readMatrix(fin);

    if (!fin) {
        cerr << "Error: Not enough matrix data in input.txt!" << endl;
        return 1;
    }

    fin.close();

    // Display Matrix A
    fout << "Matrix A:" << endl;
    A.display(fout);

    // Display Matrix B
    fout << "\nMatrix B:" << endl;
    B.display(fout);

    // Problem 2: Addition
    Matrix sum = A + B;

    fout << "\nA + B:" << endl;
    sum.display(fout);

    // Problem 3: Multiplication
    Matrix product = A * B;

    fout << "\nA * B:" << endl;
    product.display(fout);

    // Problem 4: Diagonal sums
    fout << "\nDiagonal sums for Matrix A:" << endl;

    fout << "Main diagonal sum: "
         << A.mainDiagonalSum() << endl;

    fout << "Secondary diagonal sum: "
         << A.secondaryDiagonalSum() << endl;

    // Problem 5: Swap rows 0 and 2
    fout << "\nProblem 5 - Rows 0 and 2 swapped:" << endl;
    swapRows(A, 0, 2, fout);

    // Problem 6: Swap columns 0 and 2
    fout << "\nProblem 6 - Columns 0 and 2 swapped:" << endl;
    swapColumns(A, 0, 2, fout);

    // Problem 7: Update row 1, column 2 to 99
    fout << "\nProblem 7 - Updated matrix:" << endl;
    updateMatrix(A, 1, 2, 99, fout);

    fout.close();

    cout << "Program completed successfully. "
         << "Check output.txt." << endl;

    return 0;
}
