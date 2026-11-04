
#include <iostream>  // Allows input and output using cout and cin
#include <fstream>   // Allows reading from and writing to files
#include <iomanip>   // Allows formatting output using setw()
using namespace std;

// ============================================================
// MATRIX CLASS
// This class stores an N x N matrix and provides functions
// to read, display, add, multiply, and calculate diagonal sums.
// ============================================================

class Matrix {

private:
    int N;          // Stores the size of the square matrix
    int** data;     // Pointer to a dynamically allocated 2D array

public:

    // --------------------------------------------------------
    // CONSTRUCTOR
    // Creates a matrix with the specified size.
    // Dynamically allocates memory for N rows and N columns.
    // --------------------------------------------------------
    Matrix(int size = 0) {
        N = size;
        data = new int*[N];

        for (int i = 0; i < N; i++) {
            data[i] = new int[N];
        }
    }

    // --------------------------------------------------------
    // COPY CONSTRUCTOR
    // Creates a deep copy of another Matrix object.
    // Each element is copied into newly allocated memory.
    // This prevents two matrices from sharing the same memory.
    // --------------------------------------------------------
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

    // --------------------------------------------------------
    // ASSIGNMENT OPERATOR
    // Allows one Matrix object to be assigned to another.
    // Example: A = B;
    // First releases old memory, then copies the new matrix.
    // --------------------------------------------------------
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {

            // Delete the old matrix memory
            for (int i = 0; i < N; i++) {
                delete[] data[i];
            }
            delete[] data;

            // Copy the size of the other matrix
            N = other.N;
            data = new int*[N];

            // Allocate memory and copy every element
            for (int i = 0; i < N; i++) {
                data[i] = new int[N];

                for (int j = 0; j < N; j++) {
                    data[i][j] = other.data[i][j];
                }
            }
        }

        // Return the current Matrix object
        return *this;
    }

    // --------------------------------------------------------
    // DESTRUCTOR
    // Releases dynamically allocated memory when the Matrix
    // object is destroyed. This helps prevent memory leaks.
    // --------------------------------------------------------
    ~Matrix() {
        for (int i = 0; i < N; i++) {
            delete[] data[i];
        }

        delete[] data;
    }

    // --------------------------------------------------------
    // GET MATRIX SIZE
    // Returns the number of rows and columns in the matrix.
    // --------------------------------------------------------
    int getSize() const {
        return N;
    }

    // --------------------------------------------------------
    // GET ELEMENT
    // Returns the value stored at a specified row and column.
    // --------------------------------------------------------
    int getElement(int row, int col) const {
        return data[row][col];
    }

    // --------------------------------------------------------
    // SET ELEMENT
    // Changes the value at a specified row and column.
    // --------------------------------------------------------
    void setElement(int row, int col, int value) {
        data[row][col] = value;
    }

    // --------------------------------------------------------
    // READ MATRIX FROM FILE
    // Reads N x N values from the input file.
    // Each value is stored in the corresponding array position.
    // --------------------------------------------------------
    void readMatrix(ifstream& fin) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                fin >> data[i][j];
            }
        }
    }

    // --------------------------------------------------------
    // DISPLAY MATRIX
    // Displays the matrix with properly aligned columns.
    // ostream allows output to be sent to either cout or fout.
    // setw(4) reserves four spaces for each matrix element.
    // --------------------------------------------------------
    void display(ostream& out) const {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                out << setw(4) << data[i][j];
            }
            out << endl;
        }
    }

    // --------------------------------------------------------
    // ADDITION OPERATOR OVERLOADING (+)
    // Adds two matrices element by element.
    //
    // Example:
    // Matrix sum = A + B;
    //
    // Each element in the result is the sum of the matching
    // elements from Matrix A and Matrix B.
    // --------------------------------------------------------
    Matrix operator+(const Matrix& other) const {
        Matrix result(N);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                result.data[i][j] =
                    data[i][j] + other.data[i][j];
            }
        }

        // Return the resulting matrix
        return result;
    }

    // --------------------------------------------------------
    // MULTIPLICATION OPERATOR OVERLOADING (*)
    // Multiplies two matrices using standard matrix
    // multiplication.
    //
    // Example:
    // Matrix product = A * B;
    //
    // Three nested loops are used:
    // i = Selects a row from the first matrix.
    // j = Selects a column from the second matrix.
    // k = Multiplies matching elements and adds the products.
    // --------------------------------------------------------
    Matrix operator*(const Matrix& other) const {
        Matrix result(N);

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {

                // Initialize the result element to zero
                result.data[i][j] = 0;

                for (int k = 0; k < N; k++) {

                    // Multiply corresponding row and column values
                    result.data[i][j] +=
                        data[i][k] * other.data[k][j];
                }
            }
        }

        // Return the resulting matrix
        return result;
    }

    // --------------------------------------------------------
    // MAIN DIAGONAL SUM
    // Adds the elements running from the top-left corner
    // to the bottom-right corner.
    //
    // The row and column indices are always the same.
    // Example: data[0][0] + data[1][1] + data[2][2]
    // --------------------------------------------------------
    int mainDiagonalSum() const {
        int sum = 0;

        for (int i = 0; i < N; i++) {
            sum += data[i][i];
        }

        return sum;
    }

    // --------------------------------------------------------
    // SECONDARY DIAGONAL SUM
    // Adds the elements running from the top-right corner
    // to the bottom-left corner.
    //
    // The column index is N - 1 - i.
    // --------------------------------------------------------
    int secondaryDiagonalSum() const {
        int sum = 0;

        for (int i = 0; i < N; i++) {
            sum += data[i][N - 1 - i];
        }

        return sum;
    }
};


// ============================================================
// PROBLEM 5: SWAP MATRIX ROWS
//
// Receives the Matrix by VALUE, meaning the function works
// with a copy of the original matrix.
//
// Default row indices are 0 and 1.
// Users can also specify any other valid row indices.
// ============================================================

void swapRows(Matrix matrix,
              int row1 = 0,
              int row2 = 1,
              ostream& out = cout) {

    // Get the matrix size
    int N = matrix.getSize();

    // Check whether the selected row indices are valid
    if (row1 < 0 || row1 >= N ||
        row2 < 0 || row2 >= N) {
        out << "Invalid row indices!" << endl;
        return;
    }

    // Loop through every column in the selected rows
    for (int j = 0; j < N; j++) {

        // Temporarily save the first row's element
        int temp = matrix.getElement(row1, j);

        // Move the second row's element into the first row
        matrix.setElement(row1, j,
                          matrix.getElement(row2, j));

        // Move the saved element into the second row
        matrix.setElement(row2, j, temp);
    }

    // Display the matrix after swapping the rows
    matrix.display(out);
}


// ============================================================
// PROBLEM 6: SWAP MATRIX COLUMNS
//
// Receives the Matrix by VALUE, so the original matrix
// remains unchanged.
//
// Default column indices are 0 and 1.
// ============================================================

void swapColumns(Matrix matrix,
                 int col1 = 0,
                 int col2 = 1,
                 ostream& out = cout) {

    // Get the matrix size
    int N = matrix.getSize();

    // Check whether the selected column indices are valid
    if (col1 < 0 || col1 >= N ||
        col2 < 0 || col2 >= N) {
        out << "Invalid column indices!" << endl;
        return;
    }

    // Loop through every row in the selected columns
    for (int i = 0; i < N; i++) {

        // Temporarily save the first column's element
        int temp = matrix.getElement(i, col1);

        // Move the second column's element into the first
        matrix.setElement(i, col1,
                          matrix.getElement(i, col2));

        // Move the saved element into the second column
        matrix.setElement(i, col2, temp);
    }

    // Display the matrix after swapping the columns
    matrix.display(out);
}


// ============================================================
// PROBLEM 7: UPDATE MATRIX ELEMENT
//
// Receives the Matrix by VALUE, so the original matrix
// remains unchanged.
//
// Default arguments:
// Row = 0
// Column = 0
// New value = 100
//
// Users can specify other valid positions and values.
// ============================================================

void updateMatrix(Matrix matrix,
                  int row = 0,
                  int col = 0,
                  int value = 100,
                  ostream& out = cout) {

    // Get the matrix size
    int N = matrix.getSize();

    // Check whether the selected row and column are valid
    if (row < 0 || row >= N ||
        col < 0 || col >= N) {
        out << "Invalid row or column indices!" << endl;
        return;
    }

    // Change the selected matrix element to the new value
    matrix.setElement(row, col, value);

    // Display the updated matrix
    matrix.display(out);
}


// ============================================================
// MAIN FUNCTION
//
// Controls the entire program.
//
// 1. Opens input.txt.
// 2. Opens output.txt.
// 3. Reads the matrix size.
// 4. Reads Matrix A and Matrix B.
// 5. Adds the matrices.
// 6. Multiplies the matrices.
// 7. Calculates diagonal sums.
// 8. Swaps rows.
// 9. Swaps columns.
// 10. Updates a matrix element.
// ============================================================

int main() {

    // Open the input file for reading
    ifstream fin("input.txt");

    // Open the output file for writing
    ofstream fout("output.txt");

    // Check whether input.txt opened successfully
    if (!fin) {
        cerr << "Error: Cannot open input.txt!" << endl;
        return 1;
    }

    // Check whether output.txt was created successfully
    if (!fout) {
        cerr << "Error: Cannot create output.txt!" << endl;
        return 1;
    }

    // Read the matrix size from the first line
    int N;
    fin >> N;

    // Check whether the matrix size is valid
    if (!fin || N <= 0) {
        cerr << "Invalid matrix size!" << endl;
        return 1;
    }

    // Create two Matrix objects with size N x N
    Matrix A(N);
    Matrix B(N);

    // Read the values for both matrices from input.txt
    A.readMatrix(fin);
    B.readMatrix(fin);

    // Check whether enough matrix values were provided
    if (!fin) {
        cerr << "Error: Not enough matrix data in input.txt!" << endl;
        return 1;
    }

    // Close the input file after reading
    fin.close();


    // --------------------------------------------------------
    // DISPLAY MATRIX A
    // --------------------------------------------------------
    fout << "Matrix A:" << endl;
    A.display(fout);


    // --------------------------------------------------------
    // DISPLAY MATRIX B
    // --------------------------------------------------------
    fout << "\nMatrix B:" << endl;
    B.display(fout);


    // --------------------------------------------------------
    // PROBLEM 2: ADD THE MATRICES
    // Uses the overloaded + operator.
    // --------------------------------------------------------
    Matrix sum = A + B;

    fout << "\nA + B:" << endl;
    sum.display(fout);


    // --------------------------------------------------------
    // PROBLEM 3: MULTIPLY THE MATRICES
    // Uses the overloaded * operator.
    // --------------------------------------------------------
    Matrix product = A * B;

    fout << "\nA * B:" << endl;
    product.display(fout);


    // --------------------------------------------------------
    // PROBLEM 4: CALCULATE DIAGONAL SUMS
    // Calculates both diagonal sums for Matrix A.
    // --------------------------------------------------------
    fout << "\nDiagonal sums for Matrix A:" << endl;

    fout << "Main diagonal sum: "
         << A.mainDiagonalSum() << endl;

    fout << "Secondary diagonal sum: "
         << A.secondaryDiagonalSum() << endl;


    // --------------------------------------------------------
    // PROBLEM 5: SWAP ROWS 0 AND 2
    // Only the copied matrix inside swapRows() is modified.
    // --------------------------------------------------------
    fout << "\nProblem 5 - Rows 0 and 2 swapped:" << endl;
    swapRows(A, 0, 2, fout);


    // --------------------------------------------------------
    // PROBLEM 6: SWAP COLUMNS 0 AND 2
    // Only the copied matrix inside swapColumns() is modified.
    // --------------------------------------------------------
    fout << "\nProblem 6 - Columns 0 and 2 swapped:" << endl;
    swapColumns(A, 0, 2, fout);


    // --------------------------------------------------------
    // PROBLEM 7: UPDATE ROW 1, COLUMN 2 TO 99
    // Indexing starts at zero, so this means the second row
    // and third column.
    // Only the copied matrix inside updateMatrix() is changed.
    // --------------------------------------------------------
    fout << "\nProblem 7 - Updated matrix:" << endl;
    updateMatrix(A, 1, 2, 99, fout);


    // Close the output file after writing all results
    fout.close();

    // Display a completion message in the terminal
    cout << "Program completed successfully. "
         << "Check output.txt." << endl;

    return 0;
}
