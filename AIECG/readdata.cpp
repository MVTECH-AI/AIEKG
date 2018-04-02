#include "readdata.h"

QString fileFull, fileName, filePath;  
QFileInfo fi;

ReadData::ReadData()
{

}

void ReadData::TrainAbnormalData()
{
	// find all files end with raw within certain direction
	QDir dir(".\\trainAbnormal");
	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	QFileInfoList list = dir.entryInfoList();
	for (int i = 0; i < list.size(); ++i) 
	{
		QFileInfo fileInfo = list.at(i);
		if (fileInfo.suffix() == "raw" || fileInfo.suffix() == "csv")
		{
			filepath.push_back(fileInfo.absoluteFilePath().toStdString());
		}
	}
	trainAbnormalSize = list.size();
	//qDebug() << trainAbnormalSize;

	// APIs from third-party
	for(auto it = 0; it != filepath.size(); it++)
	{
		result.push_back(readRawLeadData((filepath[it]).c_str(), MyData, strMsg));
		srcData.push_back(MyData);
		//qDebug() << QString::fromStdString(filepath[it]);
		srcMat.push_back(cvCreateMat(1,60000,CV_32FC1));
		auto *p = srcMat[it].ptr<float>(0);
		for (int j=0; j<60000; j++, p++, srcData[it]++)
		{
			*p = *srcData[it];			
			//qDebug() << *p  <<  " ";
		}	
	}

}

void ReadData::TrainNormalData()
{
	// find all files end with raw within certain direction
	QDir dir(".\\trainNormal");
	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	QFileInfoList list = dir.entryInfoList();
	for (int i = 0; i < list.size(); ++i) 
	{
		QFileInfo fileInfo = list.at(i);
		if (fileInfo.suffix() == "raw")
			filepath.push_back(fileInfo.absoluteFilePath().toStdString());
	}
	trainNormalSize = list.size();
	//qDebug() << trainNegativeSize;

	// APIs from third-party
	for(auto it = 0; it != filepath.size() - trainAbnormalSize; it++)
	{
		result.push_back(readRawLeadData((filepath[it+trainAbnormalSize]).c_str(),MyData,strMsg));//
		srcData.push_back(MyData);
		//qDebug() << QString::fromStdString(filepath[it+trainPositiveSize]);
		srcMat.push_back(cvCreateMat(1,60000,CV_32FC1));
		auto *p = srcMat[it+trainAbnormalSize].ptr<float>(0);
		for (int j = 0; j < 60000; j++, p++, srcData[it+trainAbnormalSize]++)
		{
			*p = *srcData[it+trainAbnormalSize];			
			//qDebug() << *p  <<  " ";
		}	
	}
}

void ReadData::TestAbnormalData()
{
	trainSize =  trainAbnormalSize+ trainNormalSize;

	// find all files end with raw within certain direction
	QDir dir(".\\testAbnormal");
	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	QFileInfoList list = dir.entryInfoList();
	for (int i = 0; i < list.size(); ++i) 
	{
		QFileInfo fileInfo = list.at(i);
		if (fileInfo.suffix() == "raw" || fileInfo.suffix() == "csv")
		{
			filepath.push_back(fileInfo.absoluteFilePath().toStdString());
		}
	}
	testAbnormalSize = list.size();
	//qDebug() << testPositiveSize;


	// APIs from third-party
	for(auto it = 0; it < filepath.size() - trainSize;it++) 
	{
		readRawLeadData((filepath[it+trainSize]).c_str(),MyData,strMsg);
		testData.push_back(MyData);
		//qDebug() << QString::fromStdString(filepath[it+trainSize]);
		testMat.push_back(cvCreateMat(1,60000,CV_32FC1));
		auto *p = testMat[it].ptr<float>(0);
		for (int j=0;j<60000;j++,p++,testData[it]++)
		{
			*p = *testData[it];			
			//qDebug() << *p  <<  " ";
		}	
	}
}

void ReadData::TestNormalData()
{
	trainSize = trainAbnormalSize + trainNormalSize;

	// find all files end with raw within certain direction
	QDir dir(".\\testNormal");
	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
	QFileInfoList list = dir.entryInfoList();
	for (int i = 0; i < list.size(); ++i) 
	{
		QFileInfo fileInfo = list.at(i);
		if (fileInfo.suffix() == "raw")
		{
			filepath.push_back(fileInfo.absoluteFilePath().toStdString());
		}
	}
	testNormalSize = list.size();
	//qDebug() << testNormalSize;


	// APIs from third-party
	for(auto it = 0; it < filepath.size()- trainSize - testAbnormalSize;it++)
	{
		readRawLeadData((filepath[it + trainSize + testAbnormalSize]).c_str(), MyData, strMsg);
		testData.push_back(MyData);
		//qDebug() << QString::fromStdString(filepath[it+trainSize+testPositiveSize]);
		testMat.push_back(cvCreateMat(1, 60000, CV_32FC1));
		auto *p = testMat[it+testAbnormalSize].ptr<float>(0);
		for (int j = 0;j < 60000; j++, p++, testData[it + testAbnormalSize]++){
			*p = *testData[it + testAbnormalSize];			
			//qDebug() << *p  <<  " ";
		}	
	}


}

void ReadData::readData()

{
	// for read 
	fileFull = QFileDialog::getOpenFileName();  
	fi = QFileInfo(fileFull);  
	fileName = fi.fileName();  
	filePath = fi.absolutePath();
	//status = readRawLeadData(fileFull.toStdString().c_str(),drawData,strMsg);
	//status = readcsvdata->readCsvData(fileFull,csvData);
	if (fi.suffix() == "raw")
	{
		status = readRawLeadData(fileFull.toStdString().c_str(),drawData,strMsg);
	}else if (fi.suffix() == "csv")
	{
		status = readcsvdata->readCsvData(fileFull,csvData);
	}
	
	this->realDataName =  fi.completeBaseName() + ".txt";
	//qDebug() << this->realDataName;
	//realData.push_back(drawData);
	realMat = cvCreateMat(1,60000,CV_32FC1);
	auto *p = realMat.ptr<float>(0);
	for (int j = 0; j < 60000; j++, p++){

		if (fi.suffix() == "raw")
		{
			*p = drawData[j];
		}else if(fi.suffix() == "csv")
		{
			*p = csvData[j];
		}
					
		//qDebug() << *p  <<  " ";
	}

	// for drawing the EKG	

	//	QVector<double> yData(60000);
	//	QVector<double> xData(60000);

	xData[0] = 0;

	if (status == 0)
	{
		for (int i=0;i<60000;i++)
		{
			
			if (fi.suffix() == "raw")
			{
				yData[i] = drawData[i];
			}else if(fi.suffix() == "csv")
			{
				yData[i] = csvData[i];
			}
			//qDebug() << drawData[i] ;
		}
		for (int j=1;j<60000;j++)
		{
			xData[j] = xData[j-1] +1./500;
		}
	}else if(status == -1) {
		QMessageBox::information(NULL,"File Error","Retry or not",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
		return;
	}else if (status == -2){
		QMessageBox::information(NULL,"Memory Error","Retry or not",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
		return;
	}
}

int ReadData::ptrianSize()
{
	return this->trainAbnormalSize;
}

int ReadData::ntrainSize()
{
	return this->trainNormalSize;
}

int ReadData::ptestSize()
{
	return this->testAbnormalSize;
}

int ReadData::ntestSize()
{
	return this->testNormalSize;
}

int ReadData::getStatus()
{
	return this->status;
}

QString ReadData::getDataName()
{
	return this->realDataName;
}

ReadData::~ReadData()
{

}