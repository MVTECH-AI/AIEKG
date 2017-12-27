#include "processImage.h"
#include <QtNetwork>

ImageProcess::ImageProcess()
{
	right = 0;
}

// the given image is transformed into a row matrix
Mat ImageProcess::asRowMatrix( vector<Mat>& src, int rtype, double alpha = 1, double beta = 0)
{
	// number of samples
	size_t n = src.size();

	// if there is no sample, an empty matrix is returned
	if(n == 0)
		return Mat();

	// the dimension of the sample
	size_t d = src[0].total();

	// copy data
	Mat data(n, d, rtype);

	for(int i = 0; i < n; i++)
	{

		if(src[i].empty()) 
		{
			string error_message = format("Image number %d was empty, please check your input data.", i);
			CV_Error(CV_StsBadArg, error_message);
		}
		// make sure the data can be reshape
		if(src[i].total() != d) 
		{
			string error_message = format("Wrong number of elements in matrix #%d! Expected %d was %d.", i, d, src[i].total());
			CV_Error(CV_StsBadArg, error_message);
		}
		Mat xi = data.row(i);
		// converted into 1 row, n column format
		if(src[i].isContinuous())
		{
			src[i].reshape(1, 1).convertTo(xi, rtype, alpha, beta);
		} else {
			src[i].clone().reshape(1, 1).convertTo(xi, rtype, alpha, beta);
		}
	}
	return data;
}

// Principal Component Analysis
void ImageProcess::doPCA( ReadData *pst)
{
	vector<Mat>pcaMat = pst->srcMat;
	pcaData = asRowMatrix(pcaMat,CV_32FC1);
	// qDebug() << pcaData.rows << pcaData.cols;
	// 117 rows, 60000 cols

	// the number of Principal Component 
	num_components = 26;

	// run the PCA algorithm
	PCA pca(pcaData, Mat(), CV_PCA_DATA_AS_ROW, num_components);

	// copy the result 
	Mat mean = pca.mean.clone();
	Mat eigenvalues = pca.eigenvalues.clone();  
	Mat eigenvectors = pca.eigenvectors.clone();

	// project the raw data, the dst contains all principal components
	pcaDstMat = pca.project(pcaData);
	//matSize = pcaDstMat.rows;
	//qDebug() << pcaDstMat.rows << pcaDstMat.cols << endl;
	//117 rows, 15 cols 

	// back-project to the Mat
	pcaDst = pca.backProject(pcaDstMat);
	//qDebug() << pcaDst.cols << pcaDst.rows << endl; 
	//117 rows, 60000 cols
}

void ImageProcess::trainSVMs( ReadData *pst)
{
	// Set up training data
	for (int n = 0; n < pst->ptrianSize(); n++ ){
		trainingLabels.push_back(1);
	}
	for (int m = 0; m < pst->ntrainSize(); m++){
		trainingLabels.push_back(0);
	}
	Mat(trainingLabels).copyTo(trainingClasses);

	pcaDst.convertTo(trainingData, CV_32FC1);
	//qDebug() << trainingData.rows << trainingData.cols;
	// 71 rows, 60000 cols

	// Set up SVM's parameters
	CvSVMParams SVM_params;
	SVM_params.svm_type = CvSVM::C_SVC;
	SVM_params.kernel_type = CvSVM::LINEAR; 
	SVM_params.degree = 0;
	SVM_params.gamma = 0.1;
	SVM_params.coef0 = 0;
	SVM_params.C = 0.1;
	SVM_params.nu = 0;
	SVM_params.p = 0;
	//SVM_params.class_weights = 1;
	SVM_params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 96, 0.001);

	CvParamGrid nuGrid = CvParamGrid(1,1,0.0);  
	CvParamGrid coeffGrid = CvParamGrid(1,1,0.0);  
	CvParamGrid degreeGrid = CvParamGrid(1,1,0.0);

	// Train the SVM
	//SVM.train(trainingData, trainingClasses, Mat(), Mat(), SVM_params);

	SVM.train_auto(trainingData,trainingClasses,Mat(),Mat(),SVM_params,
		10,
		SVM.get_default_grid(CvSVM::C),
		SVM.get_default_grid(CvSVM::GAMMA),
		SVM.get_default_grid(CvSVM::P),
		nuGrid,
		coeffGrid,
		degreeGrid,
		TRUE);
	SVM.save("svmModel.xml");
}


void ImageProcess::testSVMs(ReadData *pst)
{
	right = 0;
	vector<Mat> pcaTestMat = pst->testMat;
	pcaTestData = asRowMatrix(pcaTestMat,CV_32FC1);
	PCA pca(pcaTestData, Mat(), CV_PCA_DATA_AS_ROW, num_components);	
	pcaTestDstMat = pca.project(pcaTestData);
	pcaTestDst = pca.backProject(pcaTestDstMat);

	//qDebug() << pcaTestDst.cols << pcaTestDst.rows ;
	// 56 rows, 60000 cols 

	// Set up test data
	for (int n = 0; n < pst->ptestSize(); n++){
		testLabels.push_back(1);
	}
	for (int m = 0; m < pst->ntestSize(); m++){
		testLabels.push_back(0);
	}

	for (int i = 0; i < pcaTestDstMat.rows; i++){
		result = -1;
		// the result of the trained SVM
		result = SVM.predict(Mat(pcaTestDst.row(i)));
		// qDebug() << result << endl;
		if (result == testLabels[i]){
			right++;
		}
	}
	qDebug() << right * 1.0 / testLabels.size() * 100;
	//0.8333333
}
int ImageProcess::predictSVMs(ReadData *pst)
{
	// load the trained model
	CvSVM svm;
	//svm.clear();
	string modelpath = "svmModel.xml";
	FileStorage svmFile(modelpath,FileStorage::READ);
	if(svmFile.isOpened()){
		svm.load(modelpath.c_str());
	}

	// prepare the data which will be predicted
	realpredictData = pst->realMat.reshape((1,1));
	//realpredictData = asRowMatrix(pcaRealMat,CV_32FC1);
	PCA pca(realpredictData, Mat(), CV_PCA_DATA_AS_ROW, num_components);

	//qDebug() << realpredictData.rows << realpredictData.cols ;
	// 1 row, 60000 cols

	realpredictDstMat = pca.project(realpredictData);
	realpredictDst = pca.backProject(realpredictDstMat);
	ofstream writeData(pst->getDataName().toStdString().c_str());
	int response = int(svm.predict(Mat(realpredictDst.row(0))));
	// show the result and write the abnormal data to EKG.txt
	if (response == 1){
//		QMessageBox::information(NULL,QString("result"),QString("this EKG is abnormal"));
		auto *p = pst->realMat.ptr<float>(0);
		for (int j = 0;j < 60000;j++,p++){
			writeData << *p << " ";
		}
		writeData << "\n";
		writeData.close();

		// transmit data
		beginTransmission(pst);

		//remove file to result if the ekg is abnormal
		QString toDir = ".\\result";
		QString dstFile = toDir + "//" + pst->getDataName();
		QFile::copy(pst->getDataName(),dstFile);
		QFile::remove(pst->getDataName());
	}
	else if(response == 0){
//		QMessageBox::information(NULL,QString("result"),QString("this EKG is normal"));
	}
	
	
	return response;
}

void ImageProcess::beginTransmission(ReadData *pst)
{
	QTcpSocket *client = new QTcpSocket;
	client->connectToHost("192.168.1.183",12345);
	ifstream inData(pst->getDataName().toStdString().c_str());
	int length;
	inData.seekg(0,ios::end);
	length = inData.tellg();
	inData.seekg(0,ios::beg);
	char *buffer = new char[length];
	inData.read(buffer,length);
	inData.close();
	client->write(pst->getDataName().toStdString().c_str());
	client->write(" ");
	client->write(buffer,length-1);
	delete buffer;
}


