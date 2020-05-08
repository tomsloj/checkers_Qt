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

#include <iostream>
#include <algorithm>

#include "game.h"


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
    void newGame();
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    bool eventFilter(QObject*o,QEvent*e);

    void on_actionNowa_gra_triggered();

private:
    Ui::GameWindow *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *rect;
    QGraphicsRectItem *rect1;
    Game *game;

    int wid;
    int hei;

};
#endif // GAMEWINDOW_H
