#ifndef PROCESSIMAGE_H
#define PROCESSIMAGE_H
#include "readdata.h"
#include <fstream>
#include <opencv2/ml/ml.hpp>

class ReadData;

class ImageProcess : public ReadData
{
	Q_OBJECT
public:
	ImageProcess();
	Mat asRowMatrix( vector<Mat>& src, int rtype, double alpha , double beta );
	void doPCA( ReadData *pst);
	void trainSVMs( ReadData *pst);
	void testSVMs( ReadData *pst);
	void predictSVMs(ReadData *pst);
	
private:
	Mat	pcaData;
	Mat pcaDstMat;
	Mat pcaDst;
	//int matSize;
	int num_components;
	Mat trainingData;
	vector<int> trainingLabels;
	vector<int> testLabels;
	Mat trainingClasses;
	Mat pcaTestData;
	Mat pcaTestDstMat;
	Mat pcaTestDst;
	CvSVM SVM;
	int result;
	int right ;
	Mat realpredictData;
	Mat realpredictDstMat;
	Mat realpredictDst;

		
	
};



#endif