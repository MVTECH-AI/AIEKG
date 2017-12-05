#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "ui_mainwindow.h"

class ReadData;
class ImageProcess;


class MainWindow : public QMainWindow
{

	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();

private:

	Ui::MainWindowClass ui;
	QMenu *openMenu;
	QMenu *beginMenu;
	QAction *openAction;
	QAction *beginAction;
	ReadData *pReadData;
	ImageProcess *pImageProcess;

private slots:
	void BeginSVM();

};

#endif // MAINWINDOW_H
