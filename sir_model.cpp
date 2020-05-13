// This program is to simulate the pandemic curve using 4 main variables.
// s = suspected percentage
// i = infected percentage
// r = recoverd percentage
// d = death percentage
// It calculates numerical using 4 differential equations that comes from these 4 variables.

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <cstring>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;

const float INFEC = 1.0; 	//MAX should be 1.0
const float RECOV = 0.3; 	//MAX should be 0.5 and RECOV + FATAL < INFEC
const float DEFY = 0.2;  	//MAX should be 0.5 and less than INFEC
const float FATAL = 0.4; 	//MAX should be 0.5 and RECOV + FATAL < INFEC

const int STEPS = 100;	//Steps per week
const int TIME = 100;	//Number of days of simulation.

double Change(double ori, double inc)
{
	return ori + (inc/STEPS);
}

ofstream out("logFile.txt");

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	//s is suspected, i is infected, r is recovered, d is dead
	//s,r,i and d should be nonnegative numbers with s+r+i+d = 0
	double s = 0.9999999, i = 1.0 - s;
	double r = 0.0, d = 0.0;
	
	//Shows the rate of change of each variable per day.
	double dsT, diT, drT, ddT;
	
	out 	<< "CETANNO'S SIRD (Suspected, Infected, Recovered, Dead) MODEL" << endl
		<< "-----------------------------------------------------------" << endl << endl
		<< "*Disclaimer" << endl << "This is just a modified version of SIR Model" << endl << endl
		<< "CONSTANTS USED" << endl
		<< "Infections Odds  >> " << INFEC << endl
		<< "Recovery Odds    >> " << RECOV << endl
		<< "Defiant Odds     >> " << DEFY << endl
		<< "Fatality Odds    >> " << FATAL << endl
		<< "Steps per Day    >> " << STEPS << endl
		<< "Total no of Days >> " << TIME << endl << endl;
	
	dsT = - s * i * INFEC;
	diT =   s * i * INFEC + r * i * DEFY - i * (FATAL + RECOV);
	drT =   i * RECOV - r * i * DEFY;
	ddT =   i * FATAL;
	
	for (int t = 0;t < TIME;t++)
	{
		out  << setprecision(7) << fixed << "Day " << t + 1 << ":- Current total non-infected >> " << s + r << endl 
			<< "S   >> " << s << "   I   >> " << i << "  R   >> " << r << "  D   >> " << d << endl;
		
		if (t < TIME - 1)
			out << setprecision(7) << fixed << "dsT >> " << dsT << "  diT >> " << diT << "  drT >> " << drT << "  ddT >> " << ddT << endl << endl;
		else
			out << endl;
		
		for (int step = 0; step < STEPS;step++)
		{
			s = Change(s,dsT);
			i = Change(i,diT);
			r = Change(r,drT);
			d = Change(d,ddT);
			
			dsT = - s * i * INFEC;
			diT =   s * i * INFEC + r * i * DEFY - i * (FATAL + RECOV);
			drT =   i * RECOV - r * i * DEFY;
			ddT =   i * FATAL;
		}
	}
	
	cout << "Done";
	return 0;
}


