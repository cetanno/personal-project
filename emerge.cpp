// This program is to simulate the evolution happening in a population with several points and evolution cycle inputted by user.
// In each evolution cycle, point will be turned into TRUE state if the number of TRUE points adjacent to it orthogonally and diagonally are odd.

#include <iostream>
#include <windows.h>
using namespace std;

#define ROW 20
#define COL 20

bool jiman[ROW][COL];
bool repeat;

bool StartPoint (int*);
int Value (bool [][COL], int, int);
void Display (bool [][COL]);
bool Evolute (int*);
void Emerge (bool [][COL]);
void Colour(bool);
void Colour(int);

int main()
{
	int startpts;
	
	repeat = true;
	while (repeat)
		repeat = StartPoint(&startpts);
	
//	cout << startpts << endl;
	
	int point[startpts][2];
	
	for (int i = 0 ; i < startpts ; i++)
	{
		repeat = true;
		while (repeat)
		{
			cout << "What are the x y coordinates point "<< i + 1 << "?" << endl;
			
			for (int j = 0 ; j < 2 ; j++)
			{
				cin >> point[i][j];
				point[i][j]--;
			}
				
			if (point[i][0] >= 0 && point[i][0] < ROW && point[i][0] >= 0 && point[i][1] < COL)
				repeat = false;
			else
				cout << "\aInvalid input!!" << endl;
		}
	}
	
	int tempx,tempy;
	
	for (int i = 0 ; i < startpts ; i++)
	{
		tempx = point[i][0];
		tempy = point[i][1];
		
		jiman[tempx][tempy] = true;
	}
	
	int turn;
	
	repeat = true;
	while (repeat)
		repeat = Evolute(&turn);
	
	for (int i = 0 ; i < turn ; i++)
	{
		system("cls");
		cout << "Evolution #" << i << endl;
		Display(jiman);
		Emerge(jiman);
		Sleep(200);
	}
	
	cout << endl << "\aEvolution #" << turn << endl;
	Display(jiman);
	
	return 0;
}

bool StartPoint (int* x)
{
	cout << "\aHow many starting points?" << endl;
	
	cin >> *x;
		
	if (*x > 0 && *x <= 10)
		return false;
	else
	{
		cout << "\aInvalid input!!" << endl;
		return true;
	}
}

int Value (bool point[][COL], int x, int y)
{
	if (x >= 0 && x < ROW)
		if (y >= 0 && y < COL)
			if (point[x][y])
				return 1;
	
	return 0;
}

void Colour(bool state)
{
	if (state)
		SetConsoleTextAttribute((GetStdHandle(STD_OUTPUT_HANDLE)),78);
	else
		SetConsoleTextAttribute((GetStdHandle(STD_OUTPUT_HANDLE)),26);
}

void Colour(int c)
{
	SetConsoleTextAttribute((GetStdHandle(STD_OUTPUT_HANDLE)),c);
}

void Emerge (bool coord[][COL])
{
	int check;
	bool newcoord[ROW][COL];
	for (int i = 0 ; i < ROW ; i++)
		for (int j = 0 ; j < ROW ; j++)
		{
			check = Value(coord,i-1,j-1) + Value(coord,i-1,j) + Value(coord,i-1,j+1)
				 + Value(coord,i,j-1) + Value(coord,i,j+1)
				 + Value(coord,i+1,j-1) + Value(coord,i+1,j) + Value(coord,i+1,j+1);
			
			newcoord[i][j] = (check % 2);
		}
		
	for (int i = 0 ; i < ROW ; i++)
		for (int j = 0 ; j < ROW ; j++)
			coord[i][j] = newcoord[i][j];
}

void Display (bool board[][COL])
{
	for (int i = 0 ; i < ROW ; i++)
	{
		for (int j = 0 ; j < COL ; j++)
		{
			Colour(board[i][j]);
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	Colour(7);
}

bool Evolute (int* x)
{
	cout << "How many evolution would you like to see? (Max 1000)\n";
	cin >> *x;
		
	if (*x > 0 || *x <= 1000)
		return false;
	else
	{
		cout << "Invalid input!!" << endl;
		return true;
	}
}
