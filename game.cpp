#include "game.h"

Game::Game(QGraphicsScene *scene)
{
    board = new MyBoard(scene);
    maxID = 0;
    whitePawnsCounter = 0;
    blackPawnsCounter = 0;
    for( int i = 0; i < BOARD_SIZE; ++i )
        for( int j = 0; j < BOARD_SIZE; ++j )
            if( (i + j) % 2 == 1 )
            {
                if( i < BOARD_SIZE/2 - 1 )
                {
                    fields[i][j] = WHITE;
                    addWhitePawn(i,j);
                    ++whitePawnsCounter;
                }
                else
                if(i > BOARD_SIZE / 2 )
                {
                    fields[i][j] = BLACK;
                    addBlackPawn(i,j);
                    ++blackPawnsCounter;
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
    whiteTourn = true;
    beatingFlag = false;
}

Game::~Game()
{
    delete board;
}

void Game::squareClicked(int x, int y)
{
    std::cout << x << " " << y <<std::endl;
    std::pair<int, int> square = board->getSquarePos(x, y);
    //tura bialych
    if(whiteTourn)
    {
        //jesli jestesmy podczas bicia
        if(beatingFlag)
        {
            if(beat(checked, square))
            {
                board->changeColor(checked);
                isChecked = false;
                //sprawdzam czy kolejne bicie jest mozliwe
                if(beatingIsPossible(square))
                {
                    beatingFlag = true;
                    board->changeColor(square);
                    isChecked = true;
                    checked = square;
                }
                else
                {
                    changeTourn();
                    beatingFlag = false;
                }
                return;
            }
        }
        else
        {
            //nic nie bylo zaznaczone, zaznaczamy pole
            if(!isChecked && (fields[square.first][square.second] == WHITE || fields[square.first][square.second] == WHITE_QUEEN))
            {
                isChecked = true;
                checked = square;
                board->changeColor(square);
            }
            //odznaczamy pole
            else
            if(isChecked && checked == square)
            {
                isChecked = false;
                board->changeColor(square);
            }
            //zaznaczamy inne pole
            else
            if( (fields[square.first][square.second] == WHITE || fields[square.first][square.second] == WHITE_QUEEN) )
            {
                board->changeColor(checked);
                checked = square;
                board->changeColor(square);
            }
            //probujemy wykonac ruch
            else
            if(fields[square.first][square.second] == EMPTY)
            {
                if( move(checked, square) )
                {
                    board->changeColor(checked);
                    isChecked = false;
                    changeTourn();
                    return;
                }
                else
                if(beat(checked, square))
                {
                    board->changeColor(checked);
                    isChecked = false;
                    //sprawdzam czy kolejne bicie jest mozliwe
                    if(beatingIsPossible(square))
                    {
                        beatingFlag = true;
                        board->changeColor(square);
                        isChecked = true;
                        checked = square;
                    }
                    else
                    {
                        changeTourn();
                        beatingFlag = false;
                    }
                    return;
                }
            }
        }

    }
    //tura czarnych
    else
    {
        if(beatingFlag)
        {
            if(beat(checked, square))
            {
                board->changeColor(checked);
                isChecked = false;
                //sprawdzam czy kolejne bicie jest mozliwe
                if(beatingIsPossible(square))
                {
                    beatingFlag = true;
                    board->changeColor(square);
                    isChecked = true;
                    checked = square;
                }
                else
                {
                    changeTourn();
                    beatingFlag = false;
                }
                return;
            }
        }
        else
        {
            //nic nie bylo zaznaczone, zaznaczamy pole
            if(!isChecked && (fields[square.first][square.second] == BLACK || fields[square.first][square.second] == BLACK_QUEEN))
            {
                isChecked = true;
                checked = square;
                board->changeColor(square);
            }
            //odznaczamy pole
            else
            if(isChecked && checked == square)
            {
                isChecked = false;
                board->changeColor(square);
            }
            //zaznaczamy inne pole
            else
            if( (fields[square.first][square.second] == BLACK || fields[square.first][square.second] == BLACK_QUEEN) )
            {
                board->changeColor(checked);
                checked = square;
                board->changeColor(square);
            }
            //probujemy wykonac ruch
            else
            if(fields[square.first][square.second] == EMPTY)
            {
                if( move(checked, square) )
                {
                    board->changeColor(checked);
                    isChecked = false;
                    changeTourn();
                    return;
                }
                else
                if(beat(checked, square))
                {
                    board->changeColor(checked);
                    isChecked = false;
                    //sprawdzam czy kolejne bicie jest mozliwe
                    if(beatingIsPossible(square))
                    {
                        beatingFlag = true;
                        board->changeColor(square);
                        isChecked = true;
                        checked = square;
                    }
                    else
                    {
                        changeTourn();
                        beatingFlag = false;
                    }
                    return;
                }
            }
        }
    }
}

bool Game::moveIsPossible(std::pair<int, int> from)
{
    //TODO uwzglednic kierunek ruchu (tylko do przodu)
    //zwykly pionek bialy
     if( fields[from.first][from.second] == WHITE )
     {
         if( fields[from.first + 1][from.second + 1] == EMPTY ||
         fields[from.first - 1][from.second + 1] == EMPTY )
         {

             return true;
         }
     }
     else
     if( fields[from.first][from.second] == BLACK )
     {
        if( fields[from.first + 1][from.second - 1] == EMPTY ||
                fields[from.first - 1][from.second - 1] == EMPTY )
        {
            return true;
        }
     }
     //TODO damka
     else
     {

     }
     return false;
 }

bool Game::beatingIsPossible(std::pair<int, int> from)
{
    //czarny pionek
    if( fields[from.first][from.second] == BLACK )
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
    //pionek bialy
    else
    if( fields[from.first][from.second] == WHITE )
    {
        if( (from.first < BOARD_SIZE - 2 ) && (from.second < BOARD_SIZE - 2 ) )
        {
             if( fields[from.first + 1][from.second + 1] == BLACK && fields[from.first + 2][from.second + 2] == EMPTY )
                 return true;
             else
             if( fields[from.first + 1][from.second + 1] == BLACK_QUEEN && fields[from.first + 2][from.second + 2] == EMPTY )
                 return true;
        }
        if( (from.first < BOARD_SIZE - 2 ) && (from.second > 1 ) )
        {
             if( fields[from.first + 1][from.second - 1] == BLACK && fields[from.first + 2][from.second - 2] == EMPTY )
                 return true;
             else
             if( fields[from.first + 1][from.second - 1] == BLACK_QUEEN && fields[from.first + 2][from.second - 2] == EMPTY )
                 return true;
        }
        if( (from.first > 1 ) && (from.second < BOARD_SIZE - 2 ) )
        {
             if( fields[from.first - 1][from.second + 1] == BLACK && fields[from.first - 2][from.second + 2] == EMPTY )
                 return true;
             else
             if( fields[from.first - 1][from.second + 1] == BLACK_QUEEN && fields[from.first - 2][from.second + 2] == EMPTY )
                 return true;
        }
        if( (from.first > 1 ) && (from.second > 1 ) )
        {
             if( fields[from.first - 1][from.second - 1] == BLACK && fields[from.first - 2][from.second - 2] == EMPTY )
                 return true;
             else
             if( fields[from.first - 1][from.second - 1] == BLACK_QUEEN && fields[from.first - 2][from.second - 2] == EMPTY )
                 return true;
        }
        return false;
    }

    //TODO damki

    return false;
}

bool Game::move(std::pair<int, int> from, std::pair<int, int> to)
{
    if(fields[to.first][to.second] != EMPTY)
        return false;
    int x1 = from.first;
    int y1 = from.second;
    int x2 = to.first;
    int y2 = to.second;

    //zwykly pionek
    if( fields[x1][y1] == BLACK || fields[x1][y1] == WHITE )
    {
        if( abs(x1-x2) == 1 && abs(y1-y2) == 1)
        {
            //sprawdzamy czy ruch jest wykonany do przodu
            if(fields[x1][y1] == BLACK && x1 < x2 )
                   return false;
            if(fields[x1][y1] == WHITE && x1 > x2 )
                   return false;
            fields[x2][y2] = fields[x1][y1];
            fields[x1][y1] = EMPTY;
            move(x1, y1, x2, y2);
            board->updateField(from.first, from.second);
            return true;
        }
        return false;
    }

    /*
    //zwykly pionek
    if( fields[from.first][from.second] == BLACK || fields[from.first][from.second] == WHITE )
    {
        if( from.first + 1 == to.first && from.second + 1 == to.second )
        {
            fields[to.first][to.second] = fields[from.first][from.second];
            fields[from.first][from.second] = EMPTY;
            move(from.first, from.second, to.first, to.second);
            return true;
        }
        else
        if(from.first + 1 == to.first && from.second - 1 == to.second)
        {
            fields[to.first][to.second] = fields[from.first][from.second];
            fields[from.first][from.second] = EMPTY;
            move(from.first, from.second, to.first, to.second);
            return true;
        }
        else
        if(from.first - 1 == to.first && from.second + 1 == to.second)
        {
            fields[to.first][to.second] = fields[from.first][from.second];
            fields[from.first][from.second] = EMPTY;
            move(from.first, from.second, to.first, to.second);
            return true;
        }
        else
        if(from.first - 1 == to.first && from.second - 1 == to.second)
        {
            fields[to.first][to.second] = fields[from.first][from.second];
            fields[from.first][from.second] = EMPTY;
            move(from.first, from.second, to.first, to.second);
            return true;
        }
    }

    return false;
    */
}

bool Game::beat(std::pair<int, int> from, std::pair<int, int> to)
{
    if(fields[to.first][to.second] != EMPTY)
        return false;

    //czarny pionek
    if( fields[from.first][from.second] == BLACK )
    {
        int x1 = from.first;
        int y1 = from.second;
        int x2;
        int y2;
        int x3 = to.first;
        int y3 = to.second;
        x2 = (x1+x3)/2;
        y2 = (y1+y3)/2;

        if( abs(x1-x3) == 2 && abs(y1-y3) == 2 && (fields[x2][y2] == WHITE || fields[x2][y2] == WHITE_QUEEN))
        {
            fields[x3][y3] = fields[x1][y1];
            fields[x1][y1] = EMPTY;
            move(x1, y1, x3, y3);
            removePawn(x2, y2);
            return true;
        }
        return false;
    }
    //bialy pionek
    else
    if( fields[from.first][from.second] == WHITE )
    {
        int x1 = from.first;
        int y1 = from.second;
        int x2;
        int y2;
        int x3 = to.first;
        int y3 = to.second;
        x2 = (x1+x3)/2;
        y2 = (y1+y3)/2;

        if( abs(x1-x3) == 2 && abs(y1-y3) == 2 && (fields[x2][y2] == BLACK || fields[x2][y2] == BLACK_QUEEN))
        {
            fields[x3][y3] = fields[x1][y1];
            fields[x1][y1] = EMPTY;
            move(x1, y1, x3, y3);
            removePawn(x2, y2);
            return true;
        }
        return false;
    }
    //TODO damki
    return false;
}

void Game::move(int x1, int y1, int x2, int y2)
{
    int id = board->getPawnID(x1, y1);
    board->move(x2, y2, id);
}

void Game::addBlackPawn(int x, int y)
{
    board->addBlackPawn(x, y, maxID);
    pawns.push_back(maxID);
    ++maxID;
}

void Game::addWhitePawn(int x, int y)
{
    board->addWhitePawn(x, y, maxID);
    pawns.push_back(maxID);
    ++maxID;
}

void Game::addBlackQueen(int x, int y)
{

}

void Game::addWhiteQueen(int x, int y)
{

}
void Game::removePawn(int x, int y)
{
    int id = board->getPawnID(x,y);
    for (std::vector<int>::iterator it = pawns.begin(); it != pawns.end(); ++it)
    {
        if(*it==id)
        {
            pawns.erase(it);
            if( fields[x][y] == BLACK || fields[x][y] == BLACK_QUEEN )
                --blackPawnsCounter;
            else
            if( fields[x][y] == WHITE || fields[x][y] == WHITE_QUEEN )
                --whitePawnsCounter;
            fields[x][y]=EMPTY;
            break;
        }
    }
    board->removePawn(id);
}


void Game::changeTourn()
{
    whiteTourn = !whiteTourn;
    if(isGameOver())
    {
        std::cout << "GAME OVER" <<std::endl;
    }
}

bool Game::isGameOver()
{
    if(whiteTourn)
    {
        if(whitePawnsCounter == 0)
            return true;
    }
    else
    {
        if(blackPawnsCounter == 0)
            return true;
    }
    for( int i = 0; i < 8; ++i )
        for( int j = 0; j < 8; ++j )
        {
            if(whiteTourn)
            {
                if( fields[i][j] == WHITE || fields[i][j] == WHITE_QUEEN )
                {
                    if( moveIsPossible(std::make_pair(i, j)))
                        return false;
                    else
                    if( beatingIsPossible(std::make_pair(i, j)));
                        return false;
                }
            }
            else
            {
                if( fields[i][j] == BLACK || fields[i][j] == BLACK_QUEEN )
                {
                    if( moveIsPossible(std::make_pair(i, j)))
                        return false;
                    else
                    if( beatingIsPossible(std::make_pair(i, j)));
                        return false;
                }
            }
        }
    return false;
}
