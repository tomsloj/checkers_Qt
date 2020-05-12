#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QAction>
#include <QMessageBox>

#include <iostream>
#include <algorithm>

#include "game.h"
#include "settingswidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow(); 

private slots:
    void toolBarAction(QAction* action);
    //void resizeEvent(QResizeEvent *event);
    //void mousePressEvent(QMouseEvent *event);
    bool eventFilter(QObject*o,QEvent*e);

private:
    Ui::GameWindow *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *rect;
    QGraphicsRectItem *rect1;
    Game *game;

    int wid;
    int hei;

    void newGame();

};
#endif // GAMEWINDOW_H
