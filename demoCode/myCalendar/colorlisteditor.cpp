#include <QtGui>

 #include "colorlisteditor.h"
#include <QVariant>

 ColorListEditor::ColorListEditor(QWidget *widget) : QComboBox(widget)
 {
     populateList();
 }

 QColor ColorListEditor::color() const
 {
     return qvariant_cast<QColor>(itemData(currentIndex(), Qt::DecorationRole));
 }

 void ColorListEditor::setColor(QColor color)
 {
     setCurrentIndex(findData(color, int(Qt::DecorationRole)));
 }

 void ColorListEditor::populateList()
 {
     QStringList colorNames = QColor::colorNames();

     for (int i = 0; i < colorNames.size(); ++i) {
         QColor color(colorNames[i]);

         insertItem(i, colorNames[i]);
         setItemData(i, color, Qt::DecorationRole);
     }
 }
