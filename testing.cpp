#include "src/neuralNetwork/NeuralNetwork.hpp"
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
    innerNodes.emplace_back(768);
    innerNodes.emplace_back(384);

    int numInput = 768;
    int numOutput = 1;
    int numMembers = 256;

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
        toNext.push_back(true);
        toNext.push_back(false);
    }

    if(toNext.size() > numMembers) toNext.resize(numMembers);
    toNext.shrink_to_fit();

    cout << "Members : " << numMembers << endl;

    int avgMoves = 40;
    int numMovesChecked = 100;

    cout << "Moves checked per \"game\" : " << avgMoves*numMovesChecked << endl;
    for (int i = 0; i < 16 ; i++)
    {
        clock_t begin_time = clock();
        for (int i = 0; i < numMembers; i++)
            for (int m = 0; m < avgMoves; m++)
                for (int c = 0; c < numMovesChecked; c++)
                    myNetwork.getOutputOfMember(i);

        if (myNetwork.nextGen(toNext))
        {
            clock_t end_time = clock();
            float timeDiff = clock() - begin_time;
            int hours = floor((timeDiff / CLOCKS_PER_SEC) / 3600.0f);
            int minuets = floor((timeDiff / CLOCKS_PER_SEC - hours * 3600) / 60.0f);
            int seconds = (timeDiff / CLOCKS_PER_SEC) - hours * 3600.0f - minuets * 60.0f;
            cout << (i + 1) << "\t";
            if (hours < 10) cout << "0";
            cout << hours << ":";
            if(minuets < 10) cout << "0";
            cout << minuets << ":";
            if(seconds < 10) cout << "0";
            cout << seconds << endl;
            cout << "-----------------" << endl;
        }
        else
            break;
    }
}