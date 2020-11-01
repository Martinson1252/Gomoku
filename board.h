#pragma once
#include <iostream>
#include <string.h>
#include <cstdlib>

class Board {
private:
    int height;
    int width;
    char *board;  
    std::pair<char, char> players_symbols;   
public:             
    Board();
    Board(int width, int height);
    ~Board();
    std::pair<int,int> get_size();
    void draw_board();
    void clear_board();
    int set_position(int row, int col);
    bool is_move_valid(int row, int col);
    char get_move();
    int is_win();
    bool no_available_moves();
    int available_moves();
    char& operator[](std::pair<int, int> p);
    char get_cell(int col, int row);
    Board (const Board &board);
    Board& operator=(const Board& board);
    void make_copy(std::pair<int,int> size, void* board, char whose_turn);
    void* board_address();
    bool check(int col, int row, char piece);
    char whose_turn;
};