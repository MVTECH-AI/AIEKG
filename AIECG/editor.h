#ifndef EDITOR_H
#define EDITOR_H

#include <QtGui>
#include <QTextEdit>

class Editor :public QTextEdit
{
	Q_OBJECT

public:
	Editor(QWidget *parent = 0);
	~Editor();

	void newFile();//�½��ļ�
	bool save(); //�ļ�����
	bool saveAs();//�ļ����Ϊ
	QSize sizeHint() const;//��ȡ���ڵ��Ƽ���С
	QAction *windowMenuAction() const { return action; }

	static Editor *open(QWidget *parent = 0);//�򿪴���
	static Editor *openFile(const QString &fileName,QWidget *parent = 0);//���ļ�

protected:
	void closeEvent(QCloseEvent *event);//�ر��¼����ڳ���ر�֮ǰִ�д˺���

private slots:
	void documentWasModified();//���ô�����ʾ״̬���޸ĺ�δ�޸�����

private:
	bool okToContinue();
	bool saveFile(const QString &fileName);//�����ļ�
	void setCurrentFile(const QString &fileName);//���õ�ǰ�ļ�
	bool readFile(const QString &fileName);//���ļ�
	bool writeFile(const QString &fileName);//д�ļ�
	QString strippedName(const QString &fullFileName);//���ļ��а�ȡ�ļ���

	QString curFile;
	bool isUntitled;
	QAction *action;

};

#endif //EDITOR_H
