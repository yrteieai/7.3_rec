#include <iostream>
#include <iomanip>
using namespace std;

// Функція для виведення матриці
void PrintMatrix(int** a, const int n, int rowNo = 0, int colNo = 0) {
    cout << setw(4) << a[rowNo][colNo];
    if (colNo < n - 1) {
        PrintMatrix(a, n, rowNo, colNo + 1);
    }
    else {
        cout << endl;
        if (rowNo < n - 1) {
            PrintMatrix(a, n, rowNo + 1, 0);
        }
    }
}

// Функція для введення елементів матриці
void InputMatrix(int** a, const int n, int rowNo = 0, int colNo = 0) {
    cout << "a[" << rowNo << "][" << colNo << "] = ";
    cin >> a[rowNo][colNo];
    if (colNo < n - 1) {
        InputMatrix(a, n, rowNo, colNo + 1);
    }
    else if (rowNo < n - 1) {
        InputMatrix(a, n, rowNo + 1, 0);
    }
}

// Рекурсивна функція для переміщення елементів верхнього рядка вправо
void ShiftTopRow(int** a, int layer, int first, int last) {
    if (first == last) return;  // База рекурсії
    swap(a[layer][first], a[layer][first + 1]);
    ShiftTopRow(a, layer, first + 1, last);
}

// Рекурсивна функція для переміщення елементів правого стовпця вниз
void ShiftRightCol(int** a, int layer, int first, int last) {
    if (first == last) return;  // База рекурсії
    swap(a[first][last], a[first + 1][last]);
    ShiftRightCol(a, layer, first + 1, last);
}

// Рекурсивна функція для переміщення елементів нижнього рядка вліво
void ShiftBottomRow(int** a, int layer, int first, int last) {
    if (first == last) return;  // База рекурсії
    swap(a[last][first], a[last][first - 1]);
    ShiftBottomRow(a, layer, first - 1, last);
}

// Рекурсивна функція для переміщення елементів лівого стовпця вгору
void ShiftLeftCol(int** a, int layer, int first, int last) {
    if (first == last) return;  // База рекурсії
    swap(a[first][layer], a[first - 1][layer]);
    ShiftLeftCol(a, layer, first - 1, last);
}

// Рекурсивна функція для зсуву одного шару матриці
void ShiftLayer(int** a, int layer, int n, int k) {
    if (k == 0) return; // База рекурсії для кількості зсувів
    if (layer >= n / 2) return; // База рекурсії для шарів

    int first = layer;
    int last = n - 1 - layer;

    // Зсув верхнього рядка вправо
    ShiftTopRow(a, layer, first, last);

    // Зсув правого стовпця вниз
    ShiftRightCol(a, layer, first, last);

    // Зсув нижнього рядка вліво
    ShiftBottomRow(a, last, last, first);

    // Зсув лівого стовпця вгору
    ShiftLeftCol(a, last, last, first + 1);

    // Рекурсивний виклик для наступного зсуву на \( k-1 \)
    ShiftLayer(a, layer, n, k - 1);
}

// Рекурсивна функція для циклічного переміщення всієї матриці на k елементів
void ShiftMatrix(int** a, int n, int k, int layer = 0) {
    if (layer >= n / 2) return;  // База рекурсії для шарів
    ShiftLayer(a, layer, n, k);  // Переміщення поточного шару
    ShiftMatrix(a, n, k, layer + 1);  // Рекурсія для наступного шару
}

// Рекурсивна функція для підрахунку нульових елементів у стовпці
int CountZeroInColumn(int** a, const int n, int colNo, int rowNo = 0) {
    if (rowNo == n) return 0;
    return (a[rowNo][colNo] == 0) + CountZeroInColumn(a, n, colNo, rowNo + 1);
}

// Рекурсивна функція для знаходження номера останнього стовпця з найбільшою кількістю нульових елементів
int FindLastZeroColumn(int** a, const int n, int colNo = 0, int maxZeroCount = 0, int maxZeroCol = -1) {
    if (colNo == n) return maxZeroCol;

    int zeroCount = CountZeroInColumn(a, n, colNo);

    if (zeroCount >= maxZeroCount) {
        maxZeroCount = zeroCount;
        maxZeroCol = colNo;
    }

    return FindLastZeroColumn(a, n, colNo + 1, maxZeroCount, maxZeroCol);
}

int main() {
    int n, k;
    cout << "Enter size of the matrix (n * n): ";
    cin >> n;
    cout << "Enter number of shifts (k): ";
    cin >> k;

    // Динамічне створення квадратної матриці
    int** a = new int* [n];
    for (int i = 0; i < n; i++)
        a[i] = new int[n];

    // Введення елементів матриці
    InputMatrix(a, n);

    // Виведення початкової матриці
    cout << "Initial Matrix:" << endl;
    PrintMatrix(a, n);

    // Циклічне переміщення матриці
    ShiftMatrix(a, n, k);

    // Виведення матриці після переміщення
    cout << "Matrix after shift:" << endl;
    PrintMatrix(a, n);

    // Знаходження останнього стовпця з найбільшою кількістю нульових елементів
    int lastZeroCol = FindLastZeroColumn(a, n);
    if (lastZeroCol != -1)
        cout << "Last column with the most zero elements: " << lastZeroCol << endl;
    else
        cout << "No columns with zero elements found." << endl;

    // Звільнення пам'яті
    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}
