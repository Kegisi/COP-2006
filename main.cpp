
/*
 * Turn-Based Interactive Text Adventure Game with ASCII Graphics
 * For COP 2006
 * Professor Deepa Devasenapathy
 * By Dennis Kerry
 * November 2023
 */

#include <iostream>
#include <conio.h>

#include "constants.h"
#include "graphics.h"

class GameEntity
{
public:
    int x, y;

    GameEntity(int x, int y)
    : x(x)
    , y(y)
    {}

    void Move(char direction)
    {
        if (direction == LEFT)
        {
            x -= 1;
        }
        else if (direction == RIGHT)
        {
            x += 1;
        }
        else if (direction == DOWN)
        {
            y += 1;
        }
        else if (direction == UP)
        {
            y -= 1;
        }

        // make sure the character does not move beyond the borders of the screen
        if (x <= 0)
        {
            x = 1;
        }
        else if (x > SCREEN_WIDTH)
        {
            x = SCREEN_WIDTH;
        }
        else if (y <= 0)
        {
            y = 1;
        }
        else if (y > SCREEN_HEIGHT)
        {
            y = SCREEN_HEIGHT;
        }
    }
};

class Player : public GameEntity
{
public:
    Player(int x, int y) : GameEntity(x, y){}
};

class Orc : public GameEntity
{
public:
    Orc(int x, int y) : GameEntity(x, y){}
};

class Game
{
public:
    int turn_counter = 0;
    bool running = true;

    void UpdateScreen(Player player)
    {
        Screen::Clear();
        for (int y_pos=1; y_pos < SCREEN_HEIGHT+1; y_pos++)
        {
            for (int x_pos=1; x_pos < SCREEN_WIDTH+1; x_pos++)
            {
                if ( ((x_pos) == player.x)  && ((y_pos) == player.y) )
                {
                    std::cout << "@ ";
                }
                else
                {
                    std::cout << ". ";
                }
            }
            std::cout << '\n';
        }
        std::cout << "\nTurn:" << turn_counter << "\n\n";
        turn_counter++;
    }

    void Quit()
    {
        running = false;
        Screen::ShowCursor();
    }
};

int main()
{
    Player _player(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
    Orc orcs[] = {Orc(3,4)};
    Orc *orc = orcs;
    std::cout << "Welcome to the game!\n";
    system("PAUSE");
    Game game;
    Screen::HideCursor();
    game.UpdateScreen(_player);
    while (game.running)
    {
        // Get input
        char input = (char)getch();
        if (input == QUIT)
        {
            game.Quit();
        }
        else
        {
            _player.Move(input);
        }

        game.UpdateScreen(_player);
    }
}
