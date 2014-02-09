#ifndef _BSCALIBRA_H__
#define _BSCALIBRA_H__

/* Use Black-Scholes Model to calibrate BinomialTree model which prices european option */

#include <iostream>
#include <vector>
#include <cmath>
#include "BSE.h"
#include "BinomialTree.h"
#include "OptionPrice.h"

class EuroCalibra
{ 
	double rf_rate; // risk-free rate
	double div_yield; // diveidend yield
	double expiry; // expire date
	double t; // current time
	bool call; // true if call option
	bool euro; // true if euro option
	public:
	EuroCalibra(const double& _rate, const double& _div, const double& _expiry, const double& _t, const bool& _call, const bool& euro_):rf_rate(_rate), div_yield(_div), expiry(_expiry), t(_t), call(_call), euro(euro_){}
	int operator() (const double& udly_bgn, const double& udly_end, const double& vol_bgn, const double & vol_end, const double& price); // fucton object to get best N for Binomial Tree
	//udly is uderlyprice which is used as spot price
	//vol is volatility
	//price is strike price
	~EuroCalibra(){}
};

#endif


