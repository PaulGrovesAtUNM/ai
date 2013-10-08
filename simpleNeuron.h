#ifndef __INPUTNEURON_H__
#define __INPUTNEURON_H__


Neuron *InputNeuron_create();
Neuron *SimpleNeuron_create(Neuron *n);

// The following is part of InputNeuron
void SimpleNeuronSetInput(Neuron *n, float x1);
void SimpleNeuronSetDesired(Neuron *n, float d);

#endif
