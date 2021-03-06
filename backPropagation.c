// Back Propagation Algorithm
#include <malloc.h>

#include "neuralNetwork.h"
#include "backPropagation.h"

void BPPrintDeltas(BackProp *bp);

BackProp *BPInit(NeuralNetwork *net)
{
	// Create the bp structure based on the *net passed.
	BackProp *bp;
	int i;
	int ni, li;
	int numC = 0;
	int grr;
	
	bp = (BackProp *)malloc(sizeof(BackProp));	
	bp->deltas = (float **)malloc(sizeof(float *) * net->count);
	
	// There is one deltaW for each weight. There is a weight for each input.
	bp->deltaW = (float ***)malloc(sizeof(float *) * net->count);
	
	//The number of deltas we need is dependent on the connectivity.
	
	for (li = 0; li < net->count; li++)
	{
		bp->deltas[li] =  (float *)malloc(sizeof(float) * net->Layers[li]->count);
		bp->deltaW[li] = (float **)malloc(sizeof(float *) * net->Layers[li]->count);
		
		for (ni = 0; ni < NNGetNeuronCount(net, li); ni++)
		{
			numC = NNGetNeuronInputCount(net, li, ni);
			if (numC == 0)
				bp->deltaW[li][ni] = NULL;
			else
			{
				//bp->deltaW[li][ni] = (float *)malloc(sizeof(float) * numC);
				//for (grr = 0; grr < numC; grr++)
					//bp->deltaW[li][ni][grr] = (float)numC;
			}
		}
	}
	
	bp->net = net;	
	
	BPResetLocalDeltas(bp);
	//BPResetWeightDeltas(bp);
	
	//BPPrintDeltas(bp);
		
	return bp;
}

void BPResetLocalDeltas(BackProp *bp)
{
	int i,j;
	
	for (i = 0; i < bp->net->count; i++)
		for (j = 0; j < bp->net->Layers[i]->count; j++)		
			bp->deltas[i][j] = 0;
}

void BPResetWeightDeltas(BackProp *bp)
{
	int li,ni,ii;
	int ic;
	
	for (li = 0; li < bp->net->count; li++)
		for (ni = 0; ni < bp->net->Layers[li]->count; ni++)	
		{
			ic = NNGetNeuronInputCount(bp->net, li, ni);			
			for (ii = 0; ii < ic; ii++)
				bp->deltaW[li][ni][ii] = 0;
		}
}


void BPDelete(BackProp *bp)
{
	int i,j;
	for (i = 0; i < bp->net->count; i++)
	{
		free(bp->deltas[i]);
		//for (j = 0; j < bp->net->Layers[i]->count; j++)
		//	free(bp->deltaW[i][j]);
		//free(bp->deltaW[i]);
	}
	
	free( bp->deltas );
	//free( bp->deltaW );
	
	free(bp);
}

void BPPrintDeltas(BackProp *bp)
{
	int li, ni;
	
	printf("*** 		DELTAS		***\n");
	for (li = 0; li < bp->net->count; li++)
		for (ni = 0; ni < bp->net->Layers[li]->count; ni++)
			printf("[%i][%i] %f\n", li, ni, bp->deltas[li][ni]);		
	
}

// Used for debugging.
void ChangeDelta(BackProp *bp, int ni, int li, int layer, int node, float weight, float localDelta)
{
	//printf("[%i][%i]Back Prop to [%i][%i]: LD: %f	Weight: %f	Old Delta: %f	+: %f\n", li, ni, layer, node,localDelta, weight, bp->deltas[layer][node], weight * localDelta);
	BPPrintDeltas(bp);
	bp->deltas[layer][node] += weight * localDelta;
	BPPrintDeltas(bp);
}

void BPApply(BackProp *bp, float alpha,int epoch, float *desired)
{			
	NeuralNetwork *net = bp->net;
	// Start with the output layer.
	//  And calculate it's error.
	Neuron *n;  //Current Neuron
	Neuron *in; //Input Neuron
	float *w; //Weights array for current neuron
	float xi, localDelta; //An input value;
	int li, ni, ini, ili, ii; //Layer index, Neuron Index, Input Neuron Index, input layer index, input index loop
	float deltaW = 0;
		
	BPResetLocalDeltas(bp);
	
	// Initilize the last layer. This calculates the output error.
	li = net->count - 2; //Output layer = count - 1, last non-simple neurons = count - 2
	for (ni = 0; ni < NNGetNeuronCount(net, li); ni++)
	{		
		bp->deltas[li][ni] = desired[ni] - NNGetOutput(net, li, ni);
		// printf("Desired: %f		Output: %f		Error: %f\n", desired[ni], NNGetOutput(net, li+1, ni), outputError);
	}
		
	//printf("INITLIZED BP Delats\n");
	//BPPrintDeltas(bp);
	for (li = net->count - 2; li > 0; li--) //Skip input & output layers
	{		
		// Calculate our current neuron's delta:
		//  delta = phi' * sum(deltas from upstream neurons)
		for (ni = 0; ni < NNGetNeuronCount(net, li); ni++)
		{			
			n = NNGetNeuron(net, li, ni);
			w = GetInputWeights(n);
			bp->deltas[li][ni] *= GetDeltaPhi(n); //Set our local delta
			localDelta = bp->deltas[li][ni]; //Our local delta
			
			// Back prop our delta
			for (ii = 0; ii < GetInputNeuronCount( n ); ii++)
			{				
				in = GetInputNeuron(n, ii);
									
				xi = GetOutput(in);
				ili = GetLayerIndex(in); //Gets the layer index in our neural net
				ini = GetNeuronIndex(in); //Gets the index in our neural net.
				
				// Prop the local error to a input neuron ii 	
				//if (in != net->bias)
					//bp->deltas[ili][ini] += w[ii] * localDelta;				
								
				deltaW = NGetEta(n, epoch) * localDelta * xi;// + (alpha * bp->deltaW[li][ni][ii]); // Momentum: pg 170
				//bp->deltaW[li][ni][ii] = deltaW;
					
				// Adjust our intput weight --Wnew = Eta * local delta * input + momentum
				w[ii] += deltaW; //W = delt * out + momentum
				//printf("	[%i][%i] Weight %i Adjusted to %0.9f	LD: %f\n", n->layer, n->index, ii, w[ii], localDelta);
			}
		}
	}
	//printf("Resulting BP Deltas\n");
	//BPPrintDeltas(bp);
}