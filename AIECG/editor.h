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

	void newFile();//新建文件
	bool save(); //文件保存
	bool saveAs();//文件另存为
	QSize sizeHint() const;//获取窗口的推荐大小
	QAction *windowMenuAction() const { return action; }

	static Editor *open(QWidget *parent = 0);//打开窗口
	static Editor *openFile(const QString &fileName,QWidget *parent = 0);//打开文件

protected:
	void closeEvent(QCloseEvent *event);//关闭事件，在程序关闭之前执行此函数

private slots:
	void documentWasModified();//设置窗口显示状态，修改和未修改两种

private:
	bool okToContinue();
	bool saveFile(const QString &fileName);//保存文件
	void setCurrentFile(const QString &fileName);//设置当前文件
	bool readFile(const QString &fileName);//读文件
	bool writeFile(const QString &fileName);//写文件
	QString strippedName(const QString &fullFileName);//从文件中剥取文件名

	QString curFile;
	bool isUntitled;
	QAction *action;

};

#endif //EDITOR_H
