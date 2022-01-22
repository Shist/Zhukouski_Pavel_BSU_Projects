import os
import time
import rsa
from socket import socket
from Crypto.Cipher import AES
from Crypto import Random
from Crypto.Util.Padding import pad, unpad


def encrypt_with_RSA(msg: bytes, client_public_key):
    ans = b''
    m = (ClientInfo.KEY_LEN // 8) - 11
    n = len(msg) // m
    for i in range(n):
        ans += rsa.encrypt(msg[i * m:(i + 1) * m], client_public_key)
    return ans + rsa.encrypt(msg[n * m:], client_public_key)


class ClientInfo:
    KEY_LEN = 1024

    def __init__(self, connection: socket, address):
        self.connection = connection
        self.address = address
        self.login = ''
        self.password = ''
        self.client_public_RSA_key = None
        self.session_key = None
        self.key_time = 0

    @property
    def final_path_to_user_dir(self):
        return 'clients_files/' + self.login

    def encrypt_message(self, message: str) -> bytes:
        iv = Random.get_random_bytes(16)
        cipher = AES.new(self.session_key, AES.MODE_CBC, iv)
        cipher_text = iv + cipher.encrypt(pad(message.encode(), AES.block_size))
        return cipher_text

    def decrypt_message(self, message: bytes) -> str:
        iv = message[:16]
        cipher = AES.new(self.session_key, AES.MODE_CBC, iv)
        decrypt_text = unpad(cipher.decrypt(message[16:]), AES.block_size)
        return decrypt_text.decode()

    def encrypt_file_data(self, data: str, password=None) -> bytes:
        if password is None:
            password = self.password
        byte_key_from_password = password.__hash__().to_bytes(32, byteorder='big', signed=True)
        iv = Random.get_random_bytes(16)
        cipher = AES.new(byte_key_from_password, AES.MODE_CBC, iv)
        cipher_text = iv + cipher.encrypt(pad(data.encode(), AES.block_size))
        return cipher_text

    def decrypt_file_data(self, data: bytes, password=None) -> str:
        if password is None:
            password = self.password
        iv = data[:16]
        byte_key_from_password = password.__hash__().to_bytes(32, byteorder='big', signed=True)
        cipher = AES.new(byte_key_from_password, AES.MODE_CBC, iv)
        decrypt_text = unpad(cipher.decrypt(data[16:]), AES.block_size)
        return decrypt_text.decode()

    def registration(self, login_and_password: str):
        print(login_and_password)
        current_login, current_password = login_and_password.split('\n')
        if os.path.exists('clients_files/' + current_login):
            self.connection.send(self.encrypt_message('This login is occupied'))
        else:
            os.mkdir('clients_files/' + current_login)
            with open('clients_files/' + current_login + '/password.txt', 'wb') as f:
                f.write(self.encrypt_file_data(current_password, password=current_password))
            self.connection.send(self.encrypt_message('OK'))

    def log_in(self, login_and_password: str):
        print(login_and_password)
        current_login, current_password = login_and_password.split('\n')
        if os.path.exists('clients_files/' + current_login):
            with open('clients_files/' + current_login + '/password.txt', 'rb') as f:
                true_password = self.decrypt_file_data(f.read(), password=current_password)
            if current_password == true_password:
                self.login = current_login
                self.password = current_password
                self.connection.send(self.encrypt_message('OK'))
            else:
                self.connection.send(self.encrypt_message('Invalid password'))
        else:
            self.connection.send(self.encrypt_message('This login is not exist'))

    def get_notebook_list(self):
        files_list = '\n'.join(os.listdir(self.final_path_to_user_dir)[1:])
        self.connection.send(self.encrypt_message(files_list))

    def send_key(self, public_client_key: bytes):
        print(public_client_key)
        self.key_time = time.time()
        self.client_public_RSA_key = rsa.PublicKey.load_pkcs1(public_client_key)
        self.session_key = Random.get_random_bytes(32)
        self.connection.send(encrypt_with_RSA(self.session_key, self.client_public_RSA_key))

    def open_file(self, file_name: str):
        print(file_name)
        finish_path_to_file = self.final_path_to_user_dir + '/' + file_name
        with open(finish_path_to_file, 'rb') as file:
            self.connection.send(self.encrypt_message(self.decrypt_file_data(file.read())))

    def save_file(self, file_name_and_data: str):
        print(file_name_and_data)
        file_name, data = file_name_and_data.split('\n', 1)
        finish_path_to_file = self.final_path_to_user_dir + '/' + file_name
        with open(finish_path_to_file, 'wb') as file:
            file.write(self.encrypt_file_data(data))
            self.connection.send(self.encrypt_message('Saved'))

    def delete_file(self, file_name: str):
        print(file_name)
        finish_path_to_file = self.final_path_to_user_dir + '/' + file_name
        os.remove(finish_path_to_file)
        self.connection.send(self.encrypt_message('Deleted'))
