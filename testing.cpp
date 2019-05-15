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
    innerNodes.emplace_back(5);
    innerNodes.emplace_back(5);
    innerNodes.emplace_back(5);


    NeuralNetwork myNetwork = NeuralNetwork(6, innerNodes, 2, true);

    myNetwork.init(20);

    cout << myNetwork.toString() << endl;

    vector<float> input = vector<float>(6,0.5f);

    myNetwork.setInput(input);
    vector<vector<float>> output = myNetwork.getAllOutputs();

    cout << output.size() << endl;

    for(int i = 0 ; i < 20; i++)
    {
        cout << i << endl;
        for(int a = 0 ; a < 2 ; a++)
            cout << output[i][a] << ", ";
        cout << endl << "-------" << endl;
    }
    cout << "-------------------" << endl << "-------------------" << endl;

    vector<bool> toNext = vector<bool>();

    toNext.push_back(true);
    toNext.push_back(false);
    toNext.push_back(true);
    for( ;toNext.size() < 20 ; )
        toNext.push_back(false);

    toNext.shrink_to_fit();

    cout << "Next Size : " << toNext.size() << endl;

    myNetwork.nextGen(toNext);

    cout << myNetwork.toString() << endl;
}