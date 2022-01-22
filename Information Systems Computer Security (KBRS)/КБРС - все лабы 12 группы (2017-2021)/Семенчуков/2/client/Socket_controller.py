import socket
import sys
from typing import List

import rsa
from Cryptodome import Random
from Cryptodome.Cipher import AES
from Cryptodome.Util.Padding import pad, unpad


class Socket_controller:
    MAX_LEN = 1000000
    KEY_LEN = 1024

    @staticmethod
    def decrypt_rsa(msg: bytes, private_key) -> bytes:
        ans = b''
        m = Socket_controller.KEY_LEN // 8
        n = len(msg) // m
        for i in range(n):
            ans += rsa.decrypt(msg[i * m:(i + 1) * m], private_key)
        return ans

    @staticmethod
    def encrypt(msg: bytes, serv_key) -> bytes:
        iv = Random.get_random_bytes(16)
        cipher = AES.new(serv_key, AES.MODE_CBC, iv)
        cipher_text = iv + cipher.encrypt(pad(msg, AES.block_size))
        return cipher_text

    @staticmethod
    def decrypt(msg: bytes, serv_key: bytes) -> bytes:
        iv = msg[:16]
        cipher = AES.new(serv_key, AES.MODE_CBC, iv)
        decrypt_text = unpad(cipher.decrypt(msg[16:]), AES.block_size)
        return decrypt_text

        # def encrypt_message(self, message: str) -> bytes:
        #     iv = Random.get_random_bytes(16)
        #     cipher = AES.new(self.session_key, AES.MODE_CBC, iv)
        #     cipher_text = iv + cipher.encrypt(pad(message.encode(), AES.block_size))
        #     return cipher_text
        #
        # def decrypt_message(self, message: bytes) -> str:
        #     iv = message[:16]
        #     cipher = AES.new(self.session_key, AES.MODE_CBC, iv)
        #     decrypt_text = unpad(cipher.decrypt(message[16:]), AES.block_size)
        #     return decrypt_text.decode()

    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((self.host, self.port))
        self.open_key, self.private_key = rsa.newkeys(self.KEY_LEN)

        if self.sock.recv(self.MAX_LEN).decode() != "accepted":
            sys.exit(-1)
        self.serv_key = self.send_key()

    # command=b'k'
    def send_key(self):
        self.sock.send(b'k' + self.open_key.save_pkcs1())
        resp = self.decrypt_rsa(self.sock.recv(self.MAX_LEN), self.private_key)
        return resp
        # return rsa.PublicKey.load_pkcs1(self.decrypt(self.sock.recv(self.MAX_LEN), self.private_key))

    def _send_msg(self, command: bytes, msg: str) -> str:
        if msg == '':
            self.sock.send(command)
        else:
            self.sock.send(command + self.encrypt(msg.encode(), self.serv_key))
        resp = self.sock.recv(self.MAX_LEN)
        resp = self.decrypt(resp, self.serv_key)
        if resp == b'key expired':
            self.open_key, self.private_key = rsa.newkeys(self.KEY_LEN)
            self.serv_key = self.send_key()
            resp = self._send_msg(command, msg).encode()

        return resp.decode()

    # command=b'l'
    def login(self, login: str, password: str) -> bool:
        return self._send_msg(b'l', login + '\n' + password) == 'OK'

    # command=b'r'
    def register(self, login: str, password: str) -> str:
        return self._send_msg(b'r', login + '\n' + password)

    # command=b'g'
    def get_notebook_list(self) -> List[str]:
        return self._send_msg(b'g', '').split('\n')

    # command=b'o'
    def open_nb(self, name: str) -> str:
        return self._send_msg(b'o', name)

    # command=b's'
    def save_nb(self, name: str, content: str) -> str:
        return self._send_msg(b's', name + '\n' + content)

    def delete_nb(self, file: str) -> str:
        return self._send_msg(b'd', file)
