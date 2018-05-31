#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QtGui>
#include <QDateTime>

class DataModel :public QMainWindow
{
	Q_OBJECT

public:
	DataModel(QWidget *parent = 0);
	~DataModel();

private slots:
	void loadSignal();
	void createStatusBar();
	void rowClicked(const QModelIndex &index);

private:
	void init();
	void display();
	void createMenus();

	QLabel *ILabel;
	QLabel *GreenBtnLabel;
	QLabel *RedBtnLabel;
	QLabel *Heart1Label;
	QLabel *Heart2Label;

	QLabel *ventRateLabel;
	QLabel *PRintLabel;
	QLabel *QRSdurLabel;
	QLabel *QTLabel;
	QLabel *PRTaxesLabel;

	QLineEdit *ventRateLineEdit;
	QLineEdit *PRintLineEdit;
	QLineEdit *QRSdurLineEdit;
	QLineEdit *QTLineEdit;
	QLineEdit *PRTaxesLineEdit;

	QGridLayout *mainLayout;
	QGridLayout *rightLayout;
	QGridLayout *rightmiddleLayout;
	QHBoxLayout *hboxLayout;
	QVBoxLayout *vboxLayout;

	QWidget *widget;
	QMdiArea *mdiArea;
	QTextEdit *textEdit;
	QTableView *tableView;
	QStandardItemModel *tableModel;
	QTimer *timer;
	QLabel  *currentTimeLabel;

	QMenu *fileMenu;
	QAction *LoadSignalAction;
};

#endif //DATAMODEL_H
