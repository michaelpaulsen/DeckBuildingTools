#pragma once
#include "../../../Skele_lib/Console/Console.hpp"
namespace SKC {
    void NoNonLands(Console::Console& console, int lands) {
        console.SetFGColor(255, 0, 0).Blink();
        console.Println("NO NON-LAND CARDS USE THE MENU TO ADD SOME");

        console.NoBlink();
        console.Println("nonland to land ratio : 0 ");
        console.Println("Lands : ", lands);
        console.Println("Non-Lands : 0");
        console.Reset();

    }
    void AddCardPrompt(Console::Console& console, int& cmc, int& amount) {
        console.Println("enter the card's Converted casting cost");
        std::cin >> cmc;
        console.Println("enter the amount of that card ");
        //console.ClearLine();
        std::cin >> amount;
        console.Up().ClearLine().Up().ClearLine();
        console.Up().ClearLine().Up().ClearLine();
    }

}