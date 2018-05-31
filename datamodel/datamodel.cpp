#include "datamodel.h"


DataModel::DataModel(QWidget *parent)
	: QMainWindow(parent)
{
	
	init();

	currentTimeLabel = new QLabel;
	timer = new QTimer(this);
	timer->start(1000);
	connect(timer,SIGNAL(timeout()),this,SLOT(createStatusBar()));

	createMenus();
	createStatusBar();
	display();
	setWindowTitle("DataModel");

	widget = new QWidget(this);
	widget->setLayout(mainLayout);
	this->setCentralWidget(widget);
}

void DataModel::init()
{
	tableModel=new QStandardItemModel(40,2,this);
	tableModel->setHeaderData(0,Qt::Horizontal,tr("Name"));
	tableModel->setHeaderData(1,Qt::Horizontal,"Result");
	tableView = new QTableView;
	tableView->setModel(tableModel);
	tableView->resizeColumnsToContents();//将列设为与内容相匹配
	tableView->resizeRowsToContents();//将行设为与内容相匹配
	tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	tableView->verticalHeader()->setResizeMode(QHeaderView::Stretch);
	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置整行选中
	tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置单元格为只读属性，不可编辑
	connect(tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(rowClicked(QModelIndex)));
}

void DataModel::display()
{
	//Right Layout
	GreenBtnLabel = new QLabel;
	GreenBtnLabel->setPixmap(QPixmap(":/button_green.png"));

	RedBtnLabel = new QLabel;
	RedBtnLabel->setPixmap(QPixmap(":/button_red.png"));

	hboxLayout = new QHBoxLayout;
	hboxLayout->addWidget(GreenBtnLabel);
	hboxLayout->addWidget(RedBtnLabel);

	Heart2Label = new QLabel;
	Heart2Label->setPixmap(QPixmap(":/heart2.png"));

	Heart1Label = new QLabel;
	Heart1Label->setPixmap(QPixmap(":/heart1.png"));

	vboxLayout = new QVBoxLayout;
	vboxLayout->addWidget(Heart2Label);
	vboxLayout->addWidget(Heart1Label);

	ventRateLabel = new QLabel(tr("&Vent rate:"));
	ventRateLineEdit = new QLineEdit;
	ventRateLabel->setBuddy(ventRateLineEdit);

	PRintLabel = new QLabel(tr("&PR int:"));
	PRintLineEdit = new QLineEdit;
	PRintLabel->setBuddy(PRintLineEdit);

	QRSdurLabel = new QLabel(tr("&QRS dur:"));
	QRSdurLineEdit = new QLineEdit;
	QRSdurLabel->setBuddy(QRSdurLineEdit); 

	QTLabel = new QLabel(tr("&QT/QTc:"));
	QTLineEdit = new QLineEdit;
	QTLabel->setBuddy(QTLineEdit);

	PRTaxesLabel = new QLabel(tr("&P-R-T axes:")); 
	PRTaxesLineEdit = new QLineEdit;
	PRTaxesLabel->setBuddy(PRTaxesLineEdit);
	
	rightmiddleLayout = new QGridLayout;
	rightmiddleLayout->addWidget(ventRateLabel,0,0);
	rightmiddleLayout->addWidget(ventRateLineEdit,0,1);
	rightmiddleLayout->addWidget(PRintLabel,1,0);
	rightmiddleLayout->addWidget(PRintLineEdit,1,1);
	rightmiddleLayout->addWidget(QRSdurLabel,2,0);
	rightmiddleLayout->addWidget(QRSdurLineEdit,2,1);
	rightmiddleLayout->addWidget(QTLabel,3,0);
	rightmiddleLayout->addWidget(QTLineEdit,3,1);
	rightmiddleLayout->addWidget(PRTaxesLabel,4,0);
	rightmiddleLayout->addWidget(PRTaxesLineEdit,4,1);

	rightLayout = new QGridLayout;
	rightLayout->addLayout(hboxLayout,0,0);
	rightLayout->addLayout(rightmiddleLayout,1,0);
	rightLayout->addLayout(vboxLayout,2,0);
	rightLayout->setRowStretch(0,1);
	rightLayout->setRowStretch(1,5);
	rightLayout->setRowStretch(2,5);

	//middle Layout
	ILabel = new QLabel(tr("I"));

	mainLayout = new QGridLayout;
	mainLayout->addWidget(tableView,0,0);
	mainLayout->addWidget(ILabel,0,1);
	mainLayout->addLayout(rightLayout,0,2);
	mainLayout->setColumnStretch(0,1);
	mainLayout->setColumnStretch(1,5);
	mainLayout->setColumnStretch(2,1);
}

void DataModel::loadSignal()
{
	QString mystring = QFileDialog::getExistingDirectory(this,"one","./");

	QDir mydir;  
	mydir.setPath(mystring);  
	mydir.setFilter(QDir::Files | QDir::NoSymLinks);  
	mydir.setSorting(QDir::Name);  
	QFileInfoList list = mydir.entryInfoList();  
	QString str;  
	for(int i = 0; i < list.length(); i++)  
	{  
		QFileInfo fileinfo = list.at(i);  
		str = fileinfo.fileName();
		QStandardItem *item = new QStandardItem(str);  

		tableModel->setItem(i,0,item);  
	}
}

void DataModel::createStatusBar()
{
	QDateTime currentTime = QDateTime::currentDateTime();
	QString Timestr = currentTime.toString("yyyy-MM-dd hh:mm:ss dddd");
	currentTimeLabel->setFrameStyle(QFrame::Sunken);
	currentTimeLabel->setText(Timestr);
	currentTimeLabel->setAlignment(Qt::AlignHCenter);
	statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}")); // 设置不显示label的边框
//	statusBar()->setSizeGripEnabled(false); //设置是否显示右边的大小控制点
	statusBar()->addPermanentWidget(currentTimeLabel);
}

void DataModel::rowClicked(const QModelIndex &index)
{
	QStandardItem *item = tableModel->itemFromIndex(index);
	QString str = item->text();
	QFileInfo fileinfo = QFileInfo(str);
	if(fileinfo.suffix() == "csv")
	{
		qDebug() << "Read csv data";
	}
	else if(fileinfo.suffix() == "raw")
	{
		qDebug()<<"Read raw data";
	}
}

void DataModel::createMenus()
{
	LoadSignalAction = new QAction(tr("&Load signal"), this);
	connect(LoadSignalAction, SIGNAL(triggered()), this, SLOT(loadSignal()));

	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(LoadSignalAction);
}

DataModel::~DataModel()
{

}