#pragma once
#include <string>
#include "Graph.hh"

class MainMenu
{
    private:
        std::string menu = "";
        std::string file = "";
        Graph graph;
        int time = 0;
        double temperatureFactor = 0;

    public:
        MainMenu();
        ~MainMenu();
        void enable();
};