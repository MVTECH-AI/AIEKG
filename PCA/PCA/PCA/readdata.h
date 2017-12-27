#ifndef READDATA_H
#define READDATA_H

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
#pragma comment(lib,"SCRawReader.lib")
using namespace cv;
using namespace std;


class ReadData : public QObject
{
	Q_OBJECT

public:
	ReadData();
	~ReadData();
	vector<Mat> srcMat;
	vector<Mat> testMat;
	//vector<Mat> realMat;
	Mat realMat;
	void readtrainingPositiveData();
	void readtrainingNegativeData();
	void readtestPositiveData();
	void readtestNegativeData();
	QString getDataName();
	int ptrianSize();
	int ntrainSize();
	int ptestSize();
	int ntestSize();
	int getStatus();
	int getCounter();
private:
	vector<string> filepath;
	//vector<string> realfilepath;
	short MyData[RAWDATALEN*12];
	short drawData[RAWDATALEN*12];
	vector<short *> srcData;
	vector<short *> testData;
	vector<short *> realData;
	QString realDataName;
	char strMsg[255];
	vector<int> result;
	int status;
	int trainPositiveSize;
	int trainNegativeSize;
	int testPositiveSize;
	int testNegativeSize;
	int testSize;
	int trainSize;
	int predictCounter;

private slots:
	void Open();

};
#endif // READDATA_H