#include "GameController.h"

int main()
{
    std::unique_ptr<GameController> game(new GameController());
    game->PlayGame();
    return 0;
}