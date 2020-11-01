#pragma once
#include <cstdlib>
#include <ctime>
#include "board.h"
#include <vector>
class AI {
private:
    char symbol_player;
public:       
    AI();
    AI(char symbol_player);
    ~AI();
    void moveRandom(Board& board);
    void move(Board &board, char x, char y);
    char get_symbol_player();
    std::pair<int,int> evaluate(Board &board);
};