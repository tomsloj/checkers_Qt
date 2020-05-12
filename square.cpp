#include "square.h"

Square::Square(QColor color, int x, int y, int size /*= 20*/)
{
    this->color = color;
    if(color == Qt::white)
        toUse = false;
    else
        toUse = true;
    this->x = x;
    this->y = y;
    this->size = size;
}

void Square::uncheck()
{
    color = Qt::black;
    update();
}
void Square::check()
{
    color = Qt::red;
    update();
}

QColor Square::getColor()
{
    return color;
}

bool Square::isAvaliable()
{
    return toUse;
}

void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /*= nullptr*/)
{
    QRectF rec = boundingRect();
    //int wid = rec.size().width();
    //int hei = rec.size().height();

    QBrush brush(color);
    painter->setPen(color);
    painter->fillRect(rec, brush);
    painter->drawRect(rec);
    this->setZValue(-1);

}

QRectF Square::boundingRect() const
{
    return QRectF(x,y, size, size);
}

bool Square::isEmpty()
{
    //TODO sprawdzenie czy ma dziecko
    return true;
}
