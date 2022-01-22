import time
from threading import Thread

from src.client_info import ClientInfo


class Runner(Thread):
    MAX_LEN_OF_DATA = 1000000
    MAX_KEY_TIME = 40

    def __init__(self, client_info: ClientInfo):
        super().__init__()
        self.client_info = client_info

    def run(self):
        try:
            while True:
                encrypted_message = self.client_info.connection.recv(self.MAX_LEN_OF_DATA)
                print(encrypted_message)
                if encrypted_message[0:1] == b'k':
                    self.client_info.send_key(encrypted_message[1:])
                elif time.time() - self.client_info.key_time >= self.MAX_KEY_TIME:
                    self.client_info.connection.send(self.client_info.encrypt_message('key expired'))
                elif encrypted_message[0:1] == b'l':
                    self.client_info.log_in(self.client_info.decrypt_message(encrypted_message[1:]))
                elif encrypted_message[0:1] == b'r':
                    self.client_info.registration(self.client_info.decrypt_message(encrypted_message[1:]))
                elif self.client_info.login == '':
                    self.client_info.connection.send(self.client_info.encrypt_message('Error: You are not login'))
                elif encrypted_message[0:1] == b'g':
                    self.client_info.get_notebook_list()
                elif encrypted_message[0:1] == b'o':
                    self.client_info.open_file(self.client_info.decrypt_message(encrypted_message[1:]))
                elif encrypted_message[0:1] == b's':
                    self.client_info.save_file(self.client_info.decrypt_message(encrypted_message[1:]))
                elif encrypted_message[0:1] == b'd':
                    self.client_info.delete_file(self.client_info.decrypt_message(encrypted_message[1:]))
                elif encrypted_message == b'':
                    self.client_info.connection.close()
                    return
        except ConnectionResetError and ConnectionAbortedError:
            return
