#include "readdata.h"
#include "mainwindow.h"
#include <QTextEdit>


QString fileFull, fileName; 

ReadData::ReadData()
{
//	this->predictCounter = -1;
	
}

void ReadData::readtrainingPositiveData()
{

	// find all files end with raw within certain direction
	QDir dir(".\\trainPositive");
	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	QFileInfoList list = dir.entryInfoList();
	for (int i = 0; i < list.size(); ++i) {
		QFileInfo fileInfo = list.at(i);
		if (fileInfo.suffix() == "raw")
			filepath.push_back(fileInfo.absoluteFilePath().toStdString());
	}
	trainPositiveSize = list.size();
	//qDebug() << trainPositiveSize;

	// APIs from third-party
	for(auto it = 0; it != filepath.size();it++){
		result.push_back(readRawLeadData((filepath[it]).c_str(),MyData,strMsg));
		srcData.push_back(MyData);
		//qDebug() << QString::fromStdString(filepath[it]);
		srcMat.push_back(cvCreateMat(1,60000,CV_32FC1));
		auto *p = srcMat[it].ptr<float>(0);
		for (int j=0;j<60000;j++,p++,srcData[it]++){
			*p = *srcData[it];			
			//qDebug() << *p  <<  " ";
		}	
	}

}

void ReadData::readtrainingNegativeData()
{
	// find all files end with raw within certain direction
	QDir dir(".\\trainNegative");
	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	QFileInfoList list = dir.entryInfoList();
	for (int i = 0; i < list.size(); ++i) {
		QFileInfo fileInfo = list.at(i);
		if (fileInfo.suffix() == "raw")
			filepath.push_back(fileInfo.absoluteFilePath().toStdString());
	}
	trainNegativeSize = list.size();
	//qDebug() << trainNegativeSize;

	// APIs from third-party
	for(auto it = 0; it != filepath.size()-trainPositiveSize;it++){
		result.push_back(readRawLeadData((filepath[it+trainPositiveSize]).c_str(),MyData,strMsg));//
		srcData.push_back(MyData);
		//qDebug() << QString::fromStdString(filepath[it+trainPositiveSize]);
		srcMat.push_back(cvCreateMat(1,60000,CV_32FC1));
		auto *p = srcMat[it+trainPositiveSize].ptr<float>(0);
		for (int j=0;j<60000;j++,p++,srcData[it+trainPositiveSize]++){
			*p = *srcData[it+trainPositiveSize];			
			//qDebug() << *p  <<  " ";
		}	
	}
}

void ReadData::readtestPositiveData()
{
	trainSize =  trainPositiveSize+ trainNegativeSize;
	
	// find all files end with raw within certain direction
	QDir dir(".\\testPositive");
	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	QFileInfoList list = dir.entryInfoList();
	for (int i = 0; i < list.size(); ++i) {
		QFileInfo fileInfo = list.at(i);
		if (fileInfo.suffix() == "raw")
			filepath.push_back(fileInfo.absoluteFilePath().toStdString());
	}
	testPositiveSize = list.size();
	//qDebug() << testPositiveSize;

	
	// APIs from third-party
	for(auto it = 0; it < filepath.size()-trainSize;it++){
		readRawLeadData((filepath[it+trainSize]).c_str(),MyData,strMsg);
		testData.push_back(MyData);
		//qDebug() << QString::fromStdString(filepath[it+trainSize]);
		testMat.push_back(cvCreateMat(1,60000,CV_32FC1));
		auto *p = testMat[it].ptr<float>(0);
		for (int j=0;j<60000;j++,p++,testData[it]++){
			*p = *testData[it];			
			//qDebug() << *p  <<  " ";
		}	
	}
}

void ReadData::readtestNegativeData()
{
	trainSize = trainPositiveSize + trainNegativeSize;

	// find all files end with raw within certain direction
	QDir dir(".\\testNegative");
	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	QFileInfoList list = dir.entryInfoList();
	for (int i = 0; i < list.size(); ++i) {
		QFileInfo fileInfo = list.at(i);
		if (fileInfo.suffix() == "raw")
			filepath.push_back(fileInfo.absoluteFilePath().toStdString());
	}
	testNegativeSize = list.size();
	//qDebug() << testNegativeSize;


	// APIs from third-party
	for(auto it = 0; it < filepath.size()-trainSize-testPositiveSize;it++){
		readRawLeadData((filepath[it+trainSize+testPositiveSize]).c_str(),MyData,strMsg);
		testData.push_back(MyData);
		//qDebug() << QString::fromStdString(filepath[it+trainSize+testPositiveSize]);
		testMat.push_back(cvCreateMat(1,60000,CV_32FC1));
		auto *p = testMat[it+testPositiveSize].ptr<float>(0);
		for (int j=0;j<60000;j++,p++,testData[it+testPositiveSize]++){
			*p = *testData[it+testPositiveSize];			
			//qDebug() << *p  <<  " ";
		}	
	}


}

ReadData::~ReadData()
{
	
}

int ReadData::ptrianSize()
{
	return this->trainPositiveSize;
}

int ReadData::ntrainSize()
{
	return this->trainNegativeSize;
}

int ReadData::ptestSize()
{
	return this->testPositiveSize;
}

int ReadData::ntestSize()
{
	return this->testNegativeSize;
}

int ReadData::getStatus()
{
	return this->status;
}

int ReadData::getCounter()
{
	return this->predictCounter;
}

void ReadData::Open()
{
//	predictCounter += 1;
	QString filePath;  
	QFileInfo fi;


	// for read 
	fileFull = QFileDialog::getOpenFileName();  
	fi = QFileInfo(fileFull);  
	fileName = fi.fileName();  
	filePath = fi.absolutePath();
	status = readRawLeadData(fileFull.toStdString().c_str(),drawData,strMsg);
	this->realDataName =  fi.completeBaseName() + ".txt";
	//qDebug() << this->realDataName;
	//realData.push_back(drawData);
	realMat = cvCreateMat(1,60000,CV_32FC1);
	auto *p = realMat.ptr<float>(0);
	for (int j = 0;j < 60000;j++,p++){
			*p = drawData[j];			
			//qDebug() << *p  <<  " ";
		}

	// for drawing the EKG	
	QVector<double> yData(60000);
	QVector<double> xData(60000);
	xData[0] = 0;

	if (status == 0){
		for (int i=0;i<60000;i++){
			yData[i] = drawData[i];
			//qDebug() << drawData[i] ;
		}
		for (int j=1;j<60000;j++){
			xData[j] = xData[j-1] +1./500;
		}

	}
	else if(status == -1) {
		QMessageBox::information(NULL,"File Error","Retry or not",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
		return;
	}
	else if (status == -2){
		QMessageBox::information(NULL,"Memory Error","Retry or not",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
		return;
	}
	
	QCustomPlot *Plot = new QCustomPlot;
	for(int i =0; i < 12; i++){
		Plot->addGraph();			
		Plot->graph(i)->setLineStyle(QCPGraph::lsLine); 
		QVector<double> X(5000);
		QVector<double> Y(5000);
		for (int j = 0;j<5000;j++){
			X[j] = xData[j+5000*i]-10*i;
			Y[j] = yData[j+5000*i]-1000*i+12000;
		}
		Plot->graph(i)->setPen(QPen(Qt::black));
		Plot->graph(i)->addData(X,Y);
	
	}
	Plot->xAxis->setLabel("X");
	Plot->legend->setVisible(true);
	Plot->xAxis->setRange(0,1);
	Plot->yAxis->setRange(-200,200);
	Plot->setAutoAddPlottableToLegend(true);
	Plot->setInteractions( QCP::iRangeZoom | QCP::iRangeDrag);
	Plot->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
	Plot->setWindowTitle(tr("EKG"));
	Plot->resize(1366,768);
	Plot->show();
	

}

QString ReadData::getDataName()
{
	return this->realDataName;
}