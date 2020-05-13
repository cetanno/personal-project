// This program is to generate integers that can be expressed as sum of 2 squares (not necessarily pythagorean triples).

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
const int MAX = M * M * 2;
const int LIST = MAX / 5;

bool possible[MAX + 1];
int num[LIST];

ofstream out("Squarable_Integers.txt");

int main()
{
	
//	ios_base::sync_with_stdio(false);
//	cin.tie(NULL);
	
	
	for(int i = 0;i <= MAX;i++)
		possible[i] = false;
	
	
	for(int i = 0;i <= M;i++)
		for (int j = i;j <= M;j++)
			possible[i*i+j*j] = true;
	
	int k = 0;

		
	for(int i = 0;i <= MAX;i++)
	{
		if (possible[i])
		{
			num[k] = i;
			k++;
		}
			
	}
		
	out << "Integers that can be expressed as the sum of 2 squares are" << endl;
	
	for (int i = 0;i < k;i++)
		out << num[i] << " ";
		
	out << "\nA total of " << k << " squarable integers can be found from 0 to " << MAX << ".";
	
	cout << "Done";

	return 0;
}


