#ifndef READCSVDATA_H
#define READCSVDATA_H

#include <QtGui>
#include <QString>
#include <QFileDialog>
#include <QFileInfo>
#include <qdebug.h>
using namespace std;

class ReadCsvData : public QWidget
{
	Q_OBJECT

public:
	ReadCsvData(QWidget *parent = 0);
	~ReadCsvData();
	int readCsvData(QString fileName,float *csv);
};

#endif //READCSVDATA_H