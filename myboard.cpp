#include "myboard.h"

MyBoard::MyBoard(QGraphicsScene *scene)
{
    choosenSquare = nullptr;
    size = 20;

    for( int i = 0; i < 8; ++i )
        for( int j = 0; j < 8; ++j )
            if( (i + j) % 2 == 1 )
            {
                squares[i][j] = new Square(Qt::black, i * size, j*size, size);
                scene->addItem(squares[i][j]);
            }
            else
            {
                squares[i][j] = new Square(Qt::white, i * size, j*size, size);
                scene->addItem(squares[i][j]);
            }
}
MyBoard::~MyBoard()
{
    for( int i = 0; i < 8; ++i )
        for( int j = 0; j < 8; ++j )
            delete squares[i][j];
}

void MyBoard::squareClicked(int x, int y)
{
    Square* s = getSquare(x, y);

    if(!s->isAvaliable())
       return;

    if(choosenSquare != nullptr && choosenSquare != s)
    {
        choosenSquare->changeColor();
        choosenSquare->update();
    }



    if(s->getColor() != Qt::white)
        s->changeColor();

    if(s->getColor()==Qt::black)
        choosenSquare = nullptr;
    else
        choosenSquare = s;

    s->update();
}
void MyBoard::changeColor(std::pair<int, int> p)
{
    squares[p.first][p.second]->changeColor();
}
/*
 void MyBoard::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr )
 {
     QRectF rec = boundingRect();
     int x = rec.size().width();
     int y = rec.size().height();
     std::cout << x << " " << y << std::endl;
     int square = x/8;
     QBrush brush(Qt::green);
     painter->fillRect(rec, brush);
     painter->drawRect(rec);

     for( int i = 0; i < 8; ++i )
         for( int j = 0; j < 8; ++j )
         {
             brush.setColor(squares[i][j]->getColor());
             QRectF r(i*square, j*square, square, square);
             painter->fillRect(r, brush);
             painter->drawRect(r);
         }
 }

QRectF MyBoard::boundingRect() const
{
    return QRectF(0,0,160, 160);
}


 void MyBoard::mousePressEvent(QGraphicsSceneMouseEvent *event)
 {
     std::cout << event->pos().x() << " " << event->pos().y() << std::endl;
     update();
     QGraphicsItem::mousePressEvent(event);

     Square* s = getSquare(event->pos().x(), event->pos().y());

     if(!s->isAvaliable())
        return;

     if(choosenSquare != nullptr && choosenSquare != s)
     {
         choosenSquare->changeColor();
     }



     if(s->getColor() != Qt::white)
         s->changeColor();

     if(s->getColor()==Qt::black)
         choosenSquare = nullptr;
     else
         choosenSquare = s;

 }
*/
 Square* MyBoard::getSquare(int x, int y)
 {
     int square = size;

     int i = x/square;
     int j = y/square;

     return squares[i][j];
 }
 std::pair<int, int> MyBoard::getSquarePos(int x, int y)
 {
     int i = x/size;
     int j = y/size;

     return std::make_pair(i, j);
 }
