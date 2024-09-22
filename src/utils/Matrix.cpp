#include "Matrix.h"
#include <math.h>

Matrix::Matrix() : m_count(0), m_rows(0), m_cols(0), m_data(nullptr) { }

Matrix::Matrix(const double s) : m_rows(1), m_cols(1), m_count(1)
{
	allocate(s);
}

Matrix::Matrix(const int rows, const int cols, double initVal) :
	m_rows(rows),
	m_cols(cols),
	m_count(rows* cols)
{
	allocate(initVal);
}

Matrix::Matrix(const Matrix& b) : m_rows(b.m_rows), m_cols(b.m_cols), m_count(b.m_count)
{
	allocate();
	for (int i = 0; i < m_count; ++i) {
		m_data[i] = b.m_data[i];
	}
}

Matrix::~Matrix()
{
	deallocate();
}

double Matrix::magnitude() const
{
	// TODO: more clever way of doing this
	double mag = 0;
	for (int i = 0; i < m_cols; i++) {
		mag += m_data[i] * m_data[i];
	}
	return std::sqrt(mag);
}

double Matrix::det() const
{
#ifdef BOUNDS_CHECK
	if (m_rows != m_cols) {
		FATAL("Matrix must be square.", 2);
		return 0.0;
	}
#endif

	if (*this == identity()) {
		return 1.0;
	}

	if (m_rows == 1)
		return m_data[0];
	if (m_rows == 2)
		return m_data[0] * m_data[3] - m_data[1] * m_data[2];
	if (m_rows == 3) {
		return
			m_data[0] * m_data[4] * m_data[8] +
			m_data[1] * m_data[5] * m_data[6] +
			m_data[2] * m_data[3] * m_data[7] -
			m_data[2] * m_data[4] * m_data[6] -
			m_data[1] * m_data[3] * m_data[8] -
			m_data[0] * m_data[5] * m_data[7];
	}

	FATAL("Determinant for matrices larger than 3x3 is not supported yet.", 3);
}

Matrix Matrix::resize(int rows, int cols) const
{
#ifdef BOUNDS_CHECK
	if (rows * cols != m_count) {
		FATAL("Resize: Must have same count", -1);
	}
#endif

	Matrix res = *this;
	res.m_rows = rows;
	res.m_cols = cols;
	return res;
}

Matrix Matrix::inverse() const
{
#ifdef BOUNDS_CHECK
	if (m_rows != m_cols) {
		FATAL("Inverse: Matrix must be square.", 4);
	}
#endif

	if (m_rows == 1) {
		return Matrix(1.0 / m_data[0]);
	}

	FATAL("Haven't finished writing inverse yet :(", 69);
	
	Matrix L;
	Matrix U;
	LUdecomp(L, U);

	// solve LU decomposed system
	return Matrix(69.0);
}

Matrix Matrix::transpose() const
{
	Matrix res(m_rows, m_cols);

	for (int i = 0; i < m_cols; i++) {
		for (int j = 0; j < m_rows; j++) {
			res(i, j) = m_data[j * m_cols + i];
		}
	}

	return res;
}

void Matrix::LUdecomp(Matrix& L, Matrix& U) const
{
#ifdef BOUNDS_CHECK
	if (m_rows != m_cols) {
		FATAL("LU Decompisition: Matrix must be square", -1);
	}
	else if (fabs(m_data[0]) < c::EPS) {
		FATAL("LU Decompisition: First element must not be zero.", -1);
	}
#endif

	const unsigned short N = m_rows;
	L = L.identity();
	U = *this;

	for (int r = 1; r < N; r++) {
		for (int c = 0; c < r; c++) {
			// only helpful for large, sparse matrices
			//if (fabs(U(r, c)) < c::EPS) {
			//	continue;
			//}

			double term = U(r, c) / U(c, c);

			// don't have row notation yet
			for (int i = 0; i < N; i++) {
				U(r, i) -= U(c, i) * term;
			}
			L(r, c) = term;
		}
	}
}

Matrix Matrix::solve(Matrix& b) const
{
#ifdef BOUNDS_CHECK
	if (m_rows != m_cols) {
		FATAL("Solve: Matrix must be square", -1);
	}
	else if (fabs(m_data[0]) < c::EPS) {
		FATAL("Solve: First element must not be zero.", -1);
	}
#endif

	const unsigned short N = m_rows;
	Matrix L = identity();
	Matrix U = *this;
	Matrix y = b;
	double term1;

	// for perf gains, we modify LUdecomp algo right here
	for (int r = 1; r < N; r++) {
		term1 = 0;
		for (int c = 0; c < r; c++) {
			// only helpful for large, sparse matrices
			//if (fabs(U(r, c)) < c::EPS) {
			//	continue;
			//}

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

	// solve U*x = y
	Matrix x(m_rows, 1);

	for (int r = N - 1; r >= 0; r--) {
		term1 = 0;
		for (int c = N - 1; c >= r; c--) {
			term1 += U(r, c) * x(c);
			//Debug("(" << r + 1 << "," << c + 1 << "): " << term);
		}
		x(r) = (y(r) - term1) / U(r, r);
	}

	return x;
}

Matrix Matrix::identity() const
{
#ifdef BOUNDS_CHECK
	if (m_rows != m_cols) {
		FATAL("Identity: Matrix must be square", -1);
	}
#endif

	Matrix res(m_rows, m_cols);

	for (int i = 0; i < m_rows; i++)
	{
		res.m_data[i * m_cols + i] = 1.0;
	}

	return res;
}

Matrix Matrix::zeros(int r, int c)
{
	if (c == -1) {
		c = r;
	}

	return Matrix(r, c);
}

Matrix Matrix::ones(int r, int c)
{
#ifdef BOUNDS_CHECK
	if (r < 0) {
		FATAL("ones: cannot have negative number of rows", -r);
	}
#endif

	if (c == -1) {
		c = r;
	}

	return Matrix(r, c, 1.0);
}

Matrix Matrix::random() const
{
	Matrix res(m_rows, m_cols);

	for (int i = 0; i < m_rows * m_cols; i++) {
		res.m_data[i] = (double)rand() / RAND_MAX;
	}

	return res;
}

Matrix Matrix::randi(const int max, bool pm) const
{
	Matrix res(m_rows, m_cols);
	if (pm) {
		for (int i = 0; i < m_rows * m_cols; i++) {
			res.m_data[i] = rand() % (2 * (max + 1)) - max;
		}
		return res;
	}

	for (int i = 0; i < m_rows * m_cols; i++) {
		res.m_data[i] = rand() % (max + 1);
	}
	return res;
}

Matrix Matrix::operator-() const
{
	Matrix res = *this;

	for (int i = 0; i < (int)m_count; i++)
	{
		res.m_data[i] *= -1.0;
	}

	return res;
}

Matrix Matrix::operator+(const Matrix& b) const
{
	// Compiler prevents incompatible sizes

	Matrix res = *this;

	for (int i = 0; i < (int)m_count; i++) {
		res.m_data[i] += b.m_data[i];
	}

	return res;
}

Matrix Matrix::operator-(const Matrix& b) const
{
	// Compiler prevents incompatible sizes

	Matrix res = *this;

	for (int i = 0; i < (int)m_count; ++i) {
		res.m_data[i] -= b.m_data[i];
	}

	return res;
}

Matrix Matrix::operator*(const Matrix& b) const
{
	// Compiler prevents incompatible sizes

	Matrix res(m_rows, m_cols);

	for (int i = 0; i < m_rows; ++i) {
		for (int j = 0; j < b.m_cols; ++j) {
			for (int k = 0; k < m_cols; ++k) {
				res(i, j) += m_data[i * m_cols + k] * b(k, j);
			}
		}
	}

	return res;
}

Matrix Matrix::operator%(const Matrix& b) const
{
	// Compiler prevents incompatible sizes

	Matrix res(m_rows, m_cols);

	for (int i = 0; i < m_rows * m_cols; ++i) {
		res.m_data[i] = m_data[i] * b.m_data[i];
	}

	return res;
}

Matrix Matrix::operator*(const double s) const
{
	Matrix res = *this;

	for (int i = 0; i < m_count; i++) {
		res.m_data[i] *= s;
	}

	return res;
}

Matrix Matrix::operator/(const double s) const
{
	// leave this check in. It could happen at any point.
	if (fabs(s) < c::EPS) {
		FATAL("Cannot divide matrix by zero.", 7);
	}

	return *this * (1.0 / s);
}

bool Matrix::operator==(const Matrix& b) const
{
#ifdef BOUNDS_CHECK
	if (m_rows != b.rows() || m_cols != b.cols()) {
		FATAL("Matrices have incompatible sizes for this operation.", 8);
	}
#endif

	for (int i = 0; i < m_count; i++)
	{
		if (fabs(m_data[i] - b.m_data[i]) > c::EPS)
			return false;
	}

	return true;
}

Matrix Matrix::operator=(const std::initializer_list<double>& list)
{
	// probably don't bound check this one
	if (m_count != 0 && list.size() != m_count) {
		FATAL("Initializer list is not the same size as matrix.", 9);
	}

	// if initializing a new, empty matrix, just make row vector
	if (m_count == 0) {
		m_rows = (int) list.size();
		m_cols = 1;
	}

	int i = 0;
	for (auto& el : list) {
		m_data[i++] = el;
	}

	return *this;
}

Matrix& Matrix::operator=(const Matrix& b)
{

	if (m_rows != b.m_rows || m_cols != b.m_cols) {
		if (m_rows != 0 || m_cols != 0) {
			FATAL("Assigning matrix of different size.", -1);
		}

		// let it slide of size zero, we're just initializing
		m_count = b.m_count;
		m_rows  = b.m_rows;
		m_cols  = b.m_cols;
		deallocate();
		allocate();
	}

	for (int i = 0; i < m_count; ++i) {
		m_data[i] = b.m_data[i];
	}
	return *this;
}

double Matrix::operator()(int elm) const
{
#ifdef BOUNDS_CHECK
	if (elm >= m_count || elm < 0) {
		FATAL("Accessing out of array bounds", 10);
	}
#endif

	return m_data[elm];
}

double& Matrix::operator()(int elm)
{
#ifdef BOUNDS_CHECK
	if (elm >= m_count || elm < 0) {
		FATAL("Accessing out of array bounds", 11);
	}
#endif

	return m_data[elm];
}

double Matrix::operator()(int row, int col) const
{
#ifdef BOUNDS_CHECK
	if (row >= m_rows || row < 0 || col >= m_cols || col < 0) {
		FATAL("Accessing out of array bounds", 12);
	}
#endif

	return m_data[row * m_cols + col];
}

double& Matrix::operator()(int row, int col)
{
#ifdef BOUNDS_CHECK
	if (row >= m_rows || row < 0 || col >= m_cols || col < 0) {
		FATAL("Accessing out of array bounds", 13);
	}
#endif

	return m_data[row * m_cols + col];
}

std::ostream& operator<<(std::ostream& os, const Matrix& mat)
{
	os << " =\n";

	if (mat.m_count == 0)
	{
		os << "[ ]";
		return os;
	}

	for (std::size_t i = 0; i < mat.m_rows; i++) {
		for (std::size_t j = 0; j < mat.m_cols; j++) {
			os <<
				std::setw(6) <<
				std::setprecision(4) <<
				mat((int)(i * mat.m_cols + j));

			if ((j + 1) != mat.m_cols) {
				os << ", ";
			}
		}
		os << "\n";
	}

	return os;
}

void Matrix::allocate(const double initVal)
{
	m_data = new double[m_count] { initVal };
}

void Matrix::deallocate()
{
	delete[] m_data;
	m_data = nullptr;
}
