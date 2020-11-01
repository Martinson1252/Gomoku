#include "AI.h"

// ============================
static long holdrand = 1L;

void srand(unsigned int seed)
{
    srand(time(NULL));
    holdrand = (long)seed;
}

int rand()
{
    return (((holdrand = holdrand * 214013L + 2531011L) >> 16) & 0x7fff);
}
// ============================

AI::AI(char player)
{
    this->symbol_player = player;
}

std::pair<int, int> AI::evaluate(Board &board)
{
    char player = board.whose_turn;

    std::pair<int, int> b_size = board.get_size();
    std::pair<int, int> predicted_move;
    std::pair<int, int> temporary_good_move(-1, -1);
    std::vector<std::pair<int, int>> good_moves;

    for (int col = 0; col < b_size.first; col++)
        for (int row = 0; row < b_size.second; row++)
        {

            int win = 0;
            if (board.get_cell(col, row) == player)
            {

                for (int i = 1; i < 5; i++)
                {
                    if (board.check(col + i, row + i, player) || board.is_move_valid(col + i, row + i))
                    {
                        if (board.is_move_valid(col + i, row + i))
                            good_moves.push_back(std::pair<int, int>(col + i, row + i));
                        win++;
                    }
                }
            }
            if (win == 4)
                return good_moves[0];
        }

    good_moves.clear();

    for (int col = 0; col < b_size.first; col++)
        for (int row = 0; row < b_size.second; row++)
        {
            int win = 0;
            if (board.get_cell(col, row) == player)
            {
                for (int i = 0; i < 5; i++)
                {
          
                    if (board.check(col + i, row, player) || board.is_move_valid(col + i, row))
                    {
                        if (board.is_move_valid(col + i, row))
                        {
                            good_moves.push_back(std::pair<int, int>(col + i, row));
                            win++;
                        }
                    }
                }
            }
            if (win == 4)
                return good_moves[0];
        }

    good_moves.clear();

    for (int col = 0; col < b_size.first; col++)
        for (int row = 0; row < b_size.second; row++)
        {
            int win = 0;
            if (board.get_cell(col, row) == player)
            {

                for (int i = 0; i < 5; i++)
                {

                    if (board.check(col, row + i, player) || board.is_move_valid(col, row + i))
                    {
                        if (board.is_move_valid(col, row + i))
                        {
                            good_moves.push_back(std::pair<int, int>(col, row + i));
                            win++;
                        }
                    }
                }
            }
            if (win == 4)
                return good_moves[0];
        }

    good_moves.clear();

    std::pair<int, int> board_size = board.get_size();
    int x = rand() % board_size.first;
    int y = rand() % board_size.second;

    while (1)
    {
        int x = rand() % board_size.first;
        int y = rand() % board_size.second;
        if (board.get_cell(x, y) == ' ')
        {
            return std::pair<int, int>(x, y);
        }
    }
}

void AI::moveRandom(Board &board)
{
    std::pair<int, int> board_size = board.get_size();

    while (1)
    {
        int x = rand() % board_size.first;
        int y = rand() % board_size.second;
        if (board.get_cell(x, y) == ' ')
        {
            board.set_position(x, y);
            break;
        }
    }
}

void AI::move(Board &board, char x, char y)
{
    if (board.get_cell(x, y) == ' ')
    {
        board.set_position(x, y);
    }
}

char AI::get_symbol_player()
{
    return this->symbol_player;
}

AI::~AI()
{
}
