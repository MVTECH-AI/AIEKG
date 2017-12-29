#ifdef MAINWINDOW_H
#define MAINWINDOW_H
#include<QMainWindow>
namespace Ui
{
  class MainWindow;
}
class MainWindow::public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui:MainWindow)
	{
	  ui->setupUi(this);
	}
	MainWindow::~MainWindow()
	{
	  delete ui;
	}
}
#endif