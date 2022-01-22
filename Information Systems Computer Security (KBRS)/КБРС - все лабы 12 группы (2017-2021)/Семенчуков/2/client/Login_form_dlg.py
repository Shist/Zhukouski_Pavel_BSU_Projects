from PyQt5 import QtGui
from PyQt5 import QtWidgets, QtCore

from Base_form import Base_form
from LogIn_Form import Ui_Dialog
from Socket_controller import Socket_controller


class Login_form(Base_form):

    def __init__(self, parent: QtWidgets.QWidget, sock: Socket_controller):
        super().__init__(parent)
        self.ui = Ui_Dialog()
        self.ui.setupUi(self)
        self.sock = sock
        self.ui.switch_button.clicked.connect(self.register_option)
        self.ui.confirm_button.clicked.connect(self.confirm_option)

    def register_option(self):
        self.close()
        self.setResult(self.NEED_REGISTRATION_RESULT)

    def confirm_option(self):
        login = self.ui.login.text()
        password = self.ui.password.text()
        if self.sock.login(login, password):
            self.close()
            self.setResult(self.OK_RESULT)
        else:
            self.ui.message_label.setText("error: invalid login or password, try again")
