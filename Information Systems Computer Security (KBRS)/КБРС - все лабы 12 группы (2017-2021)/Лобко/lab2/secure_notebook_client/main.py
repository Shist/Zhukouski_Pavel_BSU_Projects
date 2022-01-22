import sys

import rsa
from PyQt5 import QtGui
from PyQt5 import QtWidgets, QtCore

from Base_form import Base_form
from LogIn_Form import Ui_Dialog
from Login_form_dlg import Login_form
from Register_form_dlg import Register_form
from Selection_dlg import Selection_form
from Selection_only_dlg import Selection_only_form
from Socket_controller import Socket_controller
from Main_wnd import Ui_MainWindow


class Client_main(QtWidgets.QMainWindow):
    def __init__(self):
        super(Client_main, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.sock = Socket_controller("10.160.77.231", 8007)
        res = Base_form.NEED_LOGIN_RESULT
        while res != Base_form.OK_RESULT:
            dialog = None
            if res == Base_form.NEED_REGISTRATION_RESULT:
                dialog = Register_form(self, self.sock)
            elif res == Base_form.NEED_LOGIN_RESULT:
                dialog = Login_form(self, self.sock)
            elif res == Base_form.CLOSED_RESULT:
                sys.exit(0)
            dialog.exec()
            res = dialog.result()
        self.current_notebook = ''
        self.ui.action_open.triggered.connect(self.open_handler)
        self.ui.action_save.triggered.connect(self.save_handler)
        self.ui.action_save_as.triggered.connect(self.save_as_handler)
        self.ui.action_delete_file.triggered.connect(self.delete_handler)

    def closeEvent(self, a0: QtGui.QCloseEvent) -> None:
        self.sock.sock.close()
        super(Client_main, self).closeEvent(a0)

    def open_handler(self):
        dlg = Selection_form(self, self.sock)
        dlg.exec()
        self.current_notebook = dlg.file
        if dlg.res == 1:
            self.ui.textEdit.setText(self.sock.open_nb(self.current_notebook))

    def save_handler(self):
        if self.current_notebook == '':
            self.save_as_handler()
            return
        self.statusBar().showMessage(self.sock.save_nb(self.current_notebook, self.ui.textEdit.toPlainText()))

    def save_as_handler(self):
        dlg = Selection_form(self, self.sock)
        dlg.exec()
        self.current_notebook = dlg.file
        self.statusBar().showMessage(self.sock.save_nb(self.current_notebook, self.ui.textEdit.toPlainText()))

    def delete_handler(self):
        dlg = Selection_only_form(self, self.sock)
        dlg.exec()
        self.statusBar().showMessage(self.sock.delete_nb(dlg.file))


if __name__ == '__main__':
    app = QtWidgets.QApplication([])
    application = Client_main()
    application.show()

    sys.exit(app.exec())
