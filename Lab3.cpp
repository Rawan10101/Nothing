#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class Matrix {
private:
    int rows;
    int cols;
    int** data;
    static int instanceCount;

public:
    Matrix(int r, int c) {
        rows = r;
        cols = c;
        data = new int* [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];

            for (int j = 0; j < cols; j++) {
                data[i][j] = 0;
            }
            instanceCount++;
        }
    }

    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        data = new int* [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];

            for (int j = 0; j < cols; j++) {
                data[i][j] = other.data[i][j];
            }
        }

        instanceCount++;
    }

    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;

        instanceCount--;
    }

    void updateInventory(const int rowIndex, const int colIndex, int newValue) {
        if (rowIndex >= 0 && colIndex >= 0 && rowIndex < rows && colIndex < cols) {
            data[rowIndex][colIndex] = newValue;
        }
    }

    void addInventory(const Matrix& other, Matrix& other2, Matrix* result) {
        if (rows == other.rows && cols == other.cols && rows == other2.rows && cols == other2.cols) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    (*result).data[i][j] = other.data[i][j] + other2.data[i][j];
                }
            }
        }
        else {
            cout << "Dimens are not correct" << endl;
        }
    }

    void displayInventory() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    static int getInstanceCount() {
        return instanceCount;
    }
};

int Matrix::instanceCount = 0;

int main() {
    Matrix a(7, 7);
    Matrix b(7, 7);
    a.updateInventory(6, 6, 7);
    b.updateInventory(6, 6, 7);
    Matrix result(7, 7);
    a.addInventory(a, b, &result);
    result.displayInventory();

    return 0;
}