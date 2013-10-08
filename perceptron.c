// Perceptron

#include <malloc.h>
#include <stdio.h>

#include "neuron.h"

/* typedef struct
{	
} PerceptronPD; */


float PerceptronPhi(float v);

void PforwardProp(Neuron *n)
{
	
	//Calculate output.
	int i = 0;
	float v = 0;
		
	n->v = 0; 	
	
	for (i = 0; i < n->nInputs; i++)
		v += n->weights[i] * n->inputNeurons[i]->getOutput(n->inputNeurons[i]);
		
	n->v = v;
	n->y = PerceptronPhi(n->v);
	n->phiPrime = 0; //?
		
	printf("Perceptron Forward Prop called...\n\r");
}

float PerceptronPhi(float v) // Acitivation function for the Perceptron.
{
	if (v >= 0)
		return 1;
	return -1;
}

void PerceptronDelete(Neuron *current)
{
	printf("Perceptron Delete...\n");
}
	
Neuron *PerceptronCreate(Neuron *n)
{
//	Neuron *percep = (Neuron *)malloc(sizeof(Neuron));

	n->create = &PerceptronCreate;
	n->forwardProp = &PforwardProp;
	
	//percep->getLocalActivation = &PgetLocalActivation;
	//percep->getOutput = &PgetActivation;
	//percep->destroy = &PerceptronDelete;
	//percep->addInput = &PaddInput;

	//percep->data = malloc(sizeof(PerceptronPD));
		 
	printf("Perceptron created...\n\r");

	return n;
}

#undef SETDATA



