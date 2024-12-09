

#ifndef EX4_DENSE_H
#define EX4_DENSE_H

#include "Matrix.h"
#include "Activation.h"

/**
 * @class this class represents the Dense.
 */
class Dense
{
protected:
	Matrix _weights, _bias;
	ActivationType _type;
public:
	/**
	 * this Constructor Constructs a Dense for the NetWork.
	 * @param w the weight for the current Dense.
	 * @param bias the _bias for the current Dense.
	 * @param type the _type of the Activation of the current Dense.
	 */
	Dense(Matrix &w, Matrix &bias, ActivationType type);

	/**
	 * this function returns the _weights of the current Dense.
	 * @return the _weights of the current Dense.
	 */
	Matrix getWeights() const;

	/**
	 * this function returns the _bias of the current Dense.
	 * @return the _bias of the current Dense.
	 */
	Matrix getBias() const;

	/**
	 * this function returns the Activation Function of the current Dense.
	 * @return the Activation Function of the current Dense.
	 */
	Activation getActivation() const;

	/**
	 * this function to overload the () operator for the Dense class, we give it a Matrix and it call for the Activation
	 * function for the current Dense with the given Matrix.
	 * @param m the given Matrix to call the Activation function with it.
	 * @return a Matrix object that has been resulted from the call of the Activation function.
	 */
	Matrix operator()(Matrix &m);
};

#endif //EX4_DENSE_H
