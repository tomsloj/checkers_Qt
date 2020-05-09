#include "gameWindow.h"
#include "ui_gamewindow.h"
#include "myfilter.h"
#include "game.h"

//int counter = 0;

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    connect(ui->toolBar, SIGNAL(triggered()), this, SLOT(newGame()));
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
    newGame();
}
void GameWindow::newGame()
{
    //ui->boardView->setBackgroundBrush(Qt::red);
    delete game;
    delete scene;
    scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(Qt::gray);
    ui->boardView->setScene(scene);
    game = new Game(scene);
}
/*
void GameWindow::resizeEvent(QResizeEvent *event)
{
}
*/

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
    }
    else
    if(e->type()==QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(e);
        int x = ui->boardView->mapToScene(mouseEvent->pos()).x();
        int y = ui->boardView->mapToScene(mouseEvent->pos()).y();
        int square = std::min(scene->width(),scene->height());


        if(x >= 0 && y >= 0 && x <= square && y <= square )
        {
            game->squareClicked(x, y);

        }


        ui->boardView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
        return true;
    }
    else
    return QObject::eventFilter(o,e);
}
