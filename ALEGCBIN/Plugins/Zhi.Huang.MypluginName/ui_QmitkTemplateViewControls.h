/********************************************************************************
** Form generated from reading UI file 'QmitkTemplateViewControls.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMITKTEMPLATEVIEWCONTROLS_H
#define UI_QMITKTEMPLATEVIEWCONTROLS_H
#include <Qt3Support/Q3TextEdit>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include<QtGui/QTabBar>
#include<QMainWindow>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolButton>
#include <QtGui/QHeaderView>
#include<QtGui/QLineedit>
#include<QtGui/QPalette>
#include <string.h>
#include <iostream>
using namespace std;
QT_BEGIN_NAMESPACE
class Ui_MypluginNameUIControl:public QMainWindow
{
public:
	QTextBrowser *textBrowser;
    QTabWidget *tabWidget;
    QWidget *tab;
	QWidget *tab_1;
    QPushButton *pushButton;
    QWidget *tab_2;
	QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
	QWidget *tab_3;
	QWidget *tab_4;
	QWidget *tab_5;
	QPushButton *pushButton_6;
	QPushButton *pushButton_7;
	QPushButton *pushButton_8;
	QPushButton *pushButton_9;
	QPushButton *pushButton_10;
    QFrame *line;
    QLabel *label;
	QLabel *label_2;
	QToolButton *toolButton;
    QToolButton *toolButton_2;
	QToolButton *toolButton_3;
	QPalette *pe;
	//QPushButton *buttonPerformImageProcessing;

	
    void setupUi(QWidget *MypluginNameUIControl)
    {
        if (MypluginNameUIControl->objectName().isEmpty())
            MypluginNameUIControl->setObjectName(QString::fromUtf8("MypluginNameUIControl"));
        MypluginNameUIControl->resize(469, 447);
        tabWidget = new QTabWidget(MypluginNameUIControl);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 510, 800));
		tab=new QWidget();
		tab->setObjectName(QString::fromUtf8("menu"));
		tabWidget->addTab(tab, QString());
		tabWidget->setStyleSheet("QTabBar::tab { height: 30px; }");
		tabWidget->setStyleSheet("background-image:url(C:/Users/MVTECH/Desktop/124.jpg)");
		//tabWidget->setStyleSheet("background-color:Off-white");
		//tabWidget->setStyleSheet("QTabBar::tab { height: 50px; width: 100px; }");
	//	buttonPerformImageProcessing = new QPushButton(MypluginNameUIControl);
    //    buttonPerformImageProcessing->setObjectName(QString::fromUtf8("buttonPerformImageProcessing"));
		line = new QFrame(tab);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(120, 90, 311, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 90, 54, 21));
        tab_1 = new QWidget();
        tab_1->setObjectName(QString::fromUtf8("loaddata"));
		toolButton = new QToolButton(tab_1);
        toolButton->setObjectName(QString::fromUtf8("Select the ECG file"));
        toolButton->setGeometry(QRect(30, 40, 131, 21));
		toolButton_2 = new QToolButton(tab_1);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        toolButton_2->setGeometry(QRect(210, 40, 101, 21));
		toolButton_3 = new QToolButton(tab_1);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        toolButton_3->setGeometry(QRect(340, 220, 91, 31));

        pushButton = new QPushButton(tab);

        pushButton->setObjectName(QString::fromUtf8("menu"));
        pushButton->setGeometry(QRect(140, 140, 81, 51));
		pushButton->setStyleSheet("background-image:url(C:/Users/MVTECH/Desktop/125.png)");
		//pushButton->setStyleSheet("background-color:gray");
		        pushButton_7 = new QPushButton(tab);
        pushButton_7->setObjectName(QString::fromUtf8("load data"));
        pushButton_7->setGeometry(QRect(230, 140, 81, 51));
		        pushButton_8 = new QPushButton(tab);
        pushButton_8->setObjectName(QString::fromUtf8("outputECG"));
        pushButton_8->setGeometry(QRect(140, 210, 81, 51));
		        pushButton_9 = new QPushButton(tab);
        pushButton_9->setObjectName(QString::fromUtf8("do svm"));
        pushButton_9->setGeometry(QRect(230, 210, 81, 51));
		        pushButton_10 = new QPushButton(tab);
        pushButton_10->setObjectName(QString::fromUtf8("the discusion"));
        pushButton_10->setGeometry(QRect(320, 210, 81, 51));
        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("outputECG"));
		label_2 = new QLabel(tab_2);
        label_2->setObjectName(QString::fromUtf8("label"));
        label_2->setGeometry(QRect(90, 30, 241, 31));
        pushButton_3 = new QPushButton(tab_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(60, 70, 75, 23));
        pushButton_4 = new QPushButton(tab_2);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(210, 70, 75, 23));
        tabWidget->addTab(tab_2, QString());
		tab_3=new QWidget();
		tab->setObjectName(QString::fromUtf8("do svm"));
		pushButton_5 = new QPushButton(tab_3);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(30, 30, 131, 41));
		tabWidget->addTab(tab_3, QString());
		        tabWidget->addTab(tab_2, QString());
		tab_4=new QWidget();
		tab->setObjectName(QString::fromUtf8("the discusion"));
		/*
		pushButton_6 = new QPushButton(tab_4);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(140, 140, 75, 23));*/
		tabWidget->addTab(tab_4, QString());
        retranslateUi(MypluginNameUIControl);
		pushButton_3->setStyleSheet("background-image:url(C:/Users/MVTECH/Desktop/125.png)");
		pushButton_4->setStyleSheet("background-image:url(C:/Users/MVTECH/Desktop/125.png)");
		pushButton_5->setStyleSheet("background-image:url(C:/Users/MVTECH/Desktop/125.png)");
		pushButton_7->setStyleSheet("background-image:url(C:/Users/MVTECH/Desktop/125.png)");
		pushButton_8->setStyleSheet("background-image:url(C:/Users/MVTECH/Desktop/125.png)");
		pushButton_9->setStyleSheet("background-image:url(C:/Users/MVTECH/Desktop/125.png)");
		pushButton_10->setStyleSheet("background-image:url(C:/Users/MVTECH/Desktop/125.png)");
		toolButton->setStyleSheet("background-image:url(C:/Users/MVTECH/Desktop/125.png)");
		toolButton_2->setStyleSheet("background-image:url(C:/Users/MVTECH/Desktop/125.png)");
		toolButton_3->setStyleSheet("background-image:url(C:/Users/MVTECH/Desktop/125.png)");
        textBrowser = new QTextBrowser(tab_1);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(50, 90, 381, 121));
		textBrowser->setStyleSheet("background-image:url(C:/Users/MVTECH/Desktop/125.png)");
	    pushButton_3->setVisible( false );
		pushButton_4->setVisible( false );
		//label_2->adjustSize();
        tabWidget->setCurrentIndex(0); // The first page shown


        QMetaObject::connectSlotsByName(MypluginNameUIControl);
    } // setupUi
	void create(int x,QString Name)//Diagnostic judgment
	{
		//string aa;
		QString temp;
		cout<<x<<endl;
		switch(x)
		{
		case 1: temp=QObject::tr("This patient has amyocardial infarction"); 
			    break;
		case 0: temp=QObject::tr("This patient has noproblem for now");
			    break;
		}
			//QObject::tr("Name");
//		cout<<aa<<endl;
		//QString temp;
		//textBrowser->append(temp);
		//temp.sprintf("%s",aa);
		textBrowser->append(Name);
		textBrowser->append(temp);

		//textBrowser->setText(temp);
	}
	void Delete()
	{
	  textBrowser->setPlainText("");
	}
    void retranslateUi(QWidget *MypluginNameUIControl)
    {
        MypluginNameUIControl->setWindowTitle(QApplication::translate("MypluginNameUIControl", "Form", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MypluginNameUIControl", "menu", 0, QApplication::UnicodeUTF8));
		pushButton_7->setText(QApplication::translate("MypluginNameUIControl", "load data", 0, QApplication::UnicodeUTF8));
		toolButton->setText(QApplication::translate("MypluginNameUIControl", "Select the ECG file", 0, QApplication::UnicodeUTF8));
		toolButton_2->setText(QApplication::translate("MypluginNameUIControl", "Check the ECG", 0, QApplication::UnicodeUTF8));
	    toolButton_3->setText(QApplication::translate("MypluginNameUIControl", "Emptied", 0, QApplication::UnicodeUTF8));
		pushButton_8->setText(QApplication::translate("MypluginNameUIControl", "outputECG", 0, QApplication::UnicodeUTF8));
		pushButton_9->setText(QApplication::translate("MypluginNameUIControl", "do svm", 0, QApplication::UnicodeUTF8));
		pushButton_10->setText(QApplication::translate("MypluginNameUIControl", "the result", 0, QApplication::UnicodeUTF8));
//        
		tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MypluginNameUIControl", "menu", 0, QApplication::UnicodeUTF8));
//		groupBox->setTitle(QApplication::translate("MypluginNameUIControl", "diagnostic result", 0, QApplication::UnicodeUTF8));
       tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("MypluginNameUIControl", "load data", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("MypluginNameUIControl", "show the ECG", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("MypluginNameUIControl", "Empty this", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("MypluginNameUIControl", "Import current data", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MypluginNameUIControl", "output the ECG", 0, QApplication::UnicodeUTF8));
		tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MypluginNameUIControl", "do SVM", 0, QApplication::UnicodeUTF8));
		tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MypluginNameUIControl", "the result", 0, QApplication::UnicodeUTF8));
		label->setText(QApplication::translate("MypluginNameUIControl", "the ECG", 0, QApplication::UnicodeUTF8));
		label_2->setText(QApplication::translate("MypluginNameUIControl", "Error: There is currently no import file", 0, QApplication::UnicodeUTF8));
		//buttonPerformImageProcessing->setText(QApplication::translate("MypluginNameUIControl", "Do Something", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MypluginNameUIControl: public Ui_MypluginNameUIControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMITKTEMPLATEVIEWCONTROLS_H
