#ifndef _IO_H__
#define _IO_H__

/* IO file input and out data from program */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

// input the parameters
void input_data(double& spot, double& rate, double& div_yield, double& expiry, bool& callo, std::vector<double>& volatility, std::vector<double>& strike, std::ifstream& infile);

// print one vector
void print_vector(std::ofstream& outfile, std::vector<double> v);

// print two vectors simultaneously
void print_vector(std::ofstream& outfile, std::vector<double> u, std::vector<double> v);

// print two vector and one vector<vector> simultaneously
void print_vector(std::ofstream& outfile, std::vector<double> u, std::vector<double> v, std::vector<std::vector<double> > x);

// show vector on console
void showvector(std::vector<double>& v);

#endif
