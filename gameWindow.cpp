#include "gameWindow.h"
#include "ui_gamewindow.h"
#include "game.h"

//int counter = 0;

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    connect(ui->toolBar, SIGNAL( actionTriggered(QAction*)), this, SLOT(toolBarAction(QAction*)));
    ui->boardView->viewport()->installEventFilter(this);
    setWindowTitle("Warcaby");

    scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(Qt::gray);
    ui->boardView->setScene(scene);
    ui->boardView->show();

    scene->installEventFilter(this);

    QSettings settings("MySoft", "Star Runner");
    settings.setValue("blackPawn", QColor(Qt::black));
    settings.setValue("whitePawn", QColor(Qt::white));

    game = new Game(scene);
}

GameWindow::~GameWindow()
{
    delete ui;
    delete game;
    delete scene;
}

/*
void GameWindow::on_actionNowa_gra_triggered()
{
    std::cout << "new game" << std::endl;
    newGame();
}
*/
void GameWindow::toolBarAction(QAction* action)
{
    QString name = action->objectName();
    std::string current_locale_text = name.toLocal8Bit().constData();
    std::cout << current_locale_text << std::endl;
    if(name == "actionNowa_gra")
        newGame();
    else
    if(name == "actionUstawienia")
    {
        SettingsWidget* window = new SettingsWidget();
        window->setWindowTitle("Ustawienia");
        window->show();
    }
}

void GameWindow::newGame()
{
    //QString name = action->objectName();
    //std::string current_locale_text = name.toLocal8Bit().constData();
    //std::cout << current_locale_text << std::endl;
    delete game;
    delete scene;
    scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(Qt::gray);
    ui->boardView->setScene(scene);
    game = new Game(scene);
}
/*
void GameWindow::mousePressEvent(QMouseEvent *event)
{
    //std::cout << event->pos().x() << " " << event->pos().y() << std::endl;
}
*/
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
        if(game->getGameOverFlag())
        {
            QMessageBox msgBox;
            msgBox.setText("Gra skończona");
            msgBox.setInformativeText("Czy chcesz zagrać jeszcze raz?");
            msgBox.setStandardButtons(QMessageBox::Yes| QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::Yes);
            msgBox.setButtonText(QMessageBox::Yes, tr("Tak"));
            msgBox.setButtonText(QMessageBox::No, tr("Nie"));
            QSpacerItem* horizontalSpacer = new QSpacerItem(200, 0, QSizePolicy::Minimum, QSizePolicy::Maximum);
            QGridLayout* layout = (QGridLayout*)msgBox.layout();
            layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
            int ret = msgBox.exec();
            switch (ret) {
              case QMessageBox::Yes:
                  newGame();
                  break;
              case QMessageBox::No:
                  this->close();
                  break;
              default:
                  // should never be reached
                  break;
            }
        }

        ui->boardView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
        return true;
    }
    else
    return QObject::eventFilter(o,e);
}
