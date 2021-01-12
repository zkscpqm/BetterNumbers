#include <utility>
#include <limits.h>
#include "Matrix2D.h"
#include "Exceptions.cpp"
#include "iostream"

static unsigned long long previous_;
static unsigned long long current_;
static unsigned index_;

// CONSTRUCTORS

Matrix2D::Matrix2D(vector *data, unsigned short rows, unsigned short cols) {

	if (areValidParams(*data, rows, cols)) {
		__rows = rows;
		__cols = cols;
		__data = *data;

	}
	else {
		throw matrixInitializationException(*data, rows, cols);
	}

}

Matrix2D::Matrix2D(nvector *data) {

	if (areValidParams(data)) {
		expandNestedVector(*data);
		__rows = data->size();
	}
	else {
		throw matrixInitializationException(*data);
	}
}

Matrix2D Matrix2D::zeros(unsigned short _l) {
	return zeros(_l, _l);
}

Matrix2D Matrix2D::zeros(unsigned short rows, unsigned short cols) {
	vector __d(rows * cols, 0.0);
	return Matrix2D(&__d, rows, cols);
}

Matrix2D Matrix2D::identity(unsigned short _l) {
	vector tmpvec(_l, 1.);
	return diagonal(tmpvec);
}

Matrix2D Matrix2D::diagonal(vector& _diag) {
	vector data;
	unsigned short _l = _diag.size();
	unsigned short arr_size =  _l * _l;
	data.reserve(arr_size);
	unsigned short diag_idx = 0;
	unsigned short val_arr_idx = 0;
	for (unsigned i = 0; i < arr_size; i++) {
		if (i == diag_idx) {
			data.emplace_back(_diag[val_arr_idx]);
			diag_idx += _l + 1;
			val_arr_idx++;
		}
		else {
			data.emplace_back(0.);
		}
	}
	return Matrix2D(&data, _l, _l);
}

// PROPERTIES

const unsigned short Matrix2D::size() const {

	return __data.size();
}

const unsigned short Matrix2D::numRows() const {
	return __rows;
}

const unsigned short Matrix2D::numCols() const {
	return __cols;
}

const vector* Matrix2D::getData() const {
	return &__data;
}

const nvector Matrix2D::getNestedData() const {
	nvector data;
	data.reserve(numRows());
	for (unsigned i = 0; i < numRows(); i++) {
		data.emplace_back(getRealRow(i));
	}
	return data;
}

const vector Matrix2D::copyData() const {
	std::vector<double> data = __data;
	return data;
}

const bool Matrix2D::isSquare() const {
	return __rows == __cols;
}

const bool Matrix2D::isDiagonal() const {
	unsigned short coeff = 0;
	for (int i = 0; i < size(); i++) {
		if (i != coeff) {
			if (__data[i] != 0.) {
				return false;
			}
		}
		else {
			coeff += __cols + 1;
		}
	}
	return true;
}
const bool Matrix2D::isIdentity() const {
	if (isSquare()) {
		unsigned short coeff = 0;
		for (int i = 0; i < size(); i++) {
			if (i != coeff) {
				if (__data[i] != 0.) {
					return false;
				}
			}
			else {
				if (__data[i] != 1.) {
					return false;
				}
				coeff += __cols + 1;
			}
		}
		return true;
	}
	return false;
}

const bool Matrix2D::isZeros() const {
	for (double x : __data) {
		if (x != 0.) {
			return false;
		}
	}
	return true;
}

// OPERATIONS

Matrix2D Matrix2D::operator+(Matrix2D& m2) {

	vector* result = new vector;
	result->reserve(size());

	if (isSameShapeAs(m2)) {
		for (int i = 0; i < size(); i++) {
			result->emplace_back(__data[i] + m2.__data[i]);
		}
		return Matrix2D(result, __rows, __cols);
	}
	else {
		throw matrixSizeError(*this, m2);
	}
	return nullptr;
}

Matrix2D Matrix2D::operator-(Matrix2D& m2) {

	vector* result = new vector;
	result->reserve(size());

	if (isSameShapeAs(m2)) {
		for (int i = 0; i < size(); i++) {
			result->emplace_back(__data[i] - m2.__data[i]);
		}
		return Matrix2D(result, __rows, __cols);
	}
	else {
		throw matrixSizeError(*this, m2);
	}
	return nullptr;
}

Matrix2D Matrix2D::operator*(double& scalar) {

	vector* result = new vector;
	result->reserve(size());
	for (int i = 0; i < size(); i++) {
		result->emplace_back(__data[i] * scalar);
	}
	return Matrix2D(result, __rows, __cols);
}

inline bool Matrix2D::operator==(const Matrix2D& other) const {
	return (__data == other.__data)
		and (__cols == other.__cols)
		and (__rows == other.__rows);
}

void Matrix2D::transpose() {
	unsigned short _tmp = __rows;
	__rows = __cols;
	__cols = _tmp;
}

void Matrix2D::reshape(unsigned short rows, unsigned short columns) {
	if (isValidReshape(rows, columns)) {
		__rows = rows;
		__cols = columns;
	}
}

double Matrix2D::valueAt(unsigned short row, unsigned short column) {
	return realValueAt(row - 1, column - 1);
}

double Matrix2D::realValueAt(unsigned short row_index, unsigned short column_index) {
	if (row_index < __rows and column_index < __cols) {
		unsigned idx = (row_index * __cols) + column_index;
		return __data[idx];
	}
	throw matrixOutOfRange(*this, row_index, column_index);
}

const vector Matrix2D::getRow(unsigned short row_number) const {
	return getRealRow(row_number - 1);
}

const vector Matrix2D::getRealRow(unsigned short row_index) const {
	if (0 <= row_index and row_index < __rows - 1) {
		unsigned short idx = row_index * __cols;
		unsigned short end_idx = idx + __cols;
		vector row;
		row.reserve(__cols);
		for (; idx < end_idx; idx++) {
			row.emplace_back(__data[idx]);
		}
		return row;
	}
	else {
		throw;
	}
}

const vector Matrix2D::getColumn(unsigned short column_number) const {
	return getRealColumn(column_number - 1);

}

const vector Matrix2D::getRealColumn(unsigned short column_idx) const {
	if (0 <= column_idx and column_idx < __cols - 1) {
		vector col;
		col.reserve(__rows);
		for (unsigned short i = column_idx; i < size(); i += __cols) {
			col.emplace_back(__data[i]);
		}
		return col;
	}
	else {
		throw;
	}
}

// CHECKS

bool Matrix2D::areValidParams(vector data, unsigned short rows, unsigned short cols) {
	return (rows > 0) && (cols > 0) && (data.size() == rows * cols);
}

bool Matrix2D::areValidParams(nvector *data) {
	int __colSize = data->at(0).size();
	for (vector col : (*data)) {
		if (col.size() != __colSize) {
			return false;
		}
	}
	return true;
}

bool Matrix2D::isSameShapeAs(Matrix2D& mx) {
	return size() == mx.size() 
		and (__cols == mx.__cols)
		and (__rows == mx.__rows);
}

bool Matrix2D::isValidReshape(unsigned short rows, unsigned short columns) {
	return rows * columns == size();
}

// HELPERS

void Matrix2D::expandNestedVector(nvector &data) {
	__cols = data.at(0).size();
	__data.reserve(data.size() * __cols);
	for (vector row : data) {
		__data.insert(__data.end(), row.begin(), row.end());
	}
}

// EXTRAS

void Matrix2D::print() {
	int col_counter = 0;
	for (double elem : __data) {
		std::cout << elem << " ";
		if (col_counter >= __cols - 1) {
			std::cout << "\n";
			col_counter = 0;
		}
		else {
			col_counter++;
		}
	}
}

Matrix2D::~Matrix2D() {}