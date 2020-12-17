#pragma once

#include "Core.h"
#include <vector>
#include <tuple>


typedef std::vector<double> vector;
typedef std::vector<vector> nvector;


class BN_API Matrix2D
{
public:

	// Constructors

	Matrix2D(vector* data, unsigned short rows, unsigned short cols);
	Matrix2D(nvector* data);

	static Matrix2D zeros(unsigned short rows, unsigned short cols); // Create a rows * cols matrix of all 0.0 values
	static Matrix2D identity(unsigned short _l); // Creates a 0.0 square matrix with the diagonal starting is upper left corner being all 1.0
	static Matrix2D diagonal(vector _diag); // Creates a square diagonal matrix with the provided vector being the diagonal
	static Matrix2D diagonal(vector _diag, unsigned short _l, bool tall); // Creates a long or tall diagonal matrix 

	~Matrix2D();

	// Properties

	unsigned short size(); // Number of elements
	unsigned short numCols(); // Number of columns
	unsigned short numRows(); // Number of rows
	vector rows();
	vector* getData();
	nvector getNestedData();
	vector copyData();
	std::tuple<unsigned short, unsigned short> shape(); // tuple (num rows, num cols)
	bool isSquare(); // Whether the number of rows is the same as the number of columns
	bool isDiagonal(); // Whether everything except the diagonal starting in upper left corner is all 0.0
	bool isIdentity(); // Whether the diagonal starting is upper left corner is all 1.0 and the rest of the matrix is 0.0
	bool isZeros(); // Whether tha matrix is comprised of all 0.0s

	// Operations

	Matrix2D operator+(Matrix2D& m2); // Matrix addition. Same size matrices required
	Matrix2D operator-(Matrix2D& m2); // Matrix subtraction. Same size matrices required
	Matrix2D operator*(double& scalar); // Matrix scalar multiplication
	void transpose(); // Transpose matrix rows and columns
	void reshape(unsigned short rows, unsigned short columns); // Reshape matrix (2D -> different shape 2D)
	double valueAt(unsigned short row, unsigned short column); // Get value at row and column using algebraic notation (first row/col = 1)
	double realValueAt(unsigned short row_index, unsigned short column_index); // Get value at row and column using array notation (first row/col = 0)
	vector getRow(unsigned short row_number); // Get array representing a row using algebraic notation (first row = 1)
	vector getRealRow(unsigned short row_index); // Get array representing a row using array notation (first row = 0)
	vector getColumn(unsigned short column_number); // Get array representing a column using algebraic notation (first col = 1)
	vector getRealColumn(unsigned short column_idx); // Get array representing a column using array notation (first col = 0)

private:
	unsigned short __rows;
	unsigned short __cols;
	vector __data;

	// Checks

	static bool areValidParams(vector* data, unsigned short rows, unsigned short cols);
	static bool areValidParams(nvector* data);
	bool isSameShapeAs(Matrix2D& __mx);
	bool isValidReshape(unsigned short rows, unsigned short columns);

	// Helpers

	void expandNestedVector(nvector& data);
};