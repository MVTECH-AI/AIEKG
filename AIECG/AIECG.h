#ifndef AIECG_H
#define AIECG_H

#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QLabel>
#include <QTextEdit>
#include <QImage>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPageSetupDialog>
#include <QClipboard>

#include "display.h"
#include "readdata.h"
#include "processImage.h"
#include "serialdialog.h"
#include "respiredialog.h"
#include "dataAcquisitiondialog.h"

class AIECG :public QMainWindow
{
	Q_OBJECT

public:
	AIECG(QWidget *parent = 0);
	~AIECG();

private slots:
	
	void print();
	void printPreview();
	void setUpPage();
	void printDocument(QPrinter *printer);
	void cut();
	void copy();
	void paste();
	void about();

private:
	void createMenus();
	void createActions();
	void createToolBars();
	void createStatusBar();

	
	ReadData *pReadData;
	ImageProcess *pImageProcess;
	Display *display;
	SerialDialog *serialdialog;
	RespireDialog *respiredialog;
	DataAcquisitionDialog *dataAcquisitiondialog;

	QImage image;
	QTextEdit *textEdit;
	QClipboard *board;

	QLabel *locationLabel;
	QLabel *formulaLabel;

	QMenu *fileMenu;
	QMenu *openSubMenu;
	QMenu *editMenu;
	QMenu *selectSubMenu;
	QMenu *viewMenu;
	QMenu *basicsMenu;
	QMenu *mathematicsMenu;
	QMenu *statisticsMenu;
	QMenu *spectralMenu;
	QMenu *filterMenu;
	QMenu *waveletMenu;
	QMenu *nonlinearMenu;
	QMenu *macroMenu;
	QMenu *optionsMenu;
	QMenu *windowMenu;
	QMenu *helpMenu;
	QMenu *macroSubMenu;

	QToolBar *fileToolBar;
	QToolBar *editToolBar;
	QToolBar *viewToolBar;
	QToolBar *basicsToolBar;
	QToolBar *mathematicsToolBar;
	QToolBar *statisticsToolBar;
	QToolBar *spectralToolBar;
	QToolBar *filterToolBar;
	QToolBar *waveletToolBar;
	QToolBar *nonlinearToolBar;
	QToolBar *macroToolBar;
	QToolBar *optionsToolBar;
	QToolBar *windowToolBar;
	QToolBar *helpToolBar;

	QAction *separatorAction;
	//File Menu Action
	QAction *NewFileAction;
	QAction *LoadSignalAction;
	QAction *LoadSignalsAction;
	QAction *LoadTextAction;
	QAction *LoadMacrosAction;
	QAction *LoadWindowAction;
	QAction *OpenSerialPortAction;
	QAction *OpenRespirationAction;
	QAction *CloseChildAction;
	QAction *SaveSignalAction;
	QAction *SaveTextAction;
	QAction *SaveWindowAction;
	QAction *ExportWindowAction;
	QAction *PageSetupAction;
	QAction *PrintPreviewAction;
	QAction *PrintAction;
	QAction *ExitAction;

	//Edit Menu Action 
	QAction *cutAction;
	QAction *copyAction;
	QAction *pasteAction;

	//View Menu Action
	QAction *openSignalAction;
	QAction *openMultipleSignalAction;
	QAction *openTagAction;
	QAction *openScrollAction;
	QAction *editSignalAction;

	//Macro Menu Action
	QAction *compileAction;
	QAction *startAction;
	QAction *stopAction;
	QAction *deleteAction;

	//Option Menu Action
	QAction *childSettingsAction;
	QAction *preferencesAction;
	QAction *editMenuAction;
	QAction *saveConfigAction;

	//Window Menu Action
	QAction *cascadeAction;
	QAction *tileAction;
	QAction *arrangeAction;
	QAction *nextAction;

	//Help Menu Action
	QAction *dataploreAction;
	QAction *macroAction;
	QAction *registryAction;
	QAction *aboutAction;
	QAction *functionAction;
	QAction *macrodefinAction;
};

#endif //AIECG_H
