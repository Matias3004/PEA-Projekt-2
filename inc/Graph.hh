#pragma once
#include <string>

#define INF 9999
// Najlepsze znane rozwiązania poszczegolnych plikow
#define FTV_47_ATSP = 1776
#define FTV_170_ATSP = 2755
#define RGB_403_ATSP = 2465

class Graph
{
    private:
        int **matrix = nullptr;
        int vertexCount = 0;
        std::string desc = "";

    public:
        Graph();
        ~Graph();
        bool readGraph(std::string);
        bool readGraphSmall(std::string);
        void generateRandomGraph(int);
        bool infDiag();
        int** getMatrix();
        int getCount();
        std::string getDesc();
        std::string toString();
};
