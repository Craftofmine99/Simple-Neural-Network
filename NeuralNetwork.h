#include <iostream>
#include <vector>

using namespace std;

class NeuralNetwork
{
private:
	mt19937 e2;
	uniform_real_distribution<float> dist;
	int numInput, numOutput, numLayers, numGenerations;
	bool constMembers;
	vector<int> numEachLayer;
	vector<vector<vector<vector<float>>>> members;
	vector<float> input;

public:
	vector<vector<vector<float>>> getTableOf(int index);

	NeuralNetwork(int input, vector<int> innerNodes, int output, bool constMembers);

	void init(int numNetworks);
	void clearInput();
	bool setInput(vector<float> input);
	vector<float> getOutputOfMember(int index);
	vector<float> getOutputOfMember(int index, vector<float> input);
	vector<vector<float>> getAllOutputs();
	vector<vector<float>> getAllOutputs(vector<float> input);
	void nextGen(vector<bool> toNext);

	string toString();
	int getNumMembers();
	void setConstantMembers(bool c);
};
