from PyQt5 import QtGui
from PyQt5 import QtWidgets, QtCore


class Base_form(QtWidgets.QDialog):
    CLOSED_RESULT: int = 0
    NEED_REGISTRATION_RESULT: int = 1
    NEED_LOGIN_RESULT: int = 2
    OK_RESULT: int = 3

    def __init__(self, parent: QtWidgets.QWidget):
        super(Base_form, self).__init__(parent)
