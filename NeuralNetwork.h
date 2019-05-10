#include <iostream>
#include <vector>

using namespace std;

class NeuralNetwork
{
private:
	int numInput, numOutput, numLayers;
	vector<int> numEachLayer;
	vector<vector<vector<vector<float>>>> members;
	vector<float> input;

public:
	vector<vector<vector<float>>> getTableOf(int index);

	NeuralNetwork(int input,vector<int> innerNodes,int output);

	void init(int numNetworks);
	void clearInput();
	bool setInput(vector<float> input);
	vector<float> getOutputOfMember(int index);
	vector<float> getOutputOfMember(int index,vector<float> input);
	vector<vector<float>> getAllOutputs();
	vector<vector<float>> getAllOutputs(vector<float> input);
	void nextGen(bool* toNext);
};
