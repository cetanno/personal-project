// This problem is to simulate a dart problem from a Numberphile interview with 3B1B.
// In each case, it randomly generates 2 positive rational values <= 1, square each of them and add them together.
// If the sum is not more than 1, it adds another 2 values and repeats until the sum is more than 1.
// Throughout the process, it calculates the number of repetition required to exceed 1.

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

#define PRECISE 10000
#define CASES 10000
#define POINT 10

ofstream out("DartProb.txt");

int main()
{
//	ios_base::sync_with_stdio(false);
//	cin.tie(NULL);
	srand(time(NULL));
	
	float x , y , sum;
	int point, max = 0, total = 0, overload = 0;
	int board[POINT];
	
	out 	<< "PRECISION  = " << PRECISE << endl
		<< "TEST CASES = " << CASES << endl << endl;
	
	for(int i = 0;i< POINT;i++) board[i] = 0;
	
	for (int i = 0;i<CASES;i++)
	{
		sum = 0.0;
		point = 0;
		
		out << "Case " << i+1 << ":\n";
		
		while (true)
		{
			x = float (rand() % PRECISE) / PRECISE;
			y = float (rand() % PRECISE) / PRECISE;
			sum += x * x + y * y;
			out << "Points = " << point << "   x-coord = " << x << "   y-coord = " << y << "   sum = " << sum << endl;
			
			if (sum <= 1)	point++;
			else break;
		}
		
		out << "Total points = " << point << endl << endl;
		
		if (point < POINT) board[point]++;
		else overload++;
		
		if (point > max)
			max = point;
	}
	
	for(int i = 0;i< POINT;i++) total += board[i] * i;
	
	for(int i = 0;i< POINT;i++)
	out	<< i << "-point(s) cases         = " << board[i] << endl;
	
	out	<< "Overpoints cases         = " << overload << endl
		<< "Max total points         = " << max << endl
		<< "Cummulative total points = " << total << endl;
	
	cout << "Done";

	return 0;
}


