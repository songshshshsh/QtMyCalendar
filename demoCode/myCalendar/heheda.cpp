#include "heheda.h"
#include <qcalendarwidget.h>
#include <QTableView>
#include <cassert>
#include <QFile>
#include <QModelIndex>

//class QCalendarView;

const static QString path = "/Users/songshihong/Desktop/Qtsave/";

Heheda::Heheda(QWidget *parent): QCalendarWidget(parent)
{
    time = new QComboBox();
    time->insertItem(0,tr("CurrentDay"));
    time->insertItem(1,tr("EveryDay"));
    time->insertItem(2,tr("EveryWeek"));
    time->insertItem(3,tr("EveryMonth"));
    options = new QComboBox();
    options->insertItem(0,tr("Add"));
    options->insertItem(1,tr("Delete"));
    options->insertItem(2,tr("Edit"));
    textlist = new dndListWidget();
    text = new QTextEdit();
    select = new QLineEdit();
    QVector<QString> temp;
    for (int i = 0; i <= 7;++i)
    {
        weeklytodolist.append(temp);
    }
    for (int i = 0; i <= 32;++i)
    {
        monthlytodolist.append(temp);
    }
    QPalette newPalette = palette();
    newPalette.setColor(QPalette::Window, Qt::white);
    setPalette(newPalette);
    setAcceptDrops(true);
    dnd = new bool(true);
    af = new bool(true);
    colorbox = new ColorListEditor();
}

void Heheda::paintCell(QPainter * painter, const QRect & rect, const QDate & date) const
{
    QCalendarWidget::paintCell(painter,rect,date);
    painter->setPen(m_outlinePen);

    QString temp;

    for (int i = 0; i < dates.size(); i++)
    {
        if (date == dates.at(i))
        {
            QBrush brush = QBrush(colors.at(i));
            painter->setOpacity(0.5);
            painter->setBrush(brush);
            qDebug()<<colors.at(i);
            painter->drawRect(rect.adjusted(0, 0, -1, -1));
            for (int j = 0;j < normaltodolist[i].size();++j)
                temp += normaltodolist[i].at(j) + '\n';
            for (int j = 0;j < filestring[i].size();++j)
                temp += filestring[i].at(j) + '\n';
        }
    }
    for (int i = 0;i < everydaytodolist.size();++i)
        temp += everydaytodolist[i] +'\n';
    for (int i = 1;i <= 7;++i)
        if (i == date.dayOfWeek())
            for (int j = 0;j < weeklytodolist[i].size();++j)
                 temp += weeklytodolist[i].at(j) +'\n';
    for (int i = 1;i < 32;++i)
        if (date.day() == i)
            for (int j = 0;j < monthlytodolist[i].size();++j)
                temp += monthlytodolist[i].at(j) + '\n';
        painter->drawText(rect,temp);
}

void Heheda::updateinfo()
{
    if (dates.contains(m_currentDate))
    {
        int index = dates.indexOf(m_currentDate);
        colors.replace(index,listColor);
        if (options->currentText() == tr("Add"))
        {
            if (time->currentText() == tr("CurrentDay"))
            {
                normaltodolist[index].append(memo);
            }
            else if (time->currentText() == tr("EveryDay"))
            {
                everydaytodolist.append(memo);
            }
            else if (time->currentText() == tr("EveryWeek"))
            {
                weeklytodolist[m_currentDate.dayOfWeek()].append(memo);
            }
            else if (time->currentText() == tr("EveryMonth"))
            {
                monthlytodolist[m_currentDate.day()].append(memo);
            }
        }
        else if (options->currentText() == tr("Delete"))
        {
            if (select->text() == QString(""))
            {
                QMessageBox::about(this,tr("warning"),tr("No input items!"));
                return;
            }
            else if (time->currentText() == tr("CurrentDay"))
            {
                int dindex = -1;
                for (int i = 0;i < normaltodolist[index].size();++i)
                    if (select->text() == normaltodolist[index].at(i))
                    {
                        dindex = i;
                        break;
                    }
                if (dindex == -1)
                    QMessageBox::about(this,tr("warning"),tr("no such item!"));
                else
                    normaltodolist[index].remove(dindex);
            }
            else if (time->currentText() == tr("EveryDay"))
            {
                int dindex = -1;
                for (int i = 0;i < everydaytodolist[index].size();++i)
                    if (select->text() == everydaytodolist[index].at(i))
                    {
                        dindex = i;
                        break;
                    }
                if (dindex == -1)
                    QMessageBox::about(this,tr("warning"),tr("no such item!"));
                else
                    everydaytodolist[index].remove(dindex);
            }
            else if (time->currentText() == tr("EveryWeek"))
            {
                int dindex = -1;
                for (int i = 0;i < weeklytodolist[m_currentDate.dayOfWeek()].size();++i)
                    if (select->text() == weeklytodolist[m_currentDate.dayOfWeek()].at(i))
                    {
                        dindex = i;
                        break;
                    }
                if (dindex == -1)
                    QMessageBox::about(this,tr("warning"),tr("no such item!"));
                else
                    weeklytodolist[m_currentDate.dayOfWeek()].remove(dindex);
            }
            else if (time->currentText() == tr("EveryMonth"))
            {
                int dindex = -1;
                for (int i = 0;i < monthlytodolist[m_currentDate.day()].size();++i)
                    if (select->text() == monthlytodolist[m_currentDate.day()].at(i))
                    {
                        dindex = i;
                        break;
                    }
                if (dindex == -1)
                    QMessageBox::about(this,tr("warning"),tr("no such item!"));
                else
                    monthlytodolist[m_currentDate.day()].remove(dindex);
            }
        }
        else if (options->currentText() == tr("Edit"))
        {
            if (select->text() == QString(""))
            {
                QMessageBox::about(this,tr("warning"),tr("No input items!"));
                return;
            }
            else if (time->currentText() == tr("CurrentDay"))
            {
                int dindex = -1;
                for (int i = 0;i < normaltodolist[index].size();++i)
                    if (select->text() == normaltodolist[index].at(i))
                    {
                        dindex = i;
                        break;
                    }
                if (dindex == -1)
                    QMessageBox::about(this,tr("warning"),tr("no such item!"));
                else
                    normaltodolist[index].replace(dindex,memo);
            }
            else if (time->currentText() == tr("EveryDay"))
            {
                int dindex = -1;
                for (int i = 0;i < everydaytodolist[index].size();++i)
                    if (select->text() == everydaytodolist[index].at(i))
                    {
                        dindex = i;
                        break;
                    }
                if (dindex == -1)
                    QMessageBox::about(this,tr("warning"),tr("no such item!"));
                else
                    everydaytodolist[index].replace(dindex,memo);
            }
            else if (time->currentText() == tr("EveryWeek"))
            {
                int dindex = -1;
                for (int i = 0;i < weeklytodolist[m_currentDate.dayOfWeek()].size();++i)
                    if (select->text() == weeklytodolist[m_currentDate.dayOfWeek()].at(i))
                    {
                        dindex = i;
                        break;
                    }
                if (dindex == -1)
                    QMessageBox::about(this,tr("warning"),tr("no such item!"));
                else
                    weeklytodolist[m_currentDate.dayOfWeek()].replace(dindex,memo);
            }
            else if (time->currentText() == tr("EveryMonth"))
            {
                int dindex = -1;
                for (int i = 0;i < monthlytodolist[m_currentDate.day()].size();++i)
                    if (select->text() == monthlytodolist[m_currentDate.day()].at(i))
                    {
                        dindex = i;
                        break;
                    }
                if (dindex == -1)
                    QMessageBox::about(this,tr("warning"),tr("no such item!"));
                else
                    monthlytodolist[m_currentDate.day()].replace(dindex,memo);
            }
        }
    }
    else
    {
        if (options->currentText() == tr("Add"))
        {
            dates.append(m_currentDate);
            int index = dates.indexOf(m_currentDate);
            colors.append(listColor);
            if (time->currentText() == tr("CurrentDay"))
            {
                QVector<QString> temp;
                filestring.append(temp);
                normaltodolist.append(temp);
                filelist.append(temp);
                normaltodolist[index].append(memo);
            }
            else if (time->currentText() == tr("EveryDay"))
            {
                QVector<QString> temp;
                normaltodolist.append(temp);
                filestring.append(temp);
                filelist.append(temp);
                everydaytodolist.append(memo);
            }
            else if (time->currentText() == tr("EveryWeek"))
            {
                QVector<QString> temp;
                normaltodolist.append(temp);
                filelist.append(temp);
                filestring.append(temp);
                weeklytodolist[m_currentDate.dayOfWeek()].append(memo);
            }
            else if (time->currentText() == tr("EveryMonth"))
            {
                QVector<QString> temp;
                normaltodolist.append(temp);
                filelist.append(temp);
                filestring.append(temp);
                monthlytodolist[m_currentDate.day()].append(memo);
            }
        }
        else
        {
            QMessageBox::about(this,tr("warning"),tr("No input items!"));
        }
    }
    int index = -1;
    for (int i = 0;i < dates.size();++i)
        if (dates.at(i) == m_currentDate)
        {
            index = i;
            break;
        }
    if (index == -1)
    {
        dates.append(m_currentDate);
        colors.append(listColor);
        QVector<QString> tempstring;
        normaltodolist.append(tempstring);
        filelist.append(tempstring);
        filestring.append(tempstring);
    }
    else
    {
        colors[index] = listColor;
    }
    textlistshow(m_currentDate);
}

void Heheda::memochanged()
{
    memo = text->toPlainText();
}

void Heheda::textlistshow(const QDate &date)
{
    //this->ui->calendarWidget->textlist
    textlist->clear();
    for (int i = 0; i < dates.size(); i++)
    {
        if (date == dates.at(i))
        {
            for (int j = 0;j < normaltodolist[i].size();++j)
                textlist->addItem(normaltodolist[i].at(j));
            for (int j = 0;j < filestring[i].size();++j)
                textlist->addItem(filestring[i].at(j));
        }
    }
    for (int i = 0;i < everydaytodolist.size();++i)
        textlist->addItem(everydaytodolist[i]);
    for (int i = 1;i <= 7;++i)
        if (i == m_currentDate.dayOfWeek())
            for (int j = 0;j < weeklytodolist[i].size();++j)
                textlist->addItem(weeklytodolist[i].at(j));
    for (int i = 1;i < 32;++i)
        if (m_currentDate.day() == i)
            for (int j = 0;j < monthlytodolist[i].size();++j)
                textlist->addItem(monthlytodolist[i].at(j));
}

void Heheda::dragEnterEvent(QDragEnterEvent *event)
{
    if (!(*dnd) || !(*af)) return;
    if (event->mimeData()->hasFormat("application/x-fridgemagnet")) {
        if (children().contains(event->source())) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void Heheda::dragMoveEvent(QDragMoveEvent *event)
{
    if (!(*dnd)|| !(*af)) return;
    if (event->mimeData()->hasFormat("application/x-fridgemagnet")) {
        if (children().contains(event->source())) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else if (event->mimeData()->hasText()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void Heheda::dropEvent(QDropEvent *event)
{
    if (!(*dnd)|| !(*af)) return;
    qDebug()<<"dnd"<<*dnd;
    if (event->mimeData()->hasFormat("application/x-fridgemagnet")) {
        const QMimeData *mime = event->mimeData();
        QByteArray itemData = mime->data("application/x-fridgemagnet");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString text;
        QPoint offset;
        dataStream >> text >> offset;
        QTableView* calendarview = this->findChild<QTableView *>("qt_calendar_calendarview");
        DragLabel *newLabel = new DragLabel(text, this);
        newLabel->move(event->pos() - offset);
        int currentmonth = this->monthShown();
        int currentyear = this->yearShown();
        QDate* firstday = new QDate(currentyear,currentmonth,1);
        QRect table = calendarview->geometry();
        int left = table.left();
        int right = table.right();
        int top = table.top();
        int bottom = table.bottom();
        QPoint currentposition = event->pos();
        int rol = (currentposition.y() - top) * 7.0/(bottom - top);
        int col = (currentposition.x() - left) * 8.0/(right - left);
        //assert(rol > 0 && col > 0);
        if (!(rol > 0 && col > 0))
        {
            QMessageBox::about(this,tr("warning"),tr("invalid area!"));
            return;
        }
        int start = firstday->dayOfWeek() % 7 + 1;
        int index = (rol - 2) * 7 + col + (7 - start);
        QDate currentday =  firstday->addDays(index);
        //newLabel->show();
        newLabel->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else if (event->mimeData()->hasText()) {
        QStringList pieces = event->mimeData()->text().split(QRegExp("\\s+"),
                             QString::SkipEmptyParts);
        QPoint position = event->pos();
        QTableView* calendarview = this->findChild<QTableView *>("qt_calendar_calendarview");
        int currentmonth = this->monthShown();
        int currentyear = this->yearShown();
        QDate* firstday = new QDate(currentyear,currentmonth,1);
        QRect table = calendarview->geometry();
        int left = table.left();
        int right = table.right();
        int top = table.top();
        int bottom = table.bottom();
        QPoint currentposition = event->pos();
        int rol = (currentposition.y() - top) * 7.0/(bottom - top);
        int col = (currentposition.x() - left) * 8.0/(right - left);
        //assert(rol > 0 && col > 0);
        if (!(rol > 0 && col > 0))
        {
            QMessageBox::about(this,tr("warning"),tr("invalid area!"));
            return;
        }
        int start = firstday->dayOfWeek() % 7 + 1;
        int index = (rol - 2) * 7 + col + (7 - start);
        QDate currentday =  firstday->addDays(index);

        foreach (QString piece, pieces) {
            DragLabel *newLabel = new DragLabel(piece, this);
            newLabel->move(position);
            //newLabel->show();
            QString temp = piece.remove("file://");
            //QFile* file = new QFile(temp);
            QString newfilename = getfilename(temp);
            qDebug()<<path+newfilename;
            qDebug()<<QFile::exists("/Users/songshihong/Desktop/Qtsave");
            if (!QFile::copy(temp,path + newfilename))
            {
                QMessageBox::about(this,tr("warning"),tr("copy failed!"));
                QFile* file = new QFile(temp);
                file->copy(path+newfilename);
                qDebug() << file->errorString() << temp;
            }
            newLabel->setAttribute(Qt::WA_DeleteOnClose);
            updatefiles(currentday,temp);
            this->update();
            position += QPoint(newLabel->width(), 0);
        }

        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}



void Heheda::updatefiles(const QDate& date,const QString piece)
{
    if (dates.contains(date))
    {
        int index = dates.indexOf(date);
        filelist[index].append(piece);
        QString t = getfilename(piece);
        filestring[index].append(t);
    }
    else
    {
        dates.append(date);
        colors.append(Qt::white);
        QVector<QString> temp;
        filelist.append(temp);
        filestring.append(temp);
        normaltodolist.append(temp);
        filelist[filelist.size()-1].append(piece);
        QString t = getfilename(piece);
        filestring[filestring.size()-1].append(t);
    }
    textlistshow(date);
}


QString Heheda::getfilename(QString name)
{
    int index = -1;
    for (int i = name.length()-1;i >= 0;--i)
        if (name.at(i) == '/')
        {
                index = i;
                break;
        }
    qDebug()<<index;
    if (index != -1)
        name.remove(0,index+1);
    return name;
}

void Heheda::setdnd(bool *dndflag)
{
    dnd = dndflag;
}

void Heheda::setaf(bool *afflag)
{
    af = afflag;
}

