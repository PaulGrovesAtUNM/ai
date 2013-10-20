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

void SimpleNeuron_addInput(Neuron *n, Neuron *node)
{
	if (n->inputNeurons) 
	{
		printf("SimpleNeuron_addInput warning: I already have an input! Ignoring...\n");	
		return; // We already have an input neuron...
	}
	
	NAddInput_base(n, node);
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

void SimpleNeuron_save(Neuron *n, FILE *fp)
{
	//Simple Neurons are at the edge.
	//  Their input should be saved (in case we're a bias neuron)
	// Call our base save method first.
	NSave_base(n, fp);
	//Now save our input. We're the only one that does this.
	fprintf(fp, "		CURRENT INPUT VALUE: %0.9f\n", n->v); 
}

Neuron *SimpleNeuron_create(Neuron *n)
{
	
	n->create = &SimpleNeuron_create;
	n->forwardProp = &SimpleNeuron_ForwardProp;
	n->addInput = &SimpleNeuron_addInput;	
	n->destroy = &SimpleNeuron_destroy;
	n->saveNeuron = &SimpleNeuron_save;
	n->data = malloc(sizeof(struct SN_Private));
	n->phiPrime = 1;
	return n;
}