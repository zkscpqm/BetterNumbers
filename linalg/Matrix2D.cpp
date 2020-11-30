#include "Matrix2D.h";
#include "Exceptions.cpp"


Matrix2D::Matrix2D(vector<double> data, int rows, int cols) {

	if (areValidParams(data, rows, cols)) {
		__rows = rows;
		__cols = cols;
		__data = data;
	}
	else {
		throw matrixInitializationException(data, rows, cols);
	}

}

bool Matrix2D::areValidParams(vector<double> data, int rows, int cols) {
	return (rows > 0) && (cols > 0) && (data.size() == rows * cols);