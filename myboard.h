#ifndef MYBOARD_H
#define MYBOARD_H

#include "square.h"
#include "pawn.h"

#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include <iostream>
#include <vector>


class MyBoard
{
public:
    MyBoard(QGraphicsScene *scene);
    ~MyBoard();
    void squareClicked(int x, int y);
    std::pair<int, int>getSquarePos(int x, int y);
    void changeColor(std::pair<int, int>);

    void move(int x, int y, int id);
    void addBlackPawn(int x, int y, int id);
    void addWhitePawn(int x, int y, int id);
    void changeToQueen(int x, int y);
    void removePawn(int id);

    int getPawnID(int x, int y);

    void updateField(int x, int y);

protected:
    //void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int size;

    Square *squares[8][8];
    Square* getSquare(int x, int y);
    Square* choosenSquare;

    std::vector< Pawn* >pawns;
    QGraphicsScene *scene;
};

#endif // MYBOARD_H
