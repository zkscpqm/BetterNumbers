#include <vector>
#include "..\..\BetterNumbers\BetterNumbers.h"
#include "gtest/gtest.h"


TEST(MatrixTest, BasicInit) {
	vector data{ 1., 2., 3., 4., 5., 6. };
	int rows = 2;
	int cols = 3;

	Matrix2D mx = Matrix2D(&data, rows, cols);

	ASSERT_EQ(rows, mx.numRows());
	ASSERT_EQ(cols, mx.numCols());
	ASSERT_EQ(data, *mx.getData());
}

TEST(MatrixTest, NestedInit) {
	nvector data{
		{ 1., 2., 3., 4., 5., 6. },
		{ 1., 2., 3., 4., 5., 6. },
		{ 1., 2., 3., 4., 5., 6. }
	};

	Matrix2D mx = Matrix2D(&data);
	ASSERT_EQ(data.size(), mx.numRows());
	ASSERT_EQ(data.at(0).size(), mx.numCols());
	ASSERT_EQ(data, mx.getNestedData());
}

TEST(MatrixTest, ZerosInitSquare) {
	unsigned short _size = 3;
	Matrix2D mx = Matrix2D::zeros(_size);
	ASSERT_EQ(_size, mx.numRows());
	ASSERT_EQ(_size, mx.numCols());
	vector data{ 0., 0., 0., 0., 0., 0., 0., 0., 0. };
	ASSERT_EQ(data, *mx.getData());
}

TEST(MatrixTest, ZerosInitRectangular) {

	int rows = 2;
	int cols = 3;

	Matrix2D mx = Matrix2D::zeros(rows, cols);
	ASSERT_EQ(rows, mx.numRows());
	ASSERT_EQ(cols, mx.numCols());
	vector data{ 0., 0., 0., 0., 0., 0. };
	ASSERT_EQ(data, *mx.getData());
}

TEST(MatrixTest, IdentityInit) {
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

TEST(MatrixTest, DiagonalInit) {
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

TEST(MatrixTest, Operators) {
	vector data_1
	{
		1., 0., 1.,
		2., 1., 0.,
		3., 4., 1.
	};
	Matrix2D mx1 = Matrix2D(&data_1, 3, 3);

	vector data_2
	{
		4., 0., 4.,
		8., 4., 0.,
		12., 16., 4.
	};
	Matrix2D mx2 = Matrix2D(&data_2, 3, 3);

	vector data_final
	{
		5., 0., 5.,
		10., 5., 0.,
		15., 20., 5.
	};
	Matrix2D mx_final = Matrix2D(&data_final, 3, 3);

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

TEST(MatrixTest, Reshaping) {
	vector _data
	{
		5., 8., 5., .1,
		10., 5., 1., 0.
	};
	Matrix2D mx = Matrix2D(&_data, 2, 4);

	mx.transpose();
	ASSERT_TRUE(mx.numRows() == 4 and mx.numCols() == 2);
	mx.reshape(8, 1);
	ASSERT_TRUE(mx.numRows() == 8 and mx.numCols() == 1);
}

TEST(MatrixTest, ValueGetters) {
	vector _data
	{
		5., 8., 5., .1,
		10., 5., 1., 0.
	};
	Matrix2D mx = Matrix2D(&_data, 2, 4);
	ASSERT_EQ(mx.valueAt(2, 1), 10);
	ASSERT_EQ(mx.realValueAt(1, 3), 0);
}