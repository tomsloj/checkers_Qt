#ifndef MYBOARD_H
#define MYBOARD_H

#include "square.h"

#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include <iostream>


class MyBoard
{
public:
    MyBoard(QGraphicsScene *scene);
    ~MyBoard();
    void squareClicked(int x, int y);
    std::pair<int, int>getSquarePos(int x, int y);
    void changeColor(std::pair<int, int>);
protected:
    //void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int size;

    Square *squares[8][8];
    Square* getSquare(int x, int y);
    Square* choosenSquare;
};

#endif // MYBOARD_H
