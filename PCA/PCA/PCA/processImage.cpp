#include "processImage.h"
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
	//qDebug() << pcaData.rows << pcaData.cols;
	// 71 rows, 60000 cols

	// the number of Principal Component 
	num_components = 15;

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
	//71 rows, 15 cols 
	
	// back-project to the Mat
	pcaDst = pca.backProject(pcaDstMat);
	//qDebug() << pcaDst.cols << pcaDst.rows << endl; 
	//71 rows, 60000 cols

	
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
	SVM_params.gamma = 1;
	SVM_params.coef0 = 0;
	SVM_params.C = 1;
	SVM_params.nu = 0;
	SVM_params.p = 0;
	SVM_params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 1000, 0.01);

	// Train the SVM
	SVM.train(trainingData, trainingClasses, Mat(), Mat(), SVM_params);
	SVM.save("svmModel.xml");
}


void ImageProcess::testSVMs(ReadData *pst)
{
	vector<Mat> pcaTestMat = pst->testMat;
	pcaTestData = asRowMatrix(pcaTestMat,CV_32FC1);
	PCA pca(pcaTestData, Mat(), CV_PCA_DATA_AS_ROW, num_components);	
	pcaTestDstMat = pca.project(pcaTestData);
	pcaTestDst = pca.backProject(pcaTestDstMat);
	//qDebug() << pcaTestDst.cols << pcaTestDst.rows ;
	// 18 rows, 60000 cols 
	
	// Set up test data
	for (int n = 0; n < pst->ptestSize(); n++ ){
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
	//qDebug() << right * 1.0 / testLabels.size();
	//0.8333333
}
void ImageProcess::predictSVMs(ReadData *pst)
{
	// load the trained model
	CvSVM svm;
	svm.clear();
	string modelpath = "svmModel.xml";
	FileStorage svmFile(modelpath,FileStorage::READ);
	if(svmFile.isOpened()){
		svm.load(modelpath.c_str());
	}

	// prepare the data which will be predicted
	vector<Mat> pcaRealMat = pst->realMat;
	realpredictData = asRowMatrix(pcaRealMat,CV_32FC1);
	PCA pca(realpredictData, Mat(), CV_PCA_DATA_AS_ROW, num_components);

	//qDebug() << realpredictData.rows << realpredictData.cols ;
	// 1 row, 60000 cols

	realpredictDstMat = pca.project(realpredictData);
	realpredictDst = pca.backProject(realpredictDstMat);
	ofstream writeData("EKG.txt",ios::app);
	// show the result and write the abnormal data to EKG.txt
	 if (svm.predict(Mat(realpredictDst.row(0))) == 1){
		 QMessageBox::information(NULL,QString("result"),QString("this EKG is abnormal"));
			auto *p = pst->realMat[pst->getCounter()].ptr<float>(0);
			for (int j = 0;j < 60000;j++,p++){
				writeData << *p << " ";
			}
			writeData << "\n";
		}
	 else{
		 QMessageBox::information(NULL,QString("result"),QString("this EKG is normal"));
	 }
	writeData.close();
}


