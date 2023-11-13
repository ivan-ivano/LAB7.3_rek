#include <iostream>
#include <iomanip>

using namespace std;

void PrintRow(int** a, const int rowNo, const int colCount, int colNo)
{
	cout << setw(4) << a[rowNo][colNo];
	if (colNo < colCount - 1)
		PrintRow(a, rowNo, colCount, colNo + 1);
	else
		cout << endl;
}
void PrintRows(int** a, const int rowCount, const int colCount, int rowNo)
{
	PrintRow(a, rowNo, colCount, 0);
	if (rowNo < rowCount - 1)
		PrintRows(a, rowCount, colCount, rowNo + 1);
	else
		cout << endl;
}
void InputRow(int** a, const int rowNo, const int colCount, int colNo)
{
	cout << "a[" << rowNo << "][" << colNo << "] = ";
	cin >> a[rowNo][colNo];
	if (colNo < colCount - 1)
		InputRow(a, rowNo, colCount, colNo + 1);
	else
		cout << endl;
}

void InputRows(int** a, const int rowCount, const int colCount, int rowNo)
{
	InputRow(a, rowNo, colCount, 0);
	if (rowNo < rowCount - 1)
		InputRows(a, rowCount, colCount, rowNo + 1);
	else
		cout << endl;
}

int sumInRow(int* row, int cols, int currentIndex = 0) {
	if (currentIndex >= cols) {
		return 0;
	}

	int currentElement = row[currentIndex];
	return currentElement + sumInRow(row, cols, currentIndex + 1);
}

bool hasNegativeInRow(int* row, int cols, int currentIndex = 0) {
	if (currentIndex >= cols) {
		return false;
	}

	if (row[currentIndex] < 0) {
		return true;
	}

	return hasNegativeInRow(row, cols, currentIndex + 1);
}

int sumInRowsWithNegative(int** matrix, int rows, int cols, int currentRow = 0) {
	if (currentRow >= rows) {
		return 0;
	}

	if (hasNegativeInRow(matrix[currentRow], cols)) {
		return sumInRow(matrix[currentRow], cols) + sumInRowsWithNegative(matrix, rows, cols, currentRow + 1);
	}

	return sumInRowsWithNegative(matrix, rows, cols, currentRow + 1);
}


bool IsMinInRowN(int** a, int rowNo, int value, int colNo, int COLS) {
	if (colNo < COLS) {
		if (a[rowNo][colNo] < value) {
			return false;
		}
		return IsMinInRowN(a, rowNo, value, colNo + 1, COLS);
	}
	return true;
}

bool IsMaxInColK(int** a, int colNo, int value, int rowNo, int ROWS) {
	if (rowNo < ROWS) {
		if (a[rowNo][colNo] > value) {
			return false;
		}
		return IsMaxInColK(a, colNo, value, rowNo + 1, ROWS);
	}
	return true;
}

void FindSaddlePoints(int** a, int rowNo, int colNo, int ROWS, int COLS, int No) {
	if (rowNo < ROWS) {
		if (IsMinInRowN(a, rowNo, a[rowNo][colNo], 0, COLS) &&
			IsMaxInColK(a, colNo, a[rowNo][colNo], 0, ROWS)) {
			cout << setw(4) << ++No << setw(6) << rowNo << setw(6) << colNo << endl;
		}
		if (colNo < COLS - 1) {
			FindSaddlePoints(a, rowNo, colNo + 1, ROWS, COLS, No);
		}
		else {
			FindSaddlePoints(a, rowNo + 1, 0, ROWS, COLS, No);
		}
	}
}


int main()
{
	int rowCount, colCount;
	cout << "rowCount = "; cin >> rowCount;
	cout << "colCount = "; cin >> colCount;
	int** a = new int* [rowCount];
	for (int i = 0; i < rowCount; i++)
		a[i] = new int[colCount];
	InputRows(a, rowCount, colCount, 0);
	PrintRows(a, rowCount, colCount, 0);
	cout << "Sum elements in row with negative elements = " << sumInRowsWithNegative(a, rowCount, colCount) << endl << endl;
	cout << "Saddle points: min in row & max in col" << endl;
	cout << setw(4) << "No" << setw(6) << "Row" << setw(6) << "Col" << endl;
	int No = 0;
	FindSaddlePoints(a, 0, 0, rowCount, colCount, No);
	cout << endl;
	for (int i = 0; i < rowCount; i++)
		delete[] a[i];
	delete[] a;
	return 0;

}



