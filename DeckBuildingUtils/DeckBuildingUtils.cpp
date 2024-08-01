#include <iostream>
#include<string>
#include <map>
#include <format>
#include "../../Skele_lib/Console/Console.hpp"
namespace c = SKC::Console; 
void NoNonLands(c::Console &console, int lands) {
    console.SetFGColor(255,0,0).Blink();
    console.Println("NO NON-LAND CARDS USE THE MENU TO ADD SOME");

    console.NoBlink();
    console.Println("nonland to land ratio : 0 ");
    console.Println(std::format("Lands : {}",lands));
    console.Println(std::format("Non-Lands : 0"));
    console.Reset();
}
void AddCardPrompt(c::Console &console, int &cmc, int &amount ) {
    
    console.Println("enter the card's Converted casting cost");
    std::cin >> cmc;
    console.ClearLine().Up().ClearLine();
    console.Println("enter the amount of that card ");
    //console.ClearLine();
    std::cin >> amount;
    console.Up().ClearLine().Up().ClearLine();
    console.Up().ClearLine().Up().ClearLine();

}
void PrintActions(c::Console &c) {
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
void PrintDeckStats(c::Console &c, int lands, int nonLands, int TotalCmc) {
    c.Print("--Deck Stats--\nTotal Number of cards = ");
    if (lands + nonLands < 60) {
        c.SetFGColor(255,0,0).SetBGColor(255, 128, 128);

    }
    c.Println(std::format("{}", lands + nonLands)).Reset();
    if (nonLands > 0) {
        c.Print("average cmc =");
        double acmc = (double)(TotalCmc) / (double)(nonLands);
        if (acmc < 3.5) {
            c.SetFGColor(128,255,128);
        }
        if (acmc >= 3.5) {
            c.SetFGColor(255,255,0);
        }
        if (acmc >= 4) {
            c.SetFGColor(255,0,0);

        }
        c.Println(std::format("{}", acmc));
        c.Reset();
        c.Print("nonland to land ratio : ");
        double nltol = (double)(nonLands) / (double)(lands);
        if (nltol >= 3 || nltol < 1) {
            c.SetFGColor(128,255,128);
        }
        if (nltol < 2) {
            c.SetFGColor(128,128,0);
        }
        if (nltol > 2 && nltol < 3) {
            c.SetFGColor(0,255,0);

        }
        c.Println(std::format("{}", nltol)); 
        c.Reset();
        c.Println(std::format("Lands : {}", lands)); 
        c.Println(std::format("non-Lands : {}", nonLands)); 
    }
    else {
        NoNonLands(c, lands);
    }
    

}
constexpr int MAX_ROWS = 30;

int main()
{
    
    SKC::Console::Console c{}; 
    int lands = 24, nonLands = 0, TotalCmc = 0;
    char command = 0;
    std::map<unsigned, unsigned> cmcs = {};
    for (int x = 1; x <= 10; ++x) cmcs[x] = 0; 
    while (command != 'x') {
        PrintDeckStats(c, lands, nonLands, TotalCmc);
        PrintActions(c);
       
        c.ClearLine();
        std::cin >> command;
       if (command == 'a') {
            int cmc = 0;
            int amount = 0;
            AddCardPrompt(c, cmc, amount); 
            TotalCmc += (cmc * amount);
            nonLands += amount; 
            cmcs[cmc] += amount; 
        }
        if (command == 'r') {
            int cmc = 0;
            int amount = 0;
            AddCardPrompt(c, cmc, amount); 
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

        for (auto const& [key, val] : cmcs)
        {
            c.Down(MAX_ROWS + 2);
            c.Print(std::format("{}", key));
            c.Left(1);
            c.Up();
            c.Print("-");
            c.Up();
            for (int x = 1; x <= MAX_ROWS; ++x) {
                if(x <= val){ 
                    c.Left(1);
                    c.Print("#");
                }
                else {
                    c.Left(1);
                    c.Print(" "); 
                }
                    c.Up();
            }
            //c.Up(MAX_ROWS - val);
            c.Right(2);
        }
        //c.ClearScreen();
        c.Move(1, 1); 
        PrintDeckStats(c, lands, nonLands, TotalCmc);

        std::cin.ignore();
        c.Clear();
        
    }
}
