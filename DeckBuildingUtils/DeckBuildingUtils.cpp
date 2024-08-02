#include <iostream>
#include<string>
#include <map>
#include <format>
#include "../../Skele_lib/Console/Console.hpp"
#include "./headers/actions.hpp"
#include "./headers/printDeckStats.h"

    
void PrintActions(SKC::Console::Console &c) {
    c.Print(R"(Copyright(C) 2023 Skeleton_craft 
This program comes with ABSOLUTELY NO WARRANTY
)");
    c.Println("--menu--"); 
    c.Println("[a]dd nonland"); 
    c.Println("[r]emove a nonland"); 
    c.Println("add a [l]and"); 
    c.Println("remove a [L]and"); 
    c.Println("[R]eset the program"); 
    c.Println("e[x]it");
    c.Println("--------"); 
}

constexpr int MAX_COL = 10;

int main()
{
    
    SKC::Console::Console c{}; 
    int lands = 24, nonLands = 0, TotalCmc = 0;
    char command = 0;
    std::map<unsigned, unsigned> cmcs = {};
    for (int x = 1; x <= 10; ++x) cmcs[x] = 0; 
    while (command != 'x') {
        PrintActions(c);
       
        c.ClearLine();
        std::cin >> command;
       if (command == 'a') {
            int cmc = 0;
            int amount = 0;
            SKC::AddCardPrompt(c, cmc, amount);
            TotalCmc += (cmc * amount);
            nonLands += amount; 
            cmcs[cmc] += amount; 
        }
        if (command == 'r') {
            int cmc = 0;
            int amount = 0;
            SKC::AddCardPrompt(c, cmc, amount);
            TotalCmc -= (cmc * amount);
            nonLands -= amount;
            cmcs[cmc] -= amount;

        }
        if (command == 'R') {
            lands = 24; 
            TotalCmc = 0; 
            nonLands = 0;
            cmcs = {}; 
            for (int x = 1; x <= 10; ++x) cmcs[x] = 0;
        }
        if (command == 'l') {
            ++lands;
        }
        if (command == 'L') {
            --lands; 
        }
        std::cout << " "; 
        std::cin.ignore();
        c.Clear();

        unsigned max = 0;
        for (auto& item : cmcs) {
            auto &[key, value] = item;
            if (max < value) max = value;
        }
        for (int x = 1; x <= 10; ++x) {
            double val = cmcs[x - 1];//((double)rand() / (double)RAND_MAX) * MAX_COL;
            if (max > MAX_COL) {
                val /= max;
                val *= MAX_COL;
            }
            c.Move(x, MAX_COL + 11).Print(x).Up().Left().Print('-');
            for (int y = 1; y <= 10; ++y) {
                auto py = (MAX_COL - y) + 10;
                double t = val - y;

                if (t < 0) continue;
                //c.Move(x, py).Print(char(219));

                if (t > 1) {
                    c.Move(x, py).Print(char(219));
                    continue;

                }
                if (t > 0.75) {
                    c.Move(x, py).Print('#');
                    continue;

                }
                if (t > 0.5) {
                    c.Move(x, py).Print(char(178));
                    continue;

                }
                c.Move(x, py).Print(char(176));
            }

        }
        c.Move(1, 1); 
        SKC::PrintDeckStats(c, lands, nonLands, TotalCmc);
        std::cin.ignore();
        c.Clear();
    }
}