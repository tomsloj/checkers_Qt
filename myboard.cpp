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
                squares[i][j]->setZValue(0);
            }
            else
            {
                squares[i][j] = new Square(Qt::white, i * size, j*size, size);
                scene->addItem(squares[i][j]);
                squares[i][j]->setZValue(0);
            }
    this->scene = scene;
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
        choosenSquare->uncheck();
        scene->update();
    }

    if(s->getColor() != Qt::white)
        s->uncheck();

    if(s->getColor()==Qt::black)
        choosenSquare = nullptr;
    else
        choosenSquare = s;
}
void MyBoard::uncheck(std::pair<int, int> p)
{
    squares[p.first][p.second]->uncheck();
}
void MyBoard::check(std::pair<int, int> p)
{
    squares[p.first][p.second]->check();
}

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

 void MyBoard::move(int x, int y, int id)
 {

     for( unsigned int i = 0; i < pawns.size(); ++i )
     {
         if(pawns[i]->getID() == id)
         {

             pawns[i]->setX(x*size);
             pawns[i]->setY(y*size);
             pawns[i]->setZValue(10);
             pawns[i]->update();
             /*
             animationID = i;
             newX = x;
             newY = y;
             //QPropertyAnimation* animation = new QPropertyAnimation(tmpPawn, "opacity");
             animation = new QPropertyAnimation(pawns[i], "opacity");
             animation->setDuration(animationTime);
             animation->setStartValue(1.0);
             animation->setEndValue(0.0);
             QObject::connect(animation, SIGNAL(finished()), SLOT(appearAnimation()));
             animation->start();
            */
             //

             //animation2->setDuration(animationTime);
             //animation2->setStartValue(0.0);
             //animation2->setEndValue(1.0);
             //animation2->start();

             //QParallelAnimationGroup *group = new QParallelAnimationGroup;
             //group->addAnimation(animation);
             //group->addAnimation(animation2);
             //group->start(QAbstractAnimation::DeleteWhenStopped);

         }

     }
 }
/*
 void MyBoard::appearAnimation()
 {
     pawns[animationID]->setX(newX*size);
     pawns[animationID]->setY(newY*size);
     pawns[animationID]->setZValue(10);
     pawns[animationID]->update();
     scene->update();
     animation = new QPropertyAnimation(pawns[animationID], "opacity");
     animation->setDuration(animationTime);
     animation->setStartValue(0.0);
     animation->setEndValue(1.0);
     animation->start();
     //QObject::connect(pawns[animationID], SIGNAL(updateOpacity()), scene, SLOT(update()));
 }

 void MyBoard::changeCoordinates(int x, int y)
 {

 }
 */
 void MyBoard::addBlackPawn(int x, int y, int id)
 {
    Pawn *p = new Pawn(x*size, y*size, size, Qt::black, id);
    pawns.push_back(p);
    scene->addItem(p);
    pawns[pawns.size()-1]->setZValue(1);
 }
 void MyBoard::addWhitePawn(int x, int y, int id)
 {
     pawns.push_back(new Pawn(x*size, y*size, size, Qt::white, id));
     scene->addItem(pawns[pawns.size()-1]);
     pawns[pawns.size()-1]->setZValue(1);
 }
 void MyBoard::changeToQueen(int x, int y)
 {
     x = x * size;
     y = y * size;
     for( unsigned int i = 0; i < pawns.size(); ++i )
     {
         if(pawns[i]->getX() == x && pawns[i]->getY() == y)
         {
             pawns[i]->setQueen();
             break;
         }
     }

 }

 void MyBoard::removePawn(int id)
 {
     for( std::vector<Pawn*>::iterator it = pawns.begin(); it != pawns.end(); ++it )
     {
         if((*it)->getID() == id)
         {
             /*
             animation = new QPropertyAnimation((*it), "opacity");
             animation->setDuration(animationTime * 10);
             animation->setStartValue(1.0);
             animation->setEndValue(0.0);
             QObject::connect(animation, SIGNAL(finished()), SLOT(eraseIterator()));
             animation->start();
             iterator = it;
             */
             Pawn* p = (*it);
             if(p->scene() != NULL)
                scene->removeItem(p);
             (p)->setZValue(-111);
             pawns.erase(it);

             //delete p;

             break;
         }
     }
 }
/*
 void MyBoard::eraseIterator()
 {
     Pawn* p = (*iterator);
     if(p->scene() != NULL)
        scene->removeItem(p);
     (p)->setZValue(-111);
     pawns.erase(iterator);
 }
*/
 int MyBoard::getPawnID(int x, int y)
 {
     x = x * size;
     y = y * size;
     for( unsigned int i = 0; i < pawns.size(); ++i )
     {
         if(pawns[i]->getX() == x && pawns[i]->getY() == y)
               return pawns[i]->getID();
     }
     return -1;
 }
 void MyBoard::updateField(int x, int y)
 {
     squares[x][y]->update();
 }
