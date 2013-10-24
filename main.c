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
			
	if (mode == 2) //Random
	{
		for (i = 0; i < 800; i++)
			si[i] = i;
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

NeuralNetwork *setupNN(int np1,int np2,float n1, float n2, float n3, int wt)
{
	NeuralNetwork *myNN;
	int li, ni, ii; //layer index, neuron index, input index
	int layers[6] = {2, 0, 0, 4, 4}; //We get 1 extra layer (simple), and a bias in the input.
	
	layers[1] = np1;
	if (np2 == 0)
	{
		layers[2] = 4;   // non-simple output		
		myNN = CreateNN(layers, 4);
	}
	else 
	{
		layers[2] = np2;
		myNN = CreateNN(layers, 5);
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
	
				
	NNSetLayerEta(myNN, 1, n1, 0);
	if ( np2 != 0 )
	{
		NNSetLayerEta(myNN, 2, n2, 0); 
		NNSetLayerEta(myNN, 3, n3, 0);
	}
	else
	{
		NNSetLayerEta(myNN, 2, n3, 0); 
	}
	
	
	return myNN;
}

float cycle(NeuralNetwork *myNN, struct _samp s, float *d)
{
	float outs[4]; //output buffer.
	int i;
	float errSqrd = 0;
			
	NNSetInput(myNN, 0, s.x1);
	NNSetInput(myNN, 1, s.x2);
	NNForwardPropagation(myNN);
	NNGetOutputs(myNN, outs);
		
	// printf("%i: %f[%f], %f[%f], %f[%f], %f[%f]\n", epoch + 1, outs[0], d[0], outs[1], d[1], outs[2], d[2], outs[3], d[3]);		
	for (i = 0; i < 4; i++)				
		errSqrd += (d[i] - outs[i]) * (d[i] - outs[i]);
	
	return errSqrd;
}

int validCode(float *actual, int *encoding)
{
	int j;
	
	for (j = 0; j < 4; j++)
	{
		if (actual[j] < 0)
			actual[j] = 0;
		else 
			actual[j] = 1;
		if (actual[j] != encoding[j])
			return 0; //False
	}
	// We have a valid encoding.
	return 1; //Proper
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


void testNN(FILE *tfp, struct _samp *trn, struct _samp *tst, int nodesPer1, int nodesPer2, float n1, float n2, float n3, int weightTypes, int sampMode)
{	
	FILE *fp;
	NeuralNetwork *myNN;
	BackProp *bp;
		
	int epoch = 0;
	
	float testRMS, trainRMS;
	int testErrs, trainErrs;
	float *d;
	
	int si[800]; 	
	
	int classEncode[][4] = {{99, 99, 99, 99}, {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}}; //Encoding for classes	
	float desired[][4] = {{99, 99, 99, 99}, {1.5, -1.5, -1.5, -1.5}, {-1.5, 1.5, -1.5, -1.5}, {-1.5, -1.5, 1.5, -1.5}, {-1.5, -1.5, -1.5, 1.5}}; //tanh range.
	float outs[4];
	
	char fname[50]; // = {"2x2_01_001_0001_W0_InOrder.txt", "2x2_01_001_0001_W1_InOrder.t
	
	char *sorders[3] = {"InOrder","RROrder","RandOrder"};
	char *wsel[3] = {"1",".1","rnd"};
	
	float runningAvg[50];	
	float avgErr = 10000;
	
	int i,j;
	int sindex;
	int c;
	
	sprintf(fname,"%ix%i_%f_%f_%f_W%s_%s.txt", nodesPer1, nodesPer2, n1, n2, n3, wsel[weightTypes], sorders[sampMode]);
	printf("Starting: %s\n",fname);
	fp = fopen(fname,"w");								
	
		
	myNN = setupNN(nodesPer1, nodesPer2, n1, n2, n3, weightTypes);
	bp = BPInit(myNN);
	
	
	initSampIndex(si, sampMode);
	
	// We are now set. 
	// Run until the rmsError < 2, or 500000 epoch.
	
	trainRMS = 1000;
	trainErrs = 1000; 
	while (epoch < 100000 && fabs(avgErr - trainRMS) > .0001)
	{
		testRMS = 0;
		trainRMS = 0;
		testErrs = 0;
		trainErrs = 0;
		if ( sampMode == 2)
			initSampIndex(si, sampMode);
		for (i = 0; i < 800; i++)
		{			
			sindex = si[i];
			c = trn[ sindex ].c;
			
			d = desired[ trn[ sindex ].c ];
			trainRMS += cycle(myNN, trn[ sindex ], d);			
			BPApply(bp, 0, epoch, d);
			NNGetOutputs(myNN, outs);
			if ( !validCode(outs, classEncode[ c ] ) )
				trainErrs++;							
		}
		
		for (i = 0; i < 800; i++)
		{
			sindex = si[i];
			c = tst[ sindex ].c;
			d = desired[ c ];					
			testRMS  += cycle(myNN, tst[ sindex ], d);
			NNGetOutputs(myNN, outs);
			if ( !validCode(outs, classEncode[ c ] ) )
				testErrs++;						
		}

		trainRMS = sqrt(trainRMS);
		testRMS = sqrt(testRMS);
		
		runningAvg[epoch % 50] = trainRMS;
		if (epoch > 2000 )
		{
			avgErr = 0;		
			for (i = 0; i < 50; i++)
				avgErr += runningAvg[i];
			avgErr = avgErr / 50.0;			
		}
				
		epoch++;
		fprintf(fp, "%i	%9.9f	%i	%9.9f	%i\n", epoch, trainRMS, trainErrs, testRMS, testErrs);
		if (epoch % 1000 == 0)
			printf("%i	%9.9f	%i	%9.9f	%i\n", epoch, trainRMS, trainErrs, testRMS, testErrs);
		//getchar();
	}		
	fprintf(tfp,"%i	%i	%f	%f	%f %s	%s	%f	%i	%f	%i\n", nodesPer1, nodesPer2, n1, n2, n3, wsel[weightTypes], sorders[sampMode], trainRMS, trainErrs, testRMS,testErrs);
	
	fclose(fp);
	DeleteNN(myNN);
	BPDelete(bp);
}

int main(int argc, char **argv)
{			
	
	struct _samp trn[800]; //training data
	struct _samp tst[800]; //testing data

	loadData("TrainingData.txt", trn);
	loadData("TestingData.txt", tst);

	FILE *fp = fopen("table.txt","w");
	fprintf(fp, "#h1	#h2	eta1	eta2	eta3	weights	selection	TrainRMS	TrainErrs	TestRMS	TestErrs\n");
	
	// Single Hidden, Vary # in Hidden	 3 times
	testNN(fp, trn, tst, 2,  0, .01,0,.001, 2, 2);	
	testNN(fp, trn, tst, 20, 0, .01,0,.001, 2, 2);
	testNN(fp, trn, tst, 50, 0, .01,0,.001, 2, 2);

	// Different weights
	testNN(fp, trn, tst,  2, 0, .01,0,.001, 0, 2);
	testNN(fp, trn, tst, 20, 0, .01,0,.001, 0, 2);
	testNN(fp, trn, tst, 50, 0, .01,0,.001, 0, 2);
	
	// Different weights
	testNN(fp, trn, tst, 2, 0,  .01,0,.001, 1, 2);
	testNN(fp, trn, tst, 20, 0, .01,0,.001, 1, 2);
	testNN(fp, trn, tst, 50, 0, .01,0,.001, 1, 2);
		
	// 2 Hidden Layers
// Single Hidden, Vary # in Hidden	 3 times
	testNN(fp, trn, tst, 2,  2, .01,.005,.001, 2, 2);	
	testNN(fp, trn, tst, 20, 5, .01,.005,.001, 2, 2);
	testNN(fp, trn, tst, 50, 10, .01,.005,.001, 2, 2);

	// Different weights
	testNN(fp, trn, tst,  2, 2, .01,.005,.001, 0, 2);
	testNN(fp, trn, tst, 20, 5, .01,.005,.001, 0, 2);
	testNN(fp, trn, tst, 50, 10, .01,.005,.001, 0, 2);
	
	// Different weights
	testNN(fp, trn, tst, 2,  2,  .01,.005,.001, 1, 2);
	testNN(fp, trn, tst, 20, 5, .01,.005,.001, 1, 2);
	testNN(fp, trn, tst, 50, 10, .01,.005,.001, 1, 2);
	
	// Pard d1
	// Different ordering
	// Single Hidden, Vary # in Hidden	 3 times
	testNN(fp, trn, tst, 2,  0, .01,0,.001, 2, 1);	
	testNN(fp, trn, tst, 20, 0, .01,0,.001, 2, 1);
	testNN(fp, trn, tst, 50, 0, .01,0,.001, 2, 1);

	// Different weights
	testNN(fp, trn, tst,  2, 0, .01,0,.001, 0, 1);
	testNN(fp, trn, tst, 20, 0, .01,0,.001, 0, 1);
	testNN(fp, trn, tst, 50, 0, .01,0,.001, 0, 1);
	
	// Different weights
	testNN(fp, trn, tst, 2, 0,  .01,0,.001, 1, 1);
	testNN(fp, trn, tst, 20, 0, .01,0,.001, 1, 1);
	testNN(fp, trn, tst, 50, 0, .01,0,.001, 1, 1);
		
	// 2 Hidden Layers
// Single Hidden, Vary # in Hidden	 3 times
	testNN(fp, trn, tst, 2,  2, .01,.005,.001, 2, 1);	
	testNN(fp, trn, tst, 20, 5, .01,.005,.001, 2, 1);
	testNN(fp, trn, tst, 50, 10, .01,.005,.001, 2, 1);

	// Different weights
	testNN(fp, trn, tst,  2, 2, .01,.005,.001, 0, 1);
	testNN(fp, trn, tst, 20, 5, .01,.005,.001, 0, 1);
	testNN(fp, trn, tst, 50, 10, .01,.005,.001, 0, 1);
	
	// Different weights
	testNN(fp, trn, tst, 2,  2,  .01,.005,.001, 1, 1);
	testNN(fp, trn, tst, 20, 5, .01,.005,.001, 1, 1);
	testNN(fp, trn, tst, 50, 10, .01,.005,.001, 1, 1);
	
	//Pard d2
	// Different ordering
	// Pard d1
	// Different ordering
	// Single Hidden, Vary # in Hidden	 3 times
	testNN(fp, trn, tst, 2,  0, .01,0,.001, 2, 0);	
	testNN(fp, trn, tst, 20, 0, .01,0,.001, 2, 0);
	testNN(fp, trn, tst, 50, 0, .01,0,.001, 2, 0);

	// Different weights
	testNN(fp, trn, tst,  2, 0, .01,.005,.001, 0, 0);
	testNN(fp, trn, tst, 20, 0, .01,.005,.001, 0, 0);
	testNN(fp, trn, tst, 50, 0, .01,.005,.001, 0, 0);
	
	// Different weights
	testNN(fp, trn, tst, 2, 0,  .01,.005,.001, 1, 0);
	testNN(fp, trn, tst, 20, 0, .01,.005,.001, 1, 0);
	testNN(fp, trn, tst, 50, 0, .01,.005,.001, 1, 0);
		
	// 2 Hidden Layers
// Single Hidden, Vary # in Hidden	 3 times
	testNN(fp, trn, tst, 2,  2, .01,.005,.001, 2, 0);	
	testNN(fp, trn, tst, 20, 5, .01,.005,.001, 2, 0);
	testNN(fp, trn, tst, 50, 10, .01,.005,.001, 2, 0);

	// Different weights
	testNN(fp, trn, tst,  2, 2, .01,.005,.001, 0, 0);
	testNN(fp, trn, tst, 20, 5, .01,.005,.001, 0, 0);
	testNN(fp, trn, tst, 50, 10, .01,.005,.001, 0, 0);
	
	// Different weights
	testNN(fp, trn, tst, 2,  2,  .01,.005,.001, 1, 0);
	testNN(fp, trn, tst, 20, 5, .01,.005,.001, 1, 0);
	testNN(fp, trn, tst, 50, 10, .01,.005,.001, 1, 0);
	

	fclose(fp);


	printf("All neurons deleted.\n");		
	getchar();
	return 0;
}
