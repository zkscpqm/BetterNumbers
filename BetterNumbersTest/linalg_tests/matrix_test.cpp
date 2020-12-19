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
}
