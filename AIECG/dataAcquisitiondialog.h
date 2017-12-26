#ifndef DATAACQUISITIONDIALOG_H
#define DATAACQUISITIONDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QTextEdit>
#include <QCheckBox>
#include <QTimeEdit>

class DataAcquisitionDialog :public QDialog
{
	Q_OBJECT

public:
	DataAcquisitionDialog(QWidget *parent = 0);
	~DataAcquisitionDialog();

private slots:
	void preferences();

private:
	QGridLayout *gridLayout;
	QGridLayout *gridLayout1;
	QGridLayout *gridLayout2;

	QVBoxLayout *vboxLayout;
	QHBoxLayout *hboxLayout1;
	QHBoxLayout *hboxLayout2;

	QGroupBox *groupBox;
	QLabel *logtimeLabel;
	QLabel *remainLabel;
	QLabel *createLabel;
	QTimeEdit *logTimeEdit;
	QTimeEdit *remainTimeEdit;
	QSpacerItem *spacerItem1;
	QSpacerItem *spacerItem2;
	QPushButton *exitButton;
	QTextEdit *textEdit;

	QTextEdit *textEdit1;
	QTextEdit *textEdit2;
	QTextEdit *textEdit3;
	QTextEdit *textEdit4;
	QTextEdit *textEdit5;
	QTextEdit *textEdit6;
	QTextEdit *textEdit7;
	QTextEdit *textEdit8;
};
#endif //DATAACQUISITIONDIALOG_H