#pragma once

#include "log.h"
#include "constants.h"
#include "Vector.h"

#include <iostream>
#include <iomanip>
#include <initializer_list>
#include <stdlib.h>

#ifdef _DEBUG
#define BOUNDS_CHECK
#endif

class Matrix
{
public:
	Matrix();
	Matrix(const double s);
	Matrix(const int rows, const int cols, double initVal = 0.0);
	Matrix(Vec2d& v);
	Matrix(Vec3d& v);
	Matrix(const Matrix& b);
	~Matrix();

	inline int	rows()  const { return m_rows; }
	inline int	cols()  const { return m_cols; }
	inline int	count() const { return m_count; }
	double		magnitude() const;
	double		det() const;
	Matrix		resize(int rows, int cols) const;
	Matrix		inverse() const;
	Matrix		transpose() const;
	void		LUdecomp(Matrix& L, Matrix& U) const;
	Matrix		solve(Matrix& b) const;
	Matrix		identity() const;
	static Matrix zeros(int r = 1, int c = -1);
	static Matrix ones(int r = 1, int c = -1);
	Matrix		random() const;
	Matrix		randi(const int max, bool pm = true) const;

	Matrix		operator-() const;
	Matrix		operator+(const Matrix& b) const;
	Matrix		operator-(const Matrix& b) const;
	Matrix		operator*(const Matrix& b) const;
	Matrix		operator%(const Matrix& b) const;
	Matrix		operator*(const double s) const;
	Matrix		operator/(const double s) const;
	bool		operator==(const Matrix& b) const;
	Matrix		operator=(const std::initializer_list<double>& list);
	Matrix&		operator=(const Matrix& b);	// Copy assignment operator
	double		operator()(int elm) const;
	double&		operator()(int elm);
	double		operator()(int row, int col) const;
	double&		operator()(int row, int col);

	friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);

private:
	int m_rows;
	int m_cols;
	int m_count;
	double* m_data;

	void allocate(double initVal = 0.0);
	void deallocate();
};
