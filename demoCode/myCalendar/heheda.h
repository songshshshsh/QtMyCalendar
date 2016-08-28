#ifndef HEHEDA_H
#define HEHEDA_H

#include <QCalendarWidget>
#include <QPen>
#include <QPushButton>
#include <QComboBox>
#include <QDebug>
#include <QPainter>
#include <QListWidget>
#include <QTextEdit>
#include "draglabel.h"
#include <QLineEdit>
#include <QMessageBox>
#include <QWidget>
#include <QtWidgets>
#include "dndlistwidget.h"
#include "colorlisteditor.h"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class Heheda : public QCalendarWidget
{
    Q_OBJECT
public:
    Heheda(QWidget *parent = Q_NULLPTR);
    void setdnd(bool* dndflag);
    void setaf(bool* afflag);

public slots:
    void updateinfo();
    void memochanged();
    void textlistshow(const QDate &date);
    void updatefiles(const QDate& date,const QString piece);

private:
    QString getfilename(QString name);

protected:
    virtual void paintCell(QPainter * painter, const QRect & rect, const QDate & date) const;
public:
    QDate m_currentDate;
    QColor listColor;
    QPen m_outlinePen;
    QBrush m_transparentBrush;

    QVector<QDate> dates;
    QVector<QVector<QString>> normaltodolist;
    QVector<QString> everydaytodolist;
    QVector<QVector<QString>> weeklytodolist;
    QVector<QVector<QString>> monthlytodolist;
    QVector<QColor> colors;
    QComboBox* time;
    QComboBox* options;
    QString memo;
    dndListWidget* textlist;
    QTextEdit* text;
    QLineEdit* select;
    QVector<QVector<QString>> filelist;
    QVector<QVector<QString>> filestring;
    bool* dnd;
    bool* af;
    ColorListEditor* colorbox;

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
};

#endif // HEHEDA_H
