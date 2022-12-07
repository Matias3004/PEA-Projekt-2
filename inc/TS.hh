#pragma once
#include "Graph.hh"
#include <vector>

class TabuSearch
{
    private:
        int **matrix = nullptr;
        int size = 0;
        int searchTime = 0;

        std::vector<int> randomPermutation(int);
        int calculatePath(std::vector<int>);

    public:
        TabuSearch(Graph, int);
        ~TabuSearch();
        void saveResultsToFile(std::string, int, double);
        void apply(std::string, unsigned int);
};