#include "NeuralNetwork.h"
#include <array>
#include <math.h>
#include <random>
#include <ctime>
#include <string>

float sigmoid(float x)
{
	return (1.0f / (1.0f + exp(-x)));
}

vector<vector<vector<float>>> NeuralNetwork::getTableOf(int index)
{
	if (index < 0 || index > members.size())
		return vector<vector<vector<float>>>();
	else
		return members[index];
}

NeuralNetwork::NeuralNetwork(int input, vector<int> innerNodes, int output, bool constMembers)
{
	numInput = input;
	numOutput = output;
	numEachLayer = innerNodes;
	numGenerations = 0;
	this->input = vector<float>();
	this->constMembers = constMembers;

	random_device rd;
	mt19937 e2(rd());
	uniform_real_distribution<float> dist(0, 1);
}

void NeuralNetwork::init(int numNetworks)
{
	members = vector<vector<vector<vector<float>>>>();
	members.reserve(numNetworks);
	for (int a = 0; a < numNetworks; a++)
	{
		members.emplace_back(vector<vector<vector<float>>>());
		members[a].reserve(numLayers + 1);
		for (int b = 0; b < numLayers + 1; b++)
		{
			members[a].emplace_back(vector<vector<float>>());
			if (b < numLayers)
				members[a][b].reserve(numEachLayer[b]);
			else
				members[a][b].reserve(numOutput);
			for (int c = 0; c < numEachLayer[b]; c++)
			{
				members[a][b].emplace_back(vector<float>());
				if (b == 0)
					members[a][b][c].reserve(numInput);
				else
					members[a][b][c].reserve(numEachLayer[b - 1]);
				for (int d = 0; d < members[a][b][c].size(); d++)
					members[a][b][c][d] = dist(e2);
			}
		}
	}
}

vector<float> NeuralNetwork::getOutputOfMember(int index, vector<float> input)
{
	if (input.size() != numInput || index < 0 || index > numInput)
		return vector<float>();

	vector<vector<vector<float>>> weights = members[index];
	vector<float> previous = input;
	vector<float> result;

	for (int a = 0; a < weights.size(); a++)
	{
		result = vector<float>();
		result.reserve(weights[a].size());
		for (int b = 0; b < weights[a].size(); b++)
		{
			float temp = 0.0f;
			for (int c = 0; c < weights[a][b].size(); c++)
				temp += previous[c] * weights[a][b][c];
			result.emplace_back(sigmoid(temp));
		}
		previous = result;
	}
	return result;
}

vector<float> NeuralNetwork::getOutputOfMember(int index)
{
	return this->getOutputOfMember(index, this->input);
}

vector<vector<float>> NeuralNetwork::getAllOutputs(vector<float> input)
{
	if (input.size() != numInput)
		return vector<vector<float>>();

	vector<vector<float>> toReturn = vector<vector<float>>();
	toReturn.resize(members.size());

	for (int i = 0; i < members.size(); i++)
		toReturn.emplace_back(this->getOutputOfMember(i, input));

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
	if (input.size() != numInput)
		return false;
	this->input = input;
	return true;
}

// recommended to allow half or less to move on to next generation
void NeuralNetwork::nextGen(vector<bool> toNext)
{
	if (toNext.size() != members.size())
		return;

	int numToNext = 0;
	vector<int> indexes = vector<int>();
	indexes.reserve(members.size() / 2);
	for (int a = 0; a < members.size(); a++)
		if (!toNext[a])
			if (constMembers)
			{
				members.erase(members.begin() + a);
				a--;
			}
			else
				members[a] = vector<vector<vector<float>>>();
		else
		{
			numToNext++;
			indexes.emplace_back(a);
		}

	int current = 0;

	float genModifier = ((1.0f / exp(pow(numGenerations, 32))) + 0.01f);

	if (constMembers)
	{
		for (int a = 0; a < members.size(); a++)
		{
			if (members[a].empty())
			{
				members[a] = vector<vector<vector<float>>>(members[indexes[current++]]);
				if (current >= indexes.size())
					current = 0;

				for (int b = 0; b < members[a].size(); b++)
					for (int c = 0; c < members[a][b].size(); c++)
						for (int d = 0; d < members[a][b][c].size(); d++)
						{
							float temp = dist(e2);
							if (temp < 0.1f)
							{
								members[a][b][c][d] += dist(e2) * (genModifier);
							}
							else if (temp < 0.2f)
							{
								members[a][b][c][d] -= dist(e2) * (genModifier);
							}
						}
			}
		}
	}
	else
	{
		vector<vector<vector<vector<float>>>> newMembers = vector<vector<vector<vector<float>>>>(members);
		for (int a = 0; a < newMembers.size(); a++)
			for (int b = 0; b < newMembers[a].size(); b++)
				for (int c = 0; c < newMembers[a][b].size(); c++)
					for (int d = 0; d < newMembers[a][b][c].size(); d++)
					{
						float temp = dist(e2);
						if (temp < 0.1f)
							newMembers[a][b][c][d] += dist(e2) * (genModifier);
						else if (temp < 0.2f)
							newMembers[a][b][c][d] -= dist(e2) * (genModifier);
					}
		members.assign(newMembers.begin(), newMembers.end());
	}
	numGenerations++;
}

string NeuralNetwork::toString()
{
	string toReturn = "{\n";
	for (int a = 0; a < members.size(); a++)
	{
		toReturn += "Member " + to_string(a) + " : [\n";
		for (int b = 0; b < members[a].size(); b++)
		{
			toReturn += "Layer " + to_string(b) + " : [\n";
			for (int c = 0; c < members[a][b].size(); b++)
			{
				toReturn += "Node : " + to_string(c) + "[\n";
				for (int d = 0; d < members[a][b][c].size(); b++)
				{
					toReturn += to_string(members[a][b][c][d]) + ",";
				}
				toReturn += "],\n";
			}
			toReturn += "],\n";
		}
		toReturn += "],\n";
	}
	toReturn += "}";
	return toReturn;
}

int NeuralNetwork::getNumMembers() { return members.size(); }
void NeuralNetwork::setConstantMembers(bool c) { this->constMembers = c; }