#pragma once

#ifdef BETTERNUMBERS_EXPORTS
#define BETTERNUMBERS_API __declspec(dllexport)
#else
#define BETTERNUMBERS_API __declspec(dllimport)
#endif

#include <vector>
#include <tuple>

using std::vector;
using std::tuple;

class Matrix2D
{
public:

	// Constructors
	Matrix2D(vector<double> data, unsigned short rows, unsigned short cols);
	Matrix2D(vector<vector<double>> data);

	static Matrix2D zeros(unsigned short rows, unsigned short cols);
	static Matrix2D identity(unsigned short _l);
	static Matrix2D diagonal(vector<double> _diag);

	~Matrix2D();

	// Operations

	Matrix2D operator+(Matrix2D&);
	Matrix2D operator-(Matrix2D&);
	Matrix2D operator*(double&);
	Matrix2D transpose();


private:
	unsigned short __rows;
	unsigned short __cols;
	vector<double> __data;



	// Checks

	static bool areValidParams(vector<double> data, unsigned short rows, unsigned short cols);
	static bool areValidParams(vector<vector<double>> data);

	// Helpers

	void expandNestedVector(vector<vector<double>> data);

};