#include "NeuralNetwork.hpp"
#include <array>
#include <math.h>
#include <ctime>
#include <string>

double sigmoid(double x)
{
	return (1.0f / (1.0f + exp(-x)));
}

vector<vector<vector<double>>> NeuralNetwork::getTableOf(int index)
{
	if (index < 0 || index > members.size())
		return vector<vector<vector<double>>>();
	else
		return members[index];
}

NeuralNetwork::NeuralNetwork(int input, vector<int> innerNodes, int output, bool constMembers)
{
	numInput = input;
	numOutput = output;
	numEachLayer = vector<int>(innerNodes);
	numGenerations = 0;
	this->numLayers = innerNodes.size();
	this->myInput = vector<double>();
	this->constMembers = constMembers;

	random_device rd;
	mt19937 e2(rd());
	uniform_real_distribution<double> dist(0, 1);

	members = vector<vector<vector<vector<double>>>>();
}

void NeuralNetwork::init(int numNetworks)
{
	members.clear();
	members.reserve(numNetworks);
	for (int a = 0; a < numNetworks; a++)
	{
		members.push_back(vector<vector<vector<double>>>());
		members[a].reserve(numLayers + 1);
		for (int b = 0; b < numLayers + 1; b++)
		{
			members[a].push_back(vector<vector<double>>());
			if (b < numLayers)
			{
				members[a][b].reserve(numEachLayer[b]);
				for (int c = 0; c < numEachLayer[b]; c++)
				{
					members[a][b].push_back(vector<double>());
					if (b == 0)
						members[a][b][c].reserve(numInput);
					else
						members[a][b][c].reserve(numEachLayer[b - 1]);
					for (int d = 0; d < members[a][b][c].capacity(); d++)
					{
						double temp = dist(e2);
						if (temp < 0.2f)
							members[a][b][c].push_back(dist(e2));
						else if (temp < 0.4f)
							members[a][b][c].push_back(-dist(e2));
						else
							members[a][b][c].push_back(0.0f);
					}
					members[a][b][c].shrink_to_fit();
				}
			}
			else
			{
				members[a][b].reserve(numOutput);
				for (int c = 0; c < numOutput; c++)
				{
					members[a][b].push_back(vector<double>());
					if (b == 0)
						members[a][b][c].reserve(numInput);
					else
						members[a][b][c].reserve(numEachLayer[b - 1]);
					for (int d = 0; d < members[a][b][c].capacity(); d++)
					{
						double temp = dist(e2);
						if (temp < 0.2f)
							members[a][b][c].push_back(dist(e2));
						else if (temp < 0.4f)
							members[a][b][c].push_back(-dist(e2));
						else
							members[a][b][c].push_back(0.0f);
					}
					members[a][b][c].shrink_to_fit();
				}
			}
			members[a][b].shrink_to_fit();
		}
		members[a].shrink_to_fit();
	}
	members.shrink_to_fit();
}

vector<double> NeuralNetwork::getOutputOfMember(int index, vector<double> input)
{
	if (input.size() != numInput || index < 0 || index >= members.size())
		return vector<double>();

	vector<vector<vector<double>>> weights = members[index];
	vector<double> previous = input;
	vector<double> result;

	for (int a = 0; a < weights.size(); a++)
	{
		result = vector<double>();
		result.reserve(weights[a].size());
		for (int b = 0; b < weights[a].size(); b++)
		{
			double temp = 0.0f;
			for (int c = 0; c < weights[a][b].size(); c++)
				temp += previous[c] * weights[a][b][c];
			result.emplace_back(sigmoid(temp));
		}
		previous = result;
	}
	return result;
}

vector<double> NeuralNetwork::getOutputOfMember(int index)
{
	return this->getOutputOfMember(index, this->myInput);
}

vector<vector<double>> NeuralNetwork::getAllOutputs(vector<double> input)
{
	if (input.size() != numInput)
		return vector<vector<double>>();

	vector<vector<double>> toReturn = vector<vector<double>>();
	toReturn.reserve(members.size());

	for (int i = 0; i < members.size(); i++)
		toReturn.emplace_back(this->getOutputOfMember(i, input));

	return toReturn;
}

vector<vector<double>> NeuralNetwork::getAllOutputs()
{
	return this->getAllOutputs(this->myInput);
}

void NeuralNetwork::clearInput()
{
	this->myInput.clear();
}

bool NeuralNetwork::setInput(vector<double> input)
{
	if (input.size() != numInput)
		return false;
	this->myInput = input;
	return true;
}

bool NeuralNetwork::nextGen(vector<bool> toNext)
{
	if (members.empty() || toNext.size() != members.size())
		return false;

	vector<int> indexes = vector<int>();
	indexes.reserve(members.size() / 2);
	for (int a = 0; a < members.size(); a++)
		if (!toNext[a])
			if (!constMembers)
				indexes.emplace_back(a);
			else
				members[a] = vector<vector<vector<double>>>();
		else if (constMembers)
			indexes.emplace(indexes.begin(), a);

	if (!constMembers)
		for (int i = 0; i < indexes.size(); i++)
			members.erase(members.begin() + indexes[i]);

	int current = 0;
	double genModifier = ((1.0f / exp(numGenerations / 32.0f)) + 0.01f);
	if (constMembers)
	{
		for (int a = 0; a < members.size(); a++)
		{
			if (members[a].empty())
			{
				members.emplace(members.begin() + a, members[indexes[current]]);
				members.erase(members.begin() + a + 1);
				current++;
				if (current >= indexes.size())
					current = 0;

				for (int b = 0; b < members[a].size(); b++)
					for (int c = 0; c < members[a][b].size(); c++)
						for (int d = 0; d < members[a][b][c].size(); d++)
						{
							double temp = dist(e2);
							if (temp < 0.1f)
							{
								members[a][b][c][d] += dist(e2) * genModifier;
							}
							else if (temp < 0.2f)
							{
								members[a][b][c][d] -= dist(e2) * genModifier;
							}
						}
			}
		}
	}
	else
	{
		vector<vector<vector<vector<double>>>> newMembers = vector<vector<vector<vector<double>>>>(members);
		for (int a = 0; a < newMembers.size(); a++)
			for (int b = 0; b < newMembers[a].size(); b++)
				for (int c = 0; c < newMembers[a][b].size(); c++)
					for (int d = 0; d < newMembers[a][b][c].size(); d++)
					{
						double temp = dist(e2);
						if (temp < 0.1f)
							newMembers[a][b][c][d] += dist(e2) * genModifier;
						else if (temp < 0.2f)
							newMembers[a][b][c][d] -= dist(e2) * genModifier;
					}
		members.insert(members.end(), newMembers.begin(), newMembers.end());
	}
	numGenerations++;
	return true;
}

string NeuralNetwork::memberToString(int index)
{
	if (index < 0 || index >= members.size())
		return "";

	string toReturn = "Member " + to_string(index) + " : [\n";
	for (int b = 0; b < members[index].size(); b++)
	{
		toReturn += "\tLayer " + to_string(b) + " : [\n";
		for (int c = 0; c < members[index][b].size(); c++)
		{
			toReturn += "\t\tNode " + to_string(c) + " : (";
			for (int d = 0; d < members[index][b][c].size(); d++)
			{
				toReturn += to_string(members[index][b][c][d]);
				if (d != members[index][b][c].size() - 1)
					toReturn += ",";
			}
			toReturn += ")";
			if (c != members[index][b].size() - 1)
				toReturn += ",";
			toReturn += "\n";
		}
		toReturn += "\t]";
		if (b != members[index].size() - 1)
			toReturn += ",";
		toReturn += "\n";
	}
	toReturn += "]";

	return toReturn;
}

string NeuralNetwork::toString()
{
	string toReturn = "{\n";
	for (int a = 0; a < members.size(); a++)
	{
		toReturn += memberToString(a);
		if (a != members.size() - 1)
			toReturn += ",";
		toReturn += "\n";
	}
	toReturn += "}";
	return toReturn;
}

void NeuralNetwork::clearMembers() { this->members.clear(); }

int NeuralNetwork::getNumMembers() { return members.size(); }
void NeuralNetwork::setConstantMembers(bool c) { this->constMembers = c; }