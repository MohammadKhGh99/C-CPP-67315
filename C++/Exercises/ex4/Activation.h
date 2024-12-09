//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"
#include <cmath>

/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
	Relu,
	Softmax
};

/**
 * @class this class represents a Activation function.
 */
class Activation
{
private:
	ActivationType _type;

	/**
	 * this function do the work for the Relu Activation function.
	 * @param x the element from a Matrix to run the Relu function on it.
	 * @return x if x>=0, 0 otherwise.
	 */
	static float _reluFunc(const float x)
	{
		if (x >= 0.0f)
		{
			return x;
		}
		return 0;
	}

	/**
	 * this function normalizes the given vector to probabilities.
	 * @param vector the given vector to run the SoftMax Activation on it.
	 * @return a new vector with the normalized probabilities.
	 */
	static Matrix _softMaxFunc(const Matrix &vector)
	{
		Matrix temp(vector.getRows(), vector.getCols());
		float sum = 0.0f;
		for (int i = 0; i < vector.getRows(); ++i)
		{
			sum += (std::exp(vector[i]));
		}
		for (int j = 0; j < vector.getRows(); ++j)
		{
			temp[j] = (1.0f / sum) * (std::exp(vector[j]));
		}
		return temp;
	}

public:
	/**
	 * this Constructor Constructs an Activation (Function) depending on the given _type of Activation.
	 * @param actType the _type of the Activation that we want to init.
	 */
	explicit Activation(ActivationType actType);

	/**
	 * this function returns the _type of the current Activation.
	 * @return the _type of the current Activation function.
	 */
	ActivationType getActivationType() const;

	/**
	 * this function to overload the () operator for the Activation class, we give it a Matrix and it call for the
	 * appropriate Activation function on the given Matrix.
	 * @param m the Matrix to call the Activation function with it.
	 * @return A Matrix object that has been resulted from the call of the Activation function.
	 */
	Matrix operator()(const Matrix &m) const;
};

#endif //ACTIVATION_H
