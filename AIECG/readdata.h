#ifndef READDATA_H
#define READDATA_H

#include <QtGui>
#include <QWidget>
#include "SCRawReader.h"
#include <string.h>
#include <QString>
#include "qcustomplot.h"
#include <QVector>
#include <QMessageBox>
#include <qdebug.h>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QMenu>
#include <QAction>
#include <QDir>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include "readcsvdata.h"
#pragma comment(lib,"SCRawReader.lib")
using namespace cv;
using namespace std;

extern QVector<double> yData;
extern QVector<double> xData;

class ReadData : public QWidget
{
	Q_OBJECT

public:
	ReadData();
	~ReadData();
	vector<Mat> srcMat;
	vector<Mat> testMat;
	//vector<Mat> realMat;
	Mat realMat;
	void TrainAbnormalData();
	void TrainNormalData();
	void TestAbnormalData();
	void TestNormalData();
	QString getDataName();
	int ptrianSize();
	int ntrainSize();
	int ptestSize();
	int ntestSize();
	int getStatus();
	int getCounter();
	void readData();

private:
	vector<string> filepath;
	//vector<string> realfilepath;
	short MyData[RAWDATALEN*12];
	short drawData[RAWDATALEN*12];
	float csvData[60000];

	vector<short *> srcData;
	vector<short *> testData;
	vector<short *> realData;
	QString realDataName;
	char strMsg[255];
	vector<int> result;
	int status;
	int trainAbnormalSize;
	int trainNormalSize;
	int testAbnormalSize;
	int testNormalSize;
	int testSize;
	int trainSize;
	int predictCounter;
	ReadCsvData *readcsvdata;
};

#endif // READDATA_H