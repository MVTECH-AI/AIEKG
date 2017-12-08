

// Blueberry
#include <berryISelectionService.h>
#include <berryIWorkbenchWindow.h>

// Qmitk
#include "QmitkTemplateView.h"

// Qt
#include<QMessageBox>
#include<QString>
#include<qdebug.h>


const std::string MypluginNameUIControl::VIEW_ID = "zhi.huang.plugin1";
//int argc;
//char * argv[100];
MypluginNameUIControl::MypluginNameUIControl()//:a(argc, argv)
{
}
MypluginNameUIControl::~MypluginNameUIControl()
{
}
void MypluginNameUIControl::SetFocus()
{
  m_Controls.buttonPerformImageProcessing->setFocus();
}

void MypluginNameUIControl::CreateQtPartControl( QWidget *parent )
{
  // create GUI widgets from the Qt Designer's .ui file
  m_Controls.setupUi( parent );
  m_Parent=parent;
  connect( m_Controls.buttonPerformImageProcessing, SIGNAL(clicked()), this, SLOT(DoImageProcessing()) );
  connect( m_Controls.pushButton, SIGNAL(clicked()), this, SLOT(Createimage()) );
   connect( m_Controls.pushButton_5, SIGNAL(clicked()), this, SLOT(Readdata()) );
}


void MypluginNameUIControl::Readdata()//data import
{

	QString fileFull, fileName, filePath;  
	QFileInfo fi;
	// for read 
	fileFull = QFileDialog::getOpenFileName();  
	fi = QFileInfo(fileFull);  
	fileName = fi.fileName();  
	filePath = fi.absolutePath();
	status = readRawLeadData(fileFull.toStdString().c_str(),drawData,strMsg);
	std::cout<<status<<endl;
	if (status == 0)
	{}
	else if(status == -1) {
		QMessageBox::information(NULL,"File Error","Retry or not",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
		return;
	}
	else if (status == -2){
		QMessageBox::information(NULL,"Memory Error","Retry or not",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
		return;
	}
}
// the given image is transformed into a row matrix
Mat MypluginNameUIControl::asRowMatrix( vector<Mat>& src, int rtype, double alpha = 1, double beta = 0)
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
void MypluginNameUIControl::predictSVMs(MypluginNameUIControl *pst)
{
	CvSVM svm;
	svm.clear();
	string modelpath = "svmModel.xml";
	FileStorage svmFile(modelpath,FileStorage::READ);
	if(svmFile.isOpened()){
		svm.load(modelpath.c_str()); 
	}

	vector<Mat> pcaRealMat = pst->realMat;
	realpredictData = asRowMatrix(pcaRealMat,CV_32FC1);
	PCA pca(realpredictData, Mat(), CV_PCA_DATA_AS_ROW, num_components);

	//qDebug() << realpredictData.rows << realpredictData.cols ;
	// 1 row, 60000 cols

	realpredictDstMat = pca.project(realpredictData);
	realpredictDst = pca.backProject(realpredictDstMat);
	ofstream writeData("EKG.txt");
	 if (svm.predict(Mat(realpredictDst.row(0))) == 1){
		 qDebug() << 1;
			auto *p = pst->realMat[0].ptr<float>(0);
			for (int j = 0;j < 60000;j++,p++){
				writeData << *p << " ";
			}
			writeData << "\n";
		}
	writeData.close();
	//qDebug() << svm.predict(Mat(projectedMat.row(0)));
}
void MypluginNameUIControl::Createimage()//do ECG imaging
{
    realData.push_back(drawData);
	//return;
	realMat.push_back(cvCreateMat(1,60000,CV_32FC1));
	auto *p = realMat[0].ptr<float>(0);
	for (int j=0;j<60000;j++,p++,realData[0]++){
			*p = *realData[0];			
			//qDebug() << *p  <<  " ";
		}

	// for drawing the EKG	
	QVector<double>yData(60000);
	QVector<double>xData(60000);
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
	QCustomPlot *Plot = new QCustomPlot;
	Plot->addGraph();
	Plot->graph(0)->setData(xData,yData);
	Plot->xAxis->setLabel("X");
	Plot->yAxis->setLabel("Y");
	Plot->xAxis->setRange(0,100);
	Plot->yAxis->setRange(-1000,1000);
	Plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	Plot->show();
}
void MypluginNameUIControl::OnSelectionChanged( berry::IWorkbenchPart::Pointer /*source*/,
                                             const QList<mitk::DataNode::Pointer>& nodes )
{
  // iterate all selected objects, adjust warning visibility
  foreach( mitk::DataNode::Pointer node, nodes )
  {
    if( node.IsNotNull() && dynamic_cast<mitk::Image*>(node->GetData()) )
    {
      m_Controls.labelWarning->setVisible( false );
      m_Controls.buttonPerformImageProcessing->setEnabled( true );
      return;
    }
  }

  m_Controls.labelWarning->setVisible( true );
  m_Controls.buttonPerformImageProcessing->setEnabled( false );
}


void MypluginNameUIControl::DoImageProcessing()
{
	
  QList<mitk::DataNode::Pointer> nodes = this->GetDataManagerSelection();
  if (nodes.empty()) return;

  mitk::DataNode* node = nodes.front();
  if (!node)
  {
    // Nothing selected. Inform the user and return
    QMessageBox::information( NULL, "Template", "Please load and select an image before starting image processing.");
    return;
  }

  // here we have a valid mitk::DataNode

  // a node itself is not very useful, we need its data item (the image)
  mitk::BaseData* data = node->GetData();
  
  if (data)
  {
    // test if this data item is an image or not (could also be a surface or something totally different)
    mitk::Image* image = dynamic_cast<mitk::Image*>( data );
    if (image)
    {
      std::stringstream message;
      std::string name;
      message << "Performing image processing for image ";
      if (node->GetName(name))
      {
        // a property called "name" was found for this DataNode
        message << "'" << name << "'";
      }
      message << ".";
      MITK_INFO << message.str();
      // actually do something here...

    }
  }
}
