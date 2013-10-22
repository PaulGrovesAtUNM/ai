#include <math.h>
#include <stdlib.h>
#include <stdio.h>


#include "neuralNetwork.h"
#include "backPropagation.h"

struct _samp {
		int c; //class
		float x1;
		float x2;		
	};
	
void loadData(char *fname, struct _samp *buffer)
{
	int i;
	int n;
	FILE *fp = fopen(fname, "r");
	
	if (!fp)
		exit(-1);
		
	// class	index	x1	x2
	for (i = 0; i < 800; i++)
		fscanf(fp, "%i	%i	%f	%f", &(buffer[i].c), &n, &(buffer[i].x1), &(buffer[i].x2));
	

}

void initSampIndex(int *si, int mode)
{
	int i;
	int j,k,l;

	if (mode == 0)
	{	
		for (i = 0; i < 800; i++)
			si[i] = i;		
	}
		
	if (mode == 1) // Round Robin
	{
		for (i = 0; i < 200; i++)
		{
			si[4 * i] = i;
			si[4 * i + 1] = i + 200;
			si[4 * i + 2] = i + 400;
			si[4 * i + 3] = i + 600;
		}		
	}
			
	if (mode == 1) //Random
	{
		for (i = 0; i < 800; i++)
			si[i] = 8;
		// Now randomize it.
		for (i = 0; i < 4000; i++)
		{
			j = rand() % 800;
			k = rand() % 800;
			l = si[j];
			si[j] = si[k];
			si[k] = l; //Shuffle.
		}		
	}	
}

NeuralNetwork *setupNN(int np1,int np2,int wt,float eta0,float tau)
{
	NeuralNetwork *myNN;
	int li, ni, ii; //layer index, neuron index, input index
	int layers[6] = {2, 2, 0, 0, 4, 4}; //We get 2 extra layers (simple), and a bias in the input.
	
	if (np2 == 0)
	{
		layers[2] = np1; // hidden
		layers[3] = 4;   // non-simple output
		layers[4] = 4;  // simple output.
		
		myNN = CreateNN(layers, 5);		
	}
	else 
	{
		layers[2] = np1;
		layers[3] = np2;
		myNN = CreateNN(layers, 6);
	}
	
	NNCreateFullyConnected(myNN);
	
	for (li = 1; li < NNGetLayerCount(myNN) - 2; li++)
		for (ni = 0; ni < NNGetNeuronCount(myNN, li); ni++)
			for (ii = 0; ii < NNGetNeuronInputCount(myNN, li, ni); ii++)
			{
				if (wt == 0)
					NNSetWeight(myNN, li, ni, ii, 1);
				if (wt == 1) 
					NNSetWeight(myNN, li, ni, ii, .1);
				if (wt == 2)
					NNSetWeight(myNN, li, ni, ii, 1 - 2 * (rand() % 2) );// -1 to 1
			}
	
				
	NNSetLayerEta(myNN, 1, eta0, tau);
	NNSetLayerEta(myNN, 2, eta0, tau); //Won't hurt anything to set output layer.
	NNSetLayerEta(myNN, 3, eta0, tau);
	NNSetLayerEta(myNN, 4, eta0, tau);
	
	return myNN;
}

float cycle(NeuralNetwork *myNN, BackProp *bp, struct _samp s, float *d, float alpha,int epoch)
{
	float outs[4]; //output buffer.
	int i;
	float errSqrd = 0;
			
	NNSetInput(myNN, 0, s.x1);
	NNSetInput(myNN, 1, s.x2);
	NNForwardPropagation(myNN);
	NNGetOutputs(myNN, outs);
		
	printf("%i: %f[%f], %f[%f], %f[%f], %f[%f]\n", epoch + 1, outs[0], d[0], outs[1], d[1], outs[2], d[2], outs[3], d[3]);		
	for (i = 0; i < 4; i++)				
		errSqrd += (d[i] - outs[i]) * (d[i] - outs[i]);
	
	BPApply(bp, 0, epoch + 1, d);
	
	return errSqrd;
}

// Tests:
//  1 and 2 Hidden Layers							// 11
//  2, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50 Nodes  // 11
//  Weights: All 1's, All .1's, Randomized near 0.  // 3
//  Eta range from 0.0001 to 0.1 				    // 4
//  Tau range from 100000 to 100 				    // 4
//  alpha range from .0001 to .1 				    // 4
//  Randomized: None, Round Robin, Full Shuffle     // 3
//  									Total:12672 Runs
void testNN(FILE *fp, struct _samp *trn, struct _samp *tst, int nodesPer1, int nodesPer2, int weightTypes, float eta0, float tau, float alpha, int sampMode)
{	
	NeuralNetwork *myNN;
	BackProp *bp;
		
	int epoch = 0;
	
	float testRMS, trainRMS;
	int testErrs, trainErrs;
	
	int si[800]; 	
	
	int classEncode[][4] = {{99, 99, 99, 99}, {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}}; //Encoding for classes	
	float desired[][4] = {{99, 99, 99, 99}, {1.5, -1.5, -1.5, -1.5}, {-1.5, 1.5, -1.5, -1.5}, {-1.5, -1.5, 1.5, -1.5}, {-1.5, -1.5, -1.5, 1.5}}; //tanh range.
	
	int i;
		
	myNN = setupNN(nodesPer1, nodesPer2, weightTypes, eta0, tau);
	bp = BPInit(myNN);
	
	
	initSampIndex(si, sampMode);
	
	// We are now set. 
	// Run until the rmsError < 2, or 200000 epoch.
	
	trainRMS = 1000;
	while (epoch < 20000 && trainRMS > 2)
	{
		for (i = 0; i < 800; i++)
		{
			trainRMS += cycle(myNN, bp, tst[ si[i] ], desired[ tst[ si[i]].c ], alpha, epoch);
			testRMS  += cycle(myNN, bp, trn[ si[i] ], desired[ trn[ si[i]].c ], alpha, epoch);
		}
		trainRMS = sqrt(trainRMS);
		testRMS = sqrt(testRMS);
		epoch++;
		printf("%i:%f	%f\n", epoch, trainRMS, testRMS);
		
		if ( sampMode == 1)
			initSampIndex(si, sampMode);
	}		
}

int main(int argc, char **argv)
{		
	FILE *fp = NULL;
	
	struct _samp trn[800]; //training data
	struct _samp tst[800]; //testing data

	loadData("TrainingData.txt", trn);
	loadData("TestingData.txt", tst);
	
	testNN(fp, trn, tst, 5, 5, 0, .1, 100000, 0, 0);

	printf("All neurons deleted.\n");		
	getchar();
	return 0;
}
