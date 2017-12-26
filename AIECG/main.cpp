#include "AIECG.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AIECG *w = new AIECG;
	w->resize(QSize(800,600));
	w->show();
	return a.exec();
}