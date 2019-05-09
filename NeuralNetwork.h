#include <iostream>

class NeuralNetwork
{
private:
	int numInput, numOutput, numLayers;
	int* numEachLayer;
	float**** members;

public:
	float*** getTableOf(int index);

	NeuralNetwork();
	NeuralNetwork(int input,int* innerNodes,int output);

	void init(int numNetworks);
	float[] getOutputOfMember(int index,float* input);
	void nextGen(bool* toNext);
}
