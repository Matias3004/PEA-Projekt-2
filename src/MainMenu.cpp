#include "../inc/MainMenu.hh"
#include "../inc/TS.hh"
#include "../inc/SA.hh"
#include <iostream>

MainMenu::MainMenu()
{
    menu.append("===========================================\n");
    menu.append("===============PEA PROJEKT 2===============\n");
    menu.append("===========================================\n");
    menu.append("\t1. Podaj czas\n");
    menu.append("\t2. Podaj wspołczynnik dT\n");
    menu.append("\t3. Wczytaj graf\n");
    menu.append("\t4. Tabu Search\n");
    menu.append("\t5. Simulated Annaeling\n");
    menu.append("\t0. Zakończ program\n");
    menu.append("===========================================\n");
    menu.append("Twoj wybor: ");
}

MainMenu::~MainMenu() {}

void MainMenu::enable()
{
    int choice = 99;

    while (true)
    {
        std::cout << "Czas: " << time << "s\n";
        std::cout << "Wspołczynnik dT: " << temperatureFactor << "\n";
        std::cout << graph.getDesc();
        std::cout << menu;

        std::cin >> choice;

        switch (choice)
        {
            case 1:
            {
                do
                {
                    std::cout << "Podaj czas [s]: ";
                    std::cin >> time;
                } while (!time);

                break;
            }
            case 2:
            {
                do
                {   
                    std::cout << "Podaj wspołczynnik dT: ";
                    std::cin >> temperatureFactor;
                } while (temperatureFactor == 0.0);

                break;
            }
            case 3:
            {
                do
                {
                    std::cout << "Podaj nazwę pliku: ";
                    std::cin >> file;
                } while (file == "");
                graph.readGraph(file);

                break;
            }
            case 4:
            {
                if (!time)
                {
                    std::cout << "Nie podano czasu wykonania";
                    std::cin.get();
                }
                else
                {
                    TabuSearch ts(graph, time);
                    ts.apply();
                    std::cin.get();
                }

                break;
            }
            case 5:
            {
                if (!time || !temperatureFactor)
                {
                    std::cout << "Nie podano czasu lub wspołczynnika dT";
                    std::cin.get();
                }
                else
                {
                    SimulatedAnnealing sa(graph, time, temperatureFactor);
                    sa.apply();
                    std::cin.get();
                }
                break;
            }
            case 0:
                return;
        }

        std::cin.ignore();
        system("clear");
    }
}