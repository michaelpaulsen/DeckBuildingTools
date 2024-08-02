#pragma once
#include "../../../Skele_lib/Console/Console.hpp"

namespace SKC {

    void PrintDeckStats(Console::Console& c, int lands, int nonLands, int TotalCmc) {
        c.Print("--Deck Stats--\nTotal Number of cards = ");
        if (lands + nonLands < 60) {
            c.SetFGColor(255, 0, 0).SetBGColor(255, 128, 128);

        }
        c.Println(std::format("{}", lands + nonLands)).Reset();
        if (nonLands == 0) {
            NoNonLands(c, lands);
            return;
        }
        c.Print("average cmc =");
        double acmc = (double)(TotalCmc) / (double)(nonLands);
        if (acmc < 3.5) {
            c.SetFGColor(128, 255, 128);
        }
        if (acmc >= 3.5) {
            c.SetFGColor(255, 255, 0);
        }
        if (acmc >= 4) {
            c.SetFGColor(255, 0, 0);

        }
        c.Println(acmc, "( ", (int)acmc + 1, " target )");
        c.Reset();
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
        c.Println(std::format("{}", nltol));
        c.Reset();
        c.Println(std::format("Lands : {}", lands));
        c.Println(std::format("non-Lands : {}", nonLands));
    }
}