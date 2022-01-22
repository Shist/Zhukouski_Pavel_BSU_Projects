from PyQt5 import QtGui
from PyQt5 import QtWidgets, QtCore

from Base_form import Base_form
from Register_Form import Ui_Dialog
from Socket_controller import Socket_controller


class Register_form(Base_form):

    def __init__(self, parent: QtWidgets.QWidget, sock: Socket_controller):
        super().__init__(parent)
        self.ui = Ui_Dialog()
        self.ui.setupUi(self)
        self.ui.switch_button.clicked.connect(self.login_option)
        self.ui.confirm_button.clicked.connect(self.confirm_option)
        self.sock = sock

    def login_option(self):
        self.close()
        self.setResult(self.NEED_LOGIN_RESULT)

    def confirm_option(self):
        login = self.ui.login.text()
        password = self.ui.password.text()
        if password != self.ui.password2.text():
            self.ui.message_label.setText('passwords are different')
            return
        resp = self.sock.register(login, password)
        if resp == 'OK':
            self.sock.login(login, password)
            self.close()
            self.setResult(self.OK_RESULT)

        else:
            self.ui.message_label.setText(resp)
