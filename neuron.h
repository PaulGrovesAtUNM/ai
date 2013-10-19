#ifndef __NEURON_H__
#define __NEURON_H__

typedef enum {SIMPLE,PERCEPTRON, LMSPERCEPTRON} NEURONS;

struct _Neuron
{
	// Over-ridable methods
	struct _Neuron *(*create)();

	void (*forwardProp)(struct _Neuron *current);
	float (*getLocalActivation)(struct _Neuron *current);
	float (*getOutput)(struct _Neuron *current);	

	void (*destroy)(struct _Neuron *current);

	void (*addInput)(struct _Neuron *current, struct _Neuron *node);
	
	// Over ridable methods for back propogation
	void (*backPropagate)(struct _Neuron *n);
	void (*accInputDeltas)(struct _Neuron *n, float delta);
	
	struct _Neuron **inputNeurons; // Array of Pointers to Neurons providing input.
	float *weights;					// One weight for each input;	
	int nInputs; // Number of inputs
	
	float v; //Local activation
	float y; // Output -- phi(v)
	
	
	// For Back Propagation	
	float deltaSum; //The sum of the delta's from neurons using my output.
	float eta; // Learning rate
	float phiPrime; // derivative of phi wrt v at v, computed at forward prop
	
	NEURONS type; //Type of neuron this is.
	int layer; //Layer and Index into the layer, this neuron's position.
	int index;
	char name[50];
	
	
	void *data; // Private data for Neuron
}; //Generic Neuron

typedef struct _Neuron Neuron;

Neuron *NewNeuron(NEURONS neuronType, char *name);
void DeleteNeuron(Neuron *current);

void ForwardPropogate(Neuron *current);

float GetLocalActivation(Neuron *current);
float GetOutput(Neuron *current);
Neuron *GetInputNeuron(Neuron *current, int iIndex);

void _addInput(Neuron *n, Neuron *nodeToAdd);
void AddInput(Neuron *current, Neuron *nodeToAdd);

void SetEta(Neuron *n, float eta);
float GetDeltaPhi(Neuron *n);

float *GetInputWeights(Neuron *n);
Neuron **GetInputNeurons(Neuron *n);
int GetInputNeuronCount(Neuron *n);

int GetLayerIndex(Neuron *n);
int GetNeuronIndex(Neuron *n);

void SetWeight(Neuron *n, int inputIndex, float w);
float GetWeight(Neuron *n, int inputIndex);

float GetEta(Neuron *n);

void PrintNeuron(Neuron *n);


#endif
