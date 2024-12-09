#include "Matrix.h"

#define MULT_ERROR "Error: the columns should be the same as the second rows"
#define ADD_ERROR "Error: both matrices should have the same size in adding"
#define READ_ERROR "Error: problem with reading the input file"
#define INVALID_INDEXES "Error: invalid indexes"
#define INVALID_DIMENSIONS "Error: invalid dimensions of Matrix"

/**
 * this Constructors Constructs Matrix with rows x cols dimensions and initializes all its elements to 0.
 * @param rows the number of rows in the current _matrix.
 * @param cols the number of columns in the current _matrix.
 */
Matrix::Matrix(int rows, int cols)
{
	if (rows <= 0 || cols <= 0)
	{
		std::cerr << INVALID_DIMENSIONS << std::endl;
		exit(EXIT_FAILURE);
	}
	_dims = {rows, cols};
	_matrix = new(std::nothrow)float[rows * cols];
	for (int i = 0; i < rows * cols; ++i)
	{
		(*this)[i] = 0;
	}
}

/**
 * this Constructor Constructs 1x1 Matrix and initializes all its elements to 0.
 */
Matrix::Matrix() : Matrix(1, 1)
{}

/**
 * this Constructor Constructs _matrix from another Matrix m.
 * @param m the another _matrix to Construct a new _matrix from it.
 */
Matrix::Matrix(const Matrix &m) :
		Matrix()
{
	this->operator=(m);
}

/**
 * Destructor to "destroy" everything in the current Matrix, freeing the memory of the allocated memory to this Matrix.
 */
Matrix::~Matrix()
{
	delete[] _matrix;
}

/**
 * this function returns the number of rows of the current Matrix.
 * @return the number of rows of the current Matrix.
 */
int Matrix::getRows() const
{
	return this->_dims.rows;
}

/**
 * this function returns the number of the columns of the current Matrix.
 * @return the number of the columns of the current Matrix.
 */
int Matrix::getCols() const
{
	return this->_dims.cols;
}

/**
 * this function make the current Matrix as one column vector.
 * @return the vector that has been made of the current Matrix.
 */
Matrix &Matrix::vectorize()
{
	this->_dims = {getRows() * getCols(), 1};
	return *this;
}

/**
 * this function prints the current Matrix's elements.
 */
void Matrix::plainPrint() const
{
	for (int i = 0; i < getRows(); ++i)
	{
		for (int j = 0; j < getCols(); ++j)
		{
			std::cout << (*this)(i, j) << " ";
		}
		std::cout << std::endl;
	}
}

/**
 * this function to overload the = operator for the Matrix class.
 * @param other the other Matrix to assign to the current Matrix.
 * @return the current Matrix after assignment.
 */
Matrix &Matrix::operator=(const Matrix &other)
{
	if (this == &other)
	{
		return *this;
	}
	delete[] this->_matrix;
	_dims = {other.getRows(), other.getCols()};
	_matrix = new(std::nothrow)float[getRows() * getCols()];
	for (int i = 0; i < other.getCols() * other.getRows(); ++i)
	{
		(*this)[i] = other[i];
	}
	return *this;
}

/**
 * this function to overload the * operator for Matrix class.
 * @param m the Matrix to multiply with the current Matrix.
 * @return A Matrix Object for the result of the multiplication.
 */
Matrix Matrix::operator*(const Matrix &m) const
{
	if (getCols() != m.getRows())
	{
		std::cerr << MULT_ERROR << std::endl;
		exit(EXIT_FAILURE);
	}
	Matrix temp(getRows(), m.getCols());
	for (int i = 0; i < getRows(); ++i)
	{
		for (int j = 0; j < m.getCols(); ++j)
		{
			for (int k = 0; k < getCols(); ++k)
			{
				temp(i, j) += (*this)(i, k) * m(k, j);
			}
		}
	}
	return temp;
}

/**
 * this function to overload the + operator for the Matrix class.
 * @param m the Matrix to add to the current Matrix.
 * @return a Matrix object that contains the adding result.
 */
Matrix Matrix::operator+(const Matrix &m) const
{
	if ((getCols() != m.getCols() && m.getCols() != 1) || getRows() != m.getRows())
	{
		std::cerr << ADD_ERROR << std::endl;
		exit(EXIT_FAILURE);
	}
	Matrix temp(getRows(), getCols());
	for (int i = 0; i < getRows(); ++i)
	{
		for (int j = 0; j < getCols(); ++j)
		{
			temp(i, j) = (*this)(i, j) + m(i, j);
		}
	}
	return temp;
}

/**
 * this function to overload the += operator for the Matrix class.
 * @param m the Matrix to add to the current Matrix.
 * @return the current Matrix with the updated _matrix.
 */
Matrix &Matrix::operator+=(const Matrix &m)
{
	if ((getCols() != m.getCols() && m.getCols() != 1) || getRows() != m.getRows())
	{
		std::cerr << ADD_ERROR << std::endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < getRows(); ++i)
	{
		for (int j = 0; j < getCols(); ++j)
		{
			(*this)(i, j) += m(i, j);
		}
	}
	return *this;
}

/**
 * this function to overload the () operator for the Matrix class, it takes two indexes and returns the element in
 * the specified location in the current Matrix.
 * @param row the row index.
 * @param col the column index.
 * @return the element (float) in the given indexes.
 */
float &Matrix::operator()(const int row, const int col) const
{
	if (row >= getRows() || row < 0 || col >= getCols() || col < 0)
	{
		std::cerr << INVALID_INDEXES << std::endl;
		exit(EXIT_FAILURE);
	}
	return _matrix[row * getCols() + col];
}

/**
 * this function to overload the [] operator for the Matrix class, it do the same as () operator but with just one
 * index.
 * @param coordinate the index to get the element in the given index.
 * @return the element that's in the given index.
 */
float &Matrix::operator[](const int coordinate) const
{
	if (coordinate < 0 || coordinate >= getRows() * getCols())
	{
		std::cerr << INVALID_INDEXES << std::endl;
		exit(EXIT_FAILURE);
	}
	return _matrix[coordinate];
}

/**
 * this function to overload the >> operator for the Matrix class.
 * @param is the input file stream.
 * @param m the _matrix to fill its elements from the input file.
 * @return an input file stream.
 */
std::istream &operator>>(std::istream &is, Matrix &m)
{
	if (is)
	{
		int i = 0;
		while (i < m.getRows() * m.getCols())
		{
			is.read((char *) &m[i], 4);
			if (!is.good() || is.eof())
			{
				std::cerr << READ_ERROR << std::endl;
				exit(EXIT_FAILURE);
			}
			i++;
		}
		return is;
	}
	else
	{
		std::cerr << READ_ERROR << std::endl;
		exit(EXIT_FAILURE);
	}
}

/**
 * this function to overload the << operator for the Matrix class.
 * @param out the output stream.
 * @param m the _matrix to export.
 * @return an output stream.
 */
std::ostream &operator<<(std::ostream &out, const Matrix &m)
{
	for (int i = 0; i <= m.getRows() - 1; ++i)
	{
		for (int j = 0; j <= m.getCols() - 1; ++j)
		{
			if (m(i, j) <= 0.1f)
			{
				out << "  ";
			}
			else
			{
				out << "**";
			}
		}
		out << std::endl;
	}
	return out;
}





