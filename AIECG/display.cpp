#include "display.h"

Display::Display(QWidget *parent)
	: QWidget(parent)
{
	customPlot = new QCustomPlot;
	textEdit1 = new QTextEdit;
	textEdit2 = new QTextEdit;
	textEdit3 = new QTextEdit;
	textEdit4 = new QTextEdit;
	gridLayout = new QGridLayout;
	gridLayout->addWidget(customPlot,0,0,1,1);
	gridLayout->addWidget(textEdit2,1,0,1,1);
	gridLayout->addWidget(textEdit3,2,0,1,1);
	gridLayout->addWidget(textEdit4,3,0,1,1);
	gridLayout->setRowStretch(0,5);
	gridLayout->setRowStretch(1,1);
	gridLayout->setRowStretch(2,1);
	gridLayout->setRowStretch(3,1);
	setLayout(gridLayout);
}

void Display::loadText()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Load Text"), QString(),
		tr("Ascii file(*.*);;Text file(*.txt);;Macro file(*.dpm);;Macro list file(*.dpl)"));

	if (!fileName.isEmpty())
	{
		QFile file(fileName);
		if (!file.open(QIODevice::ReadOnly))
		{
			QMessageBox::critical(this,tr("ERROR"),tr("couldn't open the file"));
			return;
		} 
		else
		{
			QTextStream stream(&file);
			textEdit2->setText(stream.readAll());
			file.flush();
		}
	}
	else
	{
		QMessageBox::critical(this,tr("ERROR"),tr("you don't open any file"));
	}
}

void Display::saveText()
{
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Text"), QString(),
		tr("All Files(*.*);;Text Files(*.txt);;c++ Files(*.cpp *.h);;Jsp Files(*.jsp)"));

	if (!fileName.isEmpty())
	{
		QFile file(fileName);
		if (!file.open(QIODevice::WriteOnly))
		{
		} 
		else
		{
			QTextStream stream(&file);
			stream << textEdit2->toPlainText();
			stream.flush();
			file.close();
		}
	}
}

Display::~Display()
{

}
