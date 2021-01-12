#include "../../Core.h"
#include "vector_operations.h"
#include <vector>
#include <tuple>
#include <iostream>


void VectorUtils::print_vector(vector& vec) {
	std::cout << "[ ";
	for (double element: vec) { 
		std::cout << element << " ";
	}
	std::cout << "]";
}

void VectorUtils::scale_vector_in_place(vector& vec, double scalar) {
	for (int i = 0; i < vec.size(); i++) {
		vec[i] *= scalar;
	}
}

vector VectorUtils::scale_vector(vector& vec, double scalar) {
	int v1size = vec.size();
	vector result;
	result.reserve(v1size);
	for (int i = 0; i < v1size; i++) {
		result.emplace_back(vec[i] *= scalar);
	}
	return result;
}

double VectorUtils::vector_maginitude(vector& vec) {
	double sum = 0;
	for (double element : vec) {
		sum += std::pow(element, 2);
	}
	return std::pow(sum, .5);
}

double VectorUtils::dot_product_magnitude(vector& vec1, vector& vec2, bool absolute) {
	double dpm = 0;
	for (double element : vector_hadavard_product(vec1, vec2)) {
		dpm += element;
	}
	if (!absolute) {
		return dpm;
	}
	return abs(dpm);
}

double VectorUtils::vector_dot_product(vector& vec1, vector& vec2) {
	int v1size = vec1.size();
	if (v1size == vec2.size()) {
		double result = 0;
		for (int i = 0; i < v1size; i++) {
			result += vec1[i] * vec2[i];
		}
		return result;
	}
}

nvector VectorUtils::vector_outer_product(vector& vec1, vector& vec2) {
	nvector result;
	result.reserve(vec1.size());
	for (double v1_elem : vec1) {
		vector row;
		row.reserve(vec2.size());
		for (double v2_elem : vec2) {
			row.emplace_back(v1_elem * v2_elem);
		}
		result.emplace_back(row);
	}
	return result;
}

vector VectorUtils::vector_hadavard_product(vector& vec1, vector& vec2) {
	int v1size = vec1.size();
	if (v1size == vec2.size()) {
		vector result;
		result.reserve(v1size);
		for (int i = 0; i < v1size; i++) {
			result.emplace_back(vec1[i] * vec2[i]);
		}
		return result;
	}
}

vector VectorUtils::vector_cross_product(vector& vec1, vector& vec2) {
	if (vec1.size() == 3 and vec1.size() == vec2.size()) {
		vector ret{
			vec1[1] * vec2[2] - vec1[2] * vec2[1],
			vec1[2] * vec2[0] - vec1[0] * vec2[2],
			vec1[0] * vec2[1] - vec1[1] * vec2[0]
		};
		return ret;
	}
}

bool VectorUtils::vector_is_zeros(vector& vec) {
	for (double elem : vec) {
		if (elem != 0.) {
			return false;
		}
	}
	return true;
}

double VectorUtils::vector_unit_scalar(vector& vec) {
	if (!vector_is_zeros(vec)) {
		return 1 / vector_maginitude(vec);
	}
}

void VectorUtils::vector_to_unit_in_place(vector& vec) {
	double mu = vector_unit_scalar(vec);
	scale_vector_in_place(vec, mu);
}

vector VectorUtils::vector_to_unit(vector& vec) {
	double mu = vector_unit_scalar(vec);
	return scale_vector(vec, mu);
}
