#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QPen>
#include <QComboBox>
#include <QPushButton>
#include "colorlisteditor.h"


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool dndflag;
    bool afflag;
    bool translated;


public slots:
    void changednd();
    void changeaf();

private slots:
    void on_calendarWidget_activated(const QDate &date);
    void updatecolor(int);
    void setTranslator();
    void translate(int index);

    void on_horizontalSlider_valueChanged(int value);

    void saveinfo();

private:
    Ui::MainWindow *ui;
    QColor getcolor(const QDate& date);

//    void dragEnterEvent(QDragEnterEvent *event);
//    void dragMoveEvent(QDragMoveEvent *event);
//    void dropEvent(QDropEvent *event);
//    void mousePressEvent(QMouseEvent *event);
//    QString getfilename(QString name);
//    void updatefiles(const QDate& date,const QString piece);

};

#endif // MAINWINDOW_H
