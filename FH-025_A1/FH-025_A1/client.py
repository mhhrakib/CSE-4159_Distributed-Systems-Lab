# -*- coding: utf-8 -*-
import socket


def match_string_case_insensitive(str1, str2):
    return str1.lower() == str2.lower()


client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = 'localhost'
no_more = "I have no more jokes to tell."
port = 8080
buf_size = 2048
client.connect((host, port))
knock = "Knock knock!"
again = "Would you like to listen to another? (Y/N)"


while True:
    rec = client.recv(buf_size).decode()
    print("Server: ", rec)
    if rec == no_more or rec == "Bye":
        client.close()
        break
    elif rec == knock:
        mess = input("Enter your response: ")
        client.send(mess.encode())
    elif "Let's try again." in rec:
        continue
    elif again in rec:
        mess = input("Enter your response: ")
        client.send(mess.encode())
    else:
        mess = input("Enter your response: ")
        client.send(mess.encode())
        rec = client.recv(buf_size).decode()
        print("Server: ", rec)




