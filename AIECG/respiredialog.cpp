
#include "respiredialog.h"

RespireDialog::RespireDialog(QWidget *parent)
	: QDialog(parent)
{

}

void RespireDialog::openRespiration()
{
	RespireDialog *w = new RespireDialog;
	w->setWindowTitle(tr("Serial respiration from CMS Monitor"));

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
//	taporder();
}



void RespireDialog::init()
{
	initGroupBox = new QGroupBox(tr("Init"));
	comportLabel = new QLabel(tr("COM port:"));
	comportCombo = new QComboBox;
	comportCombo->addItem(tr("COM1"));
	comportCombo->addItem(tr("COM2"));
	comportCombo->addItem(tr("COM3"));
	baudrateLabel = new QLabel(tr("Baud rate:"));
	baudrateCombo = new QComboBox;
	baudrateCombo->addItem(tr("38400"));
	baudrateCombo->addItem(tr("56000"));
	baudrateCombo->addItem(tr("115200"));
	initSpacerItem1 = new QSpacerItem(20,0,QSizePolicy::Minimum,QSizePolicy::Expanding);
	initSpacerItem2 = new QSpacerItem(20,0,QSizePolicy::Minimum,QSizePolicy::Expanding);
	initButton = new QPushButton(tr("Init"));

	initGridLayout = new QGridLayout;
	initGridLayout->addWidget(comportLabel,0,0,1,1);
	initGridLayout->addWidget(comportCombo,0,1,1,1);
	initGridLayout->addItem(initSpacerItem1,0,2,1,1);
	initGridLayout->addWidget(baudrateLabel,1,0,1,1);
	initGridLayout->addWidget(baudrateCombo,1,1,1,1);
	initGridLayout->addItem(initSpacerItem2,1,2,1,1);
	initGridLayout->addWidget(initButton,1,3,1,1);
	initGroupBox->setLayout(initGridLayout);
}

void RespireDialog::tune()
{
	tuneGroupBox = new QGroupBox(tr("Tune"));

	tuneTextEdit1  = new QTextEdit;
	tuneTextEdit2  = new QTextEdit;

	tuneGridLayout = new QGridLayout;
	tuneGridLayout->addWidget(tuneTextEdit1,0,0,1,1);
	tuneGridLayout->addWidget(tuneTextEdit2,1,0,1,1);
	tuneGroupBox->setLayout(tuneGridLayout);
}

void RespireDialog::comments()
{
	commentsGroupBox = new QGroupBox(tr("Comments"));

	commentsTextEdit = new QTextEdit;
	commentsCheckBox = new QCheckBox(tr("Stop automatically after"));
	commentsTimeEdit = new QTimeEdit();
	commentsSpacerItem = new QSpacerItem(20,20,QSizePolicy::Minimum,QSizePolicy::Expanding);
	pvCheckBox = new QCheckBox(tr("PV-Loop"));

	commentsCombo = new QComboBox;
	commentsCombo->addItem(tr("Only create signals"));
	commentsCombo->addItem(tr("Create and log signals"));
	commentsCombo->addItem(tr("Only log signals"));
	commentsButton = new QPushButton(tr("Filename"));
//	commentsLabel = new QLabel(tr("F:\st02"));


	commentsGridLayout = new QGridLayout;
	commentsGridLayout->addWidget(commentsTextEdit,0,0,1,4);
	commentsGridLayout->addWidget(commentsCheckBox,1,0,1,1);
	commentsGridLayout->addWidget(commentsTimeEdit,1,1,1,1);
	commentsGridLayout->addItem(commentsSpacerItem,1,2,1,1);
	commentsGridLayout->addWidget(pvCheckBox,1,3,1,1);
	commentsGridLayout->addWidget(commentsCombo,2,0,1,1);
	commentsGridLayout->addWidget(commentsButton,2,1,1,1);
//	commentsGridLayout->addWidget(commentsLabel,2,2,1,1);
	commentsGroupBox->setLayout(commentsGridLayout);

}


void RespireDialog::button()
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

/*
void RespireDialog::taporder()
{
	QWidget::setTabOrder(comportCombo,baudrateCombo);
	QWidget::setTabOrder(baudrateCombo,initButton);
	QWidget::setTabOrder(initButton,tuneTextEdit1);
	QWidget::setTabOrder(tuneTextEdit1,tuneTextEdit2);
	QWidget::setTabOrder(tuneTextEdit2,commentsTextEdit);
	QWidget::setTabOrder(commentsTextEdit,commentsCheckBox);
	QWidget::setTabOrder(commentsCheckBox,commentsTimeEdit);
	QWidget::setTabOrder(commentsTimeEdit,pvCheckBox);
	QWidget::setTabOrder(pvCheckBox,commentsCombo);
	QWidget::setTabOrder(commentsCombo,commentsButton);
	QWidget::setTabOrder(commentsButton,tunelastButton);
	QWidget::setTabOrder(tunelastButton,tunefromfileButton);
	QWidget::setTabOrder(tunefromfileButton,cancelButton);
	QWidget::setTabOrder(cancelButton,okButton);
}
*/

RespireDialog::~RespireDialog()
{

}