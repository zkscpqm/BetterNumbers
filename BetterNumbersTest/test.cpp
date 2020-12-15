#include "pch.h"
#include "../BetterNumbers/Matrix2D.h"
#include <vector>

TEST(MatrixTest, BasicInit) {
	std::vector<double> data = { 1, 2, 3, 4, 5, 6 };
	int rows = 2;
	int cols = 3;

	Matrix2D mx = Matrix2D(&data, rows, cols);

	ASSERT_EQ(rows, mx.rows());
	ASSERT_EQ(cols, mx.cols());
	ASSERT_EQ(data, *mx.getData());
}