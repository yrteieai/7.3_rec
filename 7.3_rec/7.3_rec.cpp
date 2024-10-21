#include <iostream>
#include <iomanip>
using namespace std;

// ������� ��� ��������� �������
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

// ������� ��� �������� �������� �������
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

// ���������� ������� ��� ���������� �������� ��������� ����� ������
void ShiftTopRow(int** a, int layer, int first, int last) {
    if (first == last) return;  // ���� ������
    swap(a[layer][first], a[layer][first + 1]);
    ShiftTopRow(a, layer, first + 1, last);
}

// ���������� ������� ��� ���������� �������� ������� ������� ����
void ShiftRightCol(int** a, int layer, int first, int last) {
    if (first == last) return;  // ���� ������
    swap(a[first][last], a[first + 1][last]);
    ShiftRightCol(a, layer, first + 1, last);
}

// ���������� ������� ��� ���������� �������� �������� ����� ����
void ShiftBottomRow(int** a, int layer, int first, int last) {
    if (first == last) return;  // ���� ������
    swap(a[last][first], a[last][first - 1]);
    ShiftBottomRow(a, layer, first - 1, last);
}

// ���������� ������� ��� ���������� �������� ����� ������� �����
void ShiftLeftCol(int** a, int layer, int first, int last) {
    if (first == last) return;  // ���� ������
    swap(a[first][layer], a[first - 1][layer]);
    ShiftLeftCol(a, layer, first - 1, last);
}

// ���������� ������� ��� ����� ������ ���� �������
void ShiftLayer(int** a, int layer, int n, int k) {
    if (k == 0) return; // ���� ������ ��� ������� �����
    if (layer >= n / 2) return; // ���� ������ ��� ����

    int first = layer;
    int last = n - 1 - layer;

    // ���� ��������� ����� ������
    ShiftTopRow(a, layer, first, last);

    // ���� ������� ������� ����
    ShiftRightCol(a, layer, first, last);

    // ���� �������� ����� ����
    ShiftBottomRow(a, last, last, first);

    // ���� ����� ������� �����
    ShiftLeftCol(a, last, last, first + 1);

    // ����������� ������ ��� ���������� ����� �� \( k-1 \)
    ShiftLayer(a, layer, n, k - 1);
}

// ���������� ������� ��� ��������� ���������� �񳺿 ������� �� k ��������
void ShiftMatrix(int** a, int n, int k, int layer = 0) {
    if (layer >= n / 2) return;  // ���� ������ ��� ����
    ShiftLayer(a, layer, n, k);  // ���������� ��������� ����
    ShiftMatrix(a, n, k, layer + 1);  // ������� ��� ���������� ����
}

// ���������� ������� ��� ��������� �������� �������� � �������
int CountZeroInColumn(int** a, const int n, int colNo, int rowNo = 0) {
    if (rowNo == n) return 0;
    return (a[rowNo][colNo] == 0) + CountZeroInColumn(a, n, colNo, rowNo + 1);
}

// ���������� ������� ��� ����������� ������ ���������� ������� � ��������� ������� �������� ��������
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

    // �������� ��������� ��������� �������
    int** a = new int* [n];
    for (int i = 0; i < n; i++)
        a[i] = new int[n];

    // �������� �������� �������
    InputMatrix(a, n);

    // ��������� ��������� �������
    cout << "Initial Matrix:" << endl;
    PrintMatrix(a, n);

    // ������� ���������� �������
    ShiftMatrix(a, n, k);

    // ��������� ������� ���� ����������
    cout << "Matrix after shift:" << endl;
    PrintMatrix(a, n);

    // ����������� ���������� ������� � ��������� ������� �������� ��������
    int lastZeroCol = FindLastZeroColumn(a, n);
    if (lastZeroCol != -1)
        cout << "Last column with the most zero elements: " << lastZeroCol << endl;
    else
        cout << "No columns with zero elements found." << endl;

    // ��������� ���'��
    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}
