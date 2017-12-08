#include <QtGui>
#include "serialdialog.h"

SerialDialog::SerialDialog(QWidget *parent)
	: QDialog(parent)
{
	//taporder();	
}

void SerialDialog::openSerialPort()
{
	SerialDialog *w = new SerialDialog;

	w->setWindowTitle(tr("Serial CMS Monitor"));
	init();
	tune();
	comments();
	button();

	gridLayout = new QGridLayout;
	gridLayout->addWidget(initGroupBox,0,0,1,1);
	gridLayout->addWidget(tuneGroupBox,1,0,1,1);
	gridLayout->addWidget(commentsGroupBox,2,0,1,1);
	gridLayout->addLayout(hboxLayout,3,0,1,1);
	w->setLayout(gridLayout);

	
	w->show();
}

void SerialDialog::init()
{
	initGroupBox = new QGroupBox(tr("Init"));
	comportLabel = new QLabel(tr("COM port:"));
	comportCombo = new QComboBox;
	comportCombo->addItem(tr("COM1"));
	baudrateLabel = new QLabel(tr("Baud rate:"));
	baudrateCombo = new QComboBox;
	baudrateCombo->addItem(tr("38400"));
	initSpacerItem = new QSpacerItem(20,20,QSizePolicy::Minimum,QSizePolicy::Expanding);
	initButton = new QPushButton(tr("Init"));

	initGridLayout = new QGridLayout;
	initGridLayout->addWidget(comportLabel,0,0,1,1);
	initGridLayout->addWidget(comportCombo,0,1,1,1);
	initGridLayout->addItem(initSpacerItem,0,2,1,1);
	initGridLayout->addWidget(baudrateLabel,2,0,1,1);
	initGridLayout->addWidget(baudrateCombo,2,1,1,1);
	initGridLayout->addWidget(initButton,1,3,1,1);
	initGroupBox->setLayout(initGridLayout);
}

void SerialDialog::tune()
{
	tuneGroupBox = new QGroupBox(tr("Tune"));

	tuneTextEdit  = new QTextEdit;
//	tunetextEdit->moveCursor(QTextCursor::Start);
//	tunetextEdit->verticalScrollBar()->setValue(tunetextEdit->verticalScrollBar()->minimumHeight());

	tuneGridLayout = new QGridLayout;
	tuneGridLayout->addWidget(tuneTextEdit,0,0,1,1);
	tuneGroupBox->setLayout(tuneGridLayout);
}

void SerialDialog::comments()
{
	commentsGroupBox = new QGroupBox(tr("Comments"));

	commentsTextEdit = new QTextEdit;
	commentsCheckBox = new QCheckBox(tr("Stop automatically after"));
	commentsTimeEdit = new QTimeEdit();
	commentsSpacerItem = new QSpacerItem(20,20,QSizePolicy::Minimum,QSizePolicy::Expanding);

	commentsCombo = new QComboBox;
	commentsCombo->addItem(tr("Only create signals"));
	commentsCombo->addItem(tr("Create and log signals"));
	commentsCombo->addItem(tr("Only log signals"));
	commentsButton = new QPushButton(tr("Filename"));
//	commentsLabel = new QLabel(tr("F:\st02"));


	commentsGridLayout = new QGridLayout;
	commentsGridLayout->addWidget(commentsTextEdit,0,0,1,3);
	commentsGridLayout->addWidget(commentsCheckBox,1,0,1,1);
	commentsGridLayout->addWidget(commentsTimeEdit,1,1,1,1);
	commentsGridLayout->addItem(commentsSpacerItem,1,2,1,1);
	commentsGridLayout->addWidget(commentsCombo,2,0,1,1);
	commentsGridLayout->addWidget(commentsButton,2,1,1,1);
	//commentsGridLayout->addWidget(commentsLabel,2,2,1,1);
	commentsGroupBox->setLayout(commentsGridLayout);

}


void SerialDialog::button()
{
	tunelastButton = new QPushButton(tr("Tune last"));
	tunefromfileButton = new QPushButton(tr("Tune from file"));
	okspacerItem = new QSpacerItem(20,0,QSizePolicy::Minimum,QSizePolicy::Expanding);
	cancelButton = new QPushButton(tr("Cancel"));
	okButton = new QPushButton(tr("OK"));

	hboxLayout = new QHBoxLayout;
	hboxLayout->addWidget(tunelastButton);
	hboxLayout->addWidget(tunefromfileButton);
	hboxLayout->addItem(okspacerItem);
	hboxLayout->addWidget(cancelButton);
	hboxLayout->addWidget(okButton);
}


void SerialDialog::taporder()
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


SerialDialog::~SerialDialog()
{

}