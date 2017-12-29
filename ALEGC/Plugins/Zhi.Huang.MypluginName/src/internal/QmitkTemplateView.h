

#ifndef QmitkTemplateView_h
#define QmitkTemplateView_h

//#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <iostream>
//#include <fstream>
//#include <opencv2/ml/ml.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QtGui/QApplication>
#include <berryISelectionListener.h>
#include <QmitkAbstractView.h>
//#include <QMenu>
#include<QString>
#include "qcustomplot.h"
using namespace cv;
#include "ui_QmitkTemplateViewControls.h"
#include "SCRawReader.h"
#pragma comment(lib,"SCRawReader.lib")
#include"readdata.h"
#include"processImage.h"

/**
\
  \brief $(view-class-name)

  \warning  This class is not yet documented. Use "git blame" and ask the author to provide basic documentation.

  \sa QmitkAbstractView
  \ingroup ${plugin_target}_internal
*/
class MypluginNameUIControl: public QmitkAbstractView
{
  // this is needed for all Qt objects that should have a Qt meta-object
  // (everything that derives from QObject and wants to have signal/slots)
   Q_OBJECT
  public:
    MypluginNameUIControl();
   ~MypluginNameUIControl();
    static const std::string VIEW_ID;
	Mat realMat;
  protected slots:

    /// \brief Called when the user clicks the GUI button
    void DoImageProcessing();
	void Createimage();
	void qwidge();
	void qwidge_2();
	void qwidge_3();
	void qwidge_4();
	//void link_qwidge_3();
	void Delete();
	void onedelete();
	public slots:
		void Readdata();
  private:
	QString realDataName;
	ReadData *pReadData;
	ImageProcess *pImageProcess;
	char strMsg[255];
	int status;
	short drawData[RAWDATALEN*12];
  protected:
	vector<short *> realData;
    virtual void CreateQtPartControl(QWidget *parent);
    virtual void SetFocus();

    /// \brief called by QmitkFunctionality when DataManager's selection has changed
    virtual void OnSelectionChanged( berry::IWorkbenchPart::Pointer source,
                                     const QList<mitk::DataNode::Pointer>& nodes );
	QWidget *m_Parent;
    Ui::MypluginNameUIControl m_Controls;

};

#endif // $(view-file-name)_h
