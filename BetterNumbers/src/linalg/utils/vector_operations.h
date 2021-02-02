#pragma once

#include "../../Core.h"
#include <vector>
#include <iostream>


typedef std::vector<double> vector;
typedef std::vector<vector> nvector;


class BN_API VectorUtils
{
public:

	static void print(vector& vec);
	static void print(nvector& vec);

	static vector* scale(vector* vec, double scalar, bool in_place=true);

	static double magnitude(vector& vec);
	static double dotProductMagnitude(vector& vec1, vector& vec2, bool absolute); // Test later
	static double dotProduct(vector& vec1, vector& vec2);

	static double sum(vector& vec1);
	static vector* elementwiseAddition(vector& vec1, vector& vec2);
	static nvector* outerProduct(vector& vec1, vector& vec2);
	static vector* hadavardProduct(vector& vec1, vector& vec2);
	static void hadavardProductInPlace(vector& vec1, vector& vec2);
	static vector* crossProduct(vector& vec1, vector& vec2);

	static bool isZeros(vector& vec);

	static double getUnitScalar(vector& vec);
	static vector* toUnit(vector& vec);
};