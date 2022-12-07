#include "../inc/SA.hh"
#include <vector>
#include <algorithm>
#include <time.h>
#include <ctime>
#include <random>
#include <iostream>
#include <fstream>

SimulatedAnnealing::SimulatedAnnealing(Graph graph, int time, double rate)
{
    matrix = graph.getMatrix();
    size = graph.getCount();
    timeBound = time;
    coolingRate = rate;
    temperatureBuffer = calculateTemperature();
}

SimulatedAnnealing::~SimulatedAnnealing() {}

void SimulatedAnnealing::saveResultsToFile(std::string filename, int result, double time, double temperature)
{
    std::ofstream file(filename + "-SA.csv");
    if (file.good() == true)
    {
        file << "Rozwiązanie, Błąd [%], Czas [s], Tk" << std::endl;
        file << result << ",TODO," << time << "," << temperature << std::endl;

        file.close();
    }
    else
    {
        std::cout << "Błąd zapisu" << std::endl;
        getchar();
    }
}

std::vector<int> SimulatedAnnealing::randomPermutation(int size)
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

double SimulatedAnnealing::calculateTemperature()
{
    std::vector<int> origin;

    int firstToSwap, secondToSwap;
    int delta = 0;
    int buffer = 0;

    for (int i = 0; i < 10000; i++)
    {
        do
        {
            firstToSwap = rand() % size;
            secondToSwap = rand() % size;
        } while (firstToSwap == secondToSwap);
        
        origin = randomPermutation(size);
        std::vector<int> neighbour(origin);

        std::swap(neighbour[firstToSwap], neighbour[secondToSwap]);

        delta = fabs(calculatePath(origin) - calculatePath(neighbour));
        buffer += delta;
    }

    buffer /= 10000;

    return (-1 * buffer) / log(0.99);
}

int SimulatedAnnealing::calculatePath(std::vector<int> path)
{
    int cost = 0;

    for (size_t i = 0; i < path.size() - 1; ++i)
        cost += matrix[path[i]][path[i + 1]];

    cost += matrix[path[size - 1]][path[0]];

    return cost;
}

double SimulatedAnnealing::getProbability(int diff, double temperature)
{
    return exp(diff / temperature);
}

void SimulatedAnnealing::apply(std::string filename, unsigned pass)
{
    std::vector<int> best;
    std::vector<int> permutation = randomPermutation(size);
    std::vector<int> next(permutation);

    std::clock_t start;

    int firstToSwap, secondToSwap;
    double temperature = temperatureBuffer;
    int result = 1 << 30;
    double time = 0;
    double foundTime = 0;
    start = std::clock();

    while (true)
    {
        while (temperature >= 0.1)
        {
            int steps = 3 * size;
            next = permutation;
            int nextCost = calculatePath(next);

            for (int i = steps; i > 0; i--)
            {
                do
                {
                    firstToSwap = rand() % size;
                    secondToSwap = rand() % size;
                } while (firstToSwap == secondToSwap);

                std::swap(next[firstToSwap], next[secondToSwap]);
                nextCost = calculatePath(next);
                int difference = result - nextCost;

                if (difference > 0)
                {
                    result = nextCost;
                    best = next;
                    foundTime = (std::clock() - start) / (double) CLOCKS_PER_SEC;
                }

                if (difference > 0 || (difference < 0 && getProbability(difference, temperature) > ((double) rand() / RAND_MAX) + 1))
                {
                    permutation = next;
                    break;
                }
                else
                    std::swap(next[firstToSwap], next[secondToSwap]);

                time = (std::clock() - start) / (double) CLOCKS_PER_SEC;

                if (time >= timeBound)
                {
                    std::cout << "Droga: ";
                    for (int i = 0; i < size; i++)
                        std::cout << best[i] << " ";

                    std::cout << "\nKoszt: " << result << std::endl;
                    std::cout << "Czas znalezienia: " << foundTime << "s" << std::endl;
                    std::cout << "Temperatura końcowa: " << temperature << std::endl;

                    filename.append(std::to_string(pass));
                    saveResultsToFile(filename, result, foundTime, temperature);

                    return;
                }
            }
            temperature *= coolingRate;
        }
        
        temperature = temperatureBuffer;
        permutation = randomPermutation(size);
    }
}