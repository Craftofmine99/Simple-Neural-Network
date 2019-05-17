#include "src/NeuralNetwork.hpp"
#include <iostream>
#include <ctime>

using namespace std;
/**
 * For testing the NeuralNetwork
 */
int main()
{
    vector<int> innerNodes = vector<int>();
    innerNodes.emplace_back(1536);
    innerNodes.emplace_back(64);

    int numInput = 768;
    int numOutput = 1;
    int numMembers = 64;

    NeuralNetwork myNetwork = NeuralNetwork(numInput, innerNodes, numOutput, true);
    myNetwork.init(numMembers);

    // cout << myNetwork.toString() << endl;

    vector<double> input = vector<double>(numInput, 0.5f);

    myNetwork.setInput(input);
    // vector<vector<double>> output = myNetwork.getAllOutputs();

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

    for (; toNext.size() < numMembers;)
    {
        toNext.push_back(false);
        toNext.push_back(true);
    }

    toNext.shrink_to_fit();

    cout << "Next Size : " << toNext.size() << endl;

    int avgMoves = 40;
    int numMovesChecked = 10000;
    for (int i = 0; true; i++)
    {
        clock_t begin_time = clock();
        for (int i = 0; i < numMembers; i++)
            for (int m = 0; m < avgMoves; m++)
                for (int c = 0; c < numMovesChecked; c++)
                    myNetwork.getOutputOfMember(i);

        if (myNetwork.nextGen(toNext))
        {
            int hours = floor((float(clock() - begin_time) / CLOCKS_PER_SEC) / 3600.0f);
            int minuets = floor((float(clock() - begin_time) / CLOCKS_PER_SEC - hours * 60) / 60.0f);
            int seconds = float(clock() - begin_time) / CLOCKS_PER_SEC - hours * 60.0f - minuets * 60.0f;
            cout << (i + 1) << "\t" << hours << " : " << minuets << " : " << seconds << endl;
        }
        else
            break;
    }
}