#pragma once

#ifdef BETTERNUMBERS_EXPORTS
#define BETTERNUMBERS_API __declspec(dllexport)
#else
#define BETTERNUMBERS_API __declspec(dllimport)
#endif

#include <vector>
#include <tuple>

class Matrix2D
{
public:

	// Constructors

	Matrix2D(std::vector<double>* data, unsigned short rows, unsigned short cols);
	Matrix2D(std::vector<std::vector<double>>* data);

	static Matrix2D zeros(unsigned short rows, unsigned short cols); // Create a rows * cols matrix of all 0.0 values
	static Matrix2D identity(unsigned short _l); // Creates a 0.0 square matrix with the diagonal starting is upper left corner being all 1.0
	static Matrix2D diagonal(std::vector<double> _diag); // Creates a square diagonal matrix with the provided vector being the diagonal
	static Matrix2D diagonal(std::vector<double> _diag, unsigned short _l, bool tall); // Creates a long or tall diagonal matrix 

	~Matrix2D();

	// Properties

	unsigned short size(); // Number of elements
	unsigned short cols(); // Number of columns
	unsigned short rows(); // Number of rows
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
	std::vector<double> getRow(unsigned short row_number); // Get array representing a row using algebraic notation (first row = 1)
	std::vector<double> getRealRow(unsigned short row_index); // Get array representing a row using array notation (first row = 0)
	std::vector<double> getColumn(unsigned short column_number); // Get array representing a column using algebraic notation (first col = 1)
	std::vector<double> getRealColumn(unsigned short column_idx); // Get array representing a column using array notation (first col = 0)

private:
	unsigned short __rows;
	unsigned short __cols;
	std::vector<double> __data;

	// Checks

	static bool areValidParams(std::vector<double>* data, unsigned short rows, unsigned short cols);
	static bool areValidParams(std::vector<std::vector<double>>* data);
	bool isSameShapeAs(Matrix2D& __mx);
	bool isValidReshape(unsigned short rows, unsigned short columns);

	// Helpers

	void expandNestedVector(std::vector<std::vector<double>>& data);
};