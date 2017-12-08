/********************************************************************************
** Form generated from reading UI file 'QmitkTemplateViewControls.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMITKTEMPLATEVIEWCONTROLS_H
#define UI_QMITKTEMPLATEVIEWCONTROLS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MypluginNameUIControl
{
public:
    QLabel *labelWarning;
    QPushButton *buttonPerformImageProcessing;
    QPushButton *pushButton_5;
    QPushButton *pushButton;

    void setupUi(QWidget *MypluginNameUIControl)
    {
        if (MypluginNameUIControl->objectName().isEmpty())
            MypluginNameUIControl->setObjectName(QString::fromUtf8("MypluginNameUIControl"));
        MypluginNameUIControl->resize(460, 735);
        MypluginNameUIControl->setMinimumSize(QSize(0, 0));
        labelWarning = new QLabel(MypluginNameUIControl);
        labelWarning->setObjectName(QString::fromUtf8("labelWarning"));
        labelWarning->setGeometry(QRect(9, 9, 138, 16));
        labelWarning->setStyleSheet(QString::fromUtf8("QLabel { color: rgb(255, 0, 0) }"));
        buttonPerformImageProcessing = new QPushButton(MypluginNameUIControl);
        buttonPerformImageProcessing->setObjectName(QString::fromUtf8("buttonPerformImageProcessing"));
        buttonPerformImageProcessing->setGeometry(QRect(9, 27, 80, 23));
        pushButton_5 = new QPushButton(MypluginNameUIControl);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(160, 170, 75, 23));
        pushButton = new QPushButton(MypluginNameUIControl);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(260, 170, 75, 23));

        retranslateUi(MypluginNameUIControl);

        QMetaObject::connectSlotsByName(MypluginNameUIControl);
    } // setupUi

    void retranslateUi(QWidget *MypluginNameUIControl)
    {
        MypluginNameUIControl->setWindowTitle(QApplication::translate("MypluginNameUIControl", "QmitkTemplate", 0, QApplication::UnicodeUTF8));
        labelWarning->setText(QApplication::translate("MypluginNameUIControl", "Please select an image!", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        buttonPerformImageProcessing->setToolTip(QApplication::translate("MypluginNameUIControl", "Do image processing", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        buttonPerformImageProcessing->setText(QApplication::translate("MypluginNameUIControl", "Do Something", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("MypluginNameUIControl", "read data", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MypluginNameUIControl", "Output ECG", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MypluginNameUIControl: public Ui_MypluginNameUIControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMITKTEMPLATEVIEWCONTROLS_H
