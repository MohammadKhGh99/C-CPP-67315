// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cstring>

/**
 * @struct MatrixDims
 * @brief Matrix dimensions container
 */
typedef struct MatrixDims
{
	int rows, cols;
} MatrixDims;

/**
 * @class this class represent a Matrix.
 */
class Matrix
{
private:
	MatrixDims _dims{};
	float *_matrix;
public:

	/**
	 * this Constructors Constructs Matrix with rows x cols dimensions and initializes all its elements to 0.
	 * @param rows the number of rows in the current _matrix.
	 * @param cols the number of columns in the current _matrix.
	 */
	Matrix(int rows, int cols);

	/**
	 * this Constructor Constructs 1x1 Matrix and initializes all its elements to 0.
	 */
	Matrix();

	/**
	 * this Constructor Constructs _matrix from another Matrix m.
	 * @param m the another _matrix to Construct a new _matrix from it.
	 */
	Matrix(const Matrix &m);

	/**
	 * Destructor to "destroy" everything in the current Matrix, freeing the memory of the allocated memory to this Matrix.
	 */
	~Matrix();

	/**
	 * this function returns the number of rows of the current Matrix.
	 * @return the number of rows of the current Matrix.
	 */
	int getRows() const;

	/**
	 * this function returns the number of the columns of the current Matrix.
	 * @return the number of the columns of the current Matrix.
	 */
	int getCols() const;

	/**
	 * this function make the current Matrix as one column vector.
	 * @return the vector that has been made of the current Matrix.
	 */
	Matrix &vectorize();

	/**
	 * this function prints the current Matrix's elements.
	 */
	void plainPrint() const;

	/**
	 * this function to overload the = operator for the Matrix class.
	 * @param other the other Matrix to assign to the current Matrix.
	 * @return the current Matrix after assignment.
	 */
	Matrix &operator=(const Matrix &other);

	/**
	 * this function to overload the * operator for Matrix class.
	 * @param m the Matrix to multiply with the current Matrix.
	 * @return A Matrix Object for the result of the multiplication.
	 */
	Matrix operator*(const Matrix &m) const;

	/**
	 * this function to overload the + operator for the Matrix class.
	 * @param m the Matrix to add to the current Matrix.
	 * @return a Matrix object that contains the adding result.
	 */
	Matrix operator+(const Matrix &m) const;

	/**
	 * this function to overload the += operator for the Matrix class.
	 * @param m the Matrix to add to the current Matrix.
	 * @return the current Matrix with the updated _matrix.
	 */
	Matrix &operator+=(const Matrix &m);

	/**
	 * this function to overload the () operator for the Matrix class, it takes two indexes and returns the element in
	 * the specified location in the current Matrix.
	 * @param row the row index.
	 * @param col the column index.
	 * @return the element (float) in the given indexes.
	 */
	float &operator()(int row, int col) const;

	/**
	 * this function to overload the [] operator for the Matrix class, it do the same as () operator but with just one
	 * index.
	 * @param coordinate the index to get the element in the given index.
	 * @return the element that's in the given index.
	 */
	float &operator[](int coordinate) const;

	/**
	 * this function to overload the >> operator for the Matrix class.
	 * @param is the input file stream.
	 * @param m the _matrix to fill its elements from the input file.
	 * @return an input file stream.
	 */
	friend std::istream &operator>>(std::istream &is, Matrix &m);

	/**
	 * this function to overload the << operator for the Matrix class.
	 * @param out the output stream.
	 * @param m the _matrix to export.
	 * @return an output stream.
	 */
	friend std::ostream &operator<<(std::ostream &out, const Matrix &m);

};

/**
 * this function to overload the * operator with the left hand side is a Matrix and the right hand side is a scalar.
 * @param m the Matrix to multiply.
 * @param c the scalar to multiply with.
 * @return a Matrix object that has been resulted from the multiplication.
 */
inline Matrix operator*(const Matrix &m, const float c)
{
	Matrix temp(m.getRows(), m.getCols());
	for (int i = 0; i < m.getRows(); ++i)
	{
		for (int j = 0; j < m.getCols(); ++j)
		{
			temp(i, j) = m(i, j) * c;
		}
	}
	return temp;
}

/**
 * this function to overload the * operator with the left hand side is a scalar and the right hand side is a Matrix.
 * @param c the scalar to multiply with.
 * @param m the Matrix to multiply.
 * @return a Matrix object that has been resulted from the multiplication.
 */
inline Matrix operator*(const float c, const Matrix &m)
{
	return m * c;
}


#endif //MATRIX_H
