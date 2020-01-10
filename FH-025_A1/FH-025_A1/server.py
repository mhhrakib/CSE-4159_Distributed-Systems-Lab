# -*- coding: utf-8 -*-
import socket
import random
import sys
import time
from threading import *
import json_test

knock = "Knock knock!"
say = "You are supposed to say, \"Who's there?\". Let's try again."
another = "Would you like to listen to another? (Y/N)"
who = "Who's there?"
num_of_jokes = 30
suppose = "You are supposed to say, "
try_again = " Let's try again."
no_more = "I have no more jokes to tell."
buf_size = 2048
max_client = 30
host = '127.0.0.1'
port = 8080
client_no = 0


def main():
    start_server()


def match_string_case_insensitive(str1, str2):
    return str1.lower() == str2.lower()


def send(connection, msg):
    try:
        connection.send(msg.encode())
        print("Server: ", msg)
    except BrokenPipeError:
        print("The client has probably left or some other error occurred.")
        # close_connection(connection)
        connection.close()


def receive(connection):
    try:
        res = connection.recv(buf_size).decode()
        return res
    except (OSError, IOError, AttributeError):
        close_connection(connection)


def close_connection(connection):
    global client_no
    client_no -= 1
    connection.close()
    # print("Active client: ", client_no)


def incr_cli():
	global client_no
	client_no += 1

def get_active_client():
    global client_no
    return client_no


def sleep():
    time.sleep(0.3)


def get_random_list(size):
    lst = []
    for i in range(1, size+1):
        lst.append(i)
    random.shuffle(lst)
    return lst


def client_thread(connection, addr, client_Id):
    jokes_list = get_random_list(num_of_jokes)
    # print(jokes_list)
    served = 0
    # connection.send(knock.encode())
    send(connection, knock)
    previous = knock
    joker = False
    while True:
        client_input = receive(connection)
        print("Client " + client_Id,": ", client_input)
        tmp = previous + " who?"
        if served == num_of_jokes:
            connection.send(no_more.encode())
            print("Closing connection to : " + addr + " Client ID: " + client_Id)
            # connection.close()
            close_connection(connection)
            break
        if previous == knock:
            if match_string_case_insensitive(client_input, who):
                id = jokes_list[served]
                rand_jokes_id = json_test.get_jokes_id_by_no(id)    # send turnip
                connection.send(rand_jokes_id.encode())
                previous = rand_jokes_id
                joker = True
            if not match_string_case_insensitive(client_input, who):    # case-insensitive check
                # connection.send(say.encode())
                send(connection, say)
                sleep()
                # connection.send(knock.encode())
                send(connection, knock)
                previous = knock
                joker = False
        elif joker:
            if match_string_case_insensitive(client_input, tmp):    # send joke to the client
                rand_jokes = json_test.get_jokes_by_id(previous)
                # connection.send(rand_jokes.encode())
                send(connection, rand_jokes)
                sleep()
                # connection.send(another.encode())
                send(connection, another)
                previous = another
                served = served + 1
                joker = False
            else:
                st = suppose + "\"" + tmp + "\"" + try_again  # start again from beginning
                # connection.send(st.encode())
                send(connection, st)
                sleep()
                # connection.send(knock.encode())
                send(connection, knock)
                previous = knock
                joker = False
        elif not joker and previous == another:
            if client_input == "Y" or client_input == "y":  # continue serving
                # connection.send(knock.encode())
                send(connection, knock)
                previous = knock
                joker = False
            else:
                bye = "Bye"
                # connection.send("Bye".encode()) # close connection
                send(connection, bye)
                print("Closing connection to : " + str(addr) + " Client ID: " + client_Id )
                # connection.close()
                close_connection(connection)
                # print("Active : ", get_active_client())
                # current_thread().
                break
                # print(current_thread())
        else:
            pass


def start_server():
    # global client_no
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR,1)
    server_socket.bind((host, port))
    server_socket.listen(max_client)
    print("Server is listening at port: ", port)
    client_id = 0
    while True:
        conn, addr = server_socket.accept()
        # ip, port = str(addr[0]), str(addr[1])
        client_id = client_id + 1
        print("Connected with " + str(addr) + " " + "Client ID: " + str(client_id))
        incr_cli()
        Thread(target=client_thread, args=(conn,addr,str(client_id),), daemon=True).start()
        # print(client_no)
        # print("Active client in start: ",get_active_client())
        if get_active_client() <= 0:
            server_socket.close()
            break


if __name__ == "__main__":
    main()

