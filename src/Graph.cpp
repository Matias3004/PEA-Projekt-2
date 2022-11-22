#include "../inc/Graph.hh"
#include <fstream>
#include <time.h>
#include <string>
#include <iostream>

Graph::Graph() {}

Graph::~Graph() {}

bool Graph::readGraph(std::string filename)
{
    int **temp;
    desc = "";
    std::string tempDesc = "";

    std::ifstream fin;
    fin.open(filename);

    if (fin.fail() || fin.eof())
        return false;

    if (vertexCount)
    {
        for (int i = 0; i < vertexCount; i++)
            delete[] matrix[i];

        delete[] matrix;
    }

    for (int i = 0; i < 3; i++)
    {
        getline(fin, tempDesc);
        desc.append(tempDesc + "\n");
    }
    
    fin >> tempDesc;
    desc.append(tempDesc);

    fin >> vertexCount;
    desc.append(std::to_string(vertexCount) + "\n");

    for (int i = 0; i < 4; i++)
        getline(fin, tempDesc);

    temp = new int *[vertexCount];

    for (int i = 0; i < vertexCount; i++)
        temp[i] = new int[vertexCount];

    for (int i = 0; i < vertexCount; i++)
    {
        for (int j = 0; j < vertexCount; j++)
            fin >> temp[j][i];
    }

    fin.close();
    matrix = temp;

    return true;
}

bool Graph::readGraphSmall(std::string filename)
{
    int **temp;

    std::ifstream fin;
    fin.open(filename);

    if (fin.fail() || fin.eof())
        return false;

    if (vertexCount)
    {
        for (int i = 0; i < vertexCount; i++)
            delete[] matrix[i];

        delete[] matrix;
    }

    fin >> vertexCount;

    temp = new int *[vertexCount];

    for (int i = 0; i < vertexCount; i++)
        temp[i] = new int[vertexCount];

    for (int i = 0; i < vertexCount; i++)
    {
        for (int j = 0; j < vertexCount; j++)
            fin >> temp[j][i];
    }

    fin.close();
    matrix = temp;

    return true;
}

void Graph::generateRandomGraph(int size)
{
    vertexCount = size;
    int **buffer = nullptr;
    buffer = new int*[vertexCount];

    srand(time(NULL));
    
    for (int i = 0; i < vertexCount; i++)
    {
        buffer[i] = new int[vertexCount];

        for (int j = 0; j < vertexCount; j++)
            buffer[i][j] = rand() % 100 + 1;
    }

    matrix = buffer;
    infDiag();
}

bool Graph::infDiag()
{
    if (!vertexCount)
        return false;
    else
    {
        for (int i = 0; i < vertexCount; i++)
            matrix[i][i] = -1;

        return true;
    }
}

int** Graph::getMatrix()
{
    return matrix;
}

int Graph::getCount()
{
    return vertexCount;
}

std::string Graph::getDesc()
{
    if (!vertexCount)
        return "Brak danych\n";
    else
        return desc;
}

std::string Graph::toString()
{
    std::string graph = "";
    graph.append(desc);

    if (vertexCount)
    {
        for (int i = 0; i < vertexCount; i++)
        {
            for (int j = 0; j < vertexCount; j++)
            {
                if ((matrix[i][j] < 10) && (matrix[i][j] >= 0))
                    graph += std::to_string(matrix[i][j]) + "    ";
                else if (((matrix[i][j] < 100) && (matrix[i][j] > 9)) || (matrix[i][j] < 0))
                    graph += std::to_string(matrix[i][j]) + "    ";
                else if (matrix[i][j] == 100000000)
                    graph += "N    ";
                else
                    graph += std::to_string(matrix[i][j]) + "  ";
            }
            graph += "\n";
        }
    }
    else
        graph = "Graf pusty\n";

    return graph;
}