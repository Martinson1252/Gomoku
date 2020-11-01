#include "board.h"

Board::Board()
{
    board = NULL;
}

Board::~Board()
{
    delete this->board;
}

std::pair<int, int> Board::get_size()
{
    return std::make_pair(this->width, this->height);
}

Board::Board(int width, int height)
{
    this->width = width;
    this->height = height;
    this->board = (char *)malloc(width * height);
    this->players_symbols.first = 'A';
    this->players_symbols.second = 'B';
    this->whose_turn = this->players_symbols.first;
    memset((void *)this->board, ' ', width * height);
}

void Board::draw_board()
{
    for (int i = 0; i < this->height; i++)
    {
        for (int j = 0; j < this->width; j++)
        {
            std::cout << *(this->board + j + this->width * i) << " | ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void Board::clear_board()
{
    this->whose_turn = 'A';
    memset((void *)this->board, ' ', this->width * this->height);
}

bool Board::is_move_valid(int col, int row)
{
    if((col < this->width && row < this->height)){
    if (*(this->board + col + this->width * row) == ' ')
    {
        return 1;
    }
    }
    return 0;
}

int Board::is_win()
{
    char player = this->whose_turn;
    if (player == 'A')
        player = 'B';
    else
        player = 'A';
            
    for (int col = 0; col < this->width - 5; col++)
        for (int row = 0; row < this->height - 5; row++)
        {
            int win = 0;
            for (int i = 0; i < 5; i++)
                if ((*this)[{row + i, col + i}] == player)
                    win++;

            if (win == 5)
                return 1;
        }

    for (int col = 0; col < this->width - 5; col++)
        for (int row = 0; row < this->height - 5; row++)
        {
            int win = 0;
            for (int i = 0; i < 5; i++)
                if ((*this)[{row, col + i}] == player)
                    win++;

            if (win == 5)
                return 1;
        }

    for (int col = 0; col < this->width - 5; col++)
        for (int row = 0; row < this->height - 5; row++)
        {
            int win = 0;
            for (int i = 0; i < 5; i++)
                if ((*this)[{row + i, col}] == player)
                    win++;

            if (win == 5)
                return 1;
        }

    if (no_available_moves())
    {
        return 2;
    }

    return 0;
}

bool Board::no_available_moves()
{
    int i = 0;
    int j = 0;
    for (i = 0; i < this->height; i++)
    {
        for (j = 1; j < this->width; j++)
        {
            if ((*this)[{i, j}] == ' ')
                return false;
        }
    }

    return true;
}

int Board::available_moves()
{
    int available_moves = 0;
    for (int i = 0 ; i < this->width*this->height;i++)
    {
        if (*(this->board + i )== ' ')
                available_moves++;
    }

    return available_moves;
}

char &Board::operator[](std::pair<int, int> p)
{
    return *(this->board + p.first + p.second * this->width);
}

char Board::get_cell(int col, int row)
{
    return *(this->board + col + row * this->width);
}


bool Board::check(int col, int row, char piece)
{
     if (col < this->width && row < this->height)
    {
        if (*(this->board + col + row * this->width) == piece)
        {
            return true;
        }
    }
    return false;
}

Board::Board(const Board &board)
{
    this->width = board.width;
    this->height = board.height;

    this->board = (char *)malloc(this->width * this->height);

    memcpy(this->board, board.board, this->width * this->height);
}

void Board::make_copy(std::pair<int, int> size, void *board, char whose_turn)
{
    this->width = size.first;
    this->height = size.second;
    this->board = (char *)malloc(this->width * this->height);
    this->whose_turn = whose_turn;
    memcpy(this->board, board, this->width * this->height);
}

void *Board::board_address()
{
    return (void *)this->board;
}

Board &Board::operator=(const Board &board)
{
    this->width = board.width;
    this->height = board.width;
    this->board = board.board;
    this->whose_turn = board.whose_turn;
    return *this;
}

int Board::set_position(int col, int row)
{
    int ret = 0;
    if (is_move_valid(col, row) != 0 && col < this->width && row < this->height)
    {
        char whoseTurn = this->whose_turn;
        if (whoseTurn == 'A')
            this->whose_turn = 'B';
        else
            this->whose_turn = 'A';

        *(this->board + col + row * this->width) = whoseTurn;
    }

    return ret;
}