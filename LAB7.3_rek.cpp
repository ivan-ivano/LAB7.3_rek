#include <iostream>
#include <iomanip>

using namespace std;
void Input(int** a, const int rowCount, const int colCount);
void Print(int** a, const int rowCount, const int colCount);
int sumInRowsWithNegative(int** matrix, int rows, int cols);
void Part2_SaddlePointRow(int** a, const int rowCount, const int colCount, int& No, const int rowNo, int colNo);
void Part2_SaddlePointRows(int** a, const int rowCount, const int colCount, int& No, int rowNo);
bool IsMaxInRowN(int** a, const int rowNo, const int max, const int colCount, int colNo);
bool IsMinInColK(int** a, const int colNo, const int min, const int rowCount, int rowNo);

int main()
{
	int rowCount, colCount;
	cout << "rowCount = "; cin >> rowCount;
	cout << "colCount = "; cin >> colCount;
	int** a = new int* [rowCount];
	for (int i = 0; i < rowCount; i++)
		a[i] = new int[colCount];
	Input(a, rowCount, colCount);
	Print(a, rowCount, colCount);
	cout << "Sum elements in row with negative elements = " << sumInRowsWithNegative(a, rowCount, colCount) << endl << endl;
	cout << "Saddle points: max in row & min in col" << endl;
	cout << setw(4) << "No" << setw(6) << "Row" << setw(6) << "Col" << endl;
	
	int No = 0;
	Part2_SaddlePointRows(a, rowCount, colCount, No, 0);
	cout << endl;
	for (int i = 0; i < rowCount; i++)
		delete[] a[i];
	delete[] a;
	return 0;

}

void Input(int** a, const int rowCount, const int colCount)
{
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < colCount; j++)
		{
			cout << "a[" << i << "][" << j << "] = ";
			cin >> a[i][j];
		}
		cout << endl;
	}
}

void Print(int** a, const int rowCount, const int colCount)
{
	cout << endl;
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < colCount; j++)
			cout << setw(4) << a[i][j];
		cout << endl;
	}
	cout << endl;
}

int sumInRowsWithNegative(int** matrix, int rows, int cols) {
	int sum = 0;

	for (int i = 0; i < rows; ++i) {
		bool hasNegative = false;
		for (int j = 0; j < cols; ++j) {
			if (matrix[i][j] < 0) {
				hasNegative = true;
				break;
			}
		}
		if (hasNegative) {
			for (int j = 0; j < cols; ++j) {
				sum += matrix[i][j];
			}
		}
	}

	return sum;
}


bool IsMaxInRowN(int** a, const int rowNo, const int max, const int colCount, int colNo)
{
	if (a[rowNo][colNo] > max)
		return false;
	if (colNo < colCount - 1)
		return IsMaxInRowN(a, rowNo, max, colCount, colNo + 1);
	else
		return true;
}
bool IsMinInColK(int** a, const int colNo, const int min, const int rowCount, int rowNo)
{
	if (a[rowNo][colNo] < min)
		return false;
	if (rowNo < rowCount - 1)
		return IsMinInColK(a, colNo, min, rowCount, rowNo + 1);
	else
		return true;
}
void Part2_SaddlePointRow(int** a, const int rowCount, const int colCount, int& No, const int rowNo, int colNo)
{
	if (IsMaxInRowN(a, rowNo, a[rowNo][colNo], colCount, 0) &&
		IsMinInColK(a, colNo, a[rowNo][colNo], rowCount, 0))
	{
		cout << setw(4) << ++No << setw(6) << rowNo << setw(6) << colNo << endl;
	}
	if (colNo < colCount - 1)
		Part2_SaddlePointRow(a, rowCount, colCount, No, rowNo, colNo + 1);
}
void Part2_SaddlePointRows(int** a, const int rowCount, const int colCount, int& No, int rowNo)
{
	Part2_SaddlePointRow(a, rowCount, colCount, No, rowNo, 0);
	if (rowNo < rowCount - 1)
		Part2_SaddlePointRows(a, rowCount, colCount, No, rowNo + 1);
}