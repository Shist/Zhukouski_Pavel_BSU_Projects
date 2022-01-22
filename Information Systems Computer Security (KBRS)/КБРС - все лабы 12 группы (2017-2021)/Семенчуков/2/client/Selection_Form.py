# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'Selection_Form.ui'
#
# Created by: PyQt5 UI code generator 5.13.0
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(378, 295)
        Dialog.setModal(True)
        self.formLayout = QtWidgets.QFormLayout(Dialog)
        self.formLayout.setObjectName("formLayout")
        self.listWidget = QtWidgets.QListWidget(Dialog)
        self.listWidget.setObjectName("listWidget")
        self.formLayout.setWidget(1, QtWidgets.QFormLayout.LabelRole, self.listWidget)
        self.label = QtWidgets.QLabel(Dialog)
        self.label.setObjectName("label")
        self.formLayout.setWidget(0, QtWidgets.QFormLayout.LabelRole, self.label)
        self.label_2 = QtWidgets.QLabel(Dialog)
        self.label_2.setObjectName("label_2")
        self.formLayout.setWidget(2, QtWidgets.QFormLayout.LabelRole, self.label_2)
        self.filename = QtWidgets.QLineEdit(Dialog)
        self.filename.setObjectName("filename")
        self.formLayout.setWidget(3, QtWidgets.QFormLayout.LabelRole, self.filename)
        self.new_button = QtWidgets.QPushButton(Dialog)
        self.new_button.setObjectName("new_button")
        self.formLayout.setWidget(3, QtWidgets.QFormLayout.FieldRole, self.new_button)
        self.verticalLayout = QtWidgets.QVBoxLayout()
        self.verticalLayout.setObjectName("verticalLayout")
        self.ok_button = QtWidgets.QPushButton(Dialog)
        self.ok_button.setObjectName("ok_button")
        self.verticalLayout.addWidget(self.ok_button)
        self.formLayout.setLayout(1, QtWidgets.QFormLayout.FieldRole, self.verticalLayout)

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "Dialog"))
        self.label.setText(_translate("Dialog", "select file:"))
        self.label_2.setText(_translate("Dialog", "or create new:"))
        self.new_button.setText(_translate("Dialog", "Create new"))
        self.ok_button.setText(_translate("Dialog", "ok"))
