#!/usr/bin/env python

from datetime import datetime
import select
import socket
import sys
import threading
import time
import base64
import hashlib
import struct
import json 



worker_signal = "stop"

def is_json(myjson):
    try:
        json_object = json.loads(myjson)
    except ValueError, e:
        return False
    return True


def sendMessage(s):
    TEXT = 0x01
    BINARY = 0x02

    # empty message to start with
    message = ""
    
    # always send entire message one frame
    b1 = 0x80

    # for Python 2
    if type(s) == unicode:
        b1 |= TEXT
        payload = s.encode("UTF8")
        
    elif type(s) == str:
        b1 |= TEXT
        payload = s

    # append 'FIN' flag to the message
    message += chr(b1)

    b2 = 0
    
    length = len(payload)
    if length < 126:
        b2 |= length
        message += chr(b2)
    
    elif length < (2 ** 16) - 1:
        b2 |= 126
        message += chr(b2)
        l = struct.pack(">H", length)
        message += l
    
    else:
        l = struct.pack(">Q", length)
        b2 |= 127
        message += chr(b2)
        message += l

    # append payload to message
    message += payload

    # sending to client
    return str(message)

def decodeCharArray(stringStreamIn):
    byteArray = [ord(character) for character in stringStreamIn]
    datalength = byteArray[1] & 127
    indexFirstMask = 2

    if datalength == 126:
        indexFirstMask = 4
    elif datalength == 127:
        indexFirstMask = 10

    # extract masks
    masks = [m for m in byteArray[indexFirstMask : indexFirstMask+4]]
    indexFirstDataByte = indexFirstMask + 4

    # list of decoded characters
    decodedChars = []
    i = indexFirstDataByte
    j = 0

    # loop each byte that was received
    while i < len(byteArray):

        # Unmask this byte and add to the decoded buffer
        decodedChars.append( chr(byteArray[i] ^ masks[j % 4]) )
        i += 1
        j += 1

    # return the decoded string
    return "".join(decodedChars)



def dohandshake(header):
    handshake = ""
    header_lines = header.split('\r\n')[1:]
    for line in header_lines:
        try:
            name, value = line.split(': ', 1)
        except ValueError:
            continue
        # If this is the key
        if name.lower() == "sec-websocket-key":
            # Replace the placeholder in the handshake response
            handshake += "HTTP/1.1 101 Switching Protocols\r\n"
            handshake += "Upgrade: WebSocket\r\n"
            handshake += "Connection: Upgrade\r\n"
            handshake += "Sec-WebSocket-Accept: " + base64.b64encode(hashlib.sha1(value + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11").digest()) + "\r\n"
            handshake += "\r\n"
            return handshake
    return False



class Server:
    def __init__(self):
        # init server properties
        self.host = ''
        self.port = 8099
        self.backlog = 5
        self.size = 1024
        self.server = None
        self.threads = []

    def open_socket(self):
        try:
            self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.server.bind((self.host,self.port))
            self.server.listen(5)
            self.server.settimeout(1)
        except socket.error, (value,message):
            if self.server:
                self.server.close()
            print ">> Could not open socket: " + message
            sys.exit(1)

    def run(self):
        self.open_socket()
        input = [self.server, sys.stdin]
        running = 1
        print '>> listen on {} port'.format(self.port)
        while running:
            try:
                inputready,outputready,exceptready = select.select(input,[],[])

                for s in inputready:

                    if s == self.server:
                        # handle the server socket
                        c = Client(self.server.accept())
                        c.start()                        
                        self.threads.append(c)
                    elif s == sys.stdin:
                        # handle standard input
                        junk = raw_input()
                        running = self.server_msg_handler(junk)
            except KeyboardInterrupt:
                print '>> Exit from keyboard. Shut down server'
                running = 0
        # close all threads
        self.server.close()
        #for c in self.threads:
          #  c.join()

    def server_msg_handler(self,msg):
        result = 1
        print '>> recieved message: {}.'.format(msg)
        if msg in ( '-exit', '-e' ):
            print ' ~ EXIT statement caught, waiting for clients to disconnect'
            result = 0
        elif msg in ( '-test', '-t' ):
            for c in self.threads:
                if c.handshaked:
                    c.client.send(sendMessage("Hello"))
                else:
                    c.client.send("Hello")
        else:
            msg = json.dumps({"status" : worker_signal, "message" : msg})
            for c in self.threads:
                if c.handshaked:
                    c.client.send(sendMessage(msg))
                else:
                    c.client.send(msg)
            
        return result
        
    def push(self, msg):
        print '>> recieved message: {}.'.format(msg)
        msg = json.dumps({"status" : worker_signal, "message" : msg})
        for c in self.threads:
            if c.handshaked:
                c.client.send(sendMessage(msg))
            else:
                c.client.send(msg)
    


            


class Client(threading.Thread):
    def __init__(self,(client,address)):
        threading.Thread.__init__(self)
        self.daemon = True
        self.client = client
        #self.client.settimeout(10)
        self.address = address
        print self.client, self.address, type(self)
        self.size = 1024
        #self.client.send(self.name)
        self.handshaked = False
        self.mode = ""

    def execute(self, commands):
        global worker_signal
        
       

        print "client: ", commands

        commands = json.loads(commands)
        print commands
        
        if commands['command'] == "stop":
            worker_signal = "stop"
            print ">> changing status to: ", worker_signal
            server.push("User " + self.name + " change status to: " + worker_signal)
        elif commands['command'] == "kill":
            worker_signal = "kill"
            print ">> changing status to: ", worker_signal
            server.push("User " + self.name + " change status to: " + worker_signal)
        elif commands['command'] == "run":
            worker_signal = "run"
            print ">> changing status to: ", worker_signal
            server.push("User " + self.name + " change status to: " + worker_signal)
        
            
        
    def run(self): 
        running = True
        first_connect = True
        while running:            
            try:
                data = self.client.recv(self.size)
            except socket.error:
                print '>> Connection refused. user {} disconnect'.format(self.name)
                server.threads.remove(self)
                self.client.close()
                running = False
                break

            if data:
                if first_connect == True:
                    handshake_response = dohandshake(data)
                    if handshake_response:
                        self.client.send(dohandshake(data))
                        self.handshaked = True
                        self.mode = "websocket"
                        first_connect = False
                        continue
                    else: 
                        self.mode = "manual"
                        first_connect = False
                    

                data = data.rstrip() if (self.mode == "manual") else decodeCharArray(data)
                 
                if is_json(data):     
                    self.execute(data)
                else:
                    server.threads.remove(self)
                    self.client.close()
                    running = False

                #print '>> received message from client {}: {}'.format(self.name,data)                    
            else:
                print '>> user {} disconnect'.format(self.name)
                server.threads.remove(self)
                self.client.close()
                running = False

def send_mail(address, text):
    # sending...
    print "sending email to ", address, "\n"
    time.sleep(1)

def send_sms(number, text):
    # sending ...
    print "sending sms to ", address, "\n"
    time.sleep();



class Worker(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self.daemon = True


    def run(self):
        running = 1
        while running:
            if worker_signal == "run":
                server.push('worker is runing...\n')
                send_mail("olgino@propaganda.ru", "Yeeaaarr")
            elif worker_signal == "stop":
                server.push('worker was stopped...\n')
            elif worker_signal == "kill":
                running = 0
            time.sleep(10)
          

server = Server()
worker = Worker()


if __name__ == "__main__":
    worker.start()
    server.run() 