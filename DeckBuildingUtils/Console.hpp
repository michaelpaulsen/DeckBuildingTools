    //Console.hpp
    //Copyright (C) 2023  Skeleton_craft 
    
    //This program is free software: you can redistribute it and/or modify
    //it under the terms of the GNU General Public License as published by
    //the Free Software Foundation, either version 3 of the License, or
    //(at your option) any later version.

    //This program is distributed in the hope that it will be useful,
    //but WITHOUT ANY WARRANTY; without even the implied warranty of
    //MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    //GNU General Public License for more details.

    //You should have received a copy of the GNU General Public License
    //along with this program.  If not, see <https://www.gnu.org/licenses/>.
#pragma once
#include <string>
#include <iostream>
#include<string>
#include <map>
#include <format>

enum Modifier {
    RESET,
    BOLD,
    FAINT,
    ITALIC,
    UNDERLINE,
    SBLNK,
    FBLNK,
    INVERT,
    HIDE,
    CROSSED,
    PRMFNT,
    ALTFNT1,
    ALTFNT2,
    ALTFNT3,
    ALTFNT4,
    ALTFNT5,
    ALTFNT6,
    ALTFNT7,
    ALTFNT8,
    ALTFNT9,
    GOTH,
    DULNB,
    NORMINTS,
    NOITA,
    NOULINE,
    NOBLINK,
    PROPSPC,
    REVER,
    REV,
    NOCROSS,
    NOPROPSPC = 50,
    FRM,
    ENC,
    OLINE,
    NOEMOJI,
    NOOLINE,
    UCLR = 58,
    DUCLR
};
enum Color {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
};
struct Console {

    static int ClearLine() {
        return std::printf("%c[K ", ESC);

    }
    static void Print(std::string text) {
        std::cout << text;
    }
    static void Println(std::string text) {
        ClearLine();
        std::cout << text << '\n';
    }
    static auto Return(int x, int y) {
        return printf("%c[%d;%dH ", ESC, x, y);

    }
    static auto SaveCursorPostition() {
        return printf("%c[s", ESC);
    }
    static auto RestoreCursorPosition() {
        return printf("%c[u", ESC);

    }
    static auto ChangeForeGroundColor(Color c, bool bright = false) {
        return printf("%c[%dm", ESC, ToAnsiColor(c, bright));
    }
    static auto ChangeBackGroundColor(Color c, bool bright = false) {
        return printf("%c[%dm", ESC, ToAnsiColor(c, bright) + 10);
    }
    static auto AddTextModifiers(Modifier mod) {
        return printf("%c[%dm", ESC, mod);

    }
    static auto Ring() {
        return printf("%c", 7);
    }
    static void Warn(std::string msg, int blink = 0) {
        ChangeForeGroundColor(YELLOW);
        PrintSpecMsg(msg, blink);
    }
    static void OKAY(std::string msg, int blink = 0) {
        ChangeForeGroundColor(GREEN, true);
        PrintSpecMsg(msg, blink);
    }
    static int MoveCursorDown(int n = 1) {
        return printf("%c[%dB", ESC, n);
    }
    static int MoveCursorUp(int n = 1) {
        return printf("%c[%dA", ESC, n);
    }
    static int MoveCursorBack(int n = 1) {
        return printf("%c[%dD", ESC, n);
    }
    static int MoveCursorForward(int n = 1) {
        return printf("%c[%dC", ESC, n);
    }
    static int ClearScreen() {
        return printf("%c[2J", ESC);
    }

private:
    static void PrintSpecMsg(std::string msg, int blink) {
        AddTextModifiers(UNDERLINE);
        if (blink == 1) {
            AddTextModifiers(SBLNK);
        }
        if (blink == 2) {
            AddTextModifiers(FBLNK);

        }
        std::cout << msg;
        AddTextModifiers(RESET);
    }
    static const char ESC = 0x1b;
    static int ToAnsiColor(Color c, bool bright) {
        return ((int(c) + 30) + bright * 60);
    }
};
