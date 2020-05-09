#include "pawn.h"

Pawn::Pawn(int x, int y, int size, QColor color, int id)
{
    isQueen = false;
    this->x = x;
    this->y = y;
    this->size = size;
    this->color = color;
    this->id = id;

}

Pawn::~Pawn()
{
    //delete ellipse;
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

void Pawn::setQueen()
{
    isQueen = true;
    update();
}

void Pawn::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /*= nullptr*/)
{
    QRectF rec = QRectF(x + size/8,y + size/8, 3*size/4, 3*size/4);

    QBrush brush(color);
    painter->setPen(color);
    painter->setBrush(color);
    if(color == Qt::black)
        painter->setPen(Qt::white);
    painter->drawEllipse(rec);

    if(isQueen)
    {
        int crownWidth = 13*size/27;
        int crownHeight = size/3;
        int x1 = x + size/4;
        int y1 = y+ size/3;
        crown.clear();
        crown.append(QPointF(x1, y1+ crownHeight));
        crown.append(QPointF(x1, y1));
        crown.append(QPointF(x1 + crownWidth/4, y1 + crownHeight/2));
        crown.append(QPointF(x1 + crownWidth/2, y1));
        crown.append(QPointF(x1 + 3*crownWidth/4, y1 + crownHeight/2));
        crown.append(QPointF(x1 + crownWidth, y1));
        crown.append(QPointF(x1 + crownWidth, y1 + crownHeight));
        painter->setPen(QPen(Qt::yellow, 0));
        painter->setBrush(Qt::yellow);
        painter->drawPolygon(crown);
    }

}

QRectF Pawn::boundingRect() const
{
    return QRectF(x,y, size, size);
}
