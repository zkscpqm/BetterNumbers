
#include "pch.h"
#include <utility>
#include <limits.h>
#include "Matrix2D.h"
#include "Exceptions.cpp"

static unsigned long long previous_;
static unsigned long long current_;
static unsigned index_;


// CONSTRUCTORS

Matrix2D::Matrix2D(vector<double> data, unsigned short rows, unsigned short cols) {

	if (areValidParams(data, rows, cols)) {
		__rows = rows;
		__cols = cols;
		__data = data;
	}
	else {
		throw matrixInitializationException(data, rows, cols);
	}

}

Matrix2D::Matrix2D(vector<vector<double>> data) {

	if (areValidParams(data)) {
		expandNestedVector(data);
		__rows = data.size();
		delete(&data);
	}
	else {
		throw;
	}
}

Matrix2D Matrix2D::zeros(unsigned short rows, unsigned short cols) {
	vector<double> __d(rows * cols, 0.0);
	return Matrix2D(__d, rows, cols);
}

Matrix2D Matrix2D::identity(unsigned short _l) {
	vector<double> data;
	unsigned arr_size = _l * _l;
	data.reserve(arr_size);
	unsigned one_idx = 0;
	for (unsigned i = 0; i < arr_size; i++) {
		if (i == one_idx) {
			data.emplace_back(1.);
			one_idx += _l + 1;
		} else {
			data.emplace_back(0.);
		}
	}
	return Matrix2D(data, _l, _l);
}


// CHECKS

bool Matrix2D::areValidParams(vector<double> data, unsigned short rows, unsigned short cols) {
	return (rows > 0) && (cols > 0) && (data.size() == rows * cols);
}

bool Matrix2D::areValidParams(vector<vector<double>> data) {
	int __colSize = data.at(0).size();
		for (vector<double> col : data) {
			if (col.size() != __colSize) {
				return false;
			}
		}
		return true;
}

// HELPERS

void Matrix2D::expandNestedVector(vector<vector<double>> data) {
	__cols = data.at(0).size();
	__data.reserve(data.size() * __cols);
	for (vector<double> row : data) {
		__data.insert(__data.end(), row.begin(), row.end());
	}
}