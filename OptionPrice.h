#ifndef _OPTIONPRICE_H__
#define _OPTIONPRICE_H__

#include <iostream>
#include <vector>
#include "BinomialTree.h"
#include "OptionPay.h"
#include "BSE.h"

/* Price the option */

//regular method
template <class T>
double pricer(Stock_BiTree& st, Option_BiTree& ot, T pay)
{
	int N = st.deep();
	//the payoff of option at expiration date
	std::vector<double> lastpay = st.Rowshow(N);
	int K = lastpay.size();
	for(int i = 0; i < K; i++)
	{   
		lastpay[i] = pay(lastpay[i]);
	}
	if(ot.euro == true)
	{    
		ot.backward_fill(lastpay);
	}
	else
	{    
		// construct a tree which store the intrinsic value of the American option
		BinomialTree in_value(N-1, 0.0);
		in_value.zeros();
		int in_N = in_value.deep();

		for(int i = 0; i <= in_N; i++)
	  	{  
			for(int j = 0; j <= i; j++)
	  		{  
				in_value.setdata(pay(st.Datashow(i, j)), i, j);
			}
		}
		std::vector<std::vector<double> > intrin = in_value.Datashow();
		ot.backward_fill(lastpay, intrin);
	}
	return ot.get_root();
}

//smooth method, option prices at second last date determined by Black-Scholes Model, increase the speed of convergence
template <class T>
double pricer_smooth(Stock_BiTree& st, Option_BiTree& ot, T& pay)
{
	int N = st.deep();
	std::vector<double> lastpay = st.Rowshow(N);
	int K = lastpay.size();
	for(int i = 0; i < K; i++)
	{  
		lastpay[i] = pay(lastpay[i]);
	}
	ot.setdata(lastpay, N);
	// BS Model get the second last continuous value of Option 
	double ttoexpir = ot.expiry - ot.delta_t;
	BS_EuroOption EuroBS(ot.strike, ot.rate, ot.dividend, ot.vol, ot.expiry, ot.call, ttoexpir);
	std::vector<double> seclastpay(K-1);
	for(int i = 0; i < K-1; i++)
	{ 
		seclastpay[i] = EuroBS(st.Datashow(N-1, i));
	}

	if(ot.euro == true)
	{   
		ot.backward_fill(seclastpay);
	}
	else
	{   
		// construct a tree which store the intrinsic value of the American option
		BinomialTree in_value(N-2, 0.0);
		in_value.zeros();
		int in_N = in_value.deep();
		for(int i = 0; i <= in_N; i++)
	  	{ 
			for(int j = 0; j <= i; j++)
	  		{ 
				in_value.setdata(pay(st.Datashow(i, j)), i, j);
			}
		}
		std::vector<std::vector<double> > intrin = in_value.Datashow();
		ot.backward_fill(seclastpay, intrin);
	}

	return ot.get_root();
}


#endif
