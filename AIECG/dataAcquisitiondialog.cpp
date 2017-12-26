#include <QtGui>
#include "dataAcquisitiondialog.h"

DataAcquisitionDialog::DataAcquisitionDialog(QWidget *parent)
	: QDialog(parent)
{
}

void DataAcquisitionDialog::preferences()
{
	DataAcquisitionDialog *w = new DataAcquisitionDialog;
	w->setWindowTitle(tr("serial communication"));

	textEdit = new QTextEdit;
	textEdit->setFixedSize(200,60);
	logtimeLabel = new QLabel(tr("Log time:"));
	logTimeEdit = new QTimeEdit;
	exitButton = new QPushButton(tr("Exit"));
	remainLabel = new QLabel(tr("Remain"));
	remainTimeEdit = new QTimeEdit;
	createLabel = new QLabel(tr("Create signals"));
	//添加空白区宽20px,高0px,宽度尽可能的缩小、放大
	spacerItem1 = new QSpacerItem(20,0,QSizePolicy::Minimum,QSizePolicy::Expanding);
	spacerItem2 = new QSpacerItem(20,0,QSizePolicy::Minimum,QSizePolicy::Expanding);

	gridLayout1 = new QGridLayout;
	gridLayout1->addWidget(textEdit,0,0,2,1);//第一行第一列，占据一行，占据一列
	gridLayout1->addWidget(logtimeLabel,0,1,1,1);
	gridLayout1->addWidget(logTimeEdit,0,2,1,1);
	gridLayout1->addWidget(exitButton,0,3,1,1);
	gridLayout1->addItem(spacerItem1,0,4,1,2);
	gridLayout1->addWidget(remainLabel,1,1,1,1);
	gridLayout1->addWidget(remainTimeEdit,1,2,1,1);
	gridLayout1->addWidget(createLabel,1,3,1,1);
	gridLayout1->addItem(spacerItem2,1,4,1,2);

	textEdit1 = new QTextEdit;
	textEdit2 = new QTextEdit;
	textEdit3 = new QTextEdit;
	textEdit4 = new QTextEdit;
	textEdit5 = new QTextEdit;
	textEdit6 = new QTextEdit;
	textEdit7 = new QTextEdit;
	textEdit8 = new QTextEdit;

	textEdit1->setStyleSheet(QString::fromUtf8("background-color:back")); //设置背景颜色为黑
	textEdit2->setStyleSheet(QString::fromUtf8("background-color:back"));
	textEdit3->setStyleSheet(QString::fromUtf8("background-color:back"));
	textEdit4->setStyleSheet(QString::fromUtf8("background-color:back"));
	textEdit5->setStyleSheet(QString::fromUtf8("background-color:back"));
	textEdit6->setStyleSheet(QString::fromUtf8("background-color:back"));
	textEdit7->setStyleSheet(QString::fromUtf8("background-color:back"));
	textEdit8->setStyleSheet(QString::fromUtf8("background-color:back"));

	gridLayout2 = new QGridLayout;
	gridLayout2->addWidget(textEdit1,0,0,1,1);
	gridLayout2->addWidget(textEdit2,0,1,1,1);
	gridLayout2->addWidget(textEdit3,1,0,1,1);
	gridLayout2->addWidget(textEdit4,1,1,1,1);
	gridLayout2->addWidget(textEdit5,2,0,1,1);
	gridLayout2->addWidget(textEdit6,2,1,1,1);
	gridLayout2->addWidget(textEdit7,3,0,1,1);
	gridLayout2->addWidget(textEdit8,3,1,1,1);

	gridLayout = new QGridLayout;
	gridLayout->addLayout(gridLayout1,0,0,1,1);
	gridLayout->addLayout(gridLayout2,1,0,1,1);

	w->setLayout(gridLayout);
	w->show();
}

/*
void DataAcquisitionDialog::taporder()
{
	QWidget::setTabOrder(comportCombo,baudrateCombo);
	QWidget::setTabOrder(baudrateCombo,initButton);
	QWidget::setTabOrder(initButton,tuneTextEdit);
	QWidget::setTabOrder(tuneTextEdit,commentsTextEdit);
	QWidget::setTabOrder(commentsTextEdit,commentsCheckBox);
	QWidget::setTabOrder(commentsCheckBox,commentsTimeEdit);
	QWidget::setTabOrder(commentsTimeEdit,commentsCombo);
	QWidget::setTabOrder(commentsCombo,commentsButton);
	QWidget::setTabOrder(commentsButton,tunelastButton);
	QWidget::setTabOrder(tunelastButton,tunefromfileButton);
	QWidget::setTabOrder(tunefromfileButton,cancelButton);
	QWidget::setTabOrder(cancelButton,okButton);
}
*/

DataAcquisitionDialog::~DataAcquisitionDialog()
{

}