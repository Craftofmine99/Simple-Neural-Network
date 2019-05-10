#include "NeuralNetwork.h"
#include <array>

vector<vector<vector<float>>> NeuralNetwork::getTableOf(int index)
{

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
	members = vector<vector<vector<vector<float>>>>();
	members.reserve(numNetworks);
	for(int a = 0 ; a < numNetworks ; a++)
	{
		members.push_back(vector<vector<vector<float>>>());
		members.at(a).reserve(numLayers + 1);
		for(int b = 0 ; b < numLayers + 1 ; b++)
		{
			members.at(a).push_back(vector<vector<float>>());
			if(b < numLayers)
				members.at(a).at(b).reserve(numEachLayer[b]);
			else
				members.at(a).at(b).reserve(numOutput);
			for(int c = 0 ; c < numEachLayer[b] ; c++)
			{
				members.at(a).at(b).push_back(vector<float>());
				if(b > 0)
					members.at(a).at(b).at(c).reserve(numInput);
				else
					members.at(a).at(b).at(c).reserve(numEachLayer[b-1]);
			}
		}
	}
}

vector<float> NeuralNetwork::getOutputOfMember(int index,vector<float> input)
{
	vector<float> toReturn;
	vector<vector<vector<float>>> member = members.at(index);

	for(int a = 0 ; a < member.size() ; a++)
	{

	}

	return toReturn;
}

void NeuralNetwork::nextGen(bool* toNext)
{

}
