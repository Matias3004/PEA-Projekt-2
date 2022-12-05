#pragma once
#include <vector>
#include "Graph.hh"

class SimulatedAnnealing
{
    private:
        std::vector<int> solution;
        double temperatureBuffer = 0;
        double coolingRate = 0;
        double timeBound = 0;
        int **matrix;
        int size;

    public:
        SimulatedAnnealing(Graph, int, double);
        ~SimulatedAnnealing();
        void saveResultsToFile(std::string, int, double, double);
        std::vector<int> randomPermutation(int);
        double calculateTemperature();
        int calculatePath(std::vector<int>);
        double getProbability(int, double);
        void apply();
};