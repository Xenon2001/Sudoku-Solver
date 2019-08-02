#include <iostream>
#include <fstream>

using namespace std;
ifstream fin("sudokuInput.txt");
ofstream fout("sudokuOutput.txt");
int SudokuBoard[10][10], nr = 1;

struct position
{
	int row, column;
}v[81];

void display()
{
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= 9; j++)
			fout << SudokuBoard[i][j] << ' ';
		fout << '\n';
	}
}

bool check(int k)
{
	//verifying the row
	for (int i = 1; i <= 9; i++)
		if (SudokuBoard[v[k].row][i] == SudokuBoard[v[k].row][v[k].column] && i != v[k].column)
			return false;
	//verifying the column
	for (int i = 1; i <= 9; i++)
		if (SudokuBoard[i][v[k].column] == SudokuBoard[v[k].row][v[k].column] && i != v[k].row)
			return false;
	//verifying the submatrix
	int row = v[k].row;
	int column = v[k].column;
	if (row <= 3)
		row = 1;
	else
		if (row <= 6)
			row = 4;
		else
			row = 7;
	if (column <= 3)
		column = 1;
	else
		if (column <= 6)
			column = 4;
		else
			column = 7;
	for (int i = row; i <= row + 2; i++)
		for (int j = column; j <= column + 2; j++)
			if (SudokuBoard[i][j] == SudokuBoard[v[k].row][v[k].column] && (i != v[k].row || j != v[k].column))
				return false;
	return true;


}

void backtracking(int k)
{
	if (k - 1 == nr)
	{
		display();
		exit(0);
	}
	else
		for (int i = 1; i <= 9; i++)
		{
			SudokuBoard[v[k].row][v[k].column] = i;
			if (check(k))
				backtracking(k + 1);
			SudokuBoard[v[k].row][v[k].column] = 0;
		}
}

int main()
{
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 9; j++)
		{
			fin >> SudokuBoard[i][j];
			if (SudokuBoard[i][j] == 0)
			{
				v[nr].row = i;
				v[nr].column = j;
				nr++;
			}

		}
	nr--;
	backtracking(1);
	return 0;
}
