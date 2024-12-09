#include "Dense.h"

#define INVALID_ACT "Error: invalid Activation Type"

/**
 * this Constructor Constructs a Dense for the NetWork.
 * @param w the weight for the current Dense.
 * @param bias the _bias for the current Dense.
 * @param type the _type of the Activation of the current Dense.
 */
Dense::Dense(Matrix &w, Matrix &bias, ActivationType type)
{
	this->_weights = w;
	this->_bias = bias;
	this->_type = type;
}

/**
 * this function returns the _weights of the current Dense.
 * @return the _weights of the current Dense.
 */
Matrix Dense::getWeights() const
{
	return this->_weights;
}

/**
 * this function returns the _bias of the current Dense.
 * @return the _bias of the current Dense.
 */
Matrix Dense::getBias() const
{
	return this->_bias;
}

/**
 * this function returns the Activation Function of the current Dense.
 * @return the Activation Function of the current Dense.
 */
Activation Dense::getActivation() const
{
	if (this->_type == Relu)
	{
		return Activation(Relu);
	}
	else if (this->_type == Softmax)
	{
		return Activation(Softmax);
	}
	else
	{
		std::cerr << INVALID_ACT << std::endl;
		exit(EXIT_FAILURE);
	}
}

/**
 * this function to overload the () operator for the Dense class, we give it a Matrix and it call for the Activation
 * function for the current Dense with the given Matrix.
 * @param m the given Matrix to call the Activation function with it.
 * @return a Matrix object that has been resulted from the call of the Activation function.
 */
Matrix Dense::operator()(Matrix &m)
{
	Activation act = getActivation();
	Matrix temp = this->_weights * m;
	temp += this->_bias;
	return act(temp);
}
