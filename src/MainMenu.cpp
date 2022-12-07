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
    menu.append("\t5. Simulated Annealing\n");
    menu.append("\t6. Test automatyczny\n");
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
                    std::string filename;
                    std::cout << "Podaj nazwę pliku do zapisania wyniku:";
                    std::cin >> filename;
                    TabuSearch ts(graph, time);
                    ts.apply(filename, time);
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
                    std::string filename;
                    std::cout << "Podaj nazwę pliku do zapisania wyniku:";
                    std::cin >> filename;
                    SimulatedAnnealing sa(graph, time, temperatureFactor);
                    sa.apply(filename, time);
                    std::cin.get();
                }
                break;
            }
            case 6:
            {
                if (!time || !temperatureFactor)
                {
                    std::cout << "Nie podano czasu lub wspolcznnika dT";
                    std::cin.get();
                }
                else
                {
                    std::string graphType;
                    std::cout << "Podaj nazwę pliku z grafem:";
                    std::cin >> graphType;

                    TabuSearch ts(graph, time);
                    for (size_t i = 0; i < 10; i++)
                    {
                        std::cout << std::endl << i + 1 << " pomiar Tabu Search..." << std::endl;
                        ts.apply(graphType, i + 1);
                    }
                        
                    SimulatedAnnealing sa(graph, time, temperatureFactor);
                    for (size_t i = 0; i < 10; i++)
                    {
                        std::cout << std::endl << i + 1 << " pomiar Simulated Annealing..." << std::endl;
                        sa.apply(graphType, i + 1);
                    }

                    std::cout << "\nPomiary zakończone" << std::endl;
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