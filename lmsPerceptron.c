// LMS Perceptron

#include <math.h>
#include <stdio.h>

#include "neuron.h"

float lmsPerceptronPhi(float v);

void lmsPerceptronFP(Neuron *n)
{
	
	//Calculate output.
	int i = 0;
	float v = 0;
		
	n->v = 0; 	
	
	for (i = 0; i < n->nInputs; i++)
		v += n->weights[i] * GetOutput(n->inputNeurons[i]);
		
	n->v = v;
	n->y = 1.7159 * tanh( .66666 * v ); // Haykin pg 181
	n->phiPrime = ( .66666 / 1.7159 ) * ( 1.7159 - n->y ) * ( 1.7159 + n->y ); // Haykin pg 169
}

float lmsPerceptronPhi(float v) // Acitivation function for the Perceptron.
{	
	return 1.7159 * tanh(.666666 * v); //Hyperbolic Tan, pg 181 Haykin
}
	
Neuron *lmsPerceptronCreate(Neuron *n)
{
//	Neuron *percep = (Neuron *)malloc(sizeof(Neuron));

	n->create = &lmsPerceptronCreate;
	n->forwardProp = &lmsPerceptronFP;
	
	printf("LMS Perceptron created...\n\r");

	return n;
}


