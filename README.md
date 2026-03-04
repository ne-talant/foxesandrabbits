

Файл: work3.cpp

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class Matrix {
    int** M;
    int rows;
    int cols;
    int sum;
public:
    Matrix() {
        rows = 0;
        cols = 0;
        M = nullptr;
        sum = 0;
    }

    Matrix(int n) {
        rows = n;
        cols = n;
        sum = 0;
        M = new int*[rows];
        for (int i = 0; i < rows; i++) {
            M[i] = new int[cols];
            for (int j = 0; j < cols; j++) {
                if (i == j) M[i][j] = 1;
                else M[i][j] = 0;
            }
        }
    }

    Matrix(int r, int c) {
        rows = r;
        cols = c;
        sum = 0;
        M = new int*[rows];
        for (int i = 0; i < rows; i++) {
            M[i] = new int[cols];
            for (int j = 0; j < cols; j++) {
                M[i][j] = 0;
            }
        }
    }

    void Input() {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                cin >> M[i][j];
    }

    void RandomFill() {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                M[i][j] = rand() % 10;
    }

    void FillByFormula() {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                M[i][j] = i * j;
    }

    void Print() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                cout << M[i][j] << " ";
            cout << endl;
        }
        cout << endl;
    }

    void CalculateSum() {
        sum = 0;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                sum += M[i][j];
        cout << sum << endl;
    }

    ~Matrix() {
        if (M != nullptr) {
            for (int i = 0; i < rows; i++)
                delete[] M[i];
            delete[] M;
        }
    }
};

int main() {
    srand(time(0));

    Matrix M1;
    Matrix M2(3);
    Matrix M3(3,4);
    Matrix M4(2,3);

    M2.Print();
    M3.Print();
    M4.Print();

    M2.FillByFormula();
    M2.Print();

    M3.RandomFill();
    M3.Print();

    M4.Input();
    M4.Print();

    M3.CalculateSum();

    return 0;
}


⸻

Файл: work4_int.cpp

#include <iostream>
using namespace std;

template <typename T>
class Matrix {
    T** M;
    int m;
    int n;
public:
    Matrix() {
        m = 0;
        n = 0;
        M = nullptr;
    }

    Matrix(int rows, int cols) {
        m = rows;
        n = cols;
        M = new T*[m];
        for (int i = 0; i < m; i++) {
            M[i] = new T[n];
            for (int j = 0; j < n; j++)
                M[i][j] = 0;
        }
    }

    Matrix(const Matrix& other) {
        m = other.m;
        n = other.n;
        M = new T*[m];
        for (int i = 0; i < m; i++) {
            M[i] = new T[n];
            for (int j = 0; j < n; j++)
                M[i][j] = other.M[i][j];
        }
    }

    void SetM(int i, int j, T value) {
        M[i][j] = value;
    }

    T GetM(int i, int j) {
        return M[i][j];
    }

    void Print(const char* name) {
        cout << "Object: " << name << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)
                cout << M[i][j] << " ";
            cout << endl;
        }
        cout << "---------------------" << endl;
    }

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            for (int i = 0; i < m; i++)
                delete[] M[i];
            delete[] M;

            m = other.m;
            n = other.n;

            M = new T*[m];
            for (int i = 0; i < m; i++) {
                M[i] = new T[n];
                for (int j = 0; j < n; j++)
                    M[i][j] = other.M[i][j];
            }
        }
        return *this;
    }

    ~Matrix() {
        if (M != nullptr) {
            for (int i = 0; i < m; i++)
                delete[] M[i];
            delete[] M;
        }
    }
};

int main() {
    Matrix<int> M(3, 4);
    M.Print("M");

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            M.SetM(i, j, i + j);

    M.Print("M");

    Matrix<int> M1 = M;
    M1.Print("M1");

    Matrix<int> M2;
    M2 = M;
    M2.Print("M2");

    Matrix<int> M3;
    M3 = M2 = M1 = M;
    M3.Print("M3");

    return 0;
}


⸻

Файл: work4_double.cpp

#include <iostream>
using namespace std;

template <typename T>
class Matrix {
    T** M;
    int m;
    int n;
public:
    Matrix() {
        m = 0;
        n = 0;
        M = nullptr;
    }

    Matrix(int rows, int cols) {
        m = rows;
        n = cols;
        M = new T*[m];
        for (int i = 0; i < m; i++) {
            M[i] = new T[n];
            for (int j = 0; j < n; j++)
                M[i][j] = 0;
        }
    }

    Matrix(const Matrix& other) {
        m = other.m;
        n = other.n;
        M = new T*[m];
        for (int i = 0; i < m; i++) {
            M[i] = new T[n];
            for (int j = 0; j < n; j++)
                M[i][j] = other.M[i][j];
        }
    }

    void SetM(int i, int j, T value) {
        M[i][j] = value;
    }

    T GetM(int i, int j) {
        return M[i][j];
    }

    void Print(const char* name) {
        cout << "Object: " << name << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)
                cout << M[i][j] << " ";
            cout << endl;
        }
        cout << "---------------------" << endl;
    }

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            for (int i = 0; i < m; i++)
                delete[] M[i];
            delete[] M;

            m = other.m;
            n = other.n;

            M = new T*[m];
            for (int i = 0; i < m; i++) {
                M[i] = new T[n];
                for (int j = 0; j < n; j++)
                    M[i][j] = other.M[i][j];
            }
        }
        return *this;
    }

    ~Matrix() {
        if (M != nullptr) {
            for (int i = 0; i < m; i++)
                delete[] M[i];
            delete[] M;
        }
    }
};

int main() {
    Matrix<double> M(3, 4);
    M.Print("M");

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            M.SetM(i, j, (i + j) * 0.5);

    M.Print("M");

    Matrix<double> M1 = M;
    M1.Print("M1");

    Matrix<double> M2;
    M2 = M;
    M2.Print("M2");

    Matrix<double> M3;
    M3 = M2 = M1 = M;
    M3.Print("M3");

    return 0;
}