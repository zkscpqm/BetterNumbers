#pragma once

#include "../../Core.h"
#include <vector>
#include <iostream>


typedef std::vector<double> vector;
typedef std::vector<vector> nvector;


class BN_API VectorUtils
{
public:

	static void print_vector(vector& vec);

	static void scale_vector_in_place(vector& vec, double scalar);
	static vector scale_vector(vector& vec, double scalar);

	static double vector_maginitude(vector& vec);
	static double dot_product_magnitude(vector& vec1, vector& vec2, bool absolute);
	static double vector_dot_product(vector& vec1, vector& vec2);

	static nvector vector_outer_product(vector& vec1, vector& vec2);
	static vector vector_hadavard_product(vector& vec1, vector& vec2);
	static vector vector_cross_product(vector& vec1, vector& vec2);

	static bool vector_is_zeros(vector& vec);

	static double vector_unit_scalar(vector& vec);
	static void vector_to_unit_in_place(vector& vec);
	static vector vector_to_unit(vector& vec);
};