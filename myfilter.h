#ifndef MYFILTER_H
#define MYFILTER_H

#include <QObject>
#include <QEvent>
#include <QMouseEvent>

#include <iostream>

class MyFilter : public QObject
{
public:
    QObject *keyObj;
    QObject *mouseObj;
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // MYFILTER_H
