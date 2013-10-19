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
Neuron *NNCreateNeuronInLayer(NeuralNetwork *net, char *name, int layer, NEURONS neuronType);
void NNSetInput(NeuralNetwork *net, int index, float x);

void NNGetOutputs(NeuralNetwork *net, float Buffer[]);
float NNGetOutput(NeuralNetwork *net, int layerIndex, int nodeIndex);
void NNCreateSimpleInputLayer(NeuralNetwork *net);
void NNCreateSimpleOutputLayer(NeuralNetwork *net);
void NNLink(NeuralNetwork *net, int fromLayer, int fromIndex, int toLayer, int toIndex);

void NNForwardPropagation(NeuralNetwork *net);

Neuron *NNGetNeuron(NeuralNetwork *net, int layerIndex, int nodeIndex);
int NNGetLayerCount(NeuralNetwork *net);
int NNGetNeuronCount(NeuralNetwork *net, int layerIndex);

void NNSetWeight(NeuralNetwork *net, int layer, int node, int inputIndex, float w);
float NNGetWeight(NeuralNetwork *net, int layer, int node, int inputIndex);

void NNPrint(NeuralNetwork *net);

#endif