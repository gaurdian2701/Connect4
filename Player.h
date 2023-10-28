#pragma once

#include <iostream>
#include <memory>
#include <limits>

class Player
{
private:
    int playerNumber;
    char colorArray[2];

    void InitializeColorArray()
    {
        colorArray[0] = 'R';
        colorArray[1] = 'B';
    }

public:
    Player(int player) : playerNumber(player)
    {
        InitializeColorArray();
        std::cout << "Player " << GetPlayerNumber() << "(" << GetCheckerColor() << ")"
                  << " is ready.\n";
    }

    ~Player()
    {
        std::cout << "Player " << GetPlayerNumber() << "(" << GetCheckerColor() << ")" << " has left the game.\n";
    }

    int GetPlayerNumber()
    {
        return playerNumber;
    }

    char GetCheckerColor()
    {
        return colorArray[playerNumber-1];
    }

    int GetColumnInput()
    {
        int col;
        if(std::cin >> col)
            return col;

        return -1;
    }
};