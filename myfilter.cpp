#include "myfilter.h"

bool MyFilter::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        std::cout << mouseEvent->pos().x() << " " << mouseEvent-> pos().y()<< "mouse Event" << std::endl;
        return true;

    }
    else
    if(event->type() == QEvent::Resize)
    {
        //this->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    }

    else
    {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}
