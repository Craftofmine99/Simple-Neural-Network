#include "NeuralNetwork.h"

float*** getTableOf(int index)
{
	return members[index];
}

NeuralNetwork::NeuralNetwork()
{

}

NeuralNetwork::NeuralNetwork(int input,int* innerNodes,int output)
{
	numInput = input;
	numOutput = output;
	numEachLayer = innerNodes;
}

void NeuralNetwork::init(int numNetworks)
{
	members = new float*[numNetworks];
	for(int a = 0 ; a < numNetworks ; a++)
	{
		members[a] = new float*[numLayers + 1];
		for(int b = 0 ; b < numLayers + 1 ; b++)
		{
			if(b < numLayers)
				members[a][b] = new float*[numEachLayer[b]];
			else
				members[a][a] = new float*[numOutput];
			for(int c = 0 ; c < numEachLayer[b] ; c++)
			{
				if(b > 0)
				{
					members[a][b][c] = new float*[numInput];
				}
				else
				{
					members[a][b][c] = new float*[numEachLayer[b-1]];
				}
			}
		}
	}
}

float[] getOutputOfMember(int index,float* input)
{

}

void nextGen(bool* toNext)
{

}
