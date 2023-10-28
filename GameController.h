#include "Player.h"

class GameController
{
private:
    int rows;
    int cols;
    int currentRow;
    int currentColumn;
    int fillcount;
    char gameMatrix[6][7] = {};
    char winner = ' ';

    void InitializeMatrix()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                gameMatrix[i][j] = ' ';
            }
        }
    }

    void DisplayMatrix()
    {
        std::cout << "---------------\n";

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                std::cout << "|" << gameMatrix[i][j];
            }
            std::cout << "|\n---------------\n";
        }
    }

    int FillColumn(char c, int col)
    {
        for (int i = 0; i < rows; i++)
            if ((gameMatrix[i + 1][col] != ' ' || i == rows - 1) && gameMatrix[i][col] == ' ')
            {
                gameMatrix[i][col] = c;
                currentRow = i;
                return 1;
            }

        return 0;
    }

    int InsertChecker(char c, int colNumber)
    {
        if (colNumber <= 0 || colNumber > cols)
        {
            std::cout << "Invalid column number! Enter again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return 0;
        }

        if (!FillColumn(c, colNumber-1))
        {
            std::cout << "Column is Full! Select another column.\n";
            return 0;
        }

        DisplayMatrix();
        return colNumber;
    }

    void GetPlayerInput(std::unique_ptr<Player> &p)
    {
        std::cout << "Player " << p->GetPlayerNumber() << "(" << p->GetCheckerColor() << "), insert column number\n";
        while (!(currentColumn = InsertChecker(p->GetCheckerColor(), p->GetColumnInput())));
        currentColumn -= 1;
        fillcount++;
    }

    bool CheckForFours(std::unique_ptr<Player> &p, int i, int j, int checkerMatch, int direction)
    {
        if (checkerMatch == 4)
            return true;

        if (gameMatrix[i][j] != p->GetCheckerColor() || i > rows || j > cols || i < 0 || j < 0)
            return false;

        switch (direction)
        {
        case 1: // Right Horizontal
            return CheckForFours(p, i, j + 1, checkerMatch + 1, direction);
            break;

        case 2: // Left Horizontal
            return CheckForFours(p, i, j - 1, checkerMatch + 1, direction);
            break;

        case 3: // Bottom Vertical
            return CheckForFours(p, i + 1, j, checkerMatch + 1, direction);
            break;

        case 4: // Upper Diagonal Right
            return CheckForFours(p, i - 1, j + 1, checkerMatch + 1, direction);
            break;

        case 5: // Upper Diagonal Left
            return CheckForFours(p, i - 1, j - 1, checkerMatch + 1, direction);
            break;

        case 6: // Lower Diagonal Left
            return CheckForFours(p, i + 1, j - 1, checkerMatch + 1, direction);
            break;

        case 7: // Lower Diagonal Right
            return CheckForFours(p, i + 1, j + 1, checkerMatch + 1, direction);
            break;

        default:
            std::cout << "Error with Pattern case check\n\n";
            break;
        }

        return false;
    }

    bool CheckForPlayerPattern(std::unique_ptr<Player> &p)
    {
        for (int i = 1; i < 8; i++)
            if(CheckForFours(p, currentRow, currentColumn, 0, i))
            {
                winner = p->GetCheckerColor();
                return true;
            }
        return false;
    }

    bool TakeTurn(std::unique_ptr<Player> &p)
    {
        GetPlayerInput(p);
        return !CheckForPlayerPattern(p);
    }

    bool CheckForFullMatrix()
    {
        return fillcount >= cols*rows ? true : false;
    }

    void InitiateGameLoop(std::unique_ptr<Player> &p1, std::unique_ptr<Player> &p2)
    {
        while (TakeTurn(p1) && TakeTurn(p2))
        {
            if(CheckForFullMatrix())
            {
                std::cout << "The game is a tie!\n";
                break;
            }
        }

        std::cout << "The winner is: Player " << winner << "\n\n";
    }

public:
    GameController()
    {
        std::cout << "The Game has started!\n";
        rows = 6;
        cols = 7;
        fillcount = 0;
        InitializeMatrix();
        DisplayMatrix();
    }

    void PlayGame()
    {
        std::unique_ptr<Player> p1(new Player(1));
        std::unique_ptr<Player> p2(new Player(2));

        InitiateGameLoop(p1, p2);
    }
};