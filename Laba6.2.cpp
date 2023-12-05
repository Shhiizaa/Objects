// Laba6.2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

class Matrix {
    int n;
    double** nums;

public:
    Matrix();
    Matrix(int n);
    Matrix(int n, double** nums);
    Matrix(const Matrix& A);
    ~Matrix();

    Matrix operator+(const Matrix& A) const;
    Matrix operator-(const Matrix& A) const;
    Matrix operator*(const Matrix& A) const;
    Matrix& operator=(const Matrix& A);

    int CalculateNorm() const;
    void Copy(const Matrix& A);
    friend ostream& operator<<(ostream& mystream, const Matrix& A);
};

ostream& operator<<(ostream& mystream, const Matrix& A) {
    for (int i = 0; i < A.n; i++) {
        for (int j = 0; j < A.n; j++) {
            mystream << setw(5) << A.nums[i][j] << " ";
        }
        mystream << endl;
    }
    return mystream;
}

Matrix::Matrix() {
    n = 1 + rand() % 5;
    try {
    nums = new double* [n];
    for (int i = 0; i < n; i++) {
        nums[i] = new double[n];
        for (int j = 0; j < n; j++) {
            nums[i][j] = -10 + rand() % 20;
        }
    }
    }
    catch (bad_alloc& e) {
        cerr << "Нехватка памяти: " << e.what() << endl;
        throw;
    }
}

Matrix::Matrix(int a) {
    n = a;
    try {
    nums = new double* [n];
    for (int i = 0; i < n; i++) {
        nums[i] = new double[n];
        for (int j = 0; j < n; j++) {
            nums[i][j] = -10 + rand() % 20;
        }
    }
    }
    catch (bad_alloc& e) {
        cerr << "Нехватка памяти: " << e.what() << endl;
        throw;
    }
}

Matrix::Matrix(int a, double** arr) {
    n = a;
    try {
    nums = new double* [n];
    for (int i = 0; i < n; i++) {
        nums[i] = new double[n];
        for (int j = 0; j < n; j++) {
            nums[i][j] = arr[i][j];
        }
    }
    }
    catch (bad_alloc& e) {
        cerr << "Нехватка памяти: " << e.what() << endl;
        throw;
    }
}

Matrix::Matrix(const Matrix& A) {
    n = A.n;
    try {
    nums = new double* [n];
    for (int i = 0; i < n; i++) {
        nums[i] = new double[n];
        for (int j = 0; j < n; j++) {
            nums[i][j] = A.nums[i][j];
        }
    }
    }
    catch (bad_alloc& e) {
        cerr << "Нехватка памяти: " << e.what() << endl;
        throw;
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < n; i++) {
        delete[] nums[i];
    }
    delete[] nums;
}

Matrix Matrix::operator+(const Matrix& A) const {
    if (n != A.n) {
        throw invalid_argument("Ошибка. Матрицы разной размерности");
    }

    Matrix B(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            B.nums[i][j] = nums[i][j] + A.nums[i][j];
        }
    }
    return B;
}

Matrix Matrix::operator-(const Matrix& A) const {
    if (n != A.n) {
        throw invalid_argument("Ошибка. Матрицы разной размерности");
    }

    Matrix B(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            B.nums[i][j] = nums[i][j] - A.nums[i][j];
        }
    }
    return B;
}

Matrix Matrix::operator*(const Matrix& A) const {
    if (n != A.n) {
        throw invalid_argument("Ошибка. Матрицы разной размерности");
    }

    Matrix B(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            B.nums[i][j] = 0;
            for (int k = 0; k < n; k++) {
                B.nums[i][j] += nums[i][k] * A.nums[k][j];
            }
        }
    }
    return B;
}

Matrix& Matrix::operator=(const Matrix& A) {
    if (this == &A) return *this;

    for (int i = 0; i < n; i++) {
        delete[] nums[i];
    }
    delete[] nums;

    n = A.n;
    nums = new double* [n];
    for (int j = 0; j < n; j++) {
        nums[j] = new double[n];
    }
    for (int k = 0; k < n; k++) {
        for (int l = 0; l < n; l++) {
            nums[k][l] = A.nums[k][l];
        }
    }

    return *this;
}

int Matrix::CalculateNorm() const {
    int* buf, max = 0;
    buf = new int[n];
    for (int i = 0; i < n; i++) {
        buf[i] = 0;
        for (int j = 0; j < n; j++) {
            buf[i] += abs(nums[i][j]);
        }
        if (max < buf[i]) max = buf[i];
    }
    delete[] buf;
    return max;
}

void Matrix::Copy(const Matrix& A) {
    for (int i = 0; i < n; i++) {
        delete[] nums[i];
    }
    delete[] nums;

    n = A.n;
    nums = new double* [n];
    for (int j = 0; j < n; j++) {
        nums[j] = new double[n];
    }
    for (int k = 0; k < n; k++) {
        for (int l = 0; l < n; l++) {
            nums[k][l] = A.nums[k][l];
        }
    }
}

void Show(Matrix* arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i];
        cout << endl;
    }
    cout << endl;
}

Matrix Sqrt(Matrix* A, int i)
{
    return (A[i] * A[i]);
}

int main() {
    setlocale(LC_ALL, "Russian");

    try {
        int n, typeOfCin, dim, a;
        int* buffer;
        buffer = new int[30];
        ofstream f;
        f.open("matrixes.txt", ios::app);
        if (!f.is_open()) {
            cerr << "Ошибка в открытии файла для записи" << endl;
            return 1;
        }
        cout << "Введите кол-во записей: ";
        cin >> n;
        Matrix* arr;
        arr = new Matrix[30];
        for (int i = 0; i < n; i++)
        {
            cout << "Введите число: " << endl << "--- 1 - Матрица случайной размерности" << endl << "--- 2 - Матрица введенной размерности" << endl << "--- 3 - Ввести размерность и значения матрицы" << endl;
            cin >> a;
            switch (a)
            {
            case 1: f << a << "\n"; break;
            case 2: {f << a << "\n"; cout << "Введите размерность матрицы: "; cin >> dim; f << dim << "\n"; } break;
            case 3: {f << a << "\n"; cout << "Введите размерность матрицы: "; cin >> dim; f << dim << "\n"; cout << "Введите значения матрицы: ";
                for (int j = 0; j < (dim * dim); j++)
                {
                    cin >> buffer[j];
                    f << buffer[j];
                    f << " ";
                }
                f << "\n";
            }
            }
        }
        f.close();
        delete[] buffer;
        ifstream F;
        F.open("matrixes.txt", ios::in);
        if (!F.is_open()) {
            cerr << "Ошибка в открытии файла для чтения" << endl;
            return 1;
        }
        n = -1;
        while (1)
        {
            n++;
            F >> a;
            if (F.eof()) break;
            switch (a)
            {
            case 1: break;
            case 2: {F >> dim; Matrix* A = new Matrix(dim); arr[n].Copy(*A); delete A; } break;
            case 3: {F >> dim; double** buf; buf = new double* [dim];
                for (int i = 0; i < dim; i++)
                {
                    buf[i] = new double[dim];
                    for (int j = 0; j < dim; j++)
                    {
                        F >> buf[i][j];
                    }
                }
                Matrix* A = new Matrix(dim, buf); arr[n].Copy(*A); delete A;
                for (int i = 0; i < dim; i++)
                {
                    delete[] buf[i];
                }
                delete[] buf;
            } break;
            }

        }
        F.close();
        int i1, i2;
        while (a)
        {
            cout << endl << "Введите число: " << endl << "--- 1 - Сложение матриц" << endl << "--- 2 - Вычитание матриц" << endl << "--- 3 - Умножение матриц" << endl << "--- 4 - Норма матрицы" << endl << "--- 5 - Возведение матрицы в квадрат" << endl << "--- 6 - Вывести матрицы" << endl << "--- 0 - Выйти" << endl;
            cin >> a;
            if (a == 0)break;
            switch (a)
            {
            case 1: {cout << "Введите номера матриц, которые следует сложить (отсчет с 1, а не 0): " << endl; cin >> i1; cin >> i2; Matrix Rez(arr[i1 - 1] + arr[i2 - 1]); cout << Rez; } break;
            case 2: {cout << "Введите номера матриц, которые следует вычесть (отсчет с 1, а не 0): " << endl; cin >> i1; cin >> i2; Matrix Rez(arr[i1 - 1] - arr[i2 - 1]); cout << Rez; } break;
            case 3: {cout << "Введите номера матриц, которые следует перемножить (отсчет с 1, а не 0): " << endl; cin >> i1; cin >> i2; Matrix Rez(arr[i1 - 1] * arr[i2 - 1]); cout << Rez; } break;
            case 4: {cout << "Введите номер матрицы (отсчет с 1, а не 0): " << endl; cin >> i1; cout << arr[i1 - 1].CalculateNorm(); } break;
            case 5: {cout << "Введите номер матрицы (отсчет с 1, а не 0): " << endl; cin >> i1; Matrix Rez(Sqrt(arr, (i1 - 1))); cout << Rez; } break;
            case 6: {Show(arr, n); } break;
            }
        }
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1; 
    }

    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
