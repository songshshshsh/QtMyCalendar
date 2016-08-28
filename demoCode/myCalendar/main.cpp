#include "mainwindow.h"
#include <QApplication>
#include "ui_mainwindow.h"
#include <QCalendarWidget>
#include <QDebug>
#include <QThread>

#include<QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QDesktopWidget* desktopWidget = QApplication::desktop();
//    QRect screenRect = desktopWidget->screenGeometry();


    //a.installTranslator(&translator);

    MainWindow* m = new MainWindow();
    m->show();


//    QCalendarWidget* tempcalendar = new QCalendarWidget(m);
//    tempcalendar->show();

//    calendar* cale = new calendar();
//    cale->resize(QSize(screenRect.width()/2, screenRect.height()/2));
//    cale->setWindowOpacity(0);
//    cale->show();

//    QCalendarWidget* calendar =  new QCalendarWidget();
//    calendar->show();
//    qDebug()<<QApplication::allWidgets();
//    foreach(QWidget *widget, QApplication::allWidgets())
//        if(widget->inherits("QCalendarView"))
//            qDebug() << widget->geometry();


//    QObject::connect(cale,SIGNAL(activated(const QDate &)),cale,SLOT(addNote(const QDate &)));

    return a.exec();
}
