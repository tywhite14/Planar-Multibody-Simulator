#include <cassert>
#include <iomanip>
#include <cmath>

#include "log.h"
#include "Matrix.h"

Matrix::Matrix() :
	_rows(0),
	_cols(0),
	_count(0)
{ }

Matrix::Matrix(Vect2d vec) :
	_rows(2),
	_cols(1),
	_count(2),
	_data({ vec.x, vec.y })
{ }

Matrix::Matrix(const unsigned int sizeIn) :
	_rows(sizeIn),
	_cols(sizeIn),
	_count(sizeIn* sizeIn),
	_data(_count, 0.0)
{ }

Matrix::Matrix(const unsigned int rows, const unsigned int cols) :
	_rows(rows),
	_cols(cols),
	_count(rows*cols),
	_data(_count, 0.0)
{ }

Matrix::Matrix(
	const unsigned int rows, 
	const unsigned int cols,
	const std::initializer_list<double>& list
) :
	_rows(rows),
	_cols(cols),
	_count(list.size()),
	_data(list)
{ }

const int Matrix::rows() const { return _rows; }
const int Matrix::cols() const { return _cols; }

const double Matrix::det() const
{
	assert(_rows == _cols);

	if (*this == identity())
	{
		return 1.0;
	}

	if (_rows == 1)
		return _data.at(0);
	if (_rows == 2)
		return _data.at(0) * _data.at(3) - _data.at(1) * _data.at(2);
	if (_rows == 3) {
		return
			_data.at(0) * _data.at(4) * _data.at(8) +
			_data.at(1) * _data.at(5) * _data.at(6) +
			_data.at(2) * _data.at(3) * _data.at(7) -
			_data.at(2) * _data.at(4) * _data.at(6) -
			_data.at(1) * _data.at(3) * _data.at(8) -
			_data.at(0) * _data.at(5) * _data.at(7);
	}
	if (_rows > 3) {
		error("Not implemented yet");
	}

	return 0.0;
}

Matrix Matrix::inverse() const
{
	assert(_rows == _cols);

	if (_rows == 1)
	{
		Matrix res(1);
		std::cout << 1.0 / _data.at(0);
		res(0) = 1.0 / _data.at(0);
		return res;
	}
	if (_rows == 2) {
		error("Not implemented yet");
	}

	return Matrix();
}

Matrix Matrix::transpose() const
{
	Matrix res(_cols, _rows);

	for (unsigned int i = 0; i < _cols; i++) {
		for (unsigned int j = 0; j < _rows; j++) {
			res(i, j) = _data.at(j * _cols + i);
		}
	}

	return res;
}

Matrix Matrix::identity() const
{
	assert(_rows == _cols);

	Matrix res(_rows);

	for (unsigned int i = 0; i < _cols; i++)
	{
		res(i, i) = 1;
	}

	return res;
}

Matrix Matrix::operator-() const
{
	Matrix res(_rows, _cols);

	for (unsigned int i =0; i<_count; i++)
	{
		res(i) = -_data[i];
	}

	return res;
}

Matrix Matrix::operator+(const Matrix& b) const
{
	assert(_rows == b._rows && _cols == b._cols);

	Matrix res(_rows, _cols);

	for (int i = 0; i < _data.size(); i++)
	{
		res(i) = _data.at(i) + b._data.at(i);
	}

	return res;
}

Matrix Matrix::operator-(const Matrix& b) const
{
	assert(_rows == b._rows && _cols == b._cols);

	Matrix temp = b;
	return *this + (-temp);
}

Matrix Matrix::operator*(const Matrix& b) const
{
	assert(_cols == b._rows);
	Matrix res(_rows, b._cols);

	for (unsigned int i = 0; i < _rows; ++i) {
		for (unsigned int j = 0; j < b._cols; ++j) {
			for (unsigned int k = 0; k < _cols; ++k) {
				res(i, j) += _data.at(i * _cols + k) * b._data.at(k * b._cols + j);
			}
		}
	}

	return res;
}

Matrix Matrix::operator*(const double s) const
{
	constexpr double tol = 1e-9;
	if (fabs(s) < tol)
		return Matrix(_rows, _cols);

	if (fabs(s + 1) < tol)
		return -*this;

	Matrix res(_rows, _cols);

	int i = 0;
	for (auto& elm : _data)
	{
		res(i++) = elm * s;
	}

	return res;
}

Matrix Matrix::operator/(const double s) const
{
	assert(s != 0);
	double sInv = 1 / s;
	return Matrix(*this * sInv);
}

bool Matrix::operator==(const Matrix& b) const
{
	assert(_rows == b._rows && _cols == b._cols);

	for (unsigned int i = 0; i < _count; i++)
	{
		if (_data.at(i) != b._data.at(i))
			return false;
	}
	return true;
}

Matrix& Matrix::operator=(const std::initializer_list<double>& list) {
	assert(list.size() == _count);

	auto it = list.begin();
	for (double& elm : _data)
	{
		elm = *it++;
	}

	return *this;
}

double& Matrix::operator()(unsigned int elm)
{
	assert(elm < _count);
	return _data.at(elm);
}
const double& Matrix::operator()(unsigned int elm) const
{
	assert(elm < _count);
	return _data.at(elm);
}
double& Matrix::operator()(unsigned int row, unsigned int col)
{
	assert(row+1 <= _rows && col+1 <= _cols);
	return _data.at(row * _cols + col);
}

std::ostream& operator<<(std::ostream& os, const Matrix& mat)
{
	os << " =\n";

	// print brackets for empty matrix
	if (mat._count == 0)
	{
		os << "[ ]";
		return os;
	}

	for (unsigned int i = 0; i < mat._rows; i++) {
		for (unsigned int j = 0; j < mat._cols; j++) {
			os << 
				std::setw(6) << 
				std::setprecision(4) <<
				mat(i * mat._cols + j);
			
			if ((j + 1) != mat._cols) {
				os << ", ";
			}
		}
		os << "\n";
	}

	return os;
}
