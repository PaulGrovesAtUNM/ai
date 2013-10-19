// Back Propagation Algorithm
#include <malloc.h>

#include "neuralNetwork.h"
#include "backPropagation.h"


BackProp *BPInit(NeuralNetwork *net)
{
	// Create the bp structure based on the *net passed.
	BackProp *bp;
	int i;
	
	bp = (BackProp *)malloc(sizeof(BackProp));	
	bp->deltas = (float **)malloc(sizeof(float *) * net->count);
	
	for (i = 0; i < net->count; i++)	
		bp->deltas[i] = (float *)malloc(sizeof(float) * net->Layers[i]->count);
	bp->net = net;	
	
	BPReset(bp);
	
	return bp;
}

void BPReset(BackProp *bp)
{
	int i,j;
	
	for (i = 0; i < bp->net->count; i++)
		for (j = 0; j < bp->net->Layers[i]->count; j++)
			bp->deltas[i][j] = 0;
}

void BPDelete(BackProp *bp)
{
	int i;
	for (i = 0; i < bp->net->count; i++)
		free(bp->deltas[i]);
	free(bp);
}

void BPApply(BackProp *bp, float alpha, float *desired)
{		
	NeuralNetwork *net = bp->net;
	// Start with the output layer.
	//  And calculate it's error.
	Neuron *n;  //Current Neuron
	Neuron *in; //Input Neuron
	float *w; //Weights array for current neuron
	int li, ni, ini, ili, ii; //Layer index, Neuron Index, Input Neuron Index, input layer index, input index loop
		
	BPReset(bp);
	
	// Initilize the last layer.
	li = net->count - 2; //Output layer = count - 1, last non-simple neurons = count - 2
	for (ni = 0; ni < NNGetNeuronCount(net, li); ni++)
		bp->deltas[li][ni] = desired[ni] - NNGetOutput(net, li + 1, ni);
		
	for (li = net->count - 2; li > 0; li--) //Skip input & output layers
	{		
		// Calculate our current neuron's delta:
		//  delta = phi' * incoming deltas
		for (ni = 0; ni < NNGetNeuronCount(net, li); ni++)
		{			
			n = NNGetNeuron(net, li, ni);
			w = GetInputWeights(n);
			bp->deltas[li][ni] *= GetDeltaPhi(n); //Set our local delta
			
			for (ii = 0; ii < GetInputNeuronCount( n ); ii++)
			{				
				in = GetInputNeuron(n, ii);
				ili = GetLayerIndex(in); //Gets the layer index in our neural net
				ini = GetNeuronIndex(in); //Gets the index in our neural net.
				
				// Prop the local error to our input neuron
				bp->deltas[ili][ini] += w[ii] * bp->deltas[li][ni];
				// Adjust our weight --Wnew = Eta * local delta * input + momentum
				w[ii] += GetEta(n) * bp->deltas[li][ni] * GetOutput(in) + (alpha * w[ii]); //W = delt * out + momentum				
			}
		}
	}		
}