#pragma once
#include <string>
#define INF 9999

class Graph
{
    private:
        int **matrix = nullptr;
        int vertexCount = 0;
        std::string desc = "";

    public:
        Graph();
        ~Graph();
        bool readGraph(std::string filename);
        bool readGraphSmall(std::string filename);
        void generateRandomGraph(int size);
        bool infDiag();
        int** getMatrix();
        int getCount();
        std::string getDesc();
        std::string toString();
};
