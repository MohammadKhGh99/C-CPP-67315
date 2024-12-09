//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Matrix.h"
#include "Digit.h"
#include "Dense.h"


#define MLP_SIZE 4

const MatrixDims imgDims = {28, 28};
const MatrixDims weightsDims[] = {{128, 784},
								  {64,  128},
								  {20,  64},
								  {10,  20}};
const MatrixDims biasDims[] = {{128, 1},
							   {64,  1},
							   {20,  1},
							   {10,  1}};

/**
 * @class this class represents the MlpNetwork.
 */
class MlpNetwork
{
private:
	Matrix _weights[MLP_SIZE], _biases[MLP_SIZE];
public:
	/**
 	 * this Constructor Constructs a Mlp Network with the given _weights and biases.
 	 * @param weights the _weights to construct the MlpNetwork with.
 	 * @param biases the biases to construct the MlpNetwork with.
 	 */
	MlpNetwork(Matrix weights[MLP_SIZE], Matrix biases[MLP_SIZE]);

	/**
	 * this function to overload the () operator for the MlpNetwork class, we give it a Matrix and it call for all the
	 * Denses that in the MlpNetwork with the given Matrix, and take the maximum probability from the resulted vector.
	 * @param m the Matrix to call the Denses with it.
	 * @return a Digit instance with the resulted value with the highest probability.
	 */
	Digit operator()(Matrix &m);
};

#endif // MLPNETWORK_H
