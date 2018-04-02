#include "readcsvdata.h"

#define ROW_COUNT 5000
#define COL_COUNT 12

float array[ROW_COUNT][COL_COUNT] = { 0 };
float data1[ROW_COUNT][COL_COUNT] = { 0 };
float data2[COL_COUNT][ROW_COUNT] = { 0 };
float data3[ROW_COUNT*COL_COUNT] = { 0 };

ReadCsvData::ReadCsvData(QWidget *parent)
	: QWidget(parent)
{

}

int ReadCsvData::readCsvData(QString fileName,float *csv)
{
	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return 0;
	}
	int line_number = 0;

	while (!file.atEnd())
	{
		QString lineString = QString(file.readLine().trimmed());
		//qDebug() << lineString.length();
		QStringList str_list = lineString.split(QRegExp("\\s{1,}"));
		//qDebug() << str_list.length();
		if (str_list.size() >= 14)
		{
			str_list.takeFirst();
			str_list.takeLast();
		}
		if (str_list.size() >= 13)
		{
			str_list.takeLast();
		}
		//qDebug() << str_list;

		for (int i = 0; i < str_list.length(); ++i)
		{
			array[line_number][i] = str_list[i].toFloat();
			//qDebug() << line_number << i << array[line_number][i];
		}
		++line_number;

		//qDebug() << str_list.length();
		//qDebug() << line_number;

		if (line_number == 5000)
		{
			for (int i = 0; i < (line_number - 1); i++)
			{
				for (int j = 0; j < str_list.length(); j++)
				{
					data1[i][j] = array[i+1][j];//去掉第一行
					//qDebug() << data1[i][j];
				}
			}

			for (int i = 0; i < (line_number - 1); i++)
			{
				for (int j = 0; j < str_list.length(); j++)
				{
					data2[j][i] = data1[i][j];//做矩阵转置
				}
			}

			for (int i = 0; i < str_list.length(); ++i)
			{
				for (int j = 0; j < (line_number - 1); j++)
				{
					data3[i*(line_number - 1)+j] = data2[i][j];//将二维数组转换为一维数组
					//qDebug() << data2[i][j];
				}
			}

			for (int i = 0; i < 60000; i++)
			{
				//qDebug() << data3[i];
				*csv = data3[i];
				//qDebug() << *pp;
				csv++;
			}
		}
	}

	return 0;
}

ReadCsvData::~ReadCsvData()
{

}