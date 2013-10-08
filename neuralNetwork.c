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
	free(net); // Delete Neural Network.			
}

Neuron *NNCreateNeuronInLayer(NeuralNetwork *net, int layer, NEURONS neuronType)
{
	int i;
	Neuron *newNeuron = NewNeuron(neuronType);
	
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
			return newNeuron;
		}	
	}
	
	// could not find an empty slot...
	printf("Warning: Layer %i full, unable to add a new Neuron.\n", layer);
	DeleteNeuron(newNeuron);
	return NULL;
}

void NNLink(NeuralNetwork *net, int fromLayer, int fromIndex, int toLayer, int toIndex)
{
	AddInput(net->Layers[toLayer]->Neurons[toIndex], net->Layers[fromLayer]->Neurons[fromIndex]);
}

void NNSetInput(NeuralNetwork *net, int index, float x)
{
	if (index >= net->Layers[0]->count )
	{
		printf("Index out of range in SetInput!\n");
		return;
	}
	
	Neuron *inpN = (Neuron *)net->Layers[0]->Neurons[index];	
	SimpleNeuronSetInput( inpN, x );
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

void NNBackPropagation(NeuralNetwork *net)
{
	// Start at the back, move to the front.
	int last = net->count - 1; //Last Layer
	int li = 0; // Layer Index
	int ni = 0; // Neuron Index
	
	for (li = net->count - 1; li > 0; li--) //Input layer doesn't really matter.
		for (ni = 0; ni < net->Layers[li]->count; ni++)
			BackPropagate(net->Layers[li]->Neurons[ni]);
}

// Creates all the neurons on the input layer, simple neurons.
void NNCreateSimpleInputLayer(NeuralNetwork *net)
{
	int i;
	//add Neurons to our input layer, which is always just SIMPLE neurons
	for (i = 0; i < net->Layers[0]->count; i++)
		net->Layers[0]->Neurons[i] = NewNeuron(SIMPLE);

}

// Creates all the neurons on the last layer, Simple Neurons
void NNCreateSimpleOutputLayer(NeuralNetwork *net)
{
	int i;
	int lastI = net->count - 1;
	//add Neurons to our output layer, which is always just SIMPLE neurons
	for (i = 0; i < net->Layers[lastI]->count; i++)
		net->Layers[lastI]->Neurons[i] = NewNeuron(SIMPLE);
}

// Sets the desired outputs at the output layer.
//  Note: This routine expects one entry PER OUTPUT NEURON
void NNSetDesiredOutputs(NeuralNetwork *net, float desired[])
{
	int ni; // Neuron index
	int ll = net->count - 1; //Last layer	
	
	// We can check to insure the final neuron is a Simle Neuron by testing the type...
	for (ni = 0; ni < net->Layers[ll]->count; ni++)
		SimpleNeuronSetDesired(net->Layers[ll]->Neurons[ni], desired[ni]);
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
