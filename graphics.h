//
// Created by Dennis Kerry on 11/14/2023.
//

#ifndef FINAL_GRAPHICS_H
#define FINAL_GRAPHICS_H
#include <iostream>
#include <cstdlib>
#include <Windows.h>

struct Screen
{
public:
    static void HideCursor()
    {
        HANDLE hStdOut = NULL;
        CONSOLE_CURSOR_INFO curInfo;

        hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleCursorInfo(hStdOut, &curInfo);
        curInfo.bVisible = FALSE;
        SetConsoleCursorInfo(hStdOut, &curInfo);

    }

    static void ShowCursor()
    {
        HANDLE hStdOut = NULL;
        CONSOLE_CURSOR_INFO curInfo;

        hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleCursorInfo(hStdOut, &curInfo);
        curInfo.bVisible = TRUE;
        SetConsoleCursorInfo(hStdOut, &curInfo);

    }

    static void Clear()
    {
        std::cout << "\033[0;0H";  // moves cursor to origin to overwrite
    }

};

#endif //FINAL_GRAPHICS_H
