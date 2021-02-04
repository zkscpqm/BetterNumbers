#include "../../Core.h"
#include "vector_operations.h"
#include <vector>
#include <tuple>
#include <iostream>


void
VectorUtils::print(vector* vec) {
	std::cout << "[ ";
	for (double element: *vec) { 
		std::cout << element << " ";
	}
	std::cout << "]";
}

void
VectorUtils::print(nvector* vec) {
	std::cout << "[ ";
	for (vector row : *vec) {
		print(&row);
	}
	std::cout << "]";
}

vector*
VectorUtils::scaleInPlace(vector* vec, double scalar) {

	for (int i = 0; i < vec->size(); i++) vec->at(i) *= scalar;
	return vec;
}

vector
VectorUtils::scale(vector* vec, double scalar) {
	vector result = vector{ *vec };
	for (int i = 0; i < vec->size(); i++) result[i] *= scalar;
	return result;
}

double
VectorUtils::magnitude(vector* vec) {
	double sum = 0;
	for (double element : *vec) {
		sum += std::pow(element, 2);
	}
	return std::pow(sum, .5);
}

double
VectorUtils::dotProductMagnitude(vector* vec1, vector* vec2, bool absolute) {
	double dpm = 0;
	for (double element : hadavardProduct(vec1, vec2)) dpm += element;
	if (!absolute) return dpm;
	else return abs(dpm);
}

double
VectorUtils::sum(vector* vec) {
	double _sum = 0.;
	for (double elem : *vec) _sum += elem;
	return _sum;
}

vector
VectorUtils::elementwiseAddition(vector* vec1, vector* vec2) {
	int v1size = vec1->size();
	if (v1size == vec2->size()) {
		vector result = vector{ *vec1 };
		for (int i = 0; i < v1size; i++) result[i] += vec2->at(i);
		return result;
	}
	else throw; //Make exception
}

vector*
VectorUtils::elementwiseAdditionInPlace(vector* vec1, vector* vec2) {
	int v1size = vec1->size();
	if (v1size == vec2->size()) {
		for (int i = 0; i < v1size; i++) vec1->at(i) += vec2->at(i);
		return vec1;
	}
	else throw; //Make exception
}


double 
VectorUtils::dotProduct(vector* vec1, vector* vec2) {
	int v1size = vec1->size();
	if (v1size == vec2->size()) {
		double result = 0;
		for (int i = 0; i < v1size; i++) result += vec1->at(i) * vec2->at(i);
		return result;
	}
	else throw;
}

nvector
VectorUtils::outerProduct(vector* vec1, vector* vec2) {
	nvector result;
	result.reserve(vec1->size());
	for (double v1_elem : *vec1) {
		vector row;
		row.reserve(vec2->size());
		for (double v2_elem : *vec2) row.emplace_back(v1_elem * v2_elem);
		result.emplace_back(row);
	}
	return result;
}

vector
VectorUtils::hadavardProduct(vector* vec1, vector* vec2) {
	int v1size = vec1->size();
	if (v1size == vec2->size()) {
		vector result = vector{ *vec1 };
		for (int i = 0; i < v1size; i++) result[i] *= vec2->at(i);
		return result;
	}
	else throw;
}

vector*
VectorUtils::hadavardProductInPlace(vector* vec1, vector* vec2) {
	int v1size = vec1->size();
	if (v1size == vec2->size()) {
		for (int i = 0; i < v1size; i++) vec1->at(i) *= vec2->at(i);
		return vec1;
	}
	else throw;
}

vector
VectorUtils::crossProduct(vector* vec1, vector* vec2) {
	if (vec1->size() == 3 and vec1->size() == vec2->size()) {
		return vector{
			vec1->at(1) * vec2->at(2) - vec1->at(2) * vec2->at(1),
			vec1->at(2) * vec2->at(0) - vec1->at(0) * vec2->at(2),
			vec1->at(0) * vec2->at(1) - vec1->at(1) * vec2->at(0)
		};
	}
	else throw;
}

vector*
VectorUtils::crossProductInPlace(vector* vec1, vector* vec2) {
	if (vec1->size() == 3 and vec1->size() == vec2->size()) {
		vec1->at(0) = vec1->at(1) * vec2->at(2) - vec1->at(2) * vec2->at(1);
		vec1->at(1) = vec1->at(2) * vec2->at(0) - vec1->at(0) * vec2->at(2);
		vec1->at(2) = vec1->at(0) * vec2->at(1) - vec1->at(1) * vec2->at(0);
		return vec1;
	}
	else throw;
}

bool
VectorUtils::isZeros(vector* vec) {
	for (double elem : *vec) {
		if (elem != 0.) {
			return false;
		}
	}
	return true;
}

double
VectorUtils::getUnitScalar(vector* vec) {
	if (!isZeros(vec)) {
		return 1 / magnitude(vec);
	}
}

vector
VectorUtils::toUnit(vector* vec) {
	double mu = getUnitScalar(vec);
	return scale(vec, mu);
}

vector*
VectorUtils::toUnitInPlace(vector* vec) {
	double mu = getUnitScalar(vec);
	return scaleInPlace(vec, mu);
}

