#include "pawn.h"

Pawn::Pawn(int x, int y, int size, QColor color, int id)
{
    isQueen = false;
    this->x = x;
    this->y = y;
    this->size = size;
    this->color = color;
    this->id = id;
    setZValue(10);
}
Pawn::Pawn(Pawn &pawn)
{
    crown = pawn.crown;
    color = pawn.color;
    x = pawn.x;
    y = pawn.y;
    size = pawn.size;
    id = pawn.id;
    isQueen = pawn.isQueen;
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

QPoint Pawn::pos()
{
    return QPoint(x,y);
}

void Pawn::setPos(QPoint p)
{
    setX(p.x());
    setY(p.y());
    update();
}


void Pawn::setQueen()
{
    isQueen = true;
    update();
}

void Pawn::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /*= nullptr*/)
{
    QRectF rec = QRectF(x + size/8,y + size/8, 3*size/4, 3*size/4);

    QColor color;
    if( this->color == Qt::black )
    {
        QSettings settings("MySoft", "Star Runner");

        color = settings.value("blackPawn", QColor(Qt::black)).value<QColor>();
    }
    else
    {
        QSettings settings("MySoft", "Star Runner");

        color = settings.value("whitePawn", QColor(Qt::black)).value<QColor>();
    }

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
        painter->setPen(QPen(Qt::black, 0.3));
        painter->setBrush(QColor("#ffeb3b"));
        painter->drawPolygon(crown);
    }

}

QRectF Pawn::boundingRect() const
{
    return QRectF(x,y, size, size);
}
/*
QRectF Pawn::geometry()
{
    return boundingRect();
}
void setGeometry(const QRect & geometry)
{

}
*/
void Pawn::changeOpacity(qreal opacity)
{
    setOpacity(opacity);
    setZValue(10);
    prepareGeometryChange();
    emit updateOpacity();
}
