#ifndef DRAGLABEL_H
#define DRAGLABEL_H

#include <QLabel>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDragMoveEvent;
class QFrame;
QT_END_NAMESPACE

//! [0]
class DragLabel : public QLabel
{
public:
    DragLabel(const QString &text, QWidget *parent);
    QString labelText() const;

private:
    QString m_labelText;
};
//! [0]

#endif // DRAGLABEL_H
