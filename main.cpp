#include "board.h"
#include "branchingfactor.h"
#include "ai.h"
#include "node.h"
#include <list>
#include <memory>

#define depth 2
#define wsp_rozgalezienia 2
int current_depth = 0;
char player_symbol = 'A';
int available_moves = 0;
int moves = 0;

int check_game(Board &board, AI &ai)
{
    int result;
    if ((result = board.is_win()) == 1)
    {
        std::cout << "AI_" << ai.get_symbol_player() << " won" << std::endl;
        return 1;
    }
    else if (result == 2)
    {
        std::cout << "Draw" << std::endl;
        return 2;
    }
    return 0;
}

#define check_game_macro(board, ai)                                   \
    {                                                                 \
        if (check_game(board, ai) == 1 || check_game(board, ai) == 2) \
        {                                                             \
            board.clear_board();                                      \
            break;                                                    \
        }                                                             \
    }
 
void zad1()
{
    Board d(10, 10);
    BranchingFactor bf;
    AI AI_first('A');
    AI AI_second('B');

    bf.gamesToPlay = 1000;

    for (int i = 0; i < bf.gamesToPlay; i++)
    {
        while (1)
        {
            int totalMoveCount = d.available_moves();
            AI_first.moveRandom(d);
            bf.moves++;
            bf.sumOfPossibleMoves += totalMoveCount;
            check_game_macro(d, AI_first);

            totalMoveCount = d.available_moves();
            AI_second.moveRandom(d);
            bf.moves++;
            bf.sumOfPossibleMoves += totalMoveCount;
            check_game_macro(d, AI_second);

            bf.avgPossibleMoves = bf.sumOfPossibleMoves / bf.moves;
            bf.totalMoves += bf.moves;
            bf.totalAvgPossibleMoves += bf.avgPossibleMoves;
        }
    }

    std::cout << "\n========================================\nGAMES PLAYED: " << bf.gamesToPlay << "\n========================================\nDEPTH (AVG MOVES PER GAME): " << bf.totalMoves / (double)bf.gamesToPlay / 100000 << "\n========================================\nBRANCHING FACTOR (AVG AVAILABLE MOVES): " << bf.totalAvgPossibleMoves / (double)bf.gamesToPlay / bf.gamesToPlay << "\n========================================\n";
    std::cout << "GAME COMPLEXITY: " << bf.totalAvgPossibleMoves / (double)bf.gamesToPlay / bf.gamesToPlay << "^" << bf.totalMoves / (double)bf.gamesToPlay << "\n========================================\n\n";
}

int minimax(int c_depth, Node &tree)
{

    if (c_depth > depth)
        return 0;
    for (int i = 0; i < wsp_rozgalezienia; i++)
    {
        std::unique_ptr<Node> node(new Node());
        node->g_State->make_copy(tree.g_State->get_size(), tree.g_State->board_address(), tree.g_State->whose_turn);

        AI test(player_symbol);
        std::pair<int, int> predicted_move = test.evaluate(*node->g_State);
        test.move(*node->g_State.get(),predicted_move.first, predicted_move.second);
        node->g_State->draw_board();

        minimax(c_depth + 1, *node);
    }
}

int main()
{   
    // Zad 1 złożoność
    zad1();


    // Zad 2 simple minimax
    //     O
    //    /  \ 
    //   O    O
    //  / \   /\
    // O  O  O  O

    std::cout << "\n Minimax:" << std::endl;
    Board d(10, 10);
    AI ai_1('A');
    AI ai_2('B');

    ai_1.moveRandom(d);
    std::unique_ptr<Node> root(new Node());
    root->g_State->make_copy(std::pair<int,int>(10,10),d.board_address(), d.whose_turn);
    minimax(1, *root);
   
    return 0;
}