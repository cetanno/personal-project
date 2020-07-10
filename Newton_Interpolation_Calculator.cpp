//THIS PROGRAM IS TO CALCULATE NEWTON'S LAW OF INTERPOLATION
//WHERE GIVEN SOME DATA, WE NEED TO PREDICT ANOTHER DATA AT ANOTHER POINT.
#include <iostream>
using namespace std;

int no;
float q, equate[5];

struct data{
	float x[5], fx[5];
};
data cb;

void Calc(int order, float *p)
{
	float diff[5];
	
	if (order < no)	cout << "Order " << order << " : ";
	
	for (int i = 0;i < no - order;i++)
	{
		diff[i] = (*(p+i+1) - *(p+i)) / (cb.x[i+order] - cb.x[i]);
		cout << diff[i] << " ";
	}
	cout << endl;
	
	equate[order] = diff[0];
	
	if (order < no) Calc(order+1, diff);
}

float Add(int term)
{
	if (term == no) return 0;
	
	float b = equate[term];
	for (int i = 0;i < term;i++) b *= q - cb.x[i];
		
	return b + Add(term + 1);
}

int main()
{
	cout << "Number of data?\n";
	cin >> no;
	
	for (int i = 0;i< no;i++)
	{
		cout << "\nInput data x and y?\n";
		cin >> cb.x[i] >> cb.fx[i];
	}
	
	equate[0] = cb.fx[0];
	Calc(1,cb.fx);
	
	cout << "\nInput desired x?\n";
	cin >> q;
	
	cout << Add(0);
	
	return 0;
}
