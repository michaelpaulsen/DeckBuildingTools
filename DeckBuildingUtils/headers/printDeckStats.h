#pragma once
#include "../../../Skele_lib/Console/Console.hpp"
#include "math.hpp"
namespace SKC {

    void PrintDeckStats(Console::Console& c, int lands, int nonLands, int TotalCmc) {
        c.Print("--Deck Stats--\nTotal Number of cards = ");
        int totalCards = lands + nonLands; 
        if (totalCards < 60) {
            c.SetFGColor(255, 0, 0).SetBGColor(255, 128, 128);
        }
        c.Println( lands + nonLands).Reset();
        if (nonLands == 0) {
            NoNonLands(c, lands);
            return;
        }
        c.Print("average cmc =");
        double acmc = (double)(TotalCmc) / (double)(nonLands);
        int targetLands = acmc + 1;
        if (acmc < 3.5) {
            c.SetFGColor(128, 255, 128);
        }
        if (acmc >= 3.5) {
            c.SetFGColor(255, 255, 0);
        }
        if (acmc >= 4) {
            c.SetFGColor(255, 0, 0);

        }
        c.Println(acmc, "( ", targetLands, " lands target )").Reset();
        c.Print("nonland to land ratio : ");
        double nltol = (double)(nonLands) / (double)(lands);
        if (nltol >= 3 || nltol < 1) {
            c.SetFGColor(128, 255, 128);
        }
        if (nltol < 2) {
            c.SetFGColor(128, 128, 0);
        }
        if (nltol > 2 && nltol < 3) {
            c.SetFGColor(0, 255, 0);

        }
        c.Println(nltol).Reset();
        c.Println("Lands : ", lands);
        c.Println("non-Lands :", nonLands);
        c.Println("chances of ", targetLands, " by turn ", targetLands);
        auto [less, exact, more] = hypergeometricChance(totalCards, lands, 7 + targetLands, targetLands); 
        c.Print("less ", floor(less * 10000) / 100);
        c.Print(" exact ", floor(exact * 10000) / 100);
        c.Println(" more ", floor(more * 10000) / 100);
    }
}