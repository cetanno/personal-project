// This program is the sudoku solver program.
// It reads a puzzle from an input file, uses backtracking (aka bruteforce) to try solve it.
// Finally, it outputs all possible solutions to the puzzle in an output file.
// This program is also implemented in the Sudoku Generator Algorithm.

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

ifstream in("Input_Sudoku.txt");
ofstream out("Output_Sudoku.txt");

//GRID SETUP
string label;
char grid[9][9];


//BRUTE FORCE SETUP
int emptycells[81], maxempty = 0, solution = 0;

//CHECKING ROW COLLISION
bool RowCollide(int x)
{
	int r = x / 9, c = x % 9;
	
	for (int i = 0;i < 9;i++)
	{
		if (i == c) continue;
		if (grid[r][i] == label[9]) continue;
		
		if (grid[r][i] == grid[r][c])
			return true;
	}
	return false;
}

//CHECKING COLUMN COLLISION
bool ColCollide(int x)
{
	int r = x / 9, c = x % 9;
	
	for (int i = 0;i < 9;i++)
	{
		if (i == r) continue;
		if (grid[i][c] == label[9]) continue;
		
		if (grid[i][c] == grid[r][c])
			return true;
	}
	return false;
}

//CHECKING BOX COLLISION
bool BoxCollide(int x)
{
	int r = x / 9, c = x % 9;
	int trir = r / 3, tric = c / 3;
	
	for (int i = 0;i < 3;i++)
		for (int j = 0;j < 3;j++)
		{
			if (i == r % 3 && j == c % 3) continue;
			if (grid[i + 3 * trir][j + 3 * tric] == label[9]) continue;
			
			if (grid[i + 3 * trir][j + 3 * tric] == grid[r][c])
				return true;
		}
	return false;
}

bool isBad(int x)
{
	return BoxCollide(x) || RowCollide(x) || ColCollide(x);
}

void BFSolve(int k)
{
//	cout << k << " ";
	if (k == maxempty)
	{
		solution++;
		out << "Solution " << solution << " :" << endl;
		for(int i = 0;i < 9;i++)
		{
			for (int j = 0;j < 9;j++)
				out << grid[i][j] << " ";
			out << endl;
		}
		
		cout << "Solution Found\a\n";
		return;
	}
	
	int r = emptycells[k] / 9, c = emptycells[k] % 9;
	
	for(int i = 0;i<9;i++)
	{
		grid[r][c] = label[i];
		if (!isBad(emptycells[k]))
			BFSolve(k+1);
		grid[r][c] = label[9];
	}
//	cout << endl;
	return;
}
 
 int main()
{             
//	INPUT LABELS AND GRID INCLUDING ANALYZING EMPTY CELLS
	in >> label;
//	cout << label << endl;
	for(int r = 0;r < 9;r++)
	{
		for(int c = 0;c < 9;c++)
		{
			in >> grid[r][c];
			if (grid[r][c] == label[9])
			{
				maxempty++;
				if (maxempty > 64)
				{
					cout << "Invalid";
					return 0;
				} 
				else	emptycells[maxempty-1] = r * 9 + c;
			}
//			cout << grid[r][c] << " ";
		}
//		cout << endl;
	}
//	cout << maxempty;

	clock_t start = clock();
	BFSolve(0);
	clock_t end = clock();
	
	ull elapsed = (end - start) / CLOCKS_PER_SEC;
	
	cout << "Time Elapsed : " << elapsed << " seconds";
	out << "Time Elapsed : " << elapsed << " seconds";
	return 0;
}


