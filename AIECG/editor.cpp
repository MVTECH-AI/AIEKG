#include "editor.h"

Editor::Editor(QWidget *parent)
	: QTextEdit(parent)
{
	action = new QAction(this);
	action->setCheckable(true);
	connect(action,SIGNAL(triggered()),this,SLOT(show()));
	connect(action,SIGNAL(triggered()),this,SLOT(setFocus()));

	isUntitled = true;//��¼�ļ��Ƿ��Ѿ�����

	connect(document(),SIGNAL(contentsChanged()),this,SLOT(documentWasModified()));//�ļ����ݷ����ı�ʱ��������

	setWindowIcon(QPixmap("C:/CppWorkspace/editor/images/document.png"));//�����Ӵ���ͼ��
	setWindowTitle("[*]");
	setAttribute(Qt::WA_DeleteOnClose);//���ڹر�ʱɾ��
}
void Editor::newFile()
{
	static int documentNumber = 1;//��¼���Ӵ��ڵĸ���

	curFile = tr("document%1.txt").arg(documentNumber);
	setWindowTitle(curFile + "[*]");
	action->setText(curFile);
	isUntitled = true;
	++documentNumber;
}

bool Editor::save()
{
	if (isUntitled){
		return saveAs();
	} else {
		return saveFile(curFile);
	}
}

bool Editor::saveAs()
{
	QString fileName = QFileDialog::getSaveFileName(this,tr("Save As"),curFile);
	if(fileName.isEmpty())
		return false;

	return saveFile(fileName);
}

QSize Editor::sizeHint() const
{
	return QSize(72 * fontMetrics().width('x'),25 * fontMetrics().lineSpacing());
}

Editor *Editor::open(QWidget *parent)//�������򿪡��򿪴��ڣ���ȡ·�����ļ���
{
	QString fileName = QFileDialog::getOpenFileName(parent,tr("Open"),".");
	if(fileName.isEmpty())
		return 0;

	return openFile(fileName,parent);
}

Editor *Editor::openFile(const QString &fileName,QWidget *parent)
{
	Editor *editor = new Editor(parent);
	if (editor->readFile(fileName)){
		editor->setCurrentFile(fileName);
		return editor;
	} else {
		delete editor;
		return 0;
	}
}

void Editor::closeEvent(QCloseEvent *event)//�ر��¼�����ʱ
{
	if (okToContinue()){
		event->accept();//���ܹر��¼�
	} else {
		event->ignore();//���ӹر��¼�
	}
}

void Editor::documentWasModified()//���ô���Ϊ���޸�״̬
{
	setWindowModified(true);
}

bool Editor::okToContinue()//�Ƿ����
{
	if (document()->isModified())//�ж��ļ��Ƿ��޸�
	{
		int r = QMessageBox::warning(this,tr("MDI Editor"),
			tr("File %1 has been modified.\n"
			"Do you want to save your changes?").arg(strippedName(curFile)),
			QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

		if (r == QMessageBox::Yes)
		{
			return save();
		} 
		else if(r == QMessageBox::Cancel)
		{
			return false;
		}
	}
	return true; 
}

bool Editor::saveFile(const QString &fileName)//�����ļ�
{
	if (writeFile(fileName))
	{
		setCurrentFile(fileName);
		return true;
	}
	else
	{
		return false;
	}
	
}

void Editor::setCurrentFile(const QString &fileName)//���õ�ǰ�ļ�
{
	curFile = fileName;
	isUntitled = false;
	action->setText(strippedName(curFile));
	document()->setModified(false);
	setWindowTitle(strippedName(curFile) + "[*]");
	setWindowModified(false);
}

bool Editor::readFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::warning(this,tr("MDI Editor"),
							tr("Cannot read file %1:\n&2.")
							.arg(file.fileName())
							.arg(file.errorString()));
		return false;
	}

	QTextStream in(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	setPlainText(in.readAll());
	QApplication::restoreOverrideCursor();
	return true;
}

bool Editor::writeFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QMessageBox::warning(this,tr("MDI Editor"),
			tr("Cannot write file %1:\n&2.")
			.arg(file.fileName())
			.arg(file.errorString()));
		return false;
	}

	QTextStream out(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	out << toPlainText();
	QApplication::restoreOverrideCursor();
	return true;
}

QString Editor::strippedName(const QString &fullFileName)//��·���а����ļ���
{
	return QFileInfo(fullFileName).fileName();
}



Editor::~Editor()
{

}