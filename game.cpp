#include "game.h"

Game::Game(QGraphicsScene *scene)
{
    board = new MyBoard(scene);
    for( int i = 0; i < BOARD_SIZE; ++i )
        for( int j = 0; j < BOARD_SIZE; ++j )
            if( (i + j) % 2 == 1 )
            {
                if( i < BOARD_SIZE/2 - 1 )
                {
                    fields[i][j] = WHITE;
                }
                else
                if(i > BOARD_SIZE / 2 )
                {
                    fields[i][j] = BLACK;
                }
                else
                {
                    fields[i][j] = EMPTY;
                }
            }
            else
            {
                fields[i][j] = BLOCKED;
            }
    isChecked = false;
}

Game::~Game()
{
    delete board;
}

void Game::squareClicked(int x, int y)
{
    std::pair<int, int> square = board->getSquarePos(x, y);
    if(!isChecked)
    {
        isChecked = true;
        checked = square;
        board->changeColor(square);
    }
    else
    if(checked == square)
    {
        isChecked = false;
        board->changeColor(square);
    }
    else
    if(fields[square.first][square.second] != EMPTY && fields[square.first][square.second] != BLOCKED )
    {
        board->changeColor(checked);
        checked = square;
        board->changeColor(square);
    }
    else
    if(fields[square.first][square.second] == EMPTY)
    {
        if( moveIsPossible(checked, square) )
        {

        }
        else
        if(beatingIsPossible(checked, square))
        {

        }
    }
}

bool Game::moveIsPossible(std::pair<int, int> from, std::pair<int, int> to)
 {
     if( (from.first + 1 == to.first && from.second + 1 == to.second) ||
         (from.first + 1 == to.first && from.second - 1 == to.second) ||
         (from.first - 1 == to.first && from.second + 1 == to.second) ||
         (from.first - 1 == to.first && from.second - 1 == to.second) )
     {
         return true;
     }
     return false;
 }

bool Game::beatingIsPossible(std::pair<int, int> from, std::pair<int, int> to)
{
    //czarny pionek
    if( fields[from.first + 1][from.second + 1] == BLACK )
    {
        if( (from.first < BOARD_SIZE - 2 ) && (from.second < BOARD_SIZE - 2 ) )
        {
             if( fields[from.first + 1][from.second + 1] == WHITE && fields[from.first + 2][from.second + 2] == EMPTY )
                 return true;
             else
             if( fields[from.first + 1][from.second + 1] == WHITE_QUEEN && fields[from.first + 2][from.second + 2] == EMPTY )
                 return true;
        }
        if( (from.first < BOARD_SIZE - 2 ) && (from.second > 1 ) )
        {
             if( fields[from.first + 1][from.second - 1] == WHITE && fields[from.first + 2][from.second - 2] == EMPTY )
                 return true;
             else
             if( fields[from.first + 1][from.second - 1] == WHITE_QUEEN && fields[from.first + 2][from.second - 2] == EMPTY )
                 return true;
        }
        if( (from.first > 1 ) && (from.second < BOARD_SIZE - 2 ) )
        {
             if( fields[from.first - 1][from.second + 1] == WHITE && fields[from.first - 2][from.second + 2] == EMPTY )
                 return true;
             else
             if( fields[from.first - 1][from.second + 1] == WHITE_QUEEN && fields[from.first - 2][from.second + 2] == EMPTY )
                 return true;
        }
        if( (from.first > 1 ) && (from.second > 1 ) )
        {
             if( fields[from.first - 1][from.second - 1] == WHITE && fields[from.first - 2][from.second - 2] == EMPTY )
                 return true;
             else
             if( fields[from.first - 1][from.second - 1] == WHITE_QUEEN && fields[from.first - 2][from.second - 2] == EMPTY )
                 return true;
        }
        return false;
    }

}

