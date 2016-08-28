#ifndef DNDLISTWIDGET_H
#define DNDLISTWIDGET_H

#include <QListWidget>
#include "draglabel.h"
#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class dndListWidget: public QListWidget
{
    Q_OBJECT
public:
    dndListWidget(QWidget *parent = Q_NULLPTR);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // DNDLISTWIDGET_H
