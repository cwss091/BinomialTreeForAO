#include "BSCalibra.h"


using namespace std;

int EuroCalibra::operator()(const double& udly_bgn, const double& udly_end, const double& vol_bgn, const double & vol_end, const double& price)
{
	//udly is uderlyprice which is used as spot price
	//vol is volatility
	//price is strike price
	//
	int N = 2;
	double udly = udly_bgn;
	double vol = vol_bgn;
	bool flag = true; //for break in loop
	
	double gate = 0.05; // gate for loop stop
	double dis = 0.0; // prices' difference calculated by binomial tree and Black-Scholes Model
	double bs_p; // price determined by Black Scholes Model
	double bt_p; // price determined by Binomial Tree 

	while(flag == true)
	{
		udly = udly_bgn;
		while(udly <= udly_end)
		{
			//cout << udly << endl;
			vol = vol_bgn;
			while(vol <= vol_end)
			{
				BS_EuroOption EuroBS(price, rf_rate, div_yield, vol, expiry, call, 0.0);
				bs_p = EuroBS(udly); // price determined by Black Scholes Model

				Stock_BiTree STree(N, udly, vol, expiry); // stock tree
				STree.zeros();
				STree.setdata(udly, 0, 0);
				STree.forward_fill();

				Option_BiTree OTree(rf_rate, div_yield, price, call, euro, STree); // Option tree
				OTree.zeros();

				VanillaPay opay; // payoff
				opay.setvalue(price, call);

				bt_p = pricer_smooth(STree, OTree, opay); // price from binomial tree
				dis = fabs(bs_p - bt_p);
				/*if(N==32)
				{
					if(udly == 106.0 && vol == 0.25)
					{
						cout << bs_p<< endl;
						cout << bt_p<< endl;
					}
				}*/
				if(dis >= gate)
				{
					flag = false;
					break;
				}
				vol += 0.05;
			}
			if(flag == false)
			{
				break;
			}
			udly += 1.0;
		}
		if(flag == false)
		{
			flag = true;
			N *= 2;
		}
		else
		{
			break;
		}
	}

	return N;
}

