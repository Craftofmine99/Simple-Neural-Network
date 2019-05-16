#include "src/NeuralNetwork.hpp"
#include <iostream>

using namespace std;
/**
 * For testing the NeuralNetwork
 */
int main()
{
    vector<int> innerNodes = vector<int>();
    innerNodes.emplace_back(128);
    innerNodes.emplace_back(128);
    innerNodes.emplace_back(128);


    int numInput = 768;
    int numOutput = 1;
    int numMembers = 64;

    NeuralNetwork myNetwork = NeuralNetwork(numInput, innerNodes, numOutput, true);
    myNetwork.init(numMembers);

    // cout << myNetwork.toString() << endl;

    vector<float> input = vector<float>(numInput,0.5f);

    myNetwork.setInput(input);
    // vector<vector<float>> output = myNetwork.getAllOutputs();

    // cout << output.size() << endl;

    // for(int i = 0 ; i < output.size(); i++)
    // {
    //     cout << i << endl;
    //     for(int a = 0 ; a < output[i].size() ; a++)
    //         cout << output[i][a] << ", ";
    //     cout << endl << "-------" << endl;
    // }
    // cout << "-------------------" << endl << "-------------------" << endl;

    vector<bool> toNext = vector<bool>();

    for( ;toNext.size() < numMembers ; )
    {
        toNext.push_back(false);
        toNext.push_back(true);
    }

    toNext.shrink_to_fit();

    cout << "Next Size : " << toNext.size() << endl;

    for(int i = 0 ; true ; i++)
    {
        for(int i = 0 ; i < numMembers ; i++)
        {
            for(int m = 0 ; m < 100000 ; m++)
            {
                myNetwork.getOutputOfMember(i);
            }
        }
        myNetwork.nextGen(toNext);
        cout << myNetwork.getNumMembers() << " - " << i << endl;
    }
}