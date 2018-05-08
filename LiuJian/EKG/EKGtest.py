from PyQt4 import QtGui,QtCore
from PyQt4.QtGui import *
from aiecg_ui import Ui_AIECG_UIClass
from ecg import ECG
import sys
import os


class MainWindow(QtGui.QMainWindow):
    def __init__(self,parent=None):
        QtGui.QWidget.__init__(self,parent)
        self.ui = Ui_AIECG_UIClass()
        self.ui.setupUi(self)
        self.ui.tableWidget.itemClicked.connect(self.outSelect)
        self.directory = './DCMResources'
        list = self.InitDataResources([],self.directory)
        self.InitTableWidget(list)

    def InitDataResources(self,fileList,direct):
        newdir = direct
        if os.path.isfile(direct):
            file_name = os.path.split(direct)[-1]
            fileList.append(os.path.splitext(file_name)[0])
        elif os.path.isdir(direct):
            for s in os.listdir(direct):
                newdir = os.path.join(direct,s)
                self.InitDataResources(fileList,newdir)
        return fileList

    def InitTableWidget(self,list):
        for i in range(len(list)):
            NameItem = QTableWidgetItem(list[i])
            NameItem.setTextColor(QColor("Black"))
            self.ui.tableWidget.setItem(i,0,NameItem)
            ResultItem = QTableWidgetItem("疑似心梗")
            ResultItem.setTextColor(QColor("Black"))
            self.ui.tableWidget.setItem(i, 1, ResultItem)

    def outSelect(self):
        if self.ui.tableWidget.currentItem().column() == 0:
            filename = self.ui.tableWidget.currentItem().text()
            print(filename)
            data_source = ECG(self.directory + "/" + filename+ ".DCM")
            data_source.draw('6x2')
            myapp.ui.label.setPixmap(QtGui.QPixmap('6x2.png'))
        else:
            print("Please Select the Name Row")

if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    myapp = MainWindow()
    myapp.ui.tableWidget.setCurrentCell(0, 0, QItemSelectionModel.Select)
    myapp.outSelect()
    myapp.ui.label.setPixmap(QtGui.QPixmap('6x2.png'))
    myapp.show()
    app.exec_()