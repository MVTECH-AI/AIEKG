#include "mainwindow.h"
#include "readdata.h"
#include "processImage.h"

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	openMenu = menuBar()->addMenu(tr("open"));
	openAction = new QAction(tr("&O open"),this);
	beginMenu = menuBar()->addMenu(tr("begin"));
	beginAction = new QAction(tr("begin"),this);
	openMenu->addAction(openAction);
	beginMenu->addAction(beginAction);
	pReadData = new ReadData;
	pReadData->readtrainingPositiveData();
	pReadData->readtrainingNegativeData();
	pReadData->readtestPositiveData();
	pReadData->readtestNegativeData();
	connect(openAction,SIGNAL(triggered()),pReadData,SLOT(Open()));
	pImageProcess = new ImageProcess;
	pImageProcess->doPCA(pReadData);
	pImageProcess->trainSVMs(pReadData);
	pImageProcess->testSVMs(pReadData);
	connect(beginAction,SIGNAL(triggered()),this,SLOT(BeginSVM()))                                                                                                                                                  ;

	

}

MainWindow::~MainWindow()
{
	QMessageBox::information(NULL,"Exit","Exit or not",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
}


void MainWindow::BeginSVM()
{
	pImageProcess->predictSVMs(pReadData);

}