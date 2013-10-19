#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "neuron.h"
#include "simpleNeuron.h"
#include "perceptron.h"
#include "lmsPerceptron.h"

Neuron *NewNeuron(NEURONS neuronType, char *name)
{
	// Create the base data
	Neuron *n = (Neuron *)malloc(sizeof(Neuron)); //We don't hold neurons, just pointers to them.
	n->addInput = NULL;
	n->create = NULL;
	n->data = NULL;
	n->destroy = NULL;
	n->forwardProp = NULL;
	
	n->backPropagate = NULL;
	// n->accInputDeltas = NULL;
	
	n->getLocalActivation = NULL;
	n->getOutput = NULL;		
	n->inputNeurons = NULL;
	n->weights = NULL;	
	n->nInputs = 0;
	n->deltaSum = 0;
	n->eta = .0001;
	n->v = 0;
	n->y = 0;
	
	n->type = neuronType;	
	n->layer = -1;
	n->index = -1;
	strcpy(n->name, name);	
	
	switch (neuronType)
	{
		case SIMPLE :
			return SimpleNeuron_create(n);
		case PERCEPTRON :				
			return PerceptronCreate(n);	
		break;
		case LMSPERCEPTRON :
			return lmsPerceptronCreate(n);
		break;
	}
	return 0;
}

void DeleteNeuron(Neuron *current)
{
	if ( current->destroy )
		current->destroy(current);
	free( current->weights );
	free( current->inputNeurons );
	free( current );
}

void ForwardPropogate(Neuron *current)
{
	current->deltaSum = 0; //Clear our delta sum for backprop.
	
	if ( current->forwardProp )
		current->forwardProp(current);
}

float GetLocalActivation(Neuron *current)
{
	if ( current->getLocalActivation )
		return current->getLocalActivation(current);		
	return current->v;
}

float GetOutput(Neuron *current)
{
	if (current->getOutput)
		return current->getOutput(current);
	return current->y;
}

Neuron *GetInputNeuron(Neuron *current, int iIndex)
{
	if (iIndex >= current->nInputs)
	{
		printf("Index out of range in GetInputNeuron.\n");
		assert(1==0);
	}
	return current->inputNeurons[iIndex];		
}

Neuron **GetInputNeurons(Neuron *n)
{
	return n->inputNeurons;
}

int GetInputNeuronCount(Neuron *n)
{
	return n->nInputs;
}

float *GetInputWeights(Neuron *n)
{
	return n->weights;
}

// For over-rides that want to call parent...
void _addInput(Neuron *n, Neuron *nodeToAdd)
{
	n->inputNeurons = (Neuron **)realloc( n->inputNeurons, sizeof(Neuron *) * (n->nInputs + 1));
	n->weights = (float *)realloc( n->weights, sizeof(float) * (n->nInputs + 1));	
	n->inputNeurons[n->nInputs] = nodeToAdd;
	n->weights[n->nInputs] = 1; //Init weight to 1.
	n->nInputs++;	
}

void AddInput(Neuron *current, Neuron *nodeToAdd)
{
	if ( current->addInput )
		current->addInput(current, nodeToAdd);
	else	
		_addInput(current, nodeToAdd);	
	
	// Call any "child" methods as well.
}

/*
// Back Propagation
//  If we are an output node:
	//  newWi = oldWi + eta * localDelta * yi
	//  localDelta = phiPrime(v) * (desired - output)
	//  e = di - yi
void BackPropagate(Neuron *n)
{	
	if ( n->backPropagate )	
		return n->backPropagate(n);
		
	float localDelta;	
	float wn;
	int i;
		
	// First update all neurons we're using as an input.
	//  The accumulated sum represents the sum of delta's of all 
	//   the higher layer neurons using our ouput.
	//  Our Delta is phiPrime * this sum * the weight associated with an input.
	//
	localDelta = n->phiPrime * n->deltaSum;
	
	printf("BackProp ld:%f\n", localDelta);
		
	// Send out delta to our inputs and adjust our weights
	for (i = 0; i < n->nInputs; i++)
	{
		wn = n->weights[i];
		BackPropagateDelta(n->inputNeurons[i], localDelta * wn);		
		n->weights[i] += wn;
		printf("	Weight: %f\n",n->weights[i]);
	}
}

void BackPropagateDelta(Neuron *n, float delta)
{
	printf("BackPropDelta\n");
	if (n->accInputDeltas)
		n->accInputDeltas(n, delta);
	else
	{
		printf("BackProp ACC: %f\n", delta);	
		n->deltaSum += delta;				
	}
}
*/
float GetDeltaPhi(Neuron *n)
{
	return n->phiPrime;
}

void SetEta(Neuron *n, float eta)
{
	n->eta = eta;
}

float GetEta(Neuron *n)
{
	return n->eta;
}

int GetLayerIndex(Neuron *n)
{
	return n->layer;
}

int GetNeuronIndex(Neuron *n)
{
	return n->index;
}

void SetWeight(Neuron *n, int inputIndex, float w)
{
	n->weights[inputIndex] = w;
}

float GetWeight(Neuron *n, int inputIndex)
{
	return n->weights[inputIndex];
}

void PrintNeuron(Neuron *n)
{
	int i;
	
	printf("Neuron Name: %s [%f]", n->name, n->y);
	printf("	Weights:");
	for (i = 0; i < n->nInputs; i++)
		printf("%f,", n->weights[i]);
	printf("\n	Inputs From:");
	for (i = 0; i < n->nInputs; i++)
		printf("%s,", n->inputNeurons[i]->name);
	printf("\n");
}
