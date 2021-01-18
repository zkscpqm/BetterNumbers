#include "../../Core.h"
#include "vector_operations.h"
#include <vector>
#include <tuple>
#include <iostream>


void VectorUtils::print(vector& vec) {
	std::cout << "[ ";
	for (double element: vec) { 
		std::cout << element << " ";
	}
	std::cout << "]";
}

void VectorUtils::print(nvector& vec) {
	std::cout << "[ ";
	for (vector row : vec) {
		print(row);
	}
	std::cout << "]";
}

void VectorUtils::scaleInPlace(vector& vec, double scalar) {
	for (int i = 0; i < vec.size(); i++) {
		vec[i] *= scalar;
	}
}

vector VectorUtils::scale(vector& vec, double scalar) {
	int v1size = vec.size();
	vector result;
	result.reserve(v1size);
	for (int i = 0; i < v1size; i++) {
		double element = vec[i];
		result.emplace_back(element *= scalar);
	}
	return result;
}

double VectorUtils::magnitude(vector& vec) {
	double sum = 0;
	for (double element : vec) {
		sum += std::pow(element, 2);
	}
	return std::pow(sum, .5);
}

double VectorUtils::dotProductMagnitude(vector& vec1, vector& vec2, bool absolute) {
	double dpm = 0;
	for (double element : hadavardProduct(vec1, vec2)) {
		dpm += element;
	}
	if (!absolute) {
		return dpm;
	}
	return abs(dpm);
}

double VectorUtils::sum(vector& vec) {
	double _sum = 0.;
	for (double elem : vec) {
		_sum += elem;
	}
	return _sum;
}

double VectorUtils::dotProduct(vector& vec1, vector& vec2) {
	int v1size = vec1.size();
	if (v1size == vec2.size()) {
		double result = 0;
		for (int i = 0; i < v1size; i++) {
			double elem1 = vec1[i];
			double elem2 = vec2[i];
			result += elem1 * elem2;
		}
		return result;
	}
}

nvector VectorUtils::outerProduct(vector& vec1, vector& vec2) {
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

vector VectorUtils::hadavardProduct(vector& vec1, vector& vec2) {
	int v1size = vec1.size();
	if (v1size == vec2.size()) {
		vector result;
		result.reserve(v1size);
		for (int i = 0; i < v1size; i++) {
			double elem1 = vec1[i];
			double elem2 = vec2[i];
			result.emplace_back(elem1 * elem2);
		}
		return result;
	}
}

void VectorUtils::hadavardProductInPlace(vector& vec1, vector& vec2) {
	int v1size = vec1.size();
	if (v1size == vec2.size()) {
		for (int i = 0; i < v1size; i++) {
			vec1[i] *= vec2[i];
		}
	}
}

vector VectorUtils::crossProduct(vector& vec1, vector& vec2) {
	if (vec1.size() == 3 and vec1.size() == vec2.size()) {
		vector ret{
			vec1[1] * vec2[2] - vec1[2] * vec2[1],
			vec1[2] * vec2[0] - vec1[0] * vec2[2],
			vec1[0] * vec2[1] - vec1[1] * vec2[0]
		};
		return ret;
	}
}

bool VectorUtils::isZeros(vector& vec) {
	for (double elem : vec) {
		if (elem != 0.) {
			return false;
		}
	}
	return true;
}

double VectorUtils::getUnitScalar(vector& vec) {
	if (!isZeros(vec)) {
		return 1 / magnitude(vec);
	}
}

void VectorUtils::toUnitInPlace(vector& vec) {
	double mu = getUnitScalar(vec);
	scaleInPlace(vec, mu);
}

vector VectorUtils::toUnit(vector& vec) {
	double mu = getUnitScalar(vec);
	return scale(vec, mu);
}
