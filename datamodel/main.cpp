#include "datamodel.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DataModel *w = new DataModel;
	w->resize(QSize(1300,800));
	w->show();
	return a.exec();
}