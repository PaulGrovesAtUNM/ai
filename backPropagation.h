#ifndef __BACKPROP__
#define __BACKPROP__

#include "neuralNetwork.h"

typedef struct {
	float **deltas; //Layer / Index of deltas.	
	NeuralNetwork *net;
} BackProp;

BackProp *BPInit(NeuralNetwork *net);
void BPReset(BackProp *bp);
void BPApply(BackProp *bp, float alpha, float *desired);
void BPDelete(BackProp *bp);
void BackPropagate(NeuralNetwork *net, float *desired);

#endif 