#include "Activation.h"

#define INVALID_ACT "Error: invalid Activation Type"

/**
 * this Constructor Constructs an Activation (Function) depending on the given _type of Activation.
 * @param actType the _type of the Activation that we want to init.
 */
Activation::Activation(ActivationType actType)
{
	this->_type = actType;
}

/**
 * this function returns the _type of the current Activation.
 * @return the _type of the current Activation function.
 */
ActivationType Activation::getActivationType() const
{
	return this->_type;
}

/**
 * this function to overload the () operator for the Activation class, we give it a Matrix and it call for the
 * appropriate Activation function on the given Matrix.
 * @param m the Matrix to call the Activation function with it.
 * @return A Matrix object that has been resulted from the call of the Activation function.
 */
Matrix Activation::operator()(const Matrix &m) const //todo
{
	Matrix temp(m.getRows(), m.getCols());
	if (this->_type == Relu)
	{
		for (int i = 0; i < m.getRows(); ++i)
		{
			for (int j = 0; j < m.getCols(); ++j)
			{
				temp(i, j) = _reluFunc(m(i, j));
			}
		}
		return temp;
	}
	else if (this->_type == Softmax)
	{
		return _softMaxFunc(m);
	}
	else
	{
		std::cerr << INVALID_ACT << std::endl;
		exit(EXIT_FAILURE);
	}
}