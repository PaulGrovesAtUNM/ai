#include <malloc.h>
#include "neuron.h"

/*typedef struct
{
	float X;	
} InputNeuronPD; */

struct SN_Private {
	float desired;
};

void SimpleNeuron_ForwardProp(Neuron *n)
{
	// Set the output to the input.
	// If we don't have any input neurons the just set it to v.
	if (n->nInputs == 0)
		n->y = n->v;	
	else
		n->y = GetOutput(n->inputNeurons[0]);			
}

void SimpleNeuron_BackProp(Neuron *n)
{
	// We back propagate our error.
	struct SN_Private *priv = (struct SN_Private *)n->data;
	
	// We only ever have a single input neuron.
	//  Our "local delta" is simply the error.	
	if (n->inputNeurons)
	{
		printf("SimpleNeuron: BackPropagating. desired: %f  Actual: %f\n", priv->desired, n->y);	
//		BackPropagateDelta(n->inputNeurons[0], priv->desired - n->y);
	}
}

void SimpleNeuron_addInput(Neuron *n, Neuron *node)
{
	if (n->inputNeurons) 
	{
		printf("SimpleNeuron_addInput warning: I already have an input! Ignoring...\n");	
		return; // We already have an input neuron...
	}
	
	_addInput(n, node);
}


// The following is part of InputNeuronl
void SimpleNeuronSetInput(Neuron *n, float x1)
{
	n->v = x1;
	// At this point perhaps begin our notifications?
}

// Set our desired output. Used for BackProp
void SimpleNeuronSetDesired(Neuron *n, float d)
{
	struct SN_Private *priv = (struct SN_Private *)n->data;
	
	priv->desired = d;
}

// Free our used memory.
void SimpleNeuron_destroy(Neuron *n)
{
	free(n->data);
}

Neuron *SimpleNeuron_create(Neuron *n)
{
	
	n->create = &SimpleNeuron_create;
	n->forwardProp = &SimpleNeuron_ForwardProp;
	n->backPropagate = &SimpleNeuron_BackProp;
	n->addInput = &SimpleNeuron_addInput;	
	n->destroy = &SimpleNeuron_destroy;
	n->data = malloc(sizeof(struct SN_Private));
	n->phiPrime = 1;
	return n;
}
