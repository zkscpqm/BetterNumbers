#include <utility>
#include <limits.h>
#include "Matrix2D.h"
#include "Exceptions.cpp"
#include "iostream"
#include "utils/vector_operations.h"

static unsigned long long previous_;
static unsigned long long current_;
static unsigned index_;

// CONSTRUCTORS

Matrix2D::Matrix2D(vector *data, unsigned short rows, unsigned short cols) {

	if (areValidParams(data, rows, cols)) {
		__rows = rows;
		__cols = cols;
		__data = data;

	}
	else throw matrixInvalidParametersException(data, rows, cols);
}

Matrix2D::Matrix2D(nvector *data) {
	if (areValidParams(data)) {
		expandNestedVector(data);
		__rows = data->size();
	}
	else throw matrixInvalidParametersException(data);
}

Matrix2D Matrix2D::zeros(unsigned short _l) {
	return zeros(_l, _l);
}

Matrix2D Matrix2D::zeros(unsigned short rows, unsigned short cols) {
	vector* __d = new vector(rows * cols, 0.0);
	return Matrix2D(__d, rows, cols);
}

Matrix2D Matrix2D::identity(unsigned short _l) {
	vector tmpvec(_l, 1.);
	return diagonal(tmpvec);
}

Matrix2D Matrix2D::diagonal(vector& _diag) {
	vector* data = new vector;
	unsigned short _l = _diag.size();
	unsigned short arr_size =  _l * _l;
	data->reserve(arr_size);
	unsigned short diag_idx = 0;
	unsigned short val_arr_idx = 0;
	for (unsigned i = 0; i < arr_size; i++) {
		if (i == diag_idx) {
			data->emplace_back(_diag[val_arr_idx]);
			diag_idx += _l + 1;
			val_arr_idx++;
		}
		else {
			data->emplace_back(0.);
		}
	}
	return Matrix2D(data, _l, _l);
}

// PROPERTIES

const unsigned short Matrix2D::size() const {

	return __data->size();
}

const unsigned short Matrix2D::numRows() const {
	return __rows;
}

const unsigned short Matrix2D::numCols() const {
	return __cols;
}

const vector* Matrix2D::getData() const {
	return __data;
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
	vector data(__data->begin(), __data->end());
	return data;
}

const bool Matrix2D::isSquare() const {
	return __rows == __cols;
}

const bool Matrix2D::isDiagonal() const {
	unsigned short coeff = 0;
	for (int i = 0; i < size(); i++) {
		if (i != coeff) {
			if (__data->at(i) != 0.) {
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
				if (__data->at(i) != 0.) {
					return false;
				}
			}
			else {
				if (__data->at(i) != 1.) {
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
	for (double x : *__data) {
		if (x != 0.) {
			return false;
		}
	}
	return true;
}

const vector Matrix2D::getDiagonal() const {
	int elems = fmin(__rows, __cols);
	vector diag;
	diag.reserve(elems);
	for (int i = 0, j = 0; i < elems; i++, j += __cols + 1) {
		diag.emplace_back(__data->at(j));
	}
	return diag;
}

const double Matrix2D::getTrace() const {
	if (isSquare()) {
		vector _diag = getDiagonal();
		return VectorUtils::sum(_diag);
	}
	else throw matrixInvalidShapeException("square");
}

// OPERATIONS

Matrix2D Matrix2D::operator+(Matrix2D& m2) {

	if (isSameShapeAs(m2)) {
		vector* result = new vector;
		result->reserve(size());
		for (int i = 0; i < size(); i++) {
			result->emplace_back(__data->at(i) + m2.__data->at(i));
		}
		return Matrix2D(result, __rows, __cols);
	}
	else throw matrixSizeError(this, &m2);
}

Matrix2D Matrix2D::operator-(Matrix2D& m2) {

	if (isSameShapeAs(m2)) {
		vector* result = new vector;
		result->reserve(size());
		for (int i = 0; i < size(); i++) {
			result->emplace_back(__data->at(i) - m2.__data->at(i));
		}
		return Matrix2D(result, __rows, __cols);
	}
	else throw matrixSizeError(this, &m2);
}

Matrix2D Matrix2D::operator*(double& scalar) {

	vector* result = new vector;
	result->reserve(size());
	for (int i = 0; i < size(); i++) {
		result->emplace_back(__data->at(i) * scalar);
	}
	return Matrix2D(result, __rows, __cols);
}

Matrix2D Matrix2D::operator*(Matrix2D& m2) {
	if (__cols == m2.__rows) {
		int mSize = __rows * m2.__cols;
		vector* result = new vector;
		result->reserve(mSize); 
		
		for (int row_idx = 0; row_idx < __rows; row_idx++) {
			vector* row = getRealRow(row_idx);
			for (int col_idx = 0; col_idx < m2.__rows; col_idx++) {
				vector* col = m2.getRealColumn(col_idx);
				double _elem = 0.;
				for (int i = 0; i < row->size(); i++) {
					_elem += row->at(i) * col->at(i);
				}
				result->emplace_back(_elem);
			}
		}
		return Matrix2D(result, __rows, m2.__cols);
	}
	else throw matrixInvalidShapeException("Left matrix columns matching right matrix rows");
}

Matrix2D* Matrix2D::hadavardMultiplication(Matrix2D& m2, bool in_place) {
	if (isSameShapeAs(m2)) {
		vector* result = new vector;
		result->reserve(size());
		for (int i = 0; i < size(); i++) {
			result->emplace_back(__data->at(i) * m2.__data->at(i));
		}
		if (in_place) {
			__data = result;
			return this;
		}
		else return new Matrix2D(result, __rows, __cols);
	}
	else throw matrixSizeError(this, &m2);
}

inline bool Matrix2D::operator==(const Matrix2D& other) const {
	return (*__data == *other.__data)
		and (__cols == other.__cols)
		and (__rows == other.__rows);
}

Matrix2D* Matrix2D::transpose(bool in_place) {
	vector* result = new vector;
	result->resize(size());
	result->at(0) = __data->at(0);
	int base_idx = 0;
	int prev = NULL;
	for (int i = 1; i < size(); i++) {
		
		int curr_idx = i - 1;
		if (prev != NULL) {
			curr_idx = prev;
		}
		int new_idx = _nextIdx(curr_idx, base_idx);
		result->at(new_idx) = __data->at(i);
		prev = new_idx;
		if (curr_idx + __rows >= size()) {
			base_idx += 1;
		}
	}
	if (in_place) {
		__data = result;
		reshape(__cols, __rows);
		return this;
	}
	else return new Matrix2D(result, __cols, __rows);

}

int Matrix2D::_nextIdx(int current_idx, int last_base) {
	if (current_idx + __rows >= size()) {
		return last_base + 1;
	}
	return current_idx + __rows;
}

Matrix2D* Matrix2D::reshape(unsigned short rows, unsigned short columns, bool in_place) {
	if (isValidReshape(rows, columns)) {
		if (in_place) {
			__rows = rows;
			__cols = columns;
			return this;
		}
		return new Matrix2D(__data, rows, columns);
	}
	else throw matrixInvalidParametersException(__data, rows, columns);
}

Matrix2D* Matrix2D::shift(double coeff, bool in_place) {
	if (isSquare()) {
		Matrix2D shiftMX = identity(__rows) * coeff;
		vector* d = VectorUtils::elementwiseAddition(*__data, *shiftMX.__data);
		if (in_place) {
			__data = d;
			return this;
		}
		else return new Matrix2D(d, __rows, __cols);
	}
	else throw matrixInvalidShapeException("square");
}

double Matrix2D::valueAt(unsigned short row, unsigned short column) {
	return realValueAt(row - 1, column - 1);
}

double Matrix2D::realValueAt(unsigned short row_index, unsigned short column_index) {
	if (row_index < __rows and column_index < __cols) {
		unsigned idx = (row_index * __cols) + column_index;
		return __data->at(idx);
	}
	throw matrixOutOfRangeException(this, row_index, column_index);
}

vector* Matrix2D::getRow(unsigned short row_number) const {
	return getRealRow(row_number - 1);
}

vector* Matrix2D::getRealRow(unsigned short row_index) const {
	if (0 <= row_index and row_index < __rows) {
		unsigned short idx = row_index * __cols;
		unsigned short end_idx = idx + __cols;
		vector* row = new vector;
		row->reserve(__cols);
		for (; idx < end_idx; idx++) {
			row->emplace_back(__data->at(idx));
		}
		return row;
	}
	else throw matrixOutOfRangeException(this);
}

vector* Matrix2D::getColumn(unsigned short column_number) const {
	return getRealColumn(column_number - 1);

}

vector* Matrix2D::getRealColumn(unsigned short column_idx) const {
	if (0 <= column_idx and column_idx < __cols) {
		vector* col = new vector;
		col->reserve(__rows);
		for (unsigned short i = column_idx; i < size(); i += __cols) {
			col->emplace_back(__data->at(i));
		}
		return col;
	}
	else throw matrixOutOfRangeException(this);
}

Matrix2D* Matrix2D::verticalBroadcastAddition(vector& vec, bool in_place) {
	if (vec.size() == __rows) {
		int matrix_idx_crawler = 0;
		int matrix_column_counter = 0;
		int vector_idx_crawler = 0;
		vector* new_data = new vector;
		new_data->reserve(size());
		for (; matrix_idx_crawler < size(); matrix_idx_crawler++) {
			new_data->emplace_back(__data->at(matrix_idx_crawler) + vec[vector_idx_crawler]);
			if (matrix_column_counter == __cols - 1) {
				matrix_column_counter = 0;
				vector_idx_crawler++;
			}
			else matrix_column_counter++;
		}
		if (in_place) {
			__data = new_data;
			return this;
		}
		else return new Matrix2D(new_data, __rows, __cols);
	}
	else throw matrixInvalidShapeException("The vector must be the same size as the matrix rows");
}

Matrix2D* Matrix2D::horizontalBroadcastAddition(vector& vec, bool in_place) {
	if (vec.size() == __cols) {
		int matrix_idx_crawler = 0;
		int vector_idx_crawler = 0;
		vector* new_data = new vector;
		new_data->reserve(size());
		for (; matrix_idx_crawler < size(); matrix_idx_crawler++) {
			new_data->emplace_back(__data->at(matrix_idx_crawler) + vec[vector_idx_crawler]);
			if (vector_idx_crawler == __cols - 1) {
				vector_idx_crawler = 0;
			}
			else {
				vector_idx_crawler++;
			}
		}
		if (in_place) {
			__data = new_data;
			return this;
		}
		else return new Matrix2D(new_data, __rows, __cols);
	}
	else throw matrixInvalidShapeException("The vector must be the same size as the matrix cols");
}

// CHECKS

bool Matrix2D::areValidParams(vector* data, unsigned short rows, unsigned short cols) {
	return (rows > 0) && (cols > 0) && (data->size() == rows * cols);
}

bool Matrix2D::areValidParams(nvector *data) {
	int __colSize = data->at(0).size();
	for (vector col : *data) {
		if (col.size() != __colSize) return false;
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

void Matrix2D::expandNestedVector(nvector* data) {
	__cols = data->at(0).size();
	vector* tmpData = new vector;
	tmpData->reserve(data->size() * __cols);
	for (vector row : *data) {
		tmpData->insert(tmpData->end(), row.begin(), row.end());
	}
	__data = tmpData;
}

// EXTRAS

void Matrix2D::print() {
	int col_counter = 0;
	for (double elem : *__data) {
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

Matrix2D::~Matrix2D() {
	delete __data;
}
