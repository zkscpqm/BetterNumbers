#pragma once

#include <vector>
#include <tuple>

using std::vector;
using std::tuple;

class Matrix2D
{
public:

	// Constructors
	Matrix2D(vector<double> data, int rows, int cols);
	Matrix2D(vector<vector<double>> data);
	Matrix2D zeros(int rows, int cols);
	Matrix2D identity(int _l);
	Matrix2D diagonal(vector<double> _diag);
	~Matrix2D();

	// Operations

	Matrix2D operator+(Matrix2D&);
	Matrix2D operator-(Matrix2D&);
	Matrix2D operator*(double&);
	Matrix2D transpose();

	// Checks

	bool areValidParams(vector<double> data, int rows, int cols);

private:
	int __rows;
	int __cols;
	vector<double> __data;
};