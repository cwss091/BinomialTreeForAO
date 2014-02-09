/** These are the functions declared in IO.h. **/

#include "IO.h"

using namespace std;

void input_data(double& spot, double& rate, double& div_yield, double& expiry, bool& callo, vector<double>& volatility, vector<double>& strike, ifstream& infile)
{
    infile >> spot; // spot price
    infile >> rate; // risk free rate
    infile >> div_yield; // dividend yield
    infile >> expiry; // expire date
	infile >> callo;
	double temp_vol;
	int sizev = volatility.size();
	for(int i = 0; i < sizev; i++)
	{
		infile >> temp_vol;
		volatility[i] = temp_vol;
	}
	//cout << volatility[0] << endl;
	int sizes = strike.size();
	double temp_str;
	for(int i = 0; i < sizes; i++)
	{ 
		infile >> temp_str; // strike price
		strike[i] = temp_str;
	}
}

void print_vector(ofstream& outfile, vector<double> v)
{
    vector<double>::iterator it = v.begin();
	while(it != v.end()) outfile << *it++ << ",";
	cout << endl;
	cout << endl;
}

void print_vector(ofstream& outfile, vector<double> u, vector<double> v)
{
	vector<double>::iterator it = v.begin();
    vector<double>::iterator ip = u.begin();
    while(it != v.end()) outfile << *ip++ << "," << *it++ << endl;
}

void print_vector(ofstream& outfile, vector<double> u, vector<double> v, vector<vector<double> > x)
{ 
	int usize = u.size();
	int vsize = v.size();
	for(int i = 0; i < usize; i++)
	{ 
		for(int j = 0; j < vsize; j++)
		{ 
			outfile << u[i] << "," << v[j] << "," << x[i][j] << endl;
		}
	}
}


void showvector(vector<double>& v)
{
	vector<double>::iterator it = v.begin();
	while(it != v.end()) 
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}
