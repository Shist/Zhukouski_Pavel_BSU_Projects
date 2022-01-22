import socket

from src.client_info import ClientInfo
from src.runner import Runner

HOST = ''
PORT = 8007
COUNT_OF_CLIENTS = 10


def get_server_socket():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((HOST, PORT))
    server.listen(COUNT_OF_CLIENTS)
    print(socket.gethostbyname(socket.gethostname()))
    return server


def main():
    server_socket = get_server_socket()
    while True:
        connection, address = server_socket.accept()
        connection.send('accepted'.encode())
        print('server start')
        Runner(ClientInfo(connection, address)).start()


if __name__ == '__main__':
    main()
