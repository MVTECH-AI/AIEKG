#ifndef DISPLAY_H
#define DISPLAY_H

#include <QtGui>
#include <QWidget>
#include "qcustomplot.h"

class Display :public QWidget
{
	Q_OBJECT

public:
	Display(QWidget *parent = 0);
	~Display();

private slots:
	void loadText();
	void saveText();

private:
	QGridLayout *gridLayout;
	QTextEdit *textEdit1;
	QTextEdit *textEdit2;
	QTextEdit *textEdit3;
	QTextEdit *textEdit4;
	QCustomPlot *customPlot;
};

#endif //DISPLAY_H
