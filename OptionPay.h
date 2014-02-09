#ifndef _OPTIONPAY_H__
#define _OPTIONPAY_H__

/* Payoff of the option */

#include <iostream>
#include <vector>
//#include "BinomialTree.h"

class Payoff
{ 
	protected:
		double strike; //strike price
		bool call; // if call, be true
	public:
		Payoff(){}
		void setvalue(double _strike, bool _call); // setvalue
		virtual double operator() (double spot) = 0;
		~Payoff(){}
};

// Payoff of Vanilla Option
class VanillaPay: public Payoff
{ 
	public:
		double operator() (double spot);
};

#endif

