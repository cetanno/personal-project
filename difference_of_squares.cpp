// This program is to generate integers that can be expressed as positive difference of 2 squares.

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <cstring>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

const int M = 1000;
const int MAX = M * M;
const int LIST = MAX;

bool possible[MAX + 1];
int num[LIST];

ofstream out("Difference_of_Squares.txt");

int main()
{
	
//	ios_base::sync_with_stdio(false);
//	cin.tie(NULL);
	
	
	for(int i = 0;i <= MAX;i++)
		possible[i] = false;
	
	
	for(int i = 0;i <= M;i++)
		for (int j = 0;j <= i;j++)
			possible[i*i-j*j] = true;
	
	int k = 0;

		
	for(int i = 0;i <= MAX;i++)
	{
		if (possible[i])
		{
			num[k] = i;
			k++;
		}
			
	}
		
	out << "Integers that can be expressed as a^2-b^2 with a>=b are" << endl;
	
	for (int i = 0;i < k;i++)
		out << num[i] << " ";
		
	out << "\nA total of " << k << " integers can be found from 0 to " << MAX << ".";
	
	cout << "Done";

	return 0;
}


