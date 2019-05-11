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
	if(index < 0 || index > members.size())
		return vector<vector<vector<float>>>();
	else 
		return members[index];
}

NeuralNetwork::NeuralNetwork(int input,vector<int> innerNodes,int output)
{
	numInput = input;
	numOutput = output;
	numEachLayer = innerNodes;
	this->input = vector<float>();
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
	if(input.size() != numInput || index < 0 || index > numInput)
		return vector<float>();

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

vector<float> NeuralNetwork::getOutputOfMember(int index)
{
	return this->getOutputOfMember(index,this->input);
}

vector<vector<float>> NeuralNetwork::getAllOutputs(vector<float> input)
{
	if(input.size() != numInput)
		return vector<vector<float>>();

	vector<vector<float>> toReturn = vector<vector<float>>();
	toReturn.resize(members.size());

	for(int i = 0 ; i < members.size() ; i++)
		toReturn.emplace_back(this->getOutputOfMember(i,input));

	return toReturn;
}

vector<vector<float>> NeuralNetwork::getAllOutputs()
{
	return this->getAllOutputs(this->input);
}

void NeuralNetwork::clearInput()
{
	this->input.clear();
}

bool NeuralNetwork::setInput(vector<float> input)
{
	if(input.size() != numInput)
		return false;
	this->input = input;
	return true;
}

void NeuralNetwork::nextGen(bool* toNext)
{

}
