#include "tool.h"

Tool::Tool()
{

}

Tool::~Tool()
{

}

bool Tool::handleEvent(QEvent *event){
    qDebug("tool handleEvent");
//    if (event->type() == QEvent::KeyPress) {
//        QKeyEvent *ke = reinterpret_cast<QKeyEvent *>(event);
//        keyPress(ke);
//        return true;
//    } else if (event->type() == QEvent::MouseButtonPress) {
//        QMouseEvent *me = reinterpret_cast<QMouseEvent *>(event);
//        mousePress(me);
//    } else if (event->type() == QEvent::MouseMove) {
//        QMouseEvent *me = reinterpret_cast<QMouseEvent *>(event);
//        mouseMove(me);
//    } else if (event->type() == QEvent::MouseButtonRelease) {
//        QMouseEvent *me = reinterpret_cast<QMouseEvent *>(event);
//        mouseRelease(me);
//    }

    return true;
}
