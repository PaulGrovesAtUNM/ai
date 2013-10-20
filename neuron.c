#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "neuron.h"
#include "simpleNeuron.h"
#include "perceptron.h"
#include "lmsPerceptron.h"

Neuron *NewNeuron(NEURONS neuronType, char *name)
{
	// Create the base data
	Neuron *n = (Neuron *)malloc(sizeof(Neuron)); //We don't hold neurons, just pointers to them.
	n->addInput = &NAddInput_base;
	n->saveNeuron = &NSave_base;
	n->create = NULL;
	n->data = NULL;
	n->destroy = NULL;
	n->forwardProp = NULL;
	n->getLocalActivation = NULL;
	n->getOutput = NULL;		
	n->inputNeurons = NULL;
	n->weights = NULL;	
	n->nInputs = 0;
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
void NAddInput_base(Neuron *n, Neuron *nodeToAdd)
{
	n->inputNeurons = (Neuron **)realloc( n->inputNeurons, sizeof(Neuron *) * (n->nInputs + 1));
	n->weights = (float *)realloc( n->weights, sizeof(float) * (n->nInputs + 1));	
	n->inputNeurons[n->nInputs] = nodeToAdd;
	n->weights[n->nInputs] = 1; //Init weight to 1.
	n->nInputs++;	
}

void NAddInput(Neuron *n, Neuron *nodeToAdd)
{
	n->addInput(n, nodeToAdd);		
}

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

char *GetName(Neuron *n)
{
	return n->name;
}

void NSave(Neuron *n, FILE *fp)
{
	n->saveNeuron(n, fp);
}

void NSave_base(Neuron *n, FILE *fp)
{
	int i;
	char *typeNames[] = {"SIMPLE", "PERCEPTRON", "LMS PERCEPTRON"}; //Human readable type names.
	
	if (n->type > 2)
	{
		perror("INVALID TYPE NAME IN NSAVE_BASE!\n");
		return;
	}
	
	fprintf(fp, "TYPE: %i	%s	NAME: %s\n", n->type, typeNames[n->type], n->name);		
	fprintf(fp, "	LOCATION: %i,%i	ETA: %f\n", n->layer, n->index, n->eta);	
	fprintf(fp, "	INPUTS: \n");
	for (i = 0; i < n->nInputs; i++)	
		fprintf(fp, "   		LOCATION: %i,%i		WEIGHT: %0.9f\n", GetLayerIndex(n->inputNeurons[i]), GetNeuronIndex(n->inputNeurons[i]), n->weights[i]);			
}
