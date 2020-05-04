#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "myfilter.h"
#include "game.h"

//int counter = 0;

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    ui->boardView->viewport()->installEventFilter(this);

    scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(Qt::gray);
    //scene->setSceneRect(-1.25, -1.25, 2.5, 2.5);
    ui->boardView->setScene(scene);
    ui->boardView->show();

    scene->installEventFilter(this);

    game = new Game(scene);
}

GameWindow::~GameWindow()
{
    delete ui;
    delete game;
    delete scene;
}


void GameWindow::on_actionNowa_gra_triggered()
{
    //ui->boardView->setBackgroundBrush(Qt::red);
}

void GameWindow::resizeEvent(QResizeEvent *event)
{

}

void GameWindow::mousePressEvent(QMouseEvent *event)
{
    //std::cout << event->pos().x() << " " << event->pos().y() << std::endl;
}

bool GameWindow::eventFilter(QObject *o,QEvent *e)
{
    if(e->type()==QEvent::Resize)
    {
        ui->boardView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
        std::cout << "resize" << std::endl;
        return true;
        //lubreturnfalse;
    }
    else
    if(e->type()==QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(e);
        int x = ui->boardView->mapToScene(mouseEvent->pos()).x();
        int y = ui->boardView->mapToScene(mouseEvent->pos()).y();
        int square = std::min(scene->width(),scene->height());
        //std::cout << x << " " << y << " " << " " << square << std::endl;
        //std::cout << ui->boardView->mapToScene(mouseEvent->pos()).x() << " " << ui->boardView->mapToScene(mouseEvent->pos()).y()<< "mouse Event" << std::endl;


        if(x >= 0 && y >= 0 && x <= square && y <= square )
        {
            //std::cout << "click " << counter << std::endl;
            //++counter;
            game->squareClicked(x, y);

        }



        return true;
    }
    else
    return QObject::eventFilter(o,e);
}
