#ifndef _GREEK_H__
#define _GREEK_H__

/* Greeks of option price */

#include <iostream>
#include <vector>
#include "BinomialTree.h"

/*class greek
{
	std::vector<std::vector<double> > stockp; // underlying price
	std::vector<std::vector<double> > optionp; // option value
	double rate; // risk free rate
	double vol; // volatility
	public:
	greek(const Stock_BiTree& SBT, const Option_BiTree& OBT);
	greek(const Stock_BiTree& SBT, const Option_BiTree& OBT, const double rate_, const double vol_);*/

std::vector<double> delta(std::vector<double> stockp, std::vector<double> optionp); // calculate delta

#endif


