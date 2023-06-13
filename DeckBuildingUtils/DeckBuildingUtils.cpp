#include <iostream>
#include<string>
#include <map>
#include <format>
#include "Console.hpp"
void NoNonLands(int lands) {
    Console::ChangeForeGroundColor(RED, true);
    Console::AddTextModifiers(FBLNK);
    Console::Println("NO NON-LAND CARDS USE THE MENU TO ADD SOME");
    Console::AddTextModifiers(NOBLINK);
    Console::Println("nonland to land ratio : 0 ");
    Console::Println(std::format("Lands : {}",lands));
    Console::Println(std::format("Non-Lands : 0"));
    Console::AddTextModifiers(RESET);
}
void AddCardPrompt(int &cmc, int &amount ) {
    Console::Println("enter the card's Converted casting cost");

    Console::ClearLine();
    std::cin >> cmc;

    Console::Println("enter the amount of that card ");
    Console::ClearLine();
    std::cin >> amount;
}
void PrintActions() {
    Console::Println("--menu--"); 
    Console::Println("[a]dd nonland"); 
    Console::Println("[r]emove a nonland"); 
    Console::Println("add a [l]and"); 
    Console::Println("remove a [L]and"); 
    Console::Println("[R]eset the program"); 
    Console::Println("e[x]it");
    Console::Println("--------"); 
}
void PrintDeckStats(int lands, int nonLands, int TotalCmc) {
    Console::Print("--Deck Stats--\nTotal Number of cards = ");
    if (lands + nonLands < 60) {
        Console::ChangeForeGroundColor(YELLOW);
        Console::AddTextModifiers(OLINE);
        Console::AddTextModifiers(UNDERLINE);

    }
    Console::Println(std::format("{}", lands + nonLands));
    Console::AddTextModifiers(RESET);
    if (nonLands > 0) {
        Console::Print("average cmc =");
        double acmc = (double)(TotalCmc) / (double)(nonLands);
        if (acmc < 3.5) {
            Console::ChangeForeGroundColor(GREEN, true);
        }
        if (acmc >= 3.5) {
            Console::ChangeForeGroundColor(YELLOW);
        }
        if (acmc >= 4) {
            Console::ChangeForeGroundColor(RED);

        }
        Console::Println(std::format("{}", acmc));
        Console::AddTextModifiers(RESET);
        Console::Print("nonland to land ratio : ");
        double nltol = (double)(nonLands) / (double)(lands);
        if (nltol >= 3 || nltol < 1) {
            Console::ChangeForeGroundColor(RED, true);

        }
        if (nltol < 2) {
            Console::ChangeForeGroundColor(YELLOW);
        }
        if (nltol > 2 && nltol < 3) {
            Console::ChangeForeGroundColor(GREEN);

        }
        Console::Println(std::format("{}", nltol)); 
        Console::AddTextModifiers(RESET);
        Console::Println(std::format("Lands : {}", lands)); 
        Console::Println(std::format("non-Lands : {}", nonLands)); 
    }
    else {
        NoNonLands(lands);
    }
    

}
constexpr int MAX_ROWS = 30;

int main()
{
    std::cout << R"(Copyright(C) 2023 Skeleton_craft 
This program comes with ABSOLUTELY NO WARRANTY
        )"; 
    int lands = 24, nonLands = 0, TotalCmc = 0;
    char command = 0;
    std::map<unsigned, unsigned> cmcs = {};
    for (int x = 1; x <= 10; ++x) cmcs[x] = 0; 
    while (command != 'x') {
        PrintDeckStats(lands, nonLands, TotalCmc);
        PrintActions();
       
        Console::ClearLine();
        std::cin >> command;
       if (command == 'a') {
            int cmc = 0;
            int amount = 0;
            AddCardPrompt(cmc, amount); 
            TotalCmc += (cmc * amount);
            nonLands += amount; 
            cmcs[cmc] += amount; 
        }
        if (command == 'r') {
            int cmc = 0;
            int amount = 0;
            AddCardPrompt(cmc, amount); 
            TotalCmc -= (cmc * amount);
            nonLands -= amount;
            cmcs[cmc] -= amount;
            /*Console::MoveCursorDown(50); 
            Console::Print(std::format("removing {} cards from slot {} cmcs {}\r", amount, cmc, cmcs[cmc]));
            Console::MoveCursorUp(50);*/

        }
        if (command == 'R') {
            lands = 24; 
            TotalCmc = 0; 
            nonLands = 0;
            cmcs = {}; 
            for (int x = 1; x <= 10; ++x) cmcs[x] = 0;
            Console::MoveCursorDown(4); 
            
        }
        if (command == 'l') {
            ++lands;
            Console::MoveCursorDown(4);
        }
        if (command == 'L') {
            --lands; 
            Console::MoveCursorDown(4);
        }
        std::cout << " "; 
        for (auto const& [key, val] : cmcs)
        {
            Console::MoveCursorDown(MAX_ROWS + 2);
            Console::Print(std::format("{}", key));
            Console::MoveCursorBack(1);
            Console::MoveCursorUp();
            Console::Print("-");
            Console::MoveCursorUp();
            for (int x = 1; x <= MAX_ROWS; ++x) {
                if(x <= val){ 
                    Console::MoveCursorBack(1);
                    Console::Print("#");
                }
                else {
                    Console::MoveCursorBack(1);
                    Console::Print(" "); 
                }
                    Console::MoveCursorUp();
            }
            //Console::MoveCursorUp(MAX_ROWS - val);
            Console::MoveCursorForward(2);
        }
        //Console::ClearScreen();
        Console::Return(0, 0); 

        
    }
}
