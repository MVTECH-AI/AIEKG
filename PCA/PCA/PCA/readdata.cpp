#include "readdata.h"



ReadData::ReadData()
{
	
	//this->readPositiveData();
	//this->readNegativeData();
	//this->readTestData();

}

void ReadData::readtrainingPositiveData()
{

	// find all files end with raw within certain direction
	QDir dir("C:\\Users\\Administrator\\Desktop\\OpenCV\\PCA\\PCA\\PCA\\trainPositive");
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
	QDir dir("C:\\Users\\Administrator\\Desktop\\OpenCV\\PCA\\PCA\\PCA\\trainNegative");
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
	QDir dir("C:\\Users\\Administrator\\Desktop\\OpenCV\\PCA\\PCA\\PCA\\testPositive");
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
	QDir dir("C:\\Users\\Administrator\\Desktop\\OpenCV\\PCA\\PCA\\PCA\\testNegative");
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

void ReadData::Open()
{

	QString fileFull, fileName, filePath;  
	QFileInfo fi;


	// for read 
	fileFull = QFileDialog::getOpenFileName();  
	fi = QFileInfo(fileFull);  
	fileName = fi.fileName();  
	filePath = fi.absolutePath();
	status = readRawLeadData(fileFull.toStdString().c_str(),drawData,strMsg);
	//qDebug() << status;
	realData.push_back(drawData);
	realMat.push_back(cvCreateMat(1,60000,CV_32FC1));
	auto *p = realMat[0].ptr<float>(0);
	for (int j=0;j<60000;j++,p++,realData[0]++){
			*p = *realData[0];			
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
	Plot->addGraph();
	Plot->graph(0)->setData(xData,yData);
	Plot->xAxis->setLabel("X");
	Plot->yAxis->setLabel("Y");
	Plot->xAxis->setRange(0,100);
	Plot->yAxis->setRange(-1000,1000);
	Plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	Plot->show();
	//Plot->savePng("wsf123.png",1000,1000);

}

