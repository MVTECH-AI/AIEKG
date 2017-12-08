#ifndef SERIALDIALOG_H
#define SERIALDIALOG_H

#include <QDialog>

class QGridLayout;
class QHBoxLayout;
class QVBoxLayout;
class QPushButton;
class QSpacerItem;
class QGroupBox;
class QLabel;
class QComboBox;
class QTextEdit;
class QCheckBox;
class QTimeEdit;

class SerialDialog :public QDialog
{
	Q_OBJECT

public:
	SerialDialog(QWidget *parent = 0);
	~SerialDialog();

private slots:
	void openSerialPort();

private:
	QGridLayout *initGridLayout;
	QGroupBox *initGroupBox;
	QLabel *comportLabel;
	QLabel *baudrateLabel;
	QComboBox *comportCombo;
	QComboBox *baudrateCombo;
	QSpacerItem *initSpacerItem;
	QPushButton *initButton;

	QGridLayout *tuneGridLayout;
	QGroupBox *tuneGroupBox;
	QTextEdit *tuneTextEdit;

	QGridLayout *commentsGridLayout;
	QGroupBox *commentsGroupBox;
	QTextEdit *commentsTextEdit;
	QCheckBox *commentsCheckBox;
	QTimeEdit *commentsTimeEdit;
	QSpacerItem *commentsSpacerItem;
	QComboBox *commentsCombo;
	QPushButton *commentsButton;
	QLabel *commentsLabel;

	QGridLayout *gridLayout;
	QHBoxLayout *hboxLayout;
	QPushButton *tunelastButton;
	QPushButton *tunefromfileButton;
	QSpacerItem *okspacerItem;
	QPushButton *cancelButton;
	QPushButton *okButton;

	void init();
	void tune();
	void comments();
	void button();
	void taporder();
	
};
#endif //SERIALDIALOG_H