#include "Greek.h"

using namespace std;

vector<double> delta(vector<double> stockp, vector<double> optionp)
{
	// underlying price at some time
	// option price at some time
	vector<double>::iterator i = stockp.begin();
	vector<double>::iterator j = optionp.begin();
	vector<double> deltavalue(stockp.size() - 1);
	for(vector<double>::iterator k = deltavalue.begin(); k != deltavalue.end(); k++)
	{
		//at ends of vector, use themselves and next(previous) value to calculate
		//if(k == deltavalue.begin())
		//{
		*k = (*(j+1) - *j) / (*(i+1) - *i);
		//}
		i++;
		j++;

		/*else if(k == deltavalue.end() - 1)
		{
			*k = (*j - *(j-1)) / (*i - *(i-1));
		}
		//inside the vector, use its previous and next value to calculate
		else
		{
			*k = (*(j+1) - *(j-1)) / (*(i+1) - *(i-1));
		}*/
	}
	return deltavalue;
}


