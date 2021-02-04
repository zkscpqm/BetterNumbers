#include <vector>
#include "..\..\BetterNumbers\src\linalg\Matrix2D.h"
#include "gtest/gtest.h"


TEST(Matrix, BasicInit) {
	vector data{ 1., 2., 3., 4., 5., 6. };
	int rows = 2;
	int cols = 3;

	Matrix2D mx = Matrix2D(&data, rows, cols);

	ASSERT_EQ(rows, mx.numRows());
	ASSERT_EQ(cols, mx.numCols());
	ASSERT_EQ(data, *mx.getData());
}

TEST(Matrix, NestedInit) {
	nvector* data = new nvector{
		{ 1., 2., 3., 4., 5., 6. },
		{ 1., 2., 3., 4., 5., 6. },
		{ 1., 2., 3., 4., 5., 6. }
	};
	Matrix2D mx = Matrix2D(data);
	ASSERT_EQ(data->size(), mx.numRows());
	ASSERT_EQ(data->at(0).size(), mx.numCols());
	ASSERT_EQ(*data, mx.getNestedData());
}

TEST(Matrix, ZerosInitSquare) {
	unsigned short _size = 3;
	Matrix2D mx = Matrix2D::zeros(_size);
	ASSERT_EQ(_size, mx.numRows());
	ASSERT_EQ(_size, mx.numCols());
	vector data{ 0., 0., 0., 0., 0., 0., 0., 0., 0. };
	ASSERT_EQ(data, *mx.getData());
}

TEST(Matrix, ZerosInitRectangular) {

	int rows = 2;
	int cols = 3;

	Matrix2D mx = Matrix2D::zeros(rows, cols);
	ASSERT_EQ(rows, mx.numRows());
	ASSERT_EQ(cols, mx.numCols());
	vector data{ 0., 0., 0., 0., 0., 0. };
	ASSERT_EQ(data, *mx.getData());
}

TEST(Matrix, IdentityInit) {
	unsigned short _size = 3;
	Matrix2D mx = Matrix2D::identity(_size);
	ASSERT_EQ(_size, mx.numRows());
	ASSERT_EQ(_size, mx.numCols());
	vector data
	{ 
		1., 0., 0., 
		0., 1., 0.,
		0., 0., 1. 
	};
	ASSERT_EQ(data, *mx.getData());
	ASSERT_TRUE(mx.isIdentity());
}

TEST(Matrix, DiagonalInit) {
	vector diag{ 1., 2., 3. };
	Matrix2D mx = Matrix2D::diagonal(diag);
	ASSERT_EQ(diag.size(), mx.numRows());
	ASSERT_EQ(diag.size(), mx.numCols());
	vector data
	{ 
		1., 0., 0., 
		0., 2., 0.,
		0., 0., 3.
	};
	ASSERT_EQ(data, *mx.getData());
	ASSERT_TRUE(mx.isDiagonal());
}

TEST(Matrix, Operators) {
	vector* data_1 = new vector
	{
		1., 0., 1.,
		2., 1., 0.,
		3., 4., 1.
	};
	Matrix2D mx1 = Matrix2D(data_1, 3, 3);

	vector* data_2 = new vector
	{
		4., 0., 4.,
		8., 4., 0.,
		12., 16., 4.
	};
	Matrix2D mx2 = Matrix2D(data_2, 3, 3);

	vector* data_final = new vector
	{
		5., 0., 5.,
		10., 5., 0.,
		15., 20., 5.
	};
	Matrix2D mx_final = Matrix2D(data_final, 3, 3);

	double scalar = 5.;
	Matrix2D mx_mul = mx1 * scalar;
	ASSERT_EQ(mx_mul, mx_final);
	Matrix2D mx_added = mx1 + mx2;
	ASSERT_EQ(mx_added, mx_final);
	Matrix2D mx_subbed = mx_final - mx2;
	ASSERT_TRUE(mx_subbed == mx1);
	Matrix2D mx_subbed2 = mx_subbed - mx1;
	ASSERT_TRUE(mx_subbed2.isZeros());
}

TEST(Matrix, Reshaping) {
	vector _data
	{
		5., 8., 5., .1,
		10., 5., 1., 0.
	};
	Matrix2D mx = Matrix2D(&_data, 2, 4);
	vector _expected_data
	{
		5., 10.,
		8., 5.,
		5., 1.,
		.1, 0.
	};
	vector _expected_data_2
	{
		5., 8., 5., .1,
		10., 5., 1., 0.
	};
	mx.transpose();
	ASSERT_EQ(mx.copyData(), _expected_data);
	ASSERT_TRUE(mx.numRows() == 4 and mx.numCols() == 2);
	mx.transpose();
	ASSERT_EQ(mx.copyData(), _expected_data_2);
	mx.reshape(8, 1);
	ASSERT_TRUE(mx.numRows() == 8 and mx.numCols() == 1);
}

TEST(Matrix, Shift) {
	vector _data
	{
		5., 8., 5., 
		.1, 10., 5.,
		1., 0., 1.
	};
	Matrix2D mx = Matrix2D(&_data, 3, 3);
	Matrix2D* mx2 = mx.shift(3);
	vector _expected_data
	{
		8., 8., 5.,
		.1, 13., 5.,
		1., 0., 4.
	};
	ASSERT_EQ(mx2.getData(), _expected_data);
}

TEST(Matrix, ValueGetters) {
	vector _data
	{
		5., 8., 5., .1,
		10., 5., 1., 0.
	};
	Matrix2D mx = Matrix2D(&_data, 2, 4);
	ASSERT_EQ(mx.valueAt(2, 1), 10);
	ASSERT_EQ(mx.realValueAt(1, 3), 0);
}

TEST(Matrix, RowAndColGetters) {
	vector _data
	{
		5., 8., 5., .1,
		10., 5., 1., 0.
	};
	Matrix2D mx = Matrix2D(&_data, 2, 4);

	vector row_1_repr = { 5., 8., 5., .1 };
	vector col_1_repr = { 5., 10. };
	ASSERT_TRUE(row_1_repr == mx.getRow(1) and row_1_repr == mx.getRealRow(0));
	ASSERT_TRUE(col_1_repr == mx.getColumn(1) and col_1_repr == mx.getRealColumn(0));
}

TEST(Matrix, Diagonal) {
	vector _data
	{
		5., 8., 5., .1, 9., 2.,
		10., 5., 1., 0., 5.5, 0.
	};
	Matrix2D mx = Matrix2D(&_data, 2, 6);
	vector expected = vector{ 5., 5. };
	ASSERT_EQ(mx.getDiagonal(), expected);
	mx.reshape(4, 3);
	vector expected2 = vector{ 5., 9., 1. };
	ASSERT_EQ(mx.getDiagonal(), expected2);
}

TEST(Matrix, Trace) {
	vector _data
	{
		5., 8., 5., 
		.1, 9., 2.,
		10., 5., 1.
	};
	Matrix2D mx = Matrix2D(&_data, 3, 3);
	ASSERT_EQ(mx.getTrace(), 15.);
}

TEST(Matrix, TraceLinearity) {
	// Is the matrix trace linear (aka closed under addition + scalar multiplication)
	vector _data1
	{
		9., 3., 4.,
		.1, 4., 2.,
		0., 0., 2.
	};
	Matrix2D mx1 = Matrix2D(&_data1, 3, 3);

	vector _data2
	{
		5., 8., 5.,
		.1, 9., 2.,
		10., 5., 1.
	};
	Matrix2D mx2 = Matrix2D(&_data2, 3, 3);

	// trace(A) + trace(B) == trace(A + B)
	ASSERT_EQ(mx1.getTrace() + mx2.getTrace(), (mx1 + mx2).getTrace());
	
	// scalar * trace(A) == trace(scalar * A)
	double scalar = 3.2;
	ASSERT_EQ(scalar * (mx1.getTrace()), (mx1 * scalar).getTrace());
}

TEST(Matrix, BroadcastAddition) {
	vector _data
	{
		9., 3., 4.,
		.1, 4., 2.,
		0., 0., 2.
	};
	Matrix2D mx = Matrix2D(&_data, 3, 3);
	vector vec{5., 6., 1.};

	vector expected
	{
		14., 9., 5.,
		5.1, 10., 3.,
		5., 6., 3.
	};
	Matrix2D actual = mx.horizontalBroadcastAddition(vec);
	ASSERT_EQ(expected, actual.copyData());
	mx.horizontalBroadcastAddition(vec, true);
	ASSERT_EQ(expected, mx.copyData());
}