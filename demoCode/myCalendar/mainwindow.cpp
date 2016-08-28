#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "draglabel.h"
#include "colorlisteditor.h"

#include <QtWidgets>
#include <QInputDialog>
#include <QComboBox>
#include <QTextCharFormat>
#include <QDebug>
#include <QtGlobal>

#include <cstdio>
#include <fstream>
#include <cstdlib>

const static QString path = "/Users/songshihong/Desktop/Qtsave/";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->enablednd->setText(tr("disable"));
    dndflag = true;
    afflag = true;
    this->ui->calendarWidget->setdnd(&dndflag);
    this->ui->calendarWidget->setaf(&afflag);
    ui->retranslateUi(this);
    ui->adjustorfix->setText(tr("Adjust"));
    setTranslator();
    translated = false;

    QApplication::connect(ui->enablednd,SIGNAL(clicked(bool)),this,SLOT(changednd()));
    QApplication::connect(ui->adjustorfix,SIGNAL(clicked(bool)),this,SLOT(changeaf()));
    QApplication::connect(this,SIGNAL(close()),this,SLOT(saveinfo()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calendarWidget_activated(const QDate &date)
{
    qDebug()<<"come in addNote"<<endl;
    this->ui->calendarWidget->m_currentDate = date;
    this->ui->calendarWidget->textlistshow(date);
    QDialog* input = new QDialog();
    input->setWindowTitle(date.toString());
    input->show();

    this->ui->calendarWidget->listColor = getcolor(date);

    QBrush brush;
    brush.setColor(this->ui->calendarWidget->listColor);

    QTextCharFormat cf = this->ui->calendarWidget->dateTextFormat(date);
    cf.setBackground(brush);
    this->ui->calendarWidget->setDateTextFormat(date, cf);

    this->ui->calendarWidget->time->setParent(input);
    this->ui->calendarWidget->options->setParent(input);

    QLabel* description = new QLabel(tr("Description:"),input);
    this->ui->calendarWidget->text->setParent(input);
    this->ui->calendarWidget->memo = this->ui->calendarWidget->text->toPlainText();
    QVBoxLayout* topLayout = new QVBoxLayout();
    topLayout->addWidget(description);
    topLayout->addWidget(this->ui->calendarWidget->text);

    QHBoxLayout* middleLayout = new QHBoxLayout();
    QPushButton *cancelbutton = new QPushButton(tr("Cancel"),input);
    connect(cancelbutton,SIGNAL(clicked()),input,SLOT(close()));
    qDebug()<<ui->calendarWidget->listColor;
    this->ui->calendarWidget->colorbox->setParent(input);
    middleLayout->addWidget(cancelbutton);
    middleLayout->addWidget(this->ui->calendarWidget->colorbox);

//    int index = -1;
//    for (int i = 0;i < this->ui->calendarWidget->dates.size();++i)
//        if (this->ui->calendarWidget->dates.at(i) == date)
//        {
//            index = i;
//            break;
//        }
//    if (index != -1)
//        this->ui->calendarWidget->listColor = this->ui->calendarWidget->colors.at(index);
//    else this->ui->calendarWidget->listColor = this->ui->calendarWidget->colorbox->color();

    connect(ui->calendarWidget->colorbox,SIGNAL(currentIndexChanged(int)),this,SLOT(updatecolor(int)));
    QVBoxLayout* bottomLayout = new QVBoxLayout();
    QHBoxLayout* optionlayout = new QHBoxLayout();
    QHBoxLayout* timelayout = new QHBoxLayout();
    QLabel* optionlabel = new QLabel(tr("options:"),input);
    optionlayout->addWidget(optionlabel);
    optionlayout->addWidget(this->ui->calendarWidget->options);
    QLabel* timelabel = new QLabel(tr("time:"),input);
    timelayout->addWidget(timelabel);
    timelayout->addWidget(this->ui->calendarWidget->time);
    QPushButton* confirmbutton = new QPushButton(tr("Ok"),input);
    bottomLayout->addLayout(optionlayout);
    bottomLayout->addLayout(timelayout);
    bottomLayout->addWidget(confirmbutton);

    QVBoxLayout* leftLayout = new QVBoxLayout();
    leftLayout->addLayout(topLayout);
    leftLayout->addLayout(middleLayout);
    leftLayout->addLayout(bottomLayout);

    QLabel* list = new QLabel(tr("list:"),input);
    this->ui->calendarWidget->textlist->setParent(input);
    QLabel* selected = new QLabel(tr("Selected:"),input);
    this->ui->calendarWidget->select->setParent(input);
    connect(this->ui->calendarWidget->textlist,SIGNAL(currentTextChanged(QString)),this->ui->calendarWidget->select,SLOT(setText(QString)));

    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->addWidget(list);
    rightLayout->addWidget(this->ui->calendarWidget->textlist);
    rightLayout->addWidget(selected);
    rightLayout->addWidget(this->ui->calendarWidget->select);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    input->setLayout(mainLayout);

    connect(this->ui->calendarWidget->text,SIGNAL(textChanged()),this->ui->calendarWidget,SLOT(memochanged()));

    this->ui->calendarWidget->memo = this->ui->calendarWidget->text->toPlainText();

    connect(confirmbutton,SIGNAL(clicked()),this->ui->calendarWidget,SLOT(updateinfo()));


//    if( !this->ui->calendarWidget->memo.isEmpty() ){
//        QBrush brush;
//        brush.setColor(this->ui->calendarWidget->listColor);

//        QTextCharFormat cf = this->ui->calendarWidget->dateTextFormat(date);
//        cf.setBackground(brush);
//        this->ui->calendarWidget->setDateTextFormat(date, cf);
//        if(this->ui->calendarWidget->dates.contains(date))
//        {
//            int index = this->ui->calendarWidget->dates.indexOf(date);
//            this->ui->calendarWidget->normaltodolist[index].append(this->ui->calendarWidget->memo);
//        }
//        else
//        {
//            this->ui->calendarWidget->dates.append(date);
//            QVector<QString> temp;
//            this->ui->calendarWidget->normaltodolist.append(temp);
//            this->ui->calendarWidget->normaltodolist[this->ui->calendarWidget->dates.size()-1].append(this->ui->calendarWidget->memo);
//        }
//    }
}

void MainWindow::updatecolor(int index)
{
    ui->calendarWidget->listColor = qvariant_cast<QColor>(ui->calendarWidget->colorbox->itemData(ui->calendarWidget->colorbox->currentIndex(), Qt::DecorationRole));
    qDebug() << ui->calendarWidget->listColor;
    return;
}

//void MainWindow::dragEnterEvent(QDragEnterEvent *event)
//{
//    if (!this->ui->calendarWidget->dndflag) return;
//    if (event->mimeData()->hasFormat("application/x-fridgemagnet")) {
//        if (children().contains(event->source())) {
//            event->setDropAction(Qt::MoveAction);
//            event->accept();
//        } else {
//            event->acceptProposedAction();
//        }
//    } else if (event->mimeData()->hasText()) {
//        event->acceptProposedAction();
//    } else {
//        event->ignore();
//    }
//}

//void MainWindow::dragMoveEvent(QDragMoveEvent *event)
//{
//    if (!this->ui->calendarWidget->dndflag) return;
//    if (event->mimeData()->hasFormat("application/x-fridgemagnet")) {
//        if (children().contains(event->source())) {
//            event->setDropAction(Qt::MoveAction);
//            event->accept();
//        } else {
//            event->acceptProposedAction();
//        }
//    } else if (event->mimeData()->hasText()) {
//        event->acceptProposedAction();
//    } else {
//        event->ignore();
//    }
//}

//void MainWindow::dropEvent(QDropEvent *event)
//{
//    if (!this->ui->calendarWidget->dndflag) return;
//    if (event->mimeData()->hasFormat("application/x-fridgemagnet")) {
//        const QMimeData *mime = event->mimeData();
//        QByteArray itemData = mime->data("application/x-fridgemagnet");
//        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

//        QString text;
//        QPoint offset;
//        dataStream >> text >> offset;
//        DragLabel *newLabel = new DragLabel(text, this);
//        newLabel->move(event->pos() - offset);

//        QDate currentday = this->ui->calendarWidget->m_currentDate;
//        //newLabel->show();
//        newLabel->setAttribute(Qt::WA_DeleteOnClose);

//        if (event->source() == this) {
//            event->setDropAction(Qt::MoveAction);
//            event->accept();
//        } else {
//            event->acceptProposedAction();
//        }
//    } else if (event->mimeData()->hasText()) {
//        QStringList pieces = event->mimeData()->text().split(QRegExp("\\s+"),
//                             QString::SkipEmptyParts);
//        QPoint position = event->pos();

//        QDate currentday =  this->ui->calendarWidget->m_currentDate;

//        foreach (QString piece, pieces) {
//            DragLabel *newLabel = new DragLabel(piece, this);
//            newLabel->move(position);
//            //newLabel->show();
//            QString temp = piece.remove("file://");
//            //QFile* file = new QFile(temp);
//            QString newfilename = getfilename(temp);
//            qDebug()<<path+newfilename;
//            qDebug()<<QFile::exists("/Users/songshihong/Desktop/Qtsave");
//            if (!QFile::copy(temp,path + newfilename))
//            {
//                QMessageBox::about(this,"warning","copy failed!");
//                QFile* file = new QFile(temp);
//                file->copy(path+newfilename);
//                qDebug() << file->errorString() << temp;
//            }
//            newLabel->setAttribute(Qt::WA_DeleteOnClose);
//            updatefiles(currentday,newfilename);
//            position += QPoint(newLabel->width(), 0);
//        }

//        event->acceptProposedAction();
//    } else {
//        event->ignore();
//    }
//}

//void MainWindow::mousePressEvent(QMouseEvent *event)
//{
//    if (!this->ui->calendarWidget->dndflag) return;
//    DragLabel *child = static_cast<DragLabel*>(childAt(event->pos()));
//    if (!child)
//        return;

//    QPoint hotSpot = event->pos() - child->pos();

//    QByteArray itemData;
//    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
//    dataStream << child->labelText() << QPoint(hotSpot);

//    QMimeData *mimeData = new QMimeData;
//    mimeData->setData("application/x-fridgemagnet", itemData);
//    mimeData->setText(child->labelText());

//    QDrag *drag = new QDrag(this);
//    drag->setMimeData(mimeData);
//    drag->setPixmap(*child->pixmap());
//    drag->setHotSpot(hotSpot);

//    child->hide();

//    if (drag->exec(Qt::MoveAction | Qt::CopyAction, Qt::CopyAction) == Qt::MoveAction)
//        child->close();
//    else
//        child->show();
//}

//void MainWindow::updatefiles(const QDate& date,const QString piece)
//{
//    if (this->ui->calendarWidget->dates.contains(date))
//    {
//        int index = this->ui->calendarWidget->dates.indexOf(date);
//        this->ui->calendarWidget->filelist[index].append(piece);
//    }
//    else
//    {
//        this->ui->calendarWidget->dates.append(date);
//        this->ui->calendarWidget->colors.append(Qt::white);
//        QVector<QString> temp;
//        this->ui->calendarWidget->filelist.append(temp);
//        this->ui->calendarWidget->normaltodolist.append(temp);
//        this->ui->calendarWidget->filelist[this->ui->calendarWidget->filelist.size()-1].append(piece);
//    }
//    this->ui->calendarWidget->textlistshow(date);
//}


//QString MainWindow::getfilename(QString name)
//{
//    int index = -1;
//    for (int i = name.length()-1;i >= 0;--i)
//        if (name.at(i) == '/')
//        {
//                index = i;
//                break;
//        }
//    qDebug()<<index;
//    if (index != -1)
//        name.remove(0,index+1);
//    return name;
//}

void MainWindow::changednd()
{
    qDebug()<<"dndchanged "<<dndflag;
    if (dndflag)
    {
        dndflag = false;
        ui->enablednd->setText(tr("enable"));
    }
    else
    {
        dndflag = true;
        ui->enablednd->setText(tr("disable"));
    }
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    this->setWindowOpacity((100 - value)*1.0 / 100);
}

void MainWindow::changeaf()
{
    if (ui->adjustorfix->text() == tr("Adjust"))
    {
        ui->adjustorfix->setText(tr("Fix"));
        afflag = true;
        qDebug()<<"get"<<this->windowOpacity();
        if (this->windowOpacity() < 1)
        {
            qDebug()<<"set";
            this->setAttribute(Qt::WA_TransparentForMouseEvents);
            this->setWindowFlags(Qt::FramelessWindowHint);
            this->show();
            //this->ui->calendarWidget->setAttribute(Qt::WA_TransparentForMouseEvents);
            //this->setAttribute(Qt::WA_TransparentForMouseEvents,true);
        }
    }
    else
    {
        ui->adjustorfix->setText(tr("Adjust"));
        afflag = false;
        if (dndflag == true)
        {
            dndflag = false;
            ui->enablednd->setText(tr("enable"));
        }
    }
}

QColor MainWindow::getcolor(const QDate& date)
{
    int index = -1;
    for (int i = 0;i < this->ui->calendarWidget->dates.size();++i)
        if (this->ui->calendarWidget->dates.at(i) == this->ui->calendarWidget->m_currentDate)
        {
            index = i;
            break;
        }
    if (index == -1)
    {
        return Qt::white;
    }
    else
    {
        return this->ui->calendarWidget->colors[index];
    }
}

void MainWindow::setTranslator()
{
    /*this->ui->calendarWidget->*/ui->language->addItem("Default Language");
    /*this->ui->calendarWidget->*/ui->language->setParent(this);
    for (int lang = QLocale::C + 1;lang <= QLocale::LastLanguage;++lang)
    {
        QString Label;
        QLocale::Language lgg = static_cast<QLocale::Language>(lang);
        QList<QLocale::Country> Countries = QLocale::countriesForLanguage(lgg);
        for (int I = 0;I < Countries.count(); ++I)
        {
            Label = QLocale::languageToString(lgg);
            QLocale::Country Country = Countries.at(I);
            Label += QChar('/');
            Label += QLocale::countryToString(Country);
            QLocale Locale(lgg,Country);
            /*this->ui->calendarWidget->*/ui->language->addItem(Label,Locale);
        }
    }
    QObject::connect(/*this->ui->calendarWidget->*/ui->language,SIGNAL(currentIndexChanged(int)),this,SLOT(translate(int)));
}

void MainWindow::translate(int index)
{
    qDebug()<<"setlanguage"<<index;
    QTranslator translator;
    qDebug() << translator.load("/Users/songshihong/Desktop/Qt/Project-Week1/demoCode/cn.qm");
    if (index == 54)
    {
        translated = true;
        qApp->installTranslator(&translator);
    }
    else if (translated)
    {
        qApp->removeTranslator(&translator);
        translated = false;
    }
    qDebug()<</*this->ui->calendarWidget->*/ui->language->itemData(index).toString();
    QLocale NewLocale(/*this->ui->calendarWidget->*/ui->language->itemData(index).toLocale());
    this->setLocale(NewLocale);
    this->update();
}

void MainWindow::saveinfo()
{
//    FILE* datesavefile = fopen("/Users/songshihong/Desktop/Qtsave/savedinfo/dateinfo");
//    FILE* weeksavefile = fopen("/Users/songshihong/Desktop/Qtsave/savedinfo/weeklyinfo");
//    FILE* monthsavefile = fopen("/Users/songshihong/Desktop/Qtsave/savedinfo/monthlyinfo");

}

