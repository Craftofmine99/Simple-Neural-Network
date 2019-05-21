#include "src/NeuralNetwork.hpp"
#include <iostream>
#include <ctime>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <cuda_profiler_api.h>

using namespace std;
/**
 * For testing the NeuralNetwork
 */

__device__
double sigmoidDevice(double x)
{
	return (1.0f / (1.0f + exp(-x)));
}

__global__
void forCuda(double *members, int *layerSizes, double* answers, double *input, int otherSize, int numInput, int memberSize)
{
    int threadIndex = threadIdx.x;

    double *previous = new double[numInput];
    double *result = new double[1];
    for(int i = 0 ; i < numInput ; i++)
        previous[i] = input[i];

    int index,tempIndex;

    for(int a = threadIndex*2 ; a < threadIndex*2+2 ; a++)
    {
        index = memberSize*a;
        for(int b = 0 ; b < otherSize ; b++)
        {
            delete [] result;
            result = new double[layerSizes[b]];
            for(int c = 0 ; c < layerSizes[b] ; c++)
            {
                double temp = 0.0;
                if(b == 0)
                {
                    tempIndex = index + c*numInput;
                    for(int d = 0 ; d < numInput ; d++)
                        temp += previous[d] * members[tempIndex + d];
                }
                else
                {
                    tempIndex = index + c*layerSizes[b-1];
                    for(int d = 0 ; d < layerSizes[b-1] ; d++)
                        temp += previous[d] * members[tempIndex + d];
                }
                result[c] = sigmoidDevice(temp);
            }
            if(b == 0)
                index += layerSizes[b]*numInput;
            else
                index += layerSizes[b]*layerSizes[b-1];
            delete [] previous;
            previous = new double[layerSizes[b]];
            for(int c = 0 ; c < layerSizes[b] ; c++)
                previous[c] = result[c];
        }
        for(int i = 0 ; i < layerSizes[otherSize-1] ; i++)
            answers[a + i] = result[i];
    }
    delete [] previous;
    delete [] result;
}

int main()
{
    vector<int> innerNodes = vector<int>();
    innerNodes.emplace_back(64);
    innerNodes.emplace_back(64);
    innerNodes.emplace_back(64);
    innerNodes.emplace_back(64);
    innerNodes.emplace_back(64);
    innerNodes.emplace_back(64);
    innerNodes.emplace_back(64);
    innerNodes.emplace_back(64);

    int numInput = 768;
    int numOutput = 1;
    int numMembers = 512;

    NeuralNetwork myNetwork = NeuralNetwork(numInput, innerNodes, numOutput, true);
    myNetwork.init(numMembers);

    vector<double> input = vector<double>(numInput, 0.5f);

    cudaProfilerStart();

    // Allocate memory
    double *members;
    int *lSizes;
    double *answers;
    cudaMallocManaged(&answers, (numMembers*numOutput)*sizeof(double));

    int membersSize = 0;
    vector<vector<vector<double>>> tempMember;
    for(int a = 0 ; a < numMembers ; a++)
    {
        tempMember = myNetwork.getTableOf(a);
        for(int b = 0 ; b < tempMember.size() ; b++)
            for(int c = 0 ; c < tempMember[b].size() ; c++)
                membersSize += tempMember[b][c].size();
    }
    cudaMallocManaged(&members, membersSize*sizeof(double));

    int size = 0;
    for(int a = 0 ; a < tempMember.size() ; a++)
        for(int b = 0 ; b < tempMember[a].size() ; b++)
            size += tempMember[a][b].size();

    vector<int> layerSizes = vector<int>(innerNodes);
    layerSizes.emplace_back(numOutput);
    cudaMallocManaged(&lSizes,layerSizes.size()*sizeof(int));
    for(int i = 0 ; i < layerSizes.size() ; i++)
        lSizes[i] = layerSizes[i];

    cout << "Size of array \"members\" : " << membersSize << endl;

    vector<bool> toNext = vector<bool>();

    for (; toNext.size() < numMembers;)
    {
        toNext.push_back(false);
        toNext.push_back(true);
        toNext.push_back(false);
        toNext.push_back(false);
    }

    toNext.shrink_to_fit();

    cout << "Members : " << numMembers << endl;

    int avgMoves = 40;
    int numMovesChecked = 100;

    cout << "Moves per \"game\" : " << avgMoves*numMovesChecked << endl;
    for (int i = 0; i < 16; i++)
    {
        clock_t begin_time = clock();

        // Fill it
        int index = 0;
        for(int a = 0 ; a < numMembers ; a++)
        {
            tempMember = myNetwork.getTableOf(a);
            for(int b = 0 ; b < tempMember.size() ; b++)
                for(int c = 0 ; c < tempMember[b].size() ; c++)
                    for(int d = 0 ; d < tempMember[b][c].size() ; d++)
                        members[index++] = tempMember[b][c][d];
        }

        double *tempInput;
        cudaMallocManaged(&tempInput, numInput*sizeof(double));

        for(int a = 0 ; a < avgMoves*numMovesChecked ; a++)
        {
            // cudaFree(answers);
            // cudaMallocManaged(&answers, (numMembers)*sizeof(double));

            for(int b = 0 ; b < numInput ; b++)
                tempInput[b] = myNetwork.dist(myNetwork.e2);

            // cout << "Start GPU" << endl;
            forCuda<<<1,numMembers/2>>>(members, lSizes, answers, tempInput, layerSizes.size(), numInput, size);
            cudaDeviceSynchronize();
            // cout << "End GPU" << endl;

            // cout << "Answer sum : " << (a+1) << endl;
            // double temp = 0.0;
            // for(int b = 0 ; b < numMembers ; b++)
            //     temp += answers[b];
            // cout << temp << endl;
        }

        cudaFree(tempInput);

        if (myNetwork.nextGen(toNext))
        {

            clock_t end_time = clock();
            int hours = floor((float(end_time - begin_time) / CLOCKS_PER_SEC) / 3600.0f);
            int minuets = floor((float(end_time - begin_time) / CLOCKS_PER_SEC - hours * 60) / 60.0f);
            int seconds = float(end_time - begin_time) / CLOCKS_PER_SEC - hours * 60.0f - minuets * 60.0f;
            cout << (i + 1) << "\t" << hours << " : " << minuets << " : " << seconds << endl;
            cout << "---------------" << endl;
        }
        else
            break;
    }


    cudaFree(members);
    cudaFree(lSizes);
    cudaFree(answers);

    cudaProfilerStop();

    return 0;
}