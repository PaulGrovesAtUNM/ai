#include <stdio.h>


#include "neuralNetwork.h"

void testNN(NeuralNetwork *myNN)
{
	float dataSet[4][3] = {{0,0,0},{0,1,1},{1,0,1},{1,1,0}}; //In, In, Out
	float output;	
	int i,j;
	
	printf("Testing...\n");
	for (j = 0; j < 100; j++ )
		for (i = 0; i < 4; i++)
		{
			NNSetDesiredOutputs(myNN, &dataSet[i][2]);
			NNForwardPropagation(myNN);
			NNGetOutputs(myNN, &output);
			printf("%i: %f xor %f = %f\n", j, dataSet[i][0], dataSet[i][1], output);
			NNBackPropagation(myNN);
		}
	printf("Done!\n");
	getchar();
}
	
	

int main(int argc, char **argv)
{
	// We need simple neurons for both the input and output layers.
	//  They are not "true" neurons, but they simplify some of the coding.
	int layerArray[] = {2, 2, 1, 1}; //2 inputs, 2 lms Perceptrons, 1 lms percep. 1 output.
	// Maybe "hide" the Simple neurons in NN?
	
	float output = -1000;
	
	NeuralNetwork *myNN = CreateNN(layerArray, 4);
	NNCreateSimpleInputLayer(myNN);
	NNCreateSimpleOutputLayer(myNN);
		
	
	// Add our layer 1 & 2 LMS's...
	NNCreateNeuronInLayer(myNN, 1, LMSPERCEPTRON);
	NNCreateNeuronInLayer(myNN, 1, LMSPERCEPTRON);
	NNCreateNeuronInLayer(myNN, 2, LMSPERCEPTRON);
	
	// Wire inputs to layer 1 neurons...
	// Wire 1st Input Neuron to Layer 1 Neurons
	NNLink(myNN,0,0,1,0); //FromLayer, fromIndex, toLayer, toIndex
	NNLink(myNN,0,0,1,1); //1st input wired to both layer 1 LMS neurons
	// Wire 2nd Input Neuron to Layer 1 Neurons
	NNLink(myNN,0,1,1,0); 
	NNLink(myNN,0,1,1,1); //2nd input wired to both layer 1 LMS neurons
	
	// Wire both Layer 1 Neurons to Layer 2 Neuron
	NNLink(myNN,1,0,2,0);
	NNLink(myNN,1,1,2,0); //Outpus of layer 1 wired to layer 2
	
	// Wire Layer 2 Neuron to Output Neuron
	NNLink(myNN,2,0,3,0); //Output of Layer 2 LMS wired to output Neuron
	// i1 --1 -- 
	//    X     > 3 -- o
	// i2 --2 -- 
	
	printf("Links created!\n");	
	getchar();
	
	// Set the desired outputs.
	// Exclusive Or:
	// 0 xor 0 = 0
	// 0 xor 1 = 1
	// 1 xor 0 = 1
	// 1 xor 1 = 0
	
	testNN(myNN);
	
		
	DeleteNN(myNN);
	
	//Neuron *myPerceptron = NewNeuron(PERCEPTRON);
	//Neuron *myInputNeuron = NewNeuron(INPUT);
	
	//float i;
	
	//i = GetLocalActivation(myPerceptron);
	
	// Add the output from our Input Neuron to our Perceptron.
	//AddInput(myPerceptron, myInputNeuron);
	
	//DeleteNeuron(myPerceptron);
	//DeleteNeuron(myInputNeuron);
	
	//ToDo:
	//  Move the code in the Perceptron that manages adding input into neuron.c. 
	//    The pointers and weights can be part of the Neuron structure so all
	//    neurons inherit them and they would all behave in the same manner.
	//  Thoughts:
	//   Overriding functions can be achieved in Neuron by having it assing 
	//    pointers to Neuron.c functions if any calls from the create functions
	//    leave pointers NULL.
	
	printf("All neurons deleted.\n");
	printf("hello world\n");
	
	getchar();
	return 0;
}
