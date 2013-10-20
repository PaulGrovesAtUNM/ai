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
	void (*addInput)(struct _Neuron *current, struct _Neuron *node);
	
	void (*saveNeuron)(struct _Neuron *n, FILE *fp);
	
	void (*destroy)(struct _Neuron *current);
	
	// Instance Data	
	struct _Neuron **inputNeurons; // Array of Pointers to Neurons providing input.
	float *weights;					// One weight for each input;	
	int nInputs; // Number of inputs
	
	float v; //Local activation
	float y; // Output -- phi(v)
	
	
	// For Back Propagation		
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

void NAddInput_base(Neuron *n, Neuron *nodeToAdd);
void NAddInput(Neuron *current, Neuron *nodeToAdd);

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
char *GetName(Neuron *n);

void NSave(Neuron *n, FILE *fp);
void NSave_base(Neuron *n, FILE *fp);


#endif
