// This program is to generate a regular minimal 9 X 9 sudoku.
// It generates based on the seed template below.
// 123|456|789
// 456|789|123
// 789|123|456
// ---+---+---
// 891|234|567
// 234|567|891
// 567|891|234
// ---+---+---
// 678|912|345
// 912|345|678
// 345|678|912
// Then, it randomly removes a cell and uses backtracking (aka brutefore) to try to solve the grid.
// If the cell can be removed, it stays removed, or else, it is declared as taboo cell.
// The process continues until all cells are removed or tabooed.

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

////////////
// SETUPS //
////////////

//SOME DEVELOPER CONSTANT
#define MAXSUDOKU 10

//GENERAL
char grid[9][9], sol[9][9];
string label = "1234567890";

//SELECTING CLUES
int maxclues, taboo, unused[81];
bool taken[81];

//SOLVING SETUP
int emptycells[81], maxempty, solution;

//OUTPUT
ofstream out("Gallery of Sudoku Problems.txt");
ofstream outsol("Gallery of Sudoku Solutions.txt");


///////////////////////
// SOLVING ALGORITHM //
///////////////////////

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

//CHECKING IF THERE IS ANY COLLISION
bool isBad(int x)
{
	return BoxCollide(x) || RowCollide(x) || ColCollide(x);
}

//SOLVE BY BRUTEFORCE
void SolveGrid(int k)
{
//	cout << k << " ";
	if (solution > 1) return;
	
	if (k == maxempty)
	{
		solution++;
		return;
	}
	
	int r = emptycells[k] / 9, c = emptycells[k] % 9;
	
	for(int i = 0;i<9;i++)
	{
		grid[r][c] = label[i];
		if (!isBad(emptycells[k]))
			SolveGrid(k+1);
		grid[r][c] = label[9];
	}
//	cout << endl;
	return;
}

//ARRANGE EMPTY CELLS
void ArrangeEmpties()
{
	int x = 0;
	for (int i = 0;i < 81;i++)
		if (grid[i / 9][i % 9] == label[9])
		{
			emptycells[x] = i;
			x++;
		}
}


///////////////////////////////////////
// PSEUDO-RANDOMLY GENERATING SUDOKU //
///////////////////////////////////////

//FILLING THE FIRST ROW
void FillLine1()
{
	int taken[9], temp;
	bool repeat;
	
	for (int i = 0;i < 9;i++)
	{
		do
		{
			repeat = false;
			temp = rand() % 9 + 1;
			for(int j = 0;j<i;j++)
				if (taken[j] == temp)
				{
					repeat = true;
					break;
				}
		}while(repeat);
		
		taken[i] = temp;
		grid[0][i] = label[temp-1];
	}
}

//DUPLICATE AND SHIFT TO THE NEXT ROW
void Shift(int row1, int row2, int shift)
{
	for (int i = 0;i < 9;i++)
		grid[row2][i] = grid[row1][(i+shift) % 9];
}

//RANDOMLY SWAPPING 2 ROWS
void SwapRow(int group)
{
	int temp, steps = rand() % 4;
	int row1, row2;
	
	while(steps--)
	{
		row1 = rand() % 3;
		row2 = (row1 + 1) % 3;
		row1 += 3 * group;
		row2 += 3 * group;
		
		for (int i = 0;i < 9;i++)
		{
			temp = grid[row1][i];
			grid[row1][i] = grid[row2][i];
			grid[row2][i] = temp;
		}
	}
}

//RANDOMLY SWAPPING 2 COLUMNS
void SwapCol(int group)
{
	int temp, steps = rand() % 4;
	int col1, col2;
	
	while(steps--)
	{
		col1 = rand() % 3;
		col2 = (col1 + 1) % 3;
		col1 += 3 * group;
		col2 += 3 * group;
		
		for (int i = 0;i < 9;i++)
		{
			temp = grid[i][col1];
			grid[i][col1] = grid[i][col2];
			grid[i][col2] = temp;
		}
	}
}

//SELECTING 3 CLUES TO BE DELETED
void InitialReduce()
{
	int temp;
	bool repeat;
	
	for (int i = 0;i < 3;i++)
	{
		do
		{
			repeat = false;
			temp = rand() % 81;
			for(int j = 0;j<i;j++)
				if (emptycells[j] == temp)
				{
					repeat = true;
					break;
				}
		}while(repeat);
		
		emptycells[i] = temp;
		taken[temp] = true;
		grid[temp / 9][temp % 9] = label[9];
	}
	
	maxempty += 3;
	maxclues -= 3;
}

//PRINTING THE GRID
void PrintGrid()
{
	for (int i = 0 ; i < 9 ; i++)
	{
		for (int j = 0 ; j < 9 ; j++)
			cout << grid[i][j] << " ";
		cout << endl;
	}
}

//GENERATE GRID
void Generate()
{
	FillLine1();
	Shift(0,1,3);
	Shift(1,2,3);
	Shift(2,3,1);
	Shift(3,4,3);
	Shift(4,5,3);
	Shift(5,6,1);
	Shift(6,7,3);
	Shift(7,8,3);
	SwapRow(0);
	SwapRow(1);
	SwapRow(2);
	SwapCol(0);
	SwapCol(1);
	SwapCol(2);
}


//////////////////
// MAIN PROGRAM //
//////////////////

int main()
{
	ios_base::sync_with_stdio(false);
	srand(time(NULL));
	
	int temp, k, t;
	
//	JUST TO SEE HOW LONG DOES IT TAKES TO GENERATE A SUDOKU
	clock_t start, end;
	double elapsed;
	
	out << label << endl;
	outsol << label << endl;
	
	for (int x = 0;x < MAXSUDOKU;x++)
	{
//		PROPER INITIALIZATION
		start = clock();
		maxclues = 81;
		maxempty = 0;
		taboo = 0;
		
//		GENERATE RANDOM GRID
		cout << "GENERATING SUDOKU " << x + 1 << endl;
		Generate();
		
//		TRANSFERING THE SOLUTION
		for (int i = 0 ; i < 9 ; i++)
			for (int j = 0 ; j < 9 ; j++)
				sol[i][j] = grid[i][j];
		
		PrintGrid();
		
		cout << "CREATING PROBLEM FOR SUDOKU " << x + 1 << endl;
		for (int i = 0;i< 81;i++)
			taken[i] = false;
		
//		TAKING OUT THE FIRST 3 CLUES (REMOVING THESE 3 WILL STILL MAINTAIN THE UNIQUENESS OF THE SOLUTION)
		InitialReduce();
		k = 3;
		cout << "REDUCING NUMBER OF CLUES FOR SUDOKU " << x + 1 << endl
			<< "PICK  CELL_NO  STATUS  EMPTY  CLUES  TABOO\n";
		while(true)
		{
			t = 0;
			for (int i = 0;i< 81;i++)
			{
				if (taken[i] == false)
				{
					unused[t] = i;
					t++;
				}
			}
			temp = unused[rand() % t];
			
			k++;
			taken[temp] = true;
			cout << setw(4) << k << "  " << setw(7) << temp << "  ";
			grid[temp / 9][temp % 9] = label[9];
			
			ArrangeEmpties();
			maxempty++;
			maxclues--;
			
//			ATTEMPT TO SOLVE THE SUDOKU
			solution = 0;
			SolveGrid(0);
			
			if(solution > 1)
			{
//				IF THE CELL REMOVED MAKES THE SUDOKU NON-UNIQUE, TABOO THE CELL
				cout << "TABOO";
				taboo++;
				maxempty--;
				maxclues++;
				grid[temp / 9][temp % 9] = sol[temp / 9][temp % 9];
			}
			else if(solution < 1)
				{
					cout << "\aSOMETHING WRONG HERE, YOU ARE NOT SUPPOSED TO GET NO SOLUTION" << endl;
					return 1;
				}
				else cout << "EMPTY";
			
			cout << "  " << setw(5) << maxempty << "  " << setw(5) << maxclues << "  " << setw(5) << taboo << endl;
			if(taboo == maxclues) break;
		}
		
//		SUCCESSFUL ATTEMPT
		cout	<< "\aGENERATION SUCCESS!!" << endl;
		cout << "PRINTING THE PROBLEM AND THE SOLUTION FOR SUDOKU " << x + 1 << endl;
		PrintGrid();
		
//		PRINT OUT THE SUDOKU PROBLEM		
		out	<< "SUDOKU " << x + 1 << " PROBLEM :\n"
			<< maxclues << " CLUES\n";
		for (int i = 0 ; i < 9 ; i++)
		{
			for (int j = 0 ; j < 9 ; j++)
				out << grid[i][j] << " ";
			out << endl;
		}
		
//		CALCULATING THE TIME ELAPSED DURING GENERATION
		end = clock();
		elapsed = (end - start) * 1000 / CLOCKS_PER_SEC;
		cout << "ELAPSED TIME : " << elapsed << " MS" << endl << endl;
		out << "ELAPSED TIME : " << elapsed << " MS" << endl << endl;
		
//		PRINT OUT THE SUDOKU SOLUTION	
		outsol << "SUDOKU " << x + 1 << " SOLUTION :\n";
		for (int i = 0 ; i < 9 ; i++)
		{
			for (int j = 0 ; j < 9 ; j++)
				outsol << sol[i][j] << " ";
			outsol << endl;
		}
		outsol << endl;
	}
	
	cout << "DONE\a";
	return 0;
}
