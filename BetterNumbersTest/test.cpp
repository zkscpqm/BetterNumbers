#include <vector>
#include "..\BetterNumbers\BetterNumbers.h"
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

	ASSERT_EQ(3, mx.numRows());
	ASSERT_EQ(6, mx.numCols());
	ASSERT_EQ(data, mx.getNestedData());
}