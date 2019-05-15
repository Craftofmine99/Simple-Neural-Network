#include <vector>
#include <iostream>
#include "src/NeuralNetwork.h"

using namespace std;
/**
 * For testing the NeuralNetwork
 */
int main()
{
    vector<int> innerNodes = vector<int>();
    innerNodes.emplace_back(4);
    innerNodes.emplace_back(4);
    innerNodes.emplace_back(4);


    int numInput = 3;
    int numOutput = 3;
    int numMembers = 20;

    NeuralNetwork myNetwork = NeuralNetwork(numInput, innerNodes, numOutput, true);
    myNetwork.init(numMembers);

    cout << myNetwork.toString() << endl;

    vector<float> input = vector<float>(numInput,0.5f);

    myNetwork.setInput(input);
    vector<vector<float>> output = myNetwork.getAllOutputs();

    cout << output.size() << endl;

    for(int i = 0 ; i < output.size(); i++)
    {
        cout << i << endl;
        for(int a = 0 ; a < output[i].size() ; a++)
            cout << output[i][a] << ", ";
        cout << endl << "-------" << endl;
    }
    cout << "-------------------" << endl << "-------------------" << endl;

    vector<bool> toNext = vector<bool>();

    toNext.push_back(true);
    toNext.push_back(false);
    toNext.push_back(true);
    for( ;toNext.size() < numMembers ; )
        toNext.push_back(false);

    toNext.shrink_to_fit();

    cout << "Next Size : " << toNext.size() << endl;

    // for(int i = 0 ; true ; i++)
    // {
    //     myNetwork.getAllOutputs();
    //     myNetwork.nextGen(toNext);
    //     cout << myNetwork.getNumMembers() << " - " << i << endl;
    // }

    cout << myNetwork.memberToString(2) << endl;
}