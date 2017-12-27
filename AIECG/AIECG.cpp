#include "AIECG.h"

QVector<double> yData(60000);
QVector<double> xData(60000);

AIECG::AIECG(QWidget *parent)
	: QMainWindow(parent)
{

	pReadData = new ReadData;
	pReadData->readtrainingPositiveData();
	pReadData->readtrainingNegativeData();
	pReadData->readtestPositiveData();
	pReadData->readtestNegativeData();

	pImageProcess = new ImageProcess;
	pImageProcess->doPCA(pReadData);
	pImageProcess->trainSVMs(pReadData);
	pImageProcess->testSVMs(pReadData);
	//connect(beginAction,SIGNAL(triggered()),this,SLOT(BeginSVM()));
	mdiArea = new QMdiArea;
	textEdit = new QTextEdit;

	splitter = new QSplitter(Qt::Vertical);
	splitter->addWidget(mdiArea);
	splitter->addWidget(textEdit);
	splitter->setStretchFactor(10, 1);

	display =new Display;
	serialdialog = new SerialDialog;
	respiredialog = new RespireDialog;
	dataAcquisitiondialog = new DataAcquisitionDialog;

	createActions();
	createMenus();
	createToolBars();

	statusBar()->showMessage(tr("Ready"),2000);

//	image.load("C:/CppWorkspace/print/image/flower.jpg"); //导入图片

	setWindowIcon(QIcon("C:/CppWorkspace/AIECG/images/AIECG.png"));
	setCentralWidget(splitter);
	setWindowTitle("AIECG");
}

void AIECG::newfile()
{
	QDialog *w = new QDialog;
	windowLabel = new QLabel(tr("window as"));
	windowListWidget = new QListWidget;
	okButton = new QPushButton(tr("OK"));
	cancelButton = new QPushButton(tr("Cancel"));

	windowListWidget->addItem("Manual channel definition window");
	windowListWidget->addItem("Manual plot-signal definition window");
	windowListWidget->addItem("Manual grid-signal definition window");
	windowListWidget->addItem("Manual IBI-signal definition window");
	windowListWidget->addItem("Text window");

	hboxLayout = new QHBoxLayout;
	hboxLayout->addWidget(okButton);
	hboxLayout->addWidget(cancelButton);

	vboxLayout = new QVBoxLayout;
	vboxLayout->addWidget(windowLabel);
	vboxLayout->addWidget(windowListWidget);
	vboxLayout->addLayout(hboxLayout);

	connect(windowListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(openChannelWidnow()));
	connect(windowListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(openPlotSignalWindow()));
	connect(windowListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(openGridSignalWindow()));
	connect(windowListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(openIBISignalWindow()));
	connect(windowListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(openTextWindow()));

	connect(okButton, SIGNAL(clicked()), this, SLOT(openChannelWidnow()));
	connect(okButton, SIGNAL(clicked()), this, SLOT(openPlotSignalWindow()));
	connect(okButton, SIGNAL(clicked()), this, SLOT(openGridSignalWindow()));
	connect(okButton, SIGNAL(clicked()), this, SLOT(openIBISignalWindow()));
	connect(okButton, SIGNAL(clicked()), this, SLOT(openTextWindow()));

	connect(cancelButton, SIGNAL(clicked()), w, SLOT(close()));

	w->setLayout(vboxLayout);
	w->setWindowTitle("Open");
	w->show();
}

void AIECG::cut()
{
	board = QApplication::clipboard();//获得系统剪贴板对象
	board->setText("Text from Qt Application");//通过setText()将数据放置到剪贴板
}

void AIECG::copy()
{
	board = QApplication::clipboard();
	board->setText("Text from Qt Application");
}

void AIECG::paste()
{
	board = QApplication::clipboard();
	QString str = board->text();//从剪贴板获得数据
	QMessageBox::information(NULL, "From clipboard", str);
}

void AIECG::print()
{
	QPrinter printer; //构建新对象
	QPrintDialog printDialog(&printer, this);

	if (printDialog.exec()) //用于判断用户是否点击“打印”按钮
	{
		QPainter painter(&printer);
		QRect rect = painter.viewport(); //获取QPainter对象的矩形区域
		QSize size = image.size(); //获取图片的大小
		size.scale(rect.size(), Qt::KeepAspectRatio);//按照图形比例大小重新设置视口矩形区域

		//打印
		painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
		painter.setWindow(image.rect());
		painter.drawImage(0, 0, image);
	}
}

void AIECG::printPreview()
{
	QPrinter printer;
	QPrintPreviewDialog previewDialog(&printer, this);

	connect(&previewDialog, SIGNAL(paintRequested(QPrinter*)), this, SLOT(printDocument(QPrinter*)));

	previewDialog.exec();
}

void AIECG::setUpPage()
{
	QPrinter printer;
	QPageSetupDialog pageSetUpDialog(&printer, this);
	if (pageSetUpDialog.exec() == QDialog::Accepted)
	{
		printer.setOrientation(QPrinter::Landscape);
	} 
	else
	{
		printer.setOrientation(QPrinter::Portrait);
	}
}

void AIECG::printDocument(QPrinter *printer)
{
	textEdit->print(printer); 
}

void AIECG::about()
{
	QMessageBox::about(this,tr("About AIECG"),
		tr("<h2>AIECG 1.1</h2>"
		"<p>Copyright &copy; 2017 Software Inc."
		"<p>AIECG is a small application that "
		"demonstrates QAction, QMainWindow, QMenuBar, "
		"QStatusBar, QToolBar, and many other Qt classes."));
}

void AIECG::openChannelWidnow()
{
	if(windowListWidget->currentRow() == 0)
	{
		editor = new Editor;
		editor->newFile();
		subWindow = mdiArea->addSubWindow(editor);
		subWindow->setWindowState(Qt::WindowMaximized);		
		subWindow->setWindowTitle("Manual channel definition window");
		subWindow->show();
	}
}

void AIECG::openPlotSignalWindow()
{

	if (windowListWidget->currentRow() == 1  )
	{
		editor = new Editor;
		editor->newFile();
		subWindow = mdiArea->addSubWindow(editor);
		subWindow->setWindowState(Qt::WindowMaximized);		
		subWindow->setWindowTitle("Manual plot-signal definition window");
		subWindow->show();
	}
}

void AIECG::openGridSignalWindow()
{
	if (windowListWidget->currentRow() == 2 )
	{
		editor = new Editor;
		editor->newFile();
		subWindow = mdiArea->addSubWindow(editor);
		subWindow->setWindowState(Qt::WindowMaximized);		
		subWindow->setWindowTitle("Manual grid-signal definition window");
		subWindow->show();
	}
}

void AIECG::openIBISignalWindow()
{
	if (windowListWidget->currentRow() == 3 )
	{
		editor = new Editor;
		editor->newFile();
		subWindow = mdiArea->addSubWindow(editor);
		subWindow->setWindowState(Qt::WindowMaximized);		
		subWindow->setWindowTitle("Manual IBI-signal definition window");
		subWindow->show();
	}
}

void AIECG::openTextWindow()
{
	if (windowListWidget->currentRow() == 4)
	{
		editor = new Editor;
		editor->newFile();
		subWindow = mdiArea->addSubWindow(editor);
		subWindow->setWindowState(Qt::WindowMaximized);		
		subWindow->setWindowTitle("Text window");
		subWindow->show();
	}
}

void AIECG::loadSignals()
{
	pReadData->readData();
	QCustomPlot *Plot = new QCustomPlot;
	for(int i =0; i < 12; i++)
	{
		Plot->addGraph();
		Plot->graph()->setPen(QPen(Qt::black));
		Plot->graph()->setLineStyle(QCPGraph::lsLine); 
		QVector<double> X(5000);
		QVector<double> Y(5000);
		for (int j = 0;j<5000;j++)
		{
			X[j] = xData[j+5000*i]-10*i;
			Y[j] = yData[j+5000*i]-2000*i+6000;
		}
		Plot->graph()->addData(X,Y);
	}
	Plot->xAxis->setLabel("X");
	Plot->xAxis->setRange(0,10);
	Plot->xAxis->setPadding(5); // a bit more space to the left border
	Plot->xAxis->setBasePen(QPen(Qt::red));
	Plot->xAxis->setTickPen(QPen(Qt::red));
	Plot->xAxis->setSubTickPen(QPen(Qt::red));
	Plot->xAxis->grid()->setSubGridVisible(true);
	Plot->xAxis->setTickLabelColor(Qt::red);
	Plot->xAxis->setLabelColor(Qt::red);
	Plot->xAxis->grid()->setPen(QPen(QColor(255, 0, 0), 0, Qt::SolidLine));
	Plot->xAxis->grid()->setSubGridPen(QPen(QColor(255, 0, 0), 0, Qt::DotLine));

	Plot->yAxis->setLabel("Y");
	Plot->yAxis->setRange(-16500,6500);
	Plot->yAxis->setPadding(5); // a bit more space to the left border
	Plot->yAxis->setBasePen(QPen(Qt::red));
	Plot->yAxis->setTickPen(QPen(Qt::red));
	Plot->yAxis->setSubTickPen(QPen(Qt::red));
	Plot->yAxis->grid()->setSubGridVisible(true);
	Plot->yAxis->setTickLabelColor(Qt::red);
	Plot->yAxis->setLabelColor(Qt::red);
	Plot->yAxis->grid()->setPen(QPen(QColor(255, 0, 0), 0, Qt::SolidLine));
	Plot->yAxis->grid()->setSubGridPen(QPen(QColor(255, 0, 0), 0, Qt::DotLine));

	Plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	subWindow = mdiArea->addSubWindow(Plot);
	subWindow->resize(600, 400);
	subWindow->setWindowState(Qt::WindowMaximized);
	subWindow->setWindowTitle("Twelve lead ECG waveform");
	subWindow->show();
}

void AIECG::loadText()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Load Text"), QString(),
		tr("Ascii file(*.*);;Text file(*.txt);;Macro file(*.dpm);;Macro list file(*.dpl)"));

	if (!fileName.isEmpty())
	{
		QFile file(fileName);
		if (!file.open(QIODevice::ReadOnly))
		{
			QMessageBox::critical(this,tr("ERROR"),tr("couldn't open the file"));
			return;
		} 
		else
		{
			QTextStream stream(&file);
			editor = new Editor;
			editor->newFile();
			editor->setText(stream.readAll());
			subWindow = mdiArea->addSubWindow(editor);
			subWindow->setWindowState(Qt::WindowMaximized);	

			file.flush();
		}
	}
	else
	{
		QMessageBox::critical(this,tr("ERROR"),tr("you don't open any file"));
	}
}

void AIECG::beginSVM()
{
	result = pImageProcess->predictSVMs(pReadData);
	if (result == 1)
	{
		textEdit->setText("the ECG is abnormal");	
	}
	else if (result == 0)
	{
		textEdit->setText("the ECG is normal");	
	}
}

void AIECG::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(NewFileAction);
	fileMenu->addAction(LoadSignalAction);
	fileMenu->addAction(LoadSignalsAction);
	fileMenu->addAction(LoadTextAction);
	fileMenu->addAction(LoadMacrosAction);
	fileMenu->addAction(LoadWindowAction);
//	fileMenu->addAction(OpenSerialPortAction);
	openSubMenu = fileMenu->addMenu(tr("&Open serial port"));
	openSubMenu->addAction(OpenSerialPortAction);
	openSubMenu->addAction(OpenRespirationAction);
	separatorAction = fileMenu->addSeparator();
	fileMenu->addAction(CloseChildAction);
	separatorAction = fileMenu->addSeparator();
	fileMenu->addAction(SaveSignalAction);
	fileMenu->addAction(SaveTextAction);
	fileMenu->addAction(SaveWindowAction);
	separatorAction = fileMenu->addSeparator();
	fileMenu->addAction(ExportWindowAction);
	separatorAction = fileMenu->addSeparator();
	fileMenu->addAction(PageSetupAction);
	fileMenu->addAction(PrintPreviewAction);
	fileMenu->addAction(PrintAction);
	separatorAction = fileMenu->addSeparator();
	fileMenu->addAction(ExitAction);

	editMenu = menuBar()->addMenu(tr("&Edit"));
	editMenu->addAction(cutAction);
	editMenu->addAction(copyAction);
	editMenu->addAction(pasteAction);

	viewMenu = menuBar()->addMenu(tr("&View"));
	viewMenu->addAction(openSignalAction);
	viewMenu->addAction(openMultipleSignalAction);
	viewMenu->addAction(openTagAction);
	viewMenu->addAction(openScrollAction);
	separatorAction = viewMenu->addSeparator();
	viewMenu->addAction(editSignalAction);

	basicsMenu = menuBar()->addMenu(tr("&Basics"));
	mathematicsMenu = menuBar()->addMenu(tr("&Mathematics"));
	statisticsMenu = menuBar()->addMenu(tr("&Statistics"));
	spectralMenu = menuBar()->addMenu(tr("&Spectral"));
	filterMenu = menuBar()->addMenu(tr("&Filter"));
	waveletMenu = menuBar()->addMenu(tr("&Wavelet"));
	nonlinearMenu = menuBar()->addMenu(tr("&Nonlinear"));

	macroMenu = menuBar()->addMenu(tr("&Macro"));
	macroMenu->addAction(compileAction);
	macroMenu->addAction(startAction);
	macroMenu->addAction(stopAction);
	separatorAction = macroMenu->addSeparator();
	macroMenu->addAction(deleteAction);

	optionsMenu = menuBar()->addMenu(tr("&Options"));
	optionsMenu->addAction(childSettingsAction);
	separatorAction = optionsMenu->addSeparator();
	optionsMenu->addAction(preferencesAction);
	optionsMenu->addAction(editMenuAction);
	separatorAction = optionsMenu->addSeparator();
	optionsMenu->addAction(saveConfigAction);

	windowMenu = menuBar()->addMenu(tr("&Window"));
	windowMenu->addAction(cascadeAction);
	windowMenu->addAction(tileAction);
	windowMenu->addAction(arrangeAction);
	windowMenu->addAction(nextAction);

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(dataploreAction);
	macroSubMenu = helpMenu->addMenu(tr("&Macro"));
	macroSubMenu->addAction(functionAction);
	macroSubMenu->addAction(macrodefinAction);
	helpMenu->addAction(registryAction);
	helpMenu->addAction(aboutAction);
}

void AIECG::createToolBars()
{
	fileToolBar = addToolBar(tr("&File"));
	fileToolBar->addAction(NewFileAction);
	fileToolBar->addAction(LoadSignalAction);
	fileToolBar->addAction(SaveSignalAction);
	fileToolBar->addAction(PrintPreviewAction);
	fileToolBar->addAction(PrintAction);

	editToolBar = addToolBar(tr("&Edit"));
	editToolBar->addAction(cutAction);
	editToolBar->addAction(copyAction);
	editToolBar->addAction(pasteAction);

	viewToolBar = addToolBar(tr("&View"));

	basicsToolBar = addToolBar(tr("&Basics"));

	mathematicsToolBar = addToolBar(tr("&Mathematics"));

	spectralToolBar = addToolBar(tr("&Spectral"));

	filterToolBar = addToolBar(tr("&Filter"));

	waveletToolBar = addToolBar(tr("&Wavelet"));

	nonlinearToolBar = addToolBar(tr("&Nonlinear"));

	macroToolBar = addToolBar(tr("&Macro"));

	optionsToolBar = addToolBar(tr("&Options"));

	windowToolBar = addToolBar(tr("&Window"));

	helpToolBar = addToolBar(tr("&Help"));
	helpToolBar->addAction(aboutAction);
}

void AIECG::createActions()
{
	//File Menu Action
	NewFileAction = new QAction(tr("&New file"), this);
	NewFileAction->setIcon(QIcon("C:/CppWorkspace/AIECG/images/new.png"));
	NewFileAction->setShortcut(QKeySequence::New);
	NewFileAction->setStatusTip(tr("Create a new file"));
	connect(NewFileAction, SIGNAL(triggered()), this, SLOT(newfile()));

	LoadSignalAction = new QAction(tr("&Load signal"), this);
	LoadSignalAction->setIcon(QIcon("C:/CppWorkspace/AIECG/images/open.png"));
	LoadSignalAction->setStatusTip(tr("loads a signal data file from the disk."));
//	connect(LoadSignalAction, SIGNAL(triggered()), pReadData, SLOT(loadSignal()));

	LoadSignalsAction = new QAction(tr("&Load signals"), this);
	LoadSignalsAction->setStatusTip(tr("allows simultaneous loading of several signals from the disk."));
	connect(LoadSignalsAction, SIGNAL(triggered()), this, SLOT(loadSignals()));
	connect(LoadSignalsAction, SIGNAL(triggered()), this, SLOT(beginSVM()));

	LoadTextAction = new QAction(tr("&Load text"), this);
	LoadTextAction->setStatusTip(tr("loads text files or macro source code files from the disk into the text editor window"));
	connect(LoadTextAction, SIGNAL(triggered()), this, SLOT(loadText()));

	LoadMacrosAction = new QAction(tr("&Load macros"), this);
	LoadMacrosAction->setStatusTip(tr("loads macro source code from the disk and compiles it immediately"));

	LoadWindowAction = new QAction(tr("&Load window"), this);
	LoadWindowAction->setStatusTip(tr("loads a window file that has previously been saved using Save window from the file menu of the signal window."));

	OpenSerialPortAction = new QAction(tr("&Open serial port from CMS"), this);
	OpenSerialPortAction->setStatusTip(tr("opens up a serial port connection to an external data source. "));
	connect(OpenSerialPortAction, SIGNAL(triggered()), serialdialog, SLOT(openSerialPort()));

	OpenRespirationAction = new QAction(tr("&Open serial port from CMS"), this);
	connect(OpenRespirationAction, SIGNAL(triggered()), respiredialog, SLOT(openRespiration()));

	CloseChildAction = new QAction(tr("&Close child"), this);
	CloseChildAction->setStatusTip(tr("closes the active child window."));

	SaveSignalAction = new QAction(tr("&Save signal"), this);
	SaveSignalAction->setIcon(QIcon("C:/CppWorkspace/AIECG/images/save.png"));
	SaveSignalAction->setStatusTip(tr("saves a signal to the disk. "));
	connect(SaveSignalAction, SIGNAL(triggered()), pReadData, SLOT(saveSignal()));

	SaveTextAction = new QAction(tr("&Save text"), this);
	SaveTextAction->setStatusTip(tr("saves the current text in the text window to a file. "));
	connect(SaveTextAction, SIGNAL(triggered()), display, SLOT(saveText()));

	SaveWindowAction = new QAction(tr("&Save window"), this);
	SaveWindowAction->setStatusTip(tr("saves the contents of a signal display window to the disk."));

	ExportWindowAction = new QAction(tr("&Export window"), this);
	ExportWindowAction->setStatusTip(tr("saves the contents of a window in bitmap or vector graphics format."));

	PageSetupAction = new QAction(tr("&Page setup"), this);
	PageSetupAction->setStatusTip(tr("invokes the page setup dialog box."));
	connect(PageSetupAction, SIGNAL(triggered()), this, SLOT(setUpPage()));

	PrintPreviewAction = new QAction(tr("&Print preview"), this);
	PrintPreviewAction->setIcon(QIcon("C:/CppWorkspace/AIECG/images/preview.png"));
	PrintPreviewAction->setStatusTip(tr("creates a preview picture of the page(s) to be printed. "));
	connect(PrintPreviewAction, SIGNAL(triggered()), this, SLOT(printPreview()));

	PrintAction = new QAction(tr("&Print"), this);
	PrintAction->setIcon(QIcon("C:/CppWorkspace/AIECG/images/print.png"));
	PrintAction->setStatusTip(tr("brings up the print dialog window. "));
	connect(PrintAction, SIGNAL(triggered()), this, SLOT(print()));

	ExitAction = new QAction(tr("&Exit"), this);
	ExitAction->setShortcut(tr("Ctrl+Q"));
	ExitAction->setStatusTip(tr("quits Dataplore and saves all settings, signals and macros by default."));
	connect(ExitAction, SIGNAL(triggered()), this, SLOT(close()));

	//Edit Menu Action
	cutAction = new QAction(tr("&Cut"), this);
	cutAction->setIcon(QIcon("C:/CppWorkspace/AIECG/images/cut.png"));
	cutAction->setShortcut(tr("Ctrl+X"));
	cutAction->setStatusTip(tr("removes the current selection and places a copy on the clipboard."));
	connect(cutAction, SIGNAL(triggered()), this, SLOT(cut()));

	copyAction = new QAction(tr("&Copy"), this);
	copyAction->setIcon(QIcon("C:/CppWorkspace/AIECG/images/copy.png"));
	copyAction->setShortcut(QKeySequence::Copy);
	copyAction->setStatusTip(tr("places a copy of the current selection on the clipboard."));
	connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));

	pasteAction = new QAction(tr("&Paste"), this);
	pasteAction->setIcon(QIcon("C:/CppWorkspace/AIECG/images/paste.png"));
	pasteAction->setShortcut(tr("Ctrl+V"));
	pasteAction->setStatusTip(tr("puts the clipboard contents into the current active window at the position of the insertion bar. "));
	connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));

	//View Menu Action
	openSignalAction = new QAction(tr("&Open signal window"), this);
	openSignalAction->setStatusTip(tr("opens a signal display window showing a plot of the selected signals within the same coordinate system. "));

	openMultipleSignalAction = new QAction(tr("&Open multiple signal window"), this);
	openMultipleSignalAction->setStatusTip(tr("opens a signal display window showing separate plots of all selected signals."));

	openTagAction = new QAction(tr("&Open tag window"), this);
	openTagAction->setStatusTip(tr("opens a signal display window showing a plot of the selected signals on the left hand side and a bar diagram showing the signal values at the current position on the right hand side."));

	openScrollAction = new QAction(tr("&Open scroll window"), this);
	openScrollAction->setStatusTip(tr("opens a signal display window showing one twentieth of each dimension of the selected signals in a separate axes system. "));

	editSignalAction = new QAction(tr("&Edit signal"), this);
	editSignalAction->setStatusTip(tr("allows you to edit a signal in a table editor and to manipulate individual values of the signal data. "));

	//Macro Menu Action
	compileAction = new QAction(tr("&Compile"), this);
	compileAction->setStatusTip(tr("compiles the macro source code in the active text window. "));

	startAction = new QAction(tr("&Start"), this);
	startAction->setStatusTip(tr("starts the execution of a macro."));

	stopAction = new QAction(tr("&Stop running macro"), this);
	stopAction->setStatusTip(tr("stops the execution of the currently running macro. "));

	deleteAction = new QAction(tr("&Delete"), this);
	deleteAction->setStatusTip(tr("allows you to remove macros from Dataplore. "));

	//Option Menu Action
	childSettingsAction = new QAction(tr("&Child Settings..."), this);
	childSettingsAction->setStatusTip(tr("allows you to change the drawing attributes of a signal plot in a signal display window."));

	preferencesAction = new QAction(tr("&Preferences..."), this);
	preferencesAction->setStatusTip(tr("invokes the configuration dialog window which allows you to set the Dataplore configuration according to your personal requirements and preferences. "));
	connect(preferencesAction, SIGNAL(triggered()), dataAcquisitiondialog, SLOT(preferences()));

	editMenuAction = new QAction(tr("&Edit Menu..."), this);
	editMenuAction->setStatusTip(tr("brings up the edit menu window with a list of all menus and the functions they contain and allows you to arrange existing or create new menus."));

	saveConfigAction = new QAction(tr("&Save Configuration"), this);
	saveConfigAction->setStatusTip(tr("saves the actual configuration of Dataplore including all settings as well as signals and macros loaded. "));

	//Window Menu Action
	cascadeAction = new QAction(tr("&Cascade"), this);
	cascadeAction->setStatusTip(tr("arranges all child windows in a cascade. "));

	tileAction = new QAction(tr("&Tile"), this);
	tileAction->setStatusTip(tr("places all child windows side by side and one at the top of the other."));

	arrangeAction = new QAction(tr("&Arrange Icons"), this);
	arrangeAction->setStatusTip(tr("creates an icon for each child window at the bottom of the Dataplore main window."));

	nextAction = new QAction(tr("&Next"), this);
	nextAction->setStatusTip(tr("makes the next child window (following the currently active in the list of child windows) the active window. "));

	//Help Menu Action
	dataploreAction = new QAction(tr("&Dataplore"), this);
	dataploreAction->setStatusTip(tr("invokes the Dataplore help pages."));

	functionAction = new QAction(tr("&Function"), this);
	functionAction->setStatusTip(tr("creates the Macro function window."));

	macrodefinAction = new QAction(tr("&Macro definitions"), this);
	macrodefinAction->setStatusTip(tr("gives a short introduction into macro programming."));

	registryAction = new QAction(tr("&Registry"), this);
	registryAction->setStatusTip(tr("brings up the Dataplore registry window "));

	aboutAction = new QAction(tr("&About"), this);
	aboutAction->setIcon(QIcon("C:/CppWorkspace/AIECG/images/help.png"));
	aboutAction->setStatusTip(tr("brings up the Dataplore about box."));
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

void AIECG::createStatusBar()
{
	locationLabel = new QLabel("bloodpressurea.dpb:[Diastolic and systolic blood pressure]:size:2000 dim:2");
	locationLabel->setAlignment(Qt::AlignHCenter);
	locationLabel->setMinimumSize(locationLabel->sizeHint());

	formulaLabel = new QLabel("X:1291.88    Y:156.325    ");
	formulaLabel->setIndent(3);

	statusBar()->addWidget(locationLabel);
	statusBar()->addWidget(formulaLabel,1);
}

AIECG::~AIECG()
{

}
