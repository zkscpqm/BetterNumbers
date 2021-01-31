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

	Matrix2D(vector* data, int rows, int cols);
	Matrix2D(nvector* data);

	// Create a rows * cols matrix of all 0.0 values
	static Matrix2D zeros(int rows, int cols);

	// Create a square _l * _l matrix of all 0.0 values
	static Matrix2D zeros(int _l);

	// Creates a 0.0 square matrix with the diagonal starting is upper left corner being all 1.0
	static Matrix2D identity(int _l);

	// Creates a square diagonal matrix with the provided vector being the diagonal
	static Matrix2D diagonal(vector& _diag);

	// Creates a long or tall diagonal matrix
	static Matrix2D diagonal(vector _diag, int _l, bool tall);

	~Matrix2D();

	// Properties

	// Number of elements
	const int size() const;

	// Number of columns
	const int numCols() const;

	// Number of rows
	const int numRows() const;

	// Returns a reference to the Matrix data as a vector 
	const vector* getData() const;

	// Returns a reference to the Matrix data as a nested vector
	const nvector getNestedData() const; 

	// Returns a copy of the Matrix data as a vector 
	const vector copyData() const;

	// Whether the number of rows is the same as the number of columns
	const bool isSquare() const;

	// Whether everything except the diagonal starting in upper left corner is all 0.0
	const bool isDiagonal() const;

	// Whether the diagonal starting is upper left corner is all 1.0 and the rest of the matrix is 0.0
	const bool isIdentity() const;

	// Whether tha matrix is comprised of all 0.0s
	const bool isZeros() const;

	// Get array representing the diagonal of the matrix
	const vector getDiagonal() const;

	// Compute the trace of the square matrix
	const double getTrace() const;


	// Operations


	// Matrix addition. Same size matrices required
	Matrix2D operator+(Matrix2D& m2);

	// Matrix subtraction. Same size matrices required
	Matrix2D operator-(Matrix2D& m2);

	// Matrix scalar multiplication
	Matrix2D operator*(double& scalar);

	// Default matrix multiplication -> M^ij * N^jk is valid for resulting size R^ik
	Matrix2D operator*(Matrix2D& m2);

	//Element-wise multiplication -> dims M^ij * N^ij is valid for resulting size R^ij
	Matrix2D hadavardMultiplication(Matrix2D& m2);

	// Matrix equality
	bool operator==(const Matrix2D& other) const; 

	// Transpose matrix rows and columns
	void transpose();

	// Reshape matrix (2D -> different shape 2D)
	void reshape(int rows, int columns);

	// Add a scaled identity matrix to this matrix
	Matrix2D shift(double coeff);

	// Get value at row and column using algebraic notation (first row/col = 1)
	double valueAt(int row, int column);

	// Get value at row and column using array notation (first row/col = 0)
	double realValueAt(int row_index, int column_index);
	
	// Get array representing a row using algebraic notation (first row = 1)
	const vector getRow(int row_number) const;
	
	// Get array representing a row using array notation (first row = 0)
	const vector getRealRow(int row_index) const;
	
	// Get array representing a column using algebraic notation (first col = 1)
	const vector getColumn(int column_number) const;
	
	// Get array representing a column using array notation (first col = 0)
	const vector getRealColumn(int column_idx) const;
	
	// Broadcasts an n-size array on every row of an n*m matrix m times
	Matrix2D verticalBroadcastAddition(vector& vec, bool in_place=false);
	
	// Broadcasts an m-size array on every column of an n*m matrix n times
	Matrix2D horizontalBroadcastAddition(vector& vec, bool in_place = false);
	

	// Extras


	// Prints the matrix
	void print();

private: // Todo: Eventually write unit tests for the private methods
	int __rows;
	int __cols;
	vector* __data;


	// Checks


	static bool areValidParams(vector* data, int rows, int cols);
	static bool areValidParams(nvector* data);
	bool isSameShapeAs(Matrix2D& __mx);

	// Can the data support the proposed rows/cols provided
	bool isValidReshape(int rows, int columns);


	// Helpers


	// Exapands a nested vector into a single vector
	void expandNestedVector(nvector* data);

	int nextIdx(int current_idx, int last_base);
};
