#pragma once

#include "../Core.h"
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
	static Matrix2D zeros(unsigned short _l); // Create a square _l * _l matrix of all 0.0 values
	static Matrix2D identity(unsigned short _l); // Creates a 0.0 square matrix with the diagonal starting is upper left corner being all 1.0
	static Matrix2D diagonal(vector& _diag); // Creates a square diagonal matrix with the provided vector being the diagonal
	static Matrix2D diagonal(vector _diag, unsigned short _l, bool tall); // Creates a long or tall diagonal matrix 

	~Matrix2D();

	// Properties

	const unsigned short size() const; // Number of elements
	const unsigned short numCols() const; // Number of columns
	const unsigned short numRows() const; // Number of rows
	const vector* getData() const; // Returns a reference to the Matrix data as a vector 
	const nvector getNestedData() const; // Returns a reference to the Matrix data as a nested vector 
	const vector copyData() const; // Returns a copy of the Matrix data as a vector 
	const bool isSquare() const; // Whether the number of rows is the same as the number of columns
	const bool isDiagonal() const; // Whether everything except the diagonal starting in upper left corner is all 0.0
	const bool isIdentity() const; // Whether the diagonal starting is upper left corner is all 1.0 and the rest of the matrix is 0.0
	const bool isZeros() const; // Whether tha matrix is comprised of all 0.0s
	const vector getDiagonal() const; // Get array representing the diagonal of the matrix
	const double getTrace() const; // Compute the trace of the square matrix


	// Operations

	Matrix2D operator+(Matrix2D& m2); // Matrix addition. Same size matrices required
	Matrix2D operator-(Matrix2D& m2); // Matrix subtraction. Same size matrices required
	Matrix2D operator*(double& scalar); // Matrix scalar multiplication
	bool operator==(const Matrix2D& other) const; // Matrix equality
	void transpose(); // Transpose matrix rows and columns
	void reshape(unsigned short rows, unsigned short columns); // Reshape matrix (2D -> different shape 2D)
	Matrix2D shift(double coeff); // Add a scaled identity matrix to this matrix
	double valueAt(unsigned short row, unsigned short column); // Get value at row and column using algebraic notation (first row/col = 1)
	double realValueAt(unsigned short row_index, unsigned short column_index); // Get value at row and column using array notation (first row/col = 0)
	const vector getRow(unsigned short row_number) const; // Get array representing a row using algebraic notation (first row = 1)
	const vector getRealRow(unsigned short row_index) const; // Get array representing a row using array notation (first row = 0)
	const vector getColumn(unsigned short column_number) const; // Get array representing a column using algebraic notation (first col = 1)
	const vector getRealColumn(unsigned short column_idx) const; // Get array representing a column using array notation (first col = 0)
	

	// Extras

	void print(); // Prints the matrix

private: // Todo: Eventually write unit tests for the private methods
	unsigned short __rows;
	unsigned short __cols;
	vector __data;

	// Checks

	static bool areValidParams(vector data, unsigned short rows, unsigned short cols);
	static bool areValidParams(nvector* data);
	bool isSameShapeAs(Matrix2D& __mx);
	bool isValidReshape(unsigned short rows, unsigned short columns);

	// Helpers

	void expandNestedVector(nvector& data);
	int nextIdx(int current_idx, int last_base);
};
