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
	
	void *data; // Private data for Neuron
}; //Generic Neuron

typedef struct _Neuron Neuron;

Neuron *NewNeuron(NEURONS neuronType);
void DeleteNeuron(Neuron *current);

void ForwardPropogate(Neuron *current);

float GetLocalActivation(Neuron *current);
float GetOutput(Neuron *current);
Neuron *GetInputNeuron(Neuron *current, int iIndex);

void _addInput(Neuron *n, Neuron *nodeToAdd);
void AddInput(Neuron *current, Neuron *nodeToAdd);

void BackPropagateDelta(Neuron *n, float delta);
void SetEta(Neuron *n, float eta);

#endif
