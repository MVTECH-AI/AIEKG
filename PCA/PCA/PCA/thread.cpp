#include "thread.h"
#include <QtNetwork\QTcpSocket>
#include <fstream>
class QTcpSocket;

Thread::Thread(ReadData *pst)
	
{

	this->file = pst->getDataName();

}
void Thread::run()
{
	//for transmission 
	ifstream inData(file.toStdString().c_str());
	int length;
	inData.seekg(0,ios::end);
	length = inData.tellg();
	inData.seekg(0,ios::beg);
	char *buffer = new char[length];
	inData.read(buffer,length);
	inData.close();
	//ofstream outData("test.txt");
	//outData.write(buffer,length);
	//delete buffer;

}