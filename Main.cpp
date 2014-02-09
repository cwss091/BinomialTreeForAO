/* Math/ISye 6767 Homework3
 * Yuliang Li
 * GTID 903012703
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "BinomialTree.h"
#include "OptionPrice.h"
#include "BSCalibra.h"
#include "Greek.h"

#include "IO.h"

const double DofY = 365.0; // days of one year is 365 

using namespace std;

int main()
{
	ifstream InputIdx("./InputIndex.txt");
	if(!InputIdx)
	{  
		cout << "No input index file, please set your input index file" << endl;
	}

	double ini_spot; // initial spot price
	double div_y; // dividended yield
	double rf_rate; // risk free rate
	double d_expirate; // expirate date
	bool iscall; // if call is true
	vector<double> vol(2); // implied volatility (former one), and historical volatility
	vector<double> strike_p(4); // strike price

	input_data(ini_spot, rf_rate, div_y, d_expirate, iscall, vol, strike_p, InputIdx);
	d_expirate = d_expirate / DofY; // change days to years
	cout << "initial spot " << ini_spot << endl;
	cout << "dividend yield " << div_y << endl;
	cout << "risk free rate " << rf_rate << endl;
	
	cout << " implied volatility and historical volatility are ";
	showvector(vol);
	cout << " the strike prices for pricing option are ";
	showvector(strike_p);

	// Calibrate the Binomial Tree with European pricer
	double udlyp[2] = {100.0, 110.0}; // underlying price's range
	double volat[2] = {0.10, 0.30}; // volatility' range
	
	EuroCalibra EuCali(rf_rate, div_y, d_expirate, 0.0, iscall, 1); // European put option to calibrate
	double calistrk = 100.0; // strike price for caliration
	int N = EuCali(udlyp[0], udlyp[1], volat[0], volat[1], calistrk); // the optimal tree steps
	cout << "the optimal N is " << N << endl;

	//price American Option and calculate delta
	int sizevol = vol.size();
	int sizestrk = strike_p.size();
	vector<vector<double> > optvalue; // option value storage
	
	// to calculate delta of the day 100 and 200 before expiration, revise the day to get integer and find appropriate row
	int r2expir[2] = {0};
	double d2expir = 100.0 / DofY;
	for(int i = 0; i < 2; i++)
	{
		double r2e = (d_expirate - d2expir) / d_expirate * N;
		r2expir[i] = int((d_expirate - d2expir) / d_expirate * N);
		if(r2e - 0.5 > r2expir[i])
		{
			r2expir[i] += 1;
		}
		d2expir += 100.0 / DofY;
	}

	ofstream OutDelta("./deltafile.csv"); // file to store delta vector
	OutDelta.open("deltafile.csv", ofstream::out);
	OutDelta.close();

	bool iseuro = 0; // price a american option
	
	for(int i = 0; i < sizevol; i++)
	{ 
		vector<double> opv_str(sizestrk); // option value for different strike price storage
		for(int j = 0; j < sizestrk; j++)
	 	{
			Stock_BiTree SBTree(N, strike_p[j], vol[i], d_expirate); // Stock tree
			SBTree.zeros();
			SBTree.setdata(ini_spot, 0, 0);
			SBTree.forward_fill();
			Option_BiTree OPTree(rf_rate, div_y, strike_p[j], iscall, iseuro, SBTree); // option tree
			OPTree.zeros();
			VanillaPay Amriko; // payoff of American Option
			Amriko.setvalue(strike_p[j], iscall);
			opv_str[j] = pricer_smooth(SBTree, OPTree, Amriko);
			cout << "volatity is " << vol[i] << " and strike price is " << strike_p[j] << " , the option price at time 0 is " << opv_str[j] << "." << endl;
			
			// calculate delata
			OutDelta.open("deltafile.csv", ofstream::out | ofstream::app);
			OutDelta << "volatility" << "," << vol[i] << "," << "strike price" << "," << strike_p[j] << endl;
			OutDelta.close();

			d2expir = 100;
			for(int k = 0; k < 2; k++)
			{
				vector<double> optv = OPTree.Rowshow(r2expir[k]); // option value of time reexpir[k]
				vector<double> stkv = SBTree.Rowshow(r2expir[k]); // stock price
				vector<double> del = delta(stkv, optv); // delta;

				OutDelta.open("deltafile.csv", ofstream::out | ofstream::app);
				OutDelta << "days before expiration" << "," << d2expir << ",";
				OutDelta << "option value(up)" << "," << "delta(down)" << endl;
				print_vector(OutDelta,optv, del);
				//print_vector(OutDelta,stkv, optv);
				OutDelta << endl;
				OutDelta.close();
				d2expir += 100;
			}			
		}
		optvalue.push_back(opv_str);
	}

	// output the option value to a csv file
	ofstream opfile("./OptionValue.csv");
	opfile << "volatility" << "," << "strike price" << "," << "option value" << endl;
	print_vector(opfile, vol, strike_p, optvalue);
	opfile.close();
	
	return 0;
}


