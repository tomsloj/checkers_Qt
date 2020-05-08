#include "pawn.h"

Pawn::Pawn(int x, int y, int size, QColor color, int id)
{
    this->x = x;
    this->y = y;
    this->size = size;
    this->color = color;
    this->id = id;

    ellipse = new QGraphicsEllipseItem(x, y, size, size);
}

Pawn::~Pawn()
{
    delete ellipse;
}
int Pawn::getID()
{
    return id;
}
int Pawn::getX()
{
    return x;
}
int Pawn::getY()
{
    return y;
}
void Pawn::setX(int x)
{
    this->x = x;
}
void Pawn::setY(int y)
{
    this->y = y;
}
void Pawn::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /*= nullptr*/)
{
    QRectF rec = QRectF(x+2,y+2, size-5, size-5);

    QBrush brush(color);
    painter->setPen(color);
    painter->setBrush(color);
    if(color == Qt::black)
        painter->setPen(Qt::white);
    painter->drawEllipse(rec);

}

QRectF Pawn::boundingRect() const
{
    return QRectF(x,y, size, size);
}
