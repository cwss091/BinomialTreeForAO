#ifndef _BINOMIALTREE_H__
#define _BINOMIALTREE_H__

/* Generate binominal tree*/

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
//#include "OptionPay.h"

class BinomialTree
{ 
	protected:
		int N; // the steps of the binomial tree
		double root; // root of the tree
	public:
		std::vector<std::vector<double> > data;

	public:
		BinomialTree(int steps, double _root);
		BinomialTree();
		int deep(); // get N of Tree
		double get_root(); // get the root of the tree
		void zeros(); // get a tree with all values are 0
		void setdata(double value, int i, int j);
		void setdata(std::vector<double> value, int i);
		double Datashow(int i, int j); // show the j-th value of i-th step
		std::vector<double> Rowshow(int i); // show the i-th step's value
		std::vector<std::vector<double> > Datashow(); // show all the data
		void print_tree(); // print tree
		~BinomialTree(){}
};

class Stock_BiTree: public BinomialTree
{
	double vol; // volatility
	double expiry; // expiration date
	double delta_t; // time length of step
	double up; // up times 
	double down; // down times
	public:
		Stock_BiTree(int steps, double _root, double _vol, double _expiry);
		void forward_fill(); //construct whole stock tree based on the root
		~Stock_BiTree();
		friend class Option_BiTree;
};

class Option_BiTree: public BinomialTree
{
	//protected:
	//how to protect this data if i write the payoff in anothor file? 
	public:
		double rate; // risk free interest rate
		double discount; // discount rate of each step
		double dividend; // dividend
		double delta_t; // delta t
		double up_riskneu; // risk neutral up probability
		double down_riskneu; // down_riskneu
		double strike; // strike price
		double vol; // volatility
		double expiry; // expiry		
		bool call; // if call, be true
		bool euro; // if euro option, be true

		Option_BiTree(double _rate, double _dividend, double _strike, bool _call, bool _euro, Stock_BiTree StockT);
		void backward_fill(std::vector<double> z); // construct the european option tree
		void backward_fill(std::vector<double> z, std::vector<std::vector<double> > intrinsic); // construct the american option tree
};

#endif
