#include "../inc/TS.hh"
#include "../inc/Graph.hh"
#include <time.h>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <random>

TabuSearch::TabuSearch(Graph graph, int time)
{
    matrix = graph.getMatrix();
    size = graph.getCount();
    searchTime = time;
}

TabuSearch::~TabuSearch() {}

std::vector<int> TabuSearch::randomPermutation(int size)
{
    std::vector<int> temp;
    temp.reserve(size);

    for (int i = 0; i < size; i++)
        temp.push_back(i);

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(temp.begin(), temp.end(), g);

    return temp;
}

int TabuSearch::calculatePath(std::vector<int> path)
{
    int cost = 0;

    for (int i = 0; i < path.size() - 1; ++i)
        cost += matrix[path[i]][path[i + 1]];

    cost += matrix[path[size - 1]][path[0]];

    return cost;
}

void TabuSearch::apply()
{
    std::vector<std::vector<int>> tabuMatrix;
    std::vector<int> best;
    std::vector<int> permutation = randomPermutation(size);
    std::vector<int> next(permutation);

    int result = 1 << 30;
    int firstToSwap;
    int secondToSwap;
    int nextCost;

    std::clock_t start;
    double time;
    double foundTime;

    tabuMatrix.resize(size);

    for (int i = 0; i < size; ++i)
        tabuMatrix[i].resize(size, 0);

    start = std::clock();

    while (true)
    {
        for (int step = 0; step < 15 * size; ++step)
        {
            firstToSwap = 0;
            secondToSwap = 0;
            nextCost = 1 << 30;

            for (int first = 0; first < size; ++first)
            {
                for (int second = first + 1; second < size; ++second)
                {
                    std::swap(permutation[first], permutation[second]);
                    int currentCost = calculatePath(permutation);

                    if (currentCost < result)
                    {
                        result = currentCost;
                        best = permutation;
                        foundTime = (std::clock() - start) / (double) CLOCKS_PER_SEC;
                    }

                    if (currentCost < nextCost)
                    {
                        if (tabuMatrix[second][first] < step)
                        {
                            nextCost = currentCost;
                            next = permutation;

                            firstToSwap = second;
                            secondToSwap = first;
                        }
                    }

                    std::swap(permutation[first], permutation[second]);

                    time = (std::clock() - start) / (double) CLOCKS_PER_SEC;

                    if (time >= searchTime)
                    {
                        std::cout << "Droga: ";
                        for (int i = 0; i < size; i++)
                            std::cout << best[i] << " ";

                        std::cout << "\nKoszt: " << result << std::endl;
                        std::cout << "Czas wykonania przeszukania: " << foundTime << "s" << std::endl;

                        return;
                    }
                }
            }
            permutation = next;
            tabuMatrix[firstToSwap][secondToSwap] += size;
        }

        permutation.clear();
        permutation = randomPermutation(size);

        for (std::vector<std::vector<int>>::iterator it = tabuMatrix.begin(); it != tabuMatrix.end(); ++it)
            it->clear();
        
        tabuMatrix.clear();
        tabuMatrix.resize(size);

        for (std::vector<std::vector<int>>::iterator it = tabuMatrix.begin(); it != tabuMatrix.end(); ++it)
            it->resize(size, 0);
    }
}