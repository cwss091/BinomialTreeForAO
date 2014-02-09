#include "BinomialTree.h"

using namespace std;

BinomialTree::BinomialTree(int steps, double _root)
{
	N = steps;
	root = _root;
}

BinomialTree::BinomialTree(){}

int BinomialTree::deep()
{
	int tDeep = N;
	return tDeep;
}

double BinomialTree::get_root()
{ 
	return data[0][0];
}

void BinomialTree::zeros() // construct tree all values are 0, for initialize tree
{ 
	vector<double> stepdata(1);
	stepdata[0] = 0;
	data.push_back(stepdata);
	for(int i = 1; i <= N; i++)
	{  
		vector<double> stepdata(i+1);
		for(int j = 0; j <= i; j++)
		{  
			stepdata[j] = 0;
		}
		data.push_back(stepdata);
	}
}

void BinomialTree::setdata(double value, int i, int j) // set one data
{
	data[i][j] = value;
}

void BinomialTree::setdata(vector<double> value, int i) // set a row
{
	int len = value.size();
	for(int j = 0; j < len; j++)
	{
		data[i][j] = value[j];
	}
}

double BinomialTree::Datashow(int i, int j) // show one
{
	return data[i][j];
}

vector<double> BinomialTree::Rowshow(int i) // show a row
{ 
	return data[i];
}

vector<vector<double> > BinomialTree::Datashow() // show all
{
	return data;
}

Stock_BiTree::Stock_BiTree(int steps, double _root, double _vol, double _expiry):BinomialTree()
{
	N = steps;
	root = _root;
	vol = _vol;
	expiry = _expiry;
	delta_t = expiry / N;
	double delvol = vol * sqrt(delta_t);
	up = exp(delvol);
	down = exp(-delvol);
}

void Stock_BiTree::forward_fill() // construct stocktree
{
	// This function's copyright belongs to Prof. Demko
	for(int i = 1; i <= N; i++)
	{
		data[i][0] = data[i-1][0] * down;
		for(int j = 1; j<=i; j++)
		{
			data[i][j] = data[i-1][j-1] * up;
		}
	}
}

Stock_BiTree::~Stock_BiTree(){}

Option_BiTree::Option_BiTree(double _rate, double _dividend, double _strike, bool _call, bool _euro, Stock_BiTree StockT)
{
	rate = _rate;
	dividend = _dividend;
	strike = _strike;
	call = _call;
	euro = _euro;
	N = StockT.N;
	vol = StockT.vol;
	expiry = StockT.expiry;
	root = 0;
	delta_t = StockT.delta_t;
	double mindisc = exp(rate * delta_t);
	discount = 1.0 / mindisc;
	up_riskneu = (mindisc * exp(-dividend * delta_t) - StockT.down) / (StockT.up - StockT.down);
	down_riskneu = 1.0 - up_riskneu;
}

void Option_BiTree::backward_fill(vector<double> z) // construct european tree
{ 
	// This function's copyright to Professor Demko
	int K = z.size();
	//cout << data[0][0] << endl;

	for(int i = 0; i < K; i++)
	{ 
		data[K-1][i] = z[i];
	}
	for(int i = K-2; i >= 0; i--)
	{ 
		for(int j = 0; j <= i; j++)
		{ 
			data[i][j] = discount * (up_riskneu * data[i+1][j+1] + down_riskneu * data[i+1][j]);
		}
	}
}

void Option_BiTree::backward_fill(vector<double> z, vector<vector<double> > intrinsic) // construct american tree
{
	int K = z.size();
	for(int i = 0; i < K; i++)
	{
		data[K-1][i] = z[i];
	}
	for(int i = K-2; i >= 0; i--)
	{
		for(int j = 0; j <= i; j++)
		{
			double temp = discount * (up_riskneu * data[i+1][j+1] + down_riskneu * data[i+1][j]);
			data[i][j] = (temp > intrinsic[i][j]) ? temp:intrinsic[i][j];
		}
	}
}

