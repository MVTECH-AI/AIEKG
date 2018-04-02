#ifndef RESPIREDIALOG_H
#define RESPIREDIALOG_H

#include <QtGui>
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

class RespireDialog :public QDialog
{
	Q_OBJECT

public:
	RespireDialog(QWidget *parent = 0);
	~RespireDialog();

private slots:
	void openRespiration();

private:
	QGridLayout *initGridLayout;
	QGroupBox *initGroupBox;
	QLabel *comportLabel;
	QLabel *baudrateLabel;
	QComboBox *comportCombo;
	QComboBox *baudrateCombo;
	QSpacerItem *initSpacerItem1;
	QSpacerItem *initSpacerItem2;
	QPushButton *initButton;
	
	QGridLayout *tuneGridLayout;
	QGroupBox *tuneGroupBox;
	QTextEdit *tuneTextEdit1;
	QTextEdit *tuneTextEdit2;


	QGridLayout *commentsGridLayout;
	QGroupBox *commentsGroupBox;
	QTextEdit *commentsTextEdit;
	QCheckBox *commentsCheckBox;
	QTimeEdit *commentsTimeEdit;	
	QSpacerItem *commentsSpacerItem;
	QCheckBox *pvCheckBox;
	QComboBox *commentsCombo;
	QPushButton *commentsButton;
//	QLabel *commentsLabel;

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
//	void taporder();
};
#endif //RESPIREDIALOG_H