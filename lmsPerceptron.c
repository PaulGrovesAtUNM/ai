// LMS Perceptron

#include <math.h>
#include <stdio.h>

#include "neuron.h"

float lmsPerceptronPhi(float v);
float lmsPercPhiPrime(float y);

void lmsPerceptronFP(Neuron *n)
{
	
	//Calculate output.
	int i = 0;
	float v = 0;
		
	n->v = 0; 	
	
	for (i = 0; i < n->nInputs; i++)
		v += n->weights[i] * GetOutput(n->inputNeurons[i]);
		
	n->v = v;
	n->y = lmsPerceptronPhi(n->v);
	n->phiPrime = lmsPercPhiPrime(n->y);
}

float lmsPerceptronPhi(float v) // Acitivation function for the Perceptron.
{	
	return 1.0/(1.0 + exp(-v)); //Sigmoid function
}

float lmsPercPhiPrime(float y)
{
	return y * (1.0 - y); // yay for simple!
}
	
Neuron *lmsPerceptronCreate(Neuron *n)
{
//	Neuron *percep = (Neuron *)malloc(sizeof(Neuron));

	n->create = &lmsPerceptronCreate;
	n->forwardProp = &lmsPerceptronFP;
	
	printf("LMS Perceptron created...\n\r");

	return n;
}



