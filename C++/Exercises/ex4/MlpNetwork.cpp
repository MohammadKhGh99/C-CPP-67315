#include "MlpNetwork.h"

/**
 * this Constructor Constructs a Mlp Network with the given _weights and biases.
 * @param weights the _weights to construct the MlpNetwork with.
 * @param biases the biases to construct the MlpNetwork with.
 */
MlpNetwork::MlpNetwork(Matrix weights[MLP_SIZE], Matrix biases[MLP_SIZE])
{
	for (int i = 0; i < MLP_SIZE; ++i)
	{
		this->_weights[i] = weights[i];
		this->_biases[i] = biases[i];
	}
}

/**
 * this function to overload the () operator for the MlpNetwork class, we give it a Matrix and it call for all the
 * Denses that in the MlpNetwork with the given Matrix, and take the maximum probability from the resulted vector.
 * @param m the Matrix to call the Denses with it.
 * @return a Digit instance with the resulted value with the highest probability.
 */
Digit MlpNetwork::operator()(Matrix &m)
{
	Matrix temp = Dense(this->_weights[0], this->_biases[0], Relu)(m);
	for (int j = 1; j < MLP_SIZE; ++j)
	{
		if (j == MLP_SIZE - 1)
		{
			temp = Dense(this->_weights[j], this->_biases[j], Softmax)(temp);
		}
		else
		{
			temp = Dense(this->_weights[j], this->_biases[j], Relu)(temp);
		}
	}
	float max = temp[0];
	unsigned int maxIndex = 0;
	for (int i = 1; i < temp.getRows(); ++i)
	{
		if (temp[i] > max)
		{
			max = temp[i];
			maxIndex = i;
		}
	}
	return {maxIndex, max};
}