#ifndef __NEURAL_NETWORK_H__
#define __NEURAL_NETWORK_H__

#include "neuron.h"

typedef struct {
	Neuron **Neurons; //An array of pointers to Neurons
	int count;
} Layer;

struct NN {
	Layer **Layers; //An array of pointers to Neuron Layers	
	int count;	
};	

typedef struct NN NeuralNetwork;

NeuralNetwork *CreateNN(int layerCounts[], int nLayers);
void DeleteNN(NeuralNetwork *net);
Neuron *NNCreateNeuronInLayer(NeuralNetwork *net, int layer, NEURONS neuronType);
void NNSetInput(NeuralNetwork *net, int index, float x);

void NNGetOutputs(NeuralNetwork *net, float Buffer[]);
void NNCreateSimpleInputLayer(NeuralNetwork *net);
void NNLink(NeuralNetwork *net, int fromLayer, int fromIndex, int toLayer, int toIndex);

void NNForwardPropagation(NeuralNetwork *net);

void NNBackPropagation(NeuralNetwork *net);
void NNSetDesiredOutputs(NeuralNetwork *net, float desired[]); //Sets the desired outputs on the output layer.

#endif