
/*
 * Turn-Based Interactive Text Adventure Game with ASCII Graphics
 * For COP 2006
 * Professor Deepa Devasenapathy
 * By Dennis Kerry
 * November 2023
 */

#include <iostream>
#include <conio.h>  // library that allows me to take user input without the need to hit space

#include "constants.h"
#include "graphics.h"

class GameEntity
{
public:
    int x, y;
    char symbol;

    GameEntity(int x, int y, char symbol)
    : x(x)
    , y(y)
    , symbol(symbol)
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

    void Kill()
    {
        x = 0;
        y = 0;
    }

    bool Colliding(GameEntity entity) const
    {
        if ( (x == entity.x) && (y == entity.y) )
        {
            return true;
        }
        return false;
    }

    int GetX() const
    {
        return x;
    }

    int GetY() const
    {
        return y;
    }

    char GetSymbol() const
    {
        return symbol;
    }
};

class Player : public GameEntity
{
public:
    Player(int x, int y, char symbol) : GameEntity(x, y, symbol)
    {}
};

class Orc : public GameEntity
{
public:
    Orc(int x, int y, char symbol) : GameEntity(x, y, symbol)
    {}
};

struct Game
{
    int turn_counter = 0;
    bool running = true;
    int stage = 0;  // 0: title slide, 1: orc fight, 2: note, 3: forest, 4: pre-boss, 5: boss fight, 6: end slide

    void UpdateScreen(GameEntity *entity)
    {
        bool space_occupied;
        Screen::Clear();
        for (int y_pos=1; y_pos < SCREEN_HEIGHT+1; y_pos++)
        {
            for (int x_pos=1; x_pos < SCREEN_WIDTH+1; x_pos++)
            {
                space_occupied = false;
                for (int i=0; i<4; i++)
                {
                    if ( (x_pos == (entity+i)->GetX()) && (y_pos == (entity+i)->GetY()) )
                    {
                        std::cout << (entity+i)->GetSymbol() << ' ';
                        space_occupied = true;
                        break;
                    }
                }
                if (!space_occupied)
                {
                    std::cout << ". ";
                }
            }
            std::cout << '\n';
        }
        std::cout << "\nTurn:" << turn_counter << "\n\n";
        turn_counter++;
    }

    void ManageStage(GameEntity *entity)
    {
        switch (stage)
        {
            case 0:  // First Orc Fight
            case 2:  // Second Orc Fight in forest
            case 4:  // Boss fight
                UpdateScreen(entity);
                for (int i=1; i<4; i++)  // delete orcs if the player touches them
                {
                    if (entity[i].Colliding(entity[0]))
                    {
                        entity[i].Kill();
                    }
                }
                if (entity[0].x == SCREEN_WIDTH-1)
                {
                    stage++;
                }
                break;
            case 1:  // Lore
                std::cout << "lore\n";
                system("PAUSE");
                system("cls");
                Screen::Clear();
                stage++;
                entity[0].x = 2;
                break;
            case 3:  // Pre-boss
                std::cout << "You gotta kill boss etc\n";
                system("PAUSE");
                system("cls");
                stage++;
                entity[0].x = 2;
                break;
            case 5:  // Game Over
                std::cout << "Game Over\n";
                Game::Quit();
        }
    }

    void Quit()
    {
        running = false;
        Screen::ShowCursor();
    }
};

int main()
{
    Player player(2, SCREEN_HEIGHT/2, PLAYER_SYMBOL);
    Player *_player;
    _player = &player;

    GameEntity entities[] = {*_player,
                             Orc((SCREEN_WIDTH*2/3),SCREEN_HEIGHT/2, ORC_SYMBOL),
                             Orc((SCREEN_WIDTH/2),SCREEN_HEIGHT*3/4, ORC_SYMBOL),
                             Orc((SCREEN_WIDTH/5),SCREEN_HEIGHT/3, ORC_SYMBOL)};

    Game game;
    std::cout << "Welcome to the game!\n\n";
    std::cout << "----------------------------------------------------------------------------------------";
    std::cout << "\nYou are a knight charged with finding and retrieving the princess of The Kingdom who \n"
                 "was kidnapped by Orcs! The court wizard found them to have taken her to the East. You \n"
                 "depart from the gates and your quest suddenly begins as you come face to face with some \n"
                 "bloodthirsty orcs...\n";
    std::cout << "\nYour sword can only slay 3 orcs before breaking, after which, you are vulnerable! Your\n"
                 " goal is to continue eastward until you find the princess! Good luck...\n";
    std::cout << "----------------------------------------------------------------------------------------\n\n";

    system("PAUSE");
    system("cls");
    Screen::Clear();
    Screen::HideCursor();
    game.UpdateScreen(entities);
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
            entities[0].Move(input);
        }

        game.ManageStage(entities);
    }
}
