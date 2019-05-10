#include "NeuralNetwork.h"
#include <array>
#include <math.h>
#include <random>

float sigmoid(float x)
{
	return ( 1.0f / (1.0f + exp(-x)));
}

vector<vector<vector<float>>> NeuralNetwork::getTableOf(int index)
{

}

NeuralNetwork::NeuralNetwork()
{

}

NeuralNetwork::NeuralNetwork(int input,vector<int> innerNodes,int output)
{
	numInput = input;
	numOutput = output;
	numEachLayer = innerNodes;
}

void NeuralNetwork::init(int numNetworks)
{
	members = vector<vector<vector<vector<float>>>>();
	members.reserve(numNetworks);
	for(int a = 0 ; a < numNetworks ; a++)
	{
		members.emplace_back(vector<vector<vector<float>>>());
		members[a].reserve(numLayers + 1);
		for(int b = 0 ; b < numLayers + 1 ; b++)
		{
			members[a].emplace_back(vector<vector<float>>());
			if(b < numLayers)
				members[a][b].reserve(numEachLayer[b]);
			else
				members[a][b].reserve(numOutput);
			for(int c = 0 ; c < numEachLayer[b] ; c++)
			{
				members[a][b].emplace_back(vector<float>());
				if(b == 0)
					members[a][b][c].reserve(numInput);
				else
					members[a][b][c].reserve(numEachLayer[b-1]);
			}
		}
	}
}

vector<float> NeuralNetwork::getOutputOfMember(int index,vector<float> input)
{
	vector<vector<vector<float>>> weights = members[index];
	vector<float> previous = input;
	vector<float> result;

	for(int a = 0 ; a < weights.size() ; a++)
	{
		result = vector<float>();
		result.reserve(weights[a].size());
		for(int b = 0 ; b < weights[a].size() ; b++)
		{
			float temp = 0.0f;
			for(int c = 0 ; c < weights[a][b].size() ; c++)
					temp += previous[c]*weights[a][b][c];
			result.emplace_back(sigmoid(temp));
		}
		previous = result;
	}
	return result;
}

void NeuralNetwork::nextGen(bool* toNext)
{

}
