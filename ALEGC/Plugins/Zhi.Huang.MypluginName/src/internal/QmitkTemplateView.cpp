

// Blueberry
#include <berryISelectionService.h>
#include <berryIWorkbenchWindow.h>

// Qmitk
#include "QmitkTemplateView.h"

// Qt
#include<QMessageBox>
#include<qdebug.h>


const std::string MypluginNameUIControl::VIEW_ID = "zhi.huang.plugin1";
//int argc;
//char * argv[100];
MypluginNameUIControl::MypluginNameUIControl()//:a(argc, argv)
{
		pReadData = new ReadData;
	pReadData->readtrainingPositiveData();
	pReadData->readtrainingNegativeData();
	pReadData->readtestPositiveData();
	pReadData->readtestNegativeData();
	//this->predictCounter=-1;
}
MypluginNameUIControl::~MypluginNameUIControl()
{
}
void MypluginNameUIControl::SetFocus()
{
//  m_Controls.buttonPerformImageProcessing->setFocus();
}

void MypluginNameUIControl::CreateQtPartControl( QWidget *parent )
{
  // create GUI widgets from the Qt Designer's .ui file
  m_Controls.setupUi( parent );
  m_Parent=parent;
 // connect( m_Controls.buttonPerformImageProcessing, SIGNAL(clicked()), this, SLOT(DoImageProcessing()) );
  connect( m_Controls.pushButton_3, SIGNAL(clicked()), this, SLOT(Createimage()) );
  connect( m_Controls.pushButton_4, SIGNAL(clicked()), this, SLOT(onedelete()) );
  connect( m_Controls.toolButton, SIGNAL(clicked()), this, SLOT(Readdata()) );
  connect( m_Controls.pushButton_7, SIGNAL(clicked()), this, SLOT(qwidge()) );
  connect( m_Controls.pushButton_8, SIGNAL(clicked()), this, SLOT(qwidge_3()) );
  connect( m_Controls.toolButton_2, SIGNAL(clicked()), this, SLOT(qwidge_3()) );
  connect( m_Controls.pushButton_9, SIGNAL(clicked()), this, SLOT(qwidge_2()) );
  connect( m_Controls.pushButton_10, SIGNAL(clicked()), this, SLOT(qwidge_4()) );
  connect( m_Controls.toolButton_3, SIGNAL(clicked()), this, SLOT(Delete()) );
}
void MypluginNameUIControl::qwidge()
{
	m_Controls.tabWidget->setCurrentIndex(1);
}
void MypluginNameUIControl::qwidge_2()
{
	m_Controls.tabWidget->setCurrentIndex(2);
}
void MypluginNameUIControl::qwidge_3()
{
	m_Controls.tabWidget->setCurrentIndex(3);
}
void MypluginNameUIControl::qwidge_4()
{
	m_Controls.tabWidget->setCurrentIndex(4);
}
void MypluginNameUIControl::Delete()
{
	m_Controls.Delete();
	//m_Controls.pushButton_8->setVisible( false );
}
void MypluginNameUIControl::onedelete()
{
	m_Controls.pushButton_3->setVisible( false );
	m_Controls.pushButton_4->setVisible( false );
	m_Controls.label_2->setVisible(true);
}
void MypluginNameUIControl::Readdata()//data import
{

	QString fileFull, fileName, filePath,patientName;  
	QFileInfo fi;
	// for read 
	fileFull = QFileDialog::getOpenFileName();  
	fi = QFileInfo(fileFull); 
	realMat=cvCreateMat(1,60000,CV_32FC1);
	patientName=fi.completeBaseName()+".row";
	fileName = fi.fileName();  
	filePath = fi.absolutePath();
	realDataName=fi.completeBaseName() + ".txt";
	//qDebug("readString= %s",qPrintable(realDataName));
	status = readRawLeadData(fileFull.toStdString().c_str(),drawData,strMsg);
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
	pImageProcess = new ImageProcess;
	pImageProcess->doPCA(pReadData);
	pImageProcess->trainSVMs(pReadData);
	pImageProcess->testSVMs(pReadData);
	m_Controls.create(pImageProcess->predictSVMs(pReadData,realDataName,realMat),patientName);
	m_Controls.pushButton_3->setVisible( true );
	m_Controls.pushButton_4->setVisible( true );
	m_Controls.label_2->setVisible(false);
}


void MypluginNameUIControl::Createimage()//do ECG imaging
{
//	predictCounter +=1;
    realData.push_back(drawData);
	//return;
	//realMat.push_back(cvCreateMat(1,60000,CV_32FC1));
	realMat=cvCreateMat(1,60000,CV_32FC1);
	//auto *p = realMat[predictCounter].ptr<float>(0);
	auto *p = realMat.ptr<float>(0);
	/*for (int j=0;j<60000;j++,p++,realData[predictCounter]++){
			*p = *realData[predictCounter];			
			//qDebug() << *p  <<  " ";
		}
		*/
		for (int j = 0;j < 60000;j++,p++){
			*p = drawData[j];			
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
	for(int i =0; i < 12; i++){
		Plot->addGraph();			
		Plot->graph(i)->setLineStyle(QCPGraph::lsLine); 
		QVector<double> X(5000);
		QVector<double> Y(5000);
		for (int j = 0;j<5000;j++){
			X[j] = xData[j+5000*i]-10*i;
			Y[j] = yData[j+5000*i]-2000*i+6000;
		}
		Plot->graph(i)->setPen(QPen(Qt::black));
		Plot->graph(i)->addData(X,Y);
	
	}
	Plot->xAxis->setLabel("X");
	Plot->legend->setVisible(true);
	Plot->xAxis->setRange(0,20);
	Plot->yAxis->setRange(-16500,6500);
	Plot->setAutoAddPlottableToLegend(true);
	Plot->setInteractions( QCP::iRangeZoom | QCP::iRangeDrag);
	Plot->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
	//Plot->setWindowTitle(tr("EKG"));
	Plot->resize(1366,768);
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
//      m_Controls.labelWarning->setVisible( false );
//      m_Controls.buttonPerformImageProcessing->setEnabled( true );
      return;
    }
  }

//  m_Controls.labelWarning->setVisible( true );
 // m_Controls.buttonPerformImageProcessing->setEnabled( false );
}
/*int MypluginNameUIControl::getCounter()
{
  return predictCounter;
}*/

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
