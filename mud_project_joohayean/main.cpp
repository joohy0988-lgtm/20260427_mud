#include "Game.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand((unsigned int)time(nullptr));

    Game game;
    game.run();

    return 0;
}