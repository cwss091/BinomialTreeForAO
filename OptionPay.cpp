#include "OptionPay.h"

/* Payoff of the option */

using namespace std;

void Payoff::setvalue(double _strike, bool _call)
{
	strike = _strike;
	call = _call;
}

double VanillaPay::operator() (double spot) // payoff of vanilla option
{
	if(call == true)
	{
		return (spot - strike > 0.0)?(spot - strike):0.0;
	}
	else
	{
		return (strike - spot > 0.0)?(strike - spot):0.0;
	}
}

