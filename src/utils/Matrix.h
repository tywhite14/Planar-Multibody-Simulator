#pragma once

#include <iostream>
#include <vector>

#include "Vect2d.h"

class Matrix
{
public:

	// default constructor to empty matrix
	Matrix();

	// Construct matrix from Vect2d
	Matrix(Vect2d vec);

	// Square matrix constructor
	Matrix(const unsigned int sizeIn);

	// non-square matrix constructor
	Matrix(const unsigned int rows, const unsigned int cols);

	// construct with initializer list
	Matrix(
		const unsigned int rows,
		const unsigned int cols,
		const std::initializer_list<double>& list
	);

	const int rows() const;
	const int cols() const;
	const double det() const;
	Matrix inverse() const;
	Matrix transpose() const;
	Matrix identity() const;
	Matrix rotation(const double angle) const;
	Matrix operator-() const;
	Matrix operator+(const Matrix& b) const;
	Matrix operator-(const Matrix& b) const;
	Matrix operator*(const Matrix& b) const;
	Vect2d operator*(const Vect2d& v) const;
	Matrix operator*(const double s) const;
	Matrix operator/(const double s) const;
	bool operator==(const Matrix& b) const;
	Matrix& operator=(const std::initializer_list<double>& list);
	double& operator()(unsigned int elm);
	const double& operator()(unsigned int elm) const;
	double& operator()(unsigned int row, unsigned int col);
	friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);

private:
	unsigned int _rows;
	unsigned int _cols;
	unsigned int _count;
	std::vector<double> _data;
};
