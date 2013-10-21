#ifndef __BACKPROP__
#define __BACKPROP__

#include "neuralNetwork.h"

typedef struct {
	float **deltas; //Layer / Index of local deltas.
	float **deltaW; //Layer / Index of weight changes (for momentum)
	NeuralNetwork *net;
} BackProp;

BackProp *BPInit(NeuralNetwork *net);

void BPResetLocalDeltas(BackProp *bp);
void BPResetWeightDeltas(BackProp *bp);

void BPApply(BackProp *bp, float alpha, int epoch, float *desired);
void BPDelete(BackProp *bp);
// void BackPropagate(NeuralNetwork *net, int epoch, float *desired);

#endif 