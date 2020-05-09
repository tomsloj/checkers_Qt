#ifndef PAWN_H
#define PAWN_H

#include <QColor>
#include <QGraphicsItem>
#include <QPainter>

class Pawn : public QGraphicsRectItem
{
public:
    Pawn(int x, int y, int size, QColor color, int id);
    ~Pawn();


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    int getID();
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    void setQueen();
private:
   // QGraphicsEllipseItem *ellipse;
    QPolygonF crown;

    QColor color;
    int x;
    int y;
    int size;
    int id;

    bool isQueen;
};

#endif // PAWN_H
