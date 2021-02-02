#include <vector>
#include "..\..\..\BetterNumbers\src\linalg\utils\vector_operations.h"
#include "gtest/gtest.h"


TEST(Vector, Scale) {
	vector vec{ 2., 3., 5. };
	double scalar = 3.;
	vector expected{ 6., 9., 15. };

	vector* res = VectorUtils::scale(&vec, scalar, false);
	ASSERT_EQ(&res, expected);
	VectorUtils::scale(&vec, scalar, true);
	ASSERT_EQ(vec, expected);
}

TEST(Vector, Magnitude) {
	vector vec{ 2., 4., 7. };
	double res = VectorUtils::magnitude(vec);
	ASSERT_EQ(res, std::sqrt(69.));
}

TEST(Vector, DotProduct) {
	vector vec1{ 4., -1., 8.5 };
	vector vec2{ 0., 3.5, 1. };
	double expected = 5.;
	ASSERT_EQ(VectorUtils::dotProduct(vec1, vec2), expected);
}

TEST(Vector, OuterProduct) {
	vector vec1{ 4., -1., 8.5 };
	vector vec2{ 0., 3.5, 1. };
	nvector expected{
		{0., 14., 4.},
		{0., -3.5, -1.},
		{0., 29.75, 8.5}
	};
	ASSERT_EQ(VectorUtils::outerProduct(vec1, vec2), expected);
}

TEST(Vector, HadavardProduct) {
	vector vec1{ 4., -1., 8.5 };
	vector vec2{ 0., 3.5, 1. };
	vector expected{ 0., -3.5, 8.5 };

	ASSERT_EQ(VectorUtils::hadavardProduct(vec1, vec2), expected);
	VectorUtils::hadavardProductInPlace(vec1, vec2);
	ASSERT_EQ(vec1, expected);
}

TEST(Vector, CrossProduct) {
	vector vec1{ 4., -1., 8.5 };
	vector vec2{ 0., 3.5, 1. };
	vector expected{ -30.75, -4.0, 14.0 };

	ASSERT_EQ(VectorUtils::crossProduct(vec1, vec2), expected);
}

TEST(Vector, IsZeros) {
	vector vec1{ 0, 0, 0, 0, 0, 0 };
	vector vec2{ 0, 0, 0, 0, 1, 0 };
	ASSERT_TRUE(VectorUtils::isZeros(vec1));
	ASSERT_FALSE(VectorUtils::isZeros(vec2));
}

TEST(Vector, Unit) {

}