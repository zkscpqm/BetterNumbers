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

	// Create a rows * cols matrix of all 0.0 values
	static Matrix2D zeros(unsigned short rows, unsigned short cols);

	// Create a square _l * _l matrix of all 0.0 values
	static Matrix2D zeros(unsigned short _l);

	// Creates a 0.0 square matrix with the diagonal starting is upper left corner being all 1.0
	static Matrix2D identity(unsigned short _l);

	// Creates a square diagonal matrix with the provided vector being the diagonal
	static Matrix2D diagonal(vector& _diag);

	// Creates a long or tall diagonal matrix
	static Matrix2D diagonal(vector _diag, unsigned short _l, bool tall);

	~Matrix2D();

	// Properties

	// Number of elements
	const unsigned short size() const;

	// Number of columns
	const unsigned short numCols() const;

	// Number of rows
	const unsigned short numRows() const;

	// Returns a reference to the Matrix data as a vector 
	const vector* getData() const;

	// Returns a copy of the Matrix data as a nested vector
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
	Matrix2D hadavardMultiplication(Matrix2D* m2);

	//In-place element-wise multiplication -> dims M^ij * N^ij is valid for resulting size R^ij
	Matrix2D* hadavardMultiplicationInPlace(Matrix2D* m2);

	// Matrix equality
	inline bool operator==(const Matrix2D& other) const; 

	// Transpose matrix rows and columns
	Matrix2D transpose();

	// Transpose matrix rows and columns in place
	Matrix2D* transposeInPlace();

	// Reshape matrix (2D -> different shape 2D)
	Matrix2D reshape(unsigned short rows, unsigned short columns);

	// Reshape matrix (2D -> different shape 2D) in place
	Matrix2D* reshapeInPlace(unsigned short rows, unsigned short columns);

	// Add a scaled identity matrix to this matrix
	Matrix2D shift(double coeff);

	// Add a scaled identity matrix to this matrix in place
	Matrix2D* shiftInPlace(double coeff);

	// Get value at row and column using algebraic notation (first row/col = 1)
	double valueAt(unsigned short row, unsigned short column);

	// Get value at row and column using array notation (first row/col = 0)
	double realValueAt(unsigned short row_index, unsigned short column_index);
	
	// Get array representing a row using algebraic notation (first row = 1)
	vector getRow(unsigned short row_number) const;
	
	// Get array representing a row using array notation (first row = 0)
	vector getRealRow(unsigned short row_index) const;
	
	// Get array representing a column using algebraic notation (first col = 1)
	vector getColumn(unsigned short column_number) const;
	
	// Get array representing a column using array notation (first col = 0)
	vector getRealColumn(unsigned short column_idx) const;
	
	// Broadcasts an n-size array on every row of an n*m matrix m times
	Matrix2D verticalBroadcastAddition(vector* vec);

	// Broadcasts an n-size array on every row of an n*m matrix m times in place
	Matrix2D* verticalBroadcastAdditionInPlace(vector* vec);
	
	// Broadcasts an m-size array on every column of an n*m matrix n times
	Matrix2D horizontalBroadcastAddition(vector* vec);

	// Broadcasts an m-size array on every column of an n*m matrix n times in place
	Matrix2D* horizontalBroadcastAdditionInPlace(vector* vec);
	

	// Extras


	// Prints the matrix
	void print();

private: // Todo: Eventually write unit tests for the private methods
	unsigned short __rows;
	unsigned short __cols;
	vector* __data = new vector; // TODO: USE SMART POINTER!!


	// Checks


	static bool areValidParams(vector* data, unsigned short rows, unsigned short cols);
	static bool areValidParams(nvector* data);
	bool isSameShapeAs(Matrix2D& __mx);

	// Can the data support the proposed rows/cols provided
	bool isValidReshape(unsigned short rows, unsigned short columns);


	// Helpers


	// Exapands a nested vector into a single vector
	void expandNestedVector(nvector* data);

	int _nextIdx(int current_idx, int last_base);
};
