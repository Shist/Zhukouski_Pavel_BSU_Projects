# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'Register_Form.ui'
#
# Created by: PyQt5 UI code generator 5.13.0
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(400, 300)
        Dialog.setModal(True)
        self.formLayout = QtWidgets.QFormLayout(Dialog)
        self.formLayout.setObjectName("formLayout")
        self.label = QtWidgets.QLabel(Dialog)
        self.label.setAlignment(QtCore.Qt.AlignCenter)
        self.label.setObjectName("label")
        self.formLayout.setWidget(0, QtWidgets.QFormLayout.SpanningRole, self.label)
        self.label_2 = QtWidgets.QLabel(Dialog)
        self.label_2.setObjectName("label_2")
        self.formLayout.setWidget(2, QtWidgets.QFormLayout.LabelRole, self.label_2)
        self.login = QtWidgets.QLineEdit(Dialog)
        self.login.setObjectName("login")
        self.formLayout.setWidget(2, QtWidgets.QFormLayout.FieldRole, self.login)
        self.label_3 = QtWidgets.QLabel(Dialog)
        self.label_3.setObjectName("label_3")
        self.formLayout.setWidget(3, QtWidgets.QFormLayout.LabelRole, self.label_3)
        self.password = QtWidgets.QLineEdit(Dialog)
        self.password.setInputMethodHints(QtCore.Qt.ImhHiddenText|QtCore.Qt.ImhNoAutoUppercase|QtCore.Qt.ImhNoPredictiveText|QtCore.Qt.ImhSensitiveData)
        self.password.setEchoMode(QtWidgets.QLineEdit.Password)
        self.password.setObjectName("password")
        self.formLayout.setWidget(3, QtWidgets.QFormLayout.FieldRole, self.password)
        self.confirm_button = QtWidgets.QPushButton(Dialog)
        self.confirm_button.setObjectName("confirm_button")
        self.formLayout.setWidget(5, QtWidgets.QFormLayout.FieldRole, self.confirm_button)
        self.label_4 = QtWidgets.QLabel(Dialog)
        self.label_4.setObjectName("label_4")
        self.formLayout.setWidget(6, QtWidgets.QFormLayout.SpanningRole, self.label_4)
        self.switch_button = QtWidgets.QPushButton(Dialog)
        self.switch_button.setObjectName("switch_button")
        self.formLayout.setWidget(7, QtWidgets.QFormLayout.FieldRole, self.switch_button)
        self.password2 = QtWidgets.QLineEdit(Dialog)
        self.password2.setEchoMode(QtWidgets.QLineEdit.Password)
        self.password2.setObjectName("password2")
        self.formLayout.setWidget(4, QtWidgets.QFormLayout.FieldRole, self.password2)
        self.label_5 = QtWidgets.QLabel(Dialog)
        self.label_5.setObjectName("label_5")
        self.formLayout.setWidget(4, QtWidgets.QFormLayout.LabelRole, self.label_5)
        self.message_label = QtWidgets.QLabel(Dialog)
        font = QtGui.QFont()
        font.setUnderline(True)
        self.message_label.setFont(font)
        self.message_label.setText("")
        self.message_label.setTextFormat(QtCore.Qt.AutoText)
        self.message_label.setObjectName("message_label")
        self.formLayout.setWidget(1, QtWidgets.QFormLayout.LabelRole, self.message_label)

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "Dialog"))
        self.label.setText(_translate("Dialog", "Register"))
        self.label_2.setText(_translate("Dialog", "Login:"))
        self.label_3.setText(_translate("Dialog", "Password:"))
        self.confirm_button.setText(_translate("Dialog", "Register"))
        self.label_4.setText(_translate("Dialog", "Already have an account?"))
        self.switch_button.setText(_translate("Dialog", "Log In"))
        self.label_5.setText(_translate("Dialog", "Confirm Password:"))
