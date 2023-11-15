//
// Created by Dennis Kerry on 11/14/2023.
//

#ifndef FINAL_GRAPHICS_H
#define FINAL_GRAPHICS_H
#include <iostream>
#include <cstdlib>

struct Screen
{
public:
    static void HideCursor()
    {
        std::cout << "\\033[?25l";
    }

    static void ShowCursor()
    {
        std::cout << "\\033[?25h";
    }

    static void Clear()
    {
        system("CLS");
    }

};

#endif //FINAL_GRAPHICS_H
