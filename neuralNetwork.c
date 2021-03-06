#include <malloc.h>

#include "neuralNetwork.h"
#include "simpleNeuron.h"

NeuralNetwork *CreateNN(int *layerCounts, int nLayers)
{
	// Initilize our Data Structure
	//  Steps:
	//   Create our NN strucuture
	//   Create an array of pLayers to hold nLayers.
	//   For each pLayer create an array of pNuerons to hold future pointers
	struct NN *net;
	int i,j;
	
	net = (struct NN *)malloc(sizeof( struct NN )); //Create NeurnalNet Struct
	net->Layers = (Layer **)malloc(sizeof(Layer *) * nLayers); //Array of pointers to Layers
	net->count = nLayers;	
		
	for (i = 0; i < nLayers; i++)	
	{
		//Create our layer structure:
		net->Layers[i] = (Layer *)malloc(sizeof(Layer));
		// In each layer create a pointer to an array of Neurons
		net->Layers[i]->Neurons = (Neuron **)malloc(sizeof(Neuron) * layerCounts[i] );
		// Null the array as a guard for later.
		for (j = 0; j < layerCounts[i]; j++) 
			net->Layers[i]->Neurons[j] = NULL; // Initilize pNeurons
		net->Layers[i]->count = layerCounts[i];
	}
	
	net->bias = NewNeuron(SIMPLE, "BIAS");
	NNSetBias(net, 1);
		
	//The caller is required to add the remaining layers.
	return net;
}

void DeleteNN(NeuralNetwork *net)
{		
	int li; //Layer index
	int ni; //Neuron index
	
	for (li = 0; li < net->count; li++)
	{
		for (ni = 0; ni < net->Layers[li]->count; ni++)
			if ( net->Layers[li]->Neurons[ni] ) // Guard against NULL
				DeleteNeuron(net->Layers[li]->Neurons[ni]); //Delete Neurons
		free( net->Layers[li]->Neurons ); //Delete Neuron Array
		free( net->Layers[li] ); // Delete Layer
	}
	
	DeleteNeuron(net->bias);
	free(net); // Delete Neural Network.			
}

Neuron *NNCreateNeuronInLayer(NeuralNetwork *net, char *name, int layer, NEURONS neuronType)
{
	int i;
	Neuron *newNeuron = NewNeuron(neuronType, name);
	
	if ( layer > net->count )
	{
		printf("Layer Index out of range.");
		return NULL;
	}
	
	// Find an emply place in our array.
	for (i = 0; i < net->Layers[layer]->count; i++)
	{
		if ( net->Layers[layer]->Neurons[i] == NULL )
		{
			net->Layers[layer]->Neurons[i] = newNeuron;
			newNeuron->layer = layer;
			newNeuron->index = i;
			return newNeuron;
		}	
	}
	
	// could not find an empty slot...
	printf("Warning: Layer %i full, unable to add a new Neuron.\n", layer);
	DeleteNeuron(newNeuron);
	return NULL;
}

void NNLinkBias(NeuralNetwork *net, int layer, int index)
{
	NAddInput(net->Layers[layer]->Neurons[index], net->bias);	
}

void NNLink(NeuralNetwork *net, int fromLayer, int fromIndex, int toLayer, int toIndex)
{
	NAddInput(net->Layers[toLayer]->Neurons[toIndex], net->Layers[fromLayer]->Neurons[fromIndex]);
}

void NNSetInput(NeuralNetwork *net, int index, float x)
{
	if (index >= net->Layers[0]->count )
	{
		printf("Index out of range in NNSetInput: %i\n", index);
		return;
	}
	
	Neuron *inpN = (Neuron *)net->Layers[0]->Neurons[index];	
	SimpleNeuronSetInput( inpN, x );
}

void NNSetBias(NeuralNetwork *net, float biasVal)
{
	SimpleNeuronSetInput(net->bias, biasVal);
	ForwardPropogate(net->bias); //Propagate 1 to the output.
}

void NNForwardPropagation(NeuralNetwork *net)
{
	// Begin with layer 0, calling all the layer's neurons to forwardPropogate.
	int li; //Layer Index
	int ni; //Neuron Index
	
	for (li = 0; li < net->count; li++)
		for (ni = 0; ni < net->Layers[li]->count; ni++)
			ForwardPropogate(net->Layers[li]->Neurons[ni]);
}

// Creates all the neurons on the input layer, simple neurons.
void NNCreateSimpleInputLayer(NeuralNetwork *net)
{
	int i;
	char name[50];
	Neuron *n;
	
	//add Neurons to our input layer, which is always just SIMPLE neurons
	for (i = 0; i < net->Layers[0]->count; i++)
	{
		sprintf(name, "X%i",i);	
		n = NewNeuron(SIMPLE, name);
		n->layer = 0;
		n->index = i;
		net->Layers[0]->Neurons[i] = n;		
	}
}

// Creates all the neurons on the last layer, Simple Neurons
void NNCreateSimpleOutputLayer(NeuralNetwork *net)
{
	int i;
	int lastI = net->count - 1;
	char name[50];
	Neuron *n;
	
	//add Neurons to our output layer, which is always just SIMPLE neurons
	for (i = 0; i < net->Layers[lastI]->count; i++)
	{
		sprintf(name, "Y%i",i);
		n = NewNeuron(SIMPLE, name);
		n->layer = lastI;
		n->index = i;
		net->Layers[lastI]->Neurons[i] = n;
	}
}

// Creates a fully connected neural network, with X0 as a bias (tied to every neuron on every layer)
void NNCreateFullyConnected(NeuralNetwork *net)
{
	Neuron *n;
	char name[50];
	int i,j, k, ol, li;
	
	NNCreateSimpleInputLayer(net);
	NNCreateSimpleOutputLayer(net);
	//Create all the in-between layers
	
	// This is the last non-simple layer.
	li = net->count - 2; //Our output layer (simple)
		
	// Create / link all neurons from layer 2 to our last hidden layer
	for (i = 1; i < li; i++)
	{
		for (j = 0; j < net->Layers[i]->count; j++)
		{
			sprintf(name, "H%i.%i", i,j);
			n = NewNeuron(LMSPERCEPTRON, name);
			n->layer = i;
			n->index = j;
			net->Layers[i]->Neurons[j] = n;
			
			//Link Bias
			NNLinkBias(net, i, j);
			// Link up every neuron in previous layer.
			for (k = 0; k < net->Layers[i - 1]->count; k++)
				NNLink(net, i - 1, k, i, j);
		}
	}
	
	// link our non-simple output layer to our simple output layer.
	for (i = 0; i < net->Layers[li]->count; i++)
	{
		sprintf(name, "OUT%i", i);
		n = NewNeuron(LMSPERCEPTRON, name);
		n->layer = li;
		n->index = i;
		net->Layers[li]->Neurons[i] = n;
		
		// Link in both the bias and our corresponding input.
		// Link in each layer 0. These are 1 to 1.
		NNLinkBias(net, li, i); // Bias
		NNLink(net, li, i, li + 1, i); //To our Simple Output Layer
		
		//Link each neuron in our last hidden layer to this one.
		for (k = 0; k < net->Layers[li - 1]->count; k++)
			NNLink(net, li - 1, k, li, i);
	}
}

Neuron *NNGetNeuron(NeuralNetwork *net, int layerIndex, int nodeIndex)
{
	return net->Layers[layerIndex]->Neurons[nodeIndex];
}

int NNGetLayerCount(NeuralNetwork *net)
{
	return net->count;
}

int NNGetNeuronCount(NeuralNetwork *net, int layerIndex)
{
	return net->Layers[layerIndex]->count;
}

int NNGetNeuronInputCount(NeuralNetwork *net, int layer, int node)
{
	return GetInputNeuronCount(net->Layers[layer]->Neurons[node]);
}

void NNGetOutputs(NeuralNetwork *net, float Buffer[])
{
	int ni; 
	int outi; //output layer index, the last layer.
	
	outi = net->count - 1;
	
	// The last layer is always the output layer.
	for (ni = 0; ni < net->Layers[outi]->count; ni++)
		Buffer[ni] = GetOutput(net->Layers[outi]->Neurons[ni]);		
}

float NNGetOutput(NeuralNetwork *net, int layerIndex, int nodeIndex)
{
	return GetOutput(net->Layers[layerIndex]->Neurons[nodeIndex]);
}

void NNSetWeight(NeuralNetwork *net, int layer, int node, int inputIndex, float w)
{
	SetWeight(net->Layers[layer]->Neurons[node], inputIndex, w);
}

float NNGetWeight(NeuralNetwork *net, int layer, int node, int inputIndex)
{
	return GetWeight(net->Layers[layer]->Neurons[node], inputIndex);
}

void NNPrint(NeuralNetwork *net)
{
	int li, ni;
	
	for (li = 0; li < net->count; li++)
	{
		printf("Layer %i:\n", li);
		for (ni = 0; ni < net->Layers[li]->count; ni++)
		{
			printf("	Node %i:\n", ni);
			PrintNeuron(net->Layers[li]->Neurons[ni]);			
		}
	}
}

void NNSetLayerEta(NeuralNetwork *net, int layerIndex, float eta0, float tao)
{
	int ni;
	
	for (ni = 0; ni < net->Layers[layerIndex]->count; ni++)	
		NSetEta(net->Layers[layerIndex]->Neurons[ni], eta0, tao);	
}

/* Saves the Neural Network to disk. */
void NNSave(NeuralNetwork *net, char *fname)
{
	//Things that need to be saved:
	//  Structure of the network -- Inputs Nodes, Hidden, Output Nodes
	//  The connections between nodes
	//  The weights
	//  The current inputs (Bias(s) are standard input nodes
	
	FILE *fp;
	int li, ni;
	
	if ( !(fp = fopen(fname, "w")) )
	{
		perror("Error opening file for saving!\n");
		return;		
	}
	
	// First let's save our structure.
	fprintf(fp, "LAYERS:%i\n", net->count);
	for (li = 0; li < net->count; li++)
	{
		fprintf(fp, "LAYER %i\n", li);
		for (ni = 0; ni < net->Layers[li]->count; ni++)
			NSave( net->Layers[li]->Neurons[ni], fp );
	}
	fclose(fp);	
}

