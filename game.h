#ifndef GAME_H
#define GAME_H

#include <vector>
#include <QGraphicsScene>

#include "myboard.h"

class Game
{
    enum field{EMPTY, BLOCKED, WHITE, BLACK, WHITE_QUEEN, BLACK_QUEEN};
public:
    Game(QGraphicsScene *scene);
    ~Game();
    std::vector< std::pair<int, int> >getWhitePawns();
    std::vector< std::pair<int, int> >getBlackPawns();

    void squareClicked(int x, int y);
private:
    MyBoard *board;
    field fields[8][8];
    bool isChecked;
    std::pair<int, int> checked;
    std::vector< std::pair<int, int> >whitePawns;
    std::vector< std::pair<int, int> >whiteQueens;
    std::vector< std::pair<int, int> >blackPawns;
    std::vector< std::pair<int, int> >blackQueens;
    std::vector< std::pair<int, int> >emptyPoints;

    bool moveIsPossible(std::pair<int, int> from, std::pair<int, int> to);
    bool beatingIsPossible(std::pair<int, int> from, std::pair<int, int> to);

    const BOARD_SIZE = 8;
};

#endif // GAME_H
