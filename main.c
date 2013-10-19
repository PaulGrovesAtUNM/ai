#include <stdio.h>


#include "neuralNetwork.h"
#include "backPropagation.h"

void testNN(NeuralNetwork *myNN)
{
	float dataSet[4][3] = {{-.5,-.5,.1},{-.5,.5,.9},{.5,-.5,.9},{.5,.5,.1}}; //In, In, Out
	int x1, x2;
	float o;
	float output;	
	int i,j;
	
	BackProp *bp = BPInit(myNN);
	
	printf("Testing...\n");
	for (j = 0; j < 1000; j++ )
		for (i = 0; i < 1000; i++)
		{
			x1 = rand() % 2;
			x2 = rand() % 2;
			o = (float)(x1 ^ x2);	
					
			NNSetInput(myNN, 0, x1);
			NNSetInput(myNN, 1, x2);
			NNForwardPropagation(myNN);
			NNGetOutputs(myNN, &output);
			
			BPApply(bp, 0, &o);
			
			printf("%i: %i xor %i = %f[%f]\n", j, x1, x2, output, o);
		}
	printf("Testing Done!\n");
	NNPrint(myNN);	
	
	BPDelete(bp);
}
	
	

int main(int argc, char **argv)
{
	// We need simple neurons for both the input and output layers.
	//  They are not "true" neurons, but they simplify some of the coding.
	int layerArray[] = {3, 2, 1, 1}; //2 inputs, 2 lms Perceptrons, 1 lms percep. 1 output, all with shared bias.
	// Maybe "hide" the Simple neurons in NN?
	float desired = .5;
	
	NeuralNetwork *myNN = CreateNN(layerArray, 4);
	NNCreateSimpleInputLayer(myNN);
	NNCreateSimpleOutputLayer(myNN);
	
	// Add our layer 1 & 2 LMS's...
	NNCreateNeuronInLayer(myNN, "Hidden 1.1", 1, LMSPERCEPTRON);
	NNCreateNeuronInLayer(myNN, "Hidden 1.2", 1, LMSPERCEPTRON);
	NNCreateNeuronInLayer(myNN, "Hidden 2.1", 2, LMSPERCEPTRON);
	
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
	
	// Wire the bias(s)
	NNLink(myNN, 0,2, 1, 0);
	NNLink(myNN, 0,2, 1, 1);
	NNLink(myNN, 0,2, 2, 0);
	NNSetInput(myNN, 2, 1); //Hardware to 1, bias.

	/* // From Paper
	NNSetInput(myNN,0, .35);
	NNSetInput(myNN,1, .9);
	NNSetWeight(myNN, 1,0, 0, .1);
	NNSetWeight(myNN, 1,0, 1, .8);
	NNSetWeight(myNN, 1,1, 0, .4);
	NNSetWeight(myNN, 1,1, 1, .6);
	NNSetWeight(myNN, 2,0, 0, .3);
	NNSetWeight(myNN, 2,0, 1, .9);	
	
	NNForwardPropagation(myNN);
	// Check the output.
	NNPrint(myNN);
	
	// Back Propagate
	printf("Propagating...\n\r\n\r");
	BackProp *bp = BPInit(myNN);
	BPApply(bp, 0, &desired);
	NNPrint(myNN);
	getchar(); */
	
	
	
	printf("Links created!\n");		
	
	// Set the desired outputs.
	// Exclusive Or:
	// 0 xor 0 = 0
	// 0 xor 1 = 1
	// 1 xor 0 = 1
	// 1 xor 1 = 0
	
	testNN(myNN);
	NNPrint(myNN);
		
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
	getchar();
	return 0;
}
