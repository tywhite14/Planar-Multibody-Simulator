#pragma once

#include <iostream>
#include <iomanip>
#include <initializer_list>
#include <vector>
#include <stdlib.h>
#include "log.h"
#include "constants.h"

#ifdef _DEBUG
#define BOUNDS_CHECK
#endif

template<std::size_t R, std::size_t C>
class Matrix
{
public:
	Matrix();
	Matrix(const double s);
	Matrix(const std::initializer_list<double>& list);
	inline int				rows() const { return R; }
	inline int				cols() const  { return C; }
	inline int				count() const { return _count; }
	double					det() const;
	Matrix<R, C>			inverse() const;
	Matrix<C, R>			transpose() const;
	void					LUdecomp(Matrix& L, Matrix& U) const;
	Matrix<R, 1>			solve(Matrix<R, 1>& b);
	static Matrix<R, C>		identity();
	static Matrix<R, C>		zeros();
	static Matrix<R, C>		ones();
	Matrix<R, C>			random() const;
	Matrix<R, C>			randi(const int max, bool pm = true) const;
	Matrix<R, C>			operator-() const;
	Matrix<R, C>			operator+(const Matrix& b) const;
	Matrix<R, C>			operator-(const Matrix& b) const;
	template <std::size_t B_COLS>
	Matrix<R, B_COLS>		operator*(const Matrix<C, B_COLS>& b) const;
	Matrix<R, C>			operator%(const Matrix<R, C>& b) const;
	Matrix<R, C>			operator*(const double s) const;
	Matrix<R, C>			operator/(const double s) const;
	bool					operator==(const Matrix& b) const;
	Matrix<R, C>			operator=(const std::initializer_list<double>& list);
	double					operator()(int elm) const;
	double&					operator()(int elm);
	double					operator()(int row, int col) const;
	double&					operator()(int row, int col);
	friend std::ostream&	operator<<(std::ostream& os, const Matrix& mat)
	{
		os << " =\n";

		if (mat._count == 0)
		{
			os << "[ ]";
			return os;
		}

		for (std::size_t i = 0; i < R; i++) {
			for (std::size_t j = 0; j < C; j++) {
				os <<
					std::setw(6) <<
					std::setprecision(4) <<
					mat((int) (i * C + j));

				if ((j + 1) != C) {
					os << ", ";
				}
			}
			os << "\n";
		}

		return os;
	}

private:
	unsigned int _count = R * C;
	double _data[R * C] = { 0 };
};

using Vec2d = Matrix<2, 1>;
using Vec3d = Matrix<3, 1>;
using Mat3d = Matrix<3, 3>;
using Mat2d = Matrix<2, 2>;

template<std::size_t R, std::size_t C>
Matrix<R, C>::Matrix()
{
}

template<std::size_t R, std::size_t C>
Matrix<R, C>::Matrix(const double s)
{
	memset(_data, s, sizeof(_data));
}

template<std::size_t R, std::size_t C>
Matrix<R, C>::Matrix(const std::initializer_list<double>& list)
{
	debug("Constructed from initializer list!");
	if (list.size() != _count) {
		if (list.size() == 1) {
			double val = *list.begin();
			for (uint32_t i = 0; i < _count; i++) {
				_data[i] = val;
			}
			return;
		}

		FATAL("Initializer list is not the same size as matrix.", 1);
	}

	int i = 0;
	for (auto& el : list) {
		_data[i++] = el;
	}
}

template<std::size_t R, std::size_t C>
double Matrix<R, C>::det() const
{
#ifdef BOUNDS_CHECK
	if (R != C) {
		FATAL("Matrix must be square.", 2);
		return 0.0;
	}
#endif

	if (*this == identity()) {
		return 1.0;
	}

	if (R == 1)
		return _data[0];
	if (R == 2)
		return _data[0] * _data[3] - _data[1] * _data[2];
	if (R == 3) {
		return
			_data[0] * _data[4] * _data[8] +
			_data[1] * _data[5] * _data[6] +
			_data[2] * _data[3] * _data[7] -
			_data[2] * _data[4] * _data[6] -
			_data[1] * _data[3] * _data[8] -
			_data[0] * _data[5] * _data[7];
	}

	FATAL("Determinant for matrices larger than 3x3 is not implemented yet.", 3);
}

template<std::size_t R, std::size_t C>
Matrix<R, C> Matrix<R, C>::inverse() const
{
#ifdef BOUNDS_CHECK
	if (R != C) {
		FATAL("Inverse: Matrix must be square.", 4);
	}
#endif
	
	if (R == 1) {
		return Matrix<R, C>(1.0 / _data[0]);
	}

	Matrix<R, C> L;
	Matrix<R, C> U;
	LUdecomp(L, U);

	// solve LU decomposed system
	return Matrix<R, C>(69.0);
}

template<std::size_t R, std::size_t C>
Matrix<C, R> Matrix<R, C>::transpose() const
{
	Matrix<C, R> res;

	for (int i = 0; i < C; i++) {
		for (int j = 0; j < R; j++) {
			res(i, j) = _data[j * C + i];
		}
	}

	return res;
}

template<std::size_t R, std::size_t C>
inline void Matrix<R, C>::LUdecomp(Matrix& L, Matrix& U) const
{
#ifdef BOUNDS_CHECK
	if (R != C) {
		FATAL("LU Decompisition: Matrix must be square", -1);
	}
	else if (fabs(_data[0]) < c::EPS) {
		FATAL("LU Decompisition: First element must not be zero.", -1);
	}
#endif

	constexpr unsigned short N = R;
	L = L.identity();
	U = *this;

	for (int r = 1; r < N; r++) {
		for (int c = 0; c < r; c++) {
			// slightly better performance for large, sparse matrices
			//if (fabs(U(r, c)) < c::EPS) { continue; }

			double term = U(r, c) / U(c, c);

			// don't have row notation yet
			for (int i = 0; i < N; i++) {
				U(r, i) -= U(c, i) * term;
			}
			L(r, c) = term;
		}
	}
}

template<std::size_t R, std::size_t C>
inline Matrix<R, 1> Matrix<R, C>::solve(Matrix<R, 1>& b)
{
#ifdef BOUNDS_CHECK
	if (R != C) {
		FATAL("Solve: Matrix must be square", -1);
	}
	else if (fabs(_data[0]) < c::EPS) {
		FATAL("Solve: First element must not be zero.", -1);
	}
#endif

	constexpr unsigned short N = R;
	Matrix<R, C> L = identity();
	Matrix<R, C> U = *this;
	Matrix<R, 1> y = b;
	double term1;

	// LU decomposition and forward substitution (L*y = b)
	for (int r = 1; r < N; r++) {
		term1 = 0;
		for (int c = 0; c < r; c++) {
			// slightly better performance for large, sparse matrices
			//if (fabs(U(r, c)) < c::EPS) { continue; }

			double term2 = U(r, c) / U(c, c);

			// don't have row notation yet
			for (int i = 0; i < N; i++) {
				U(r, i) -= U(c, i) * term2;
			}
			L(r, c) = term2;
			term1 += L(r, c) * y(c);
		}
		y(r) = b(r) - term1;
	}

	// Backward substitution (U*x = y)
	Matrix<R, 1> x;

	for (int r = N-1; r >= 0; r--) {
		term1 = 0;
		for (int c = N-1; c >= r; c--) {
			term1 += U(r, c) * x(c);
			//debug("(" << r + 1 << "," << c + 1 << "): " << term);
		}
		x(r) = (y(r) - term1) / U(r, r);
	}

	return x;
}

template<std::size_t R, std::size_t C>
Matrix<R, C> Matrix<R, C>::identity()
{
#ifdef BOUNDS_CHECK
	if (R != C) {
		FATAL("Identity: Matrix must be square", -1);
	}
#endif

	Matrix<R, C> res;

	for (int i = 0; i < R; i++)
	{
		res._data[i * C + i] = 1.0;
	}

	return res;
}

template<std::size_t R, std::size_t C>
Matrix<R, C> Matrix<R, C>::zeros()
{
	return Matrix<R, C>();
}

template<std::size_t R, std::size_t C>
Matrix<R, C> Matrix<R, C>::ones()
{
	Matrix<R, C> res;

	for (int i = 0; i < _count; i++)
	{
		res._data[i] = 1.0;
	}

	return res;
}

template<std::size_t R, std::size_t C>
Matrix<R, C> Matrix<R, C>::random() const
{
	Matrix<R, C> res;

	for (int i = 0; i < R * C; i++) {
		res._data[i] = (double) rand() / RAND_MAX;
	}

	return res;
}

template<std::size_t R, std::size_t C>
Matrix<R, C> Matrix<R, C>::randi(const int max, bool pm) const
{
	Matrix<R, C> res;
	if (pm) {
		for (int i = 0; i < R * C; i++) {
			res._data[i] = rand() % (2 * (max+1)) - max;
		}
		return res;
	}

	for (int i = 0; i < R * C; i++) {
		res._data[i] = rand() % (max + 1);
	}
	return res;
}

template<std::size_t R, std::size_t C>
Matrix<R, C> Matrix<R, C>::operator-() const
{
	Matrix<R, C> res = *this;

	for (int i = 0; i < (int)_count; i++)
	{
		res._data[i] *= -1.0;
	}

	return res;
}

template<std::size_t R, std::size_t C>
Matrix<R, C> Matrix<R, C>::operator+(const Matrix& b) const
{
	// Compiler prevents incompatible sizes

	Matrix<R, C> res = *this;

	for (int i = 0; i < (int)_count; i++) {
		res._data[i] += b._data[i];
	}

	return res;
}

template<std::size_t R, std::size_t C>
Matrix<R, C> Matrix<R, C>::operator-(const Matrix& b) const
{
	// Compiler prevents incompatible sizes

	Matrix<R, C> res = *this;

	for (int i = 0; i < (int)_count; ++i) {
		res._data[i] -= b._data[i];
	}

	return res;
}

template<std::size_t R, std::size_t C>
template <std::size_t B_COLS>
Matrix<R, B_COLS> Matrix<R, C>::operator*(const Matrix<C, B_COLS>& b) const
{
	// Compiler prevents incompatible sizes

	Matrix<R, B_COLS> res;

	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < B_COLS; ++j) {
			for (int k = 0; k < C; ++k) {
				res(i, j) += _data[i * C + k] * b(k, j);
			}
		}
	}

	return res;
}


template<std::size_t R, std::size_t C>
Matrix<R, C> Matrix<R, C>::operator%(const Matrix<R, C>& b) const
{
	// Compiler prevents incompatible sizes

	Matrix<R, C> res;

	for (int i = 0; i < R*C; ++i) {
		res._data[i] = _data[i] * b._data[i];
	}

	return res;
}

template<std::size_t R, std::size_t C>
Matrix<R, C> Matrix<R, C>::operator*(const double s) const
{
	Matrix<R, C> res = *this;

	for (unsigned int i = 0; i < _count; i++) {
		res._data[i] *= s;
	}

	return res;
}

template<std::size_t R, std::size_t C>
Matrix<R, C> Matrix<R, C>::operator/(const double s) const
{
	// leave this check in. It could happen at any point.
	if (std::fabs(s) < c::EPS) {
		FATAL("Cannot divide matrix by zero.", 7);
	}

	return *this * (1.0 / s);
}

template<std::size_t R, std::size_t C>
bool Matrix<R, C>::operator==(const Matrix& b) const
{
#ifdef BOUNDS_CHECK
	if (R != b.rows() || C != b.cols()) {
		FATAL("Matrices have incompatible sizes for this operation.", 8);
	}
#endif

	for (int i = 0; i < _count; i++)
	{
		if (fabs(_data[i] - b._data[i]) > c::EPS)
			return false;
	}

	return true;
}

template<std::size_t R, std::size_t C>
Matrix<R, C> Matrix<R, C>::operator=(const std::initializer_list<double>& list)
{
	// probably don't bound check this one
	if (list.size() != _count) {
		FATAL("Initializer list is not the same size as matrix.", 9);
	}

	int i = 0;
	for (auto& el : list) {
		_data[i++] = el;
	}

	return *this;
}

template<std::size_t R, std::size_t C>
double Matrix<R, C>::operator()(int elm) const
{
#ifdef BOUNDS_CHECK
	if ((unsigned int)elm >= _count || elm < 0) {
		FATAL("Accessing out of array bounds", 10);
	}
#endif

	return _data[elm];
}

template<std::size_t R, std::size_t C>
double& Matrix<R, C>::operator()(int elm)
{
#ifdef BOUNDS_CHECK
	if ((unsigned int)elm >= _count || elm < 0) {
		FATAL("Accessing out of array bounds", 11);
	}
#endif

	return _data[elm];
}

template<std::size_t R, std::size_t C>
double Matrix<R, C>::operator()(int row, int col) const
{
#ifdef BOUNDS_CHECK
	if (row >= R || row < 0 || col >= C || col < 0) {
		FATAL("Accessing out of array bounds", 12);
	}
#endif

	return _data[row * C + col];
}

template<std::size_t R, std::size_t C>
double& Matrix<R, C>::operator()(int row, int col)
{
#ifdef BOUNDS_CHECK
	if (row >= R || row < 0 || col >= C || col < 0) {
		FATAL("Accessing out of array bounds", 13);
	}
#endif

	return _data[row * C + col];
}

