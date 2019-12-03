#Zack Williams
#CS372-400 
#Client.py
#Client side of assignment two, connects to server.cpp and sneds the command to the server to execute as appropriate
#last modified: 12/1/19


#from socket import *
import socket
import time
import os.path
import getopt
import sys


#defualt error message for majority of errors that cna happen on client side(arg errors)
def errorMessage():
		print("Error: Client:  Invalid # arguments \n")
		print("python client.py <localhost/serverIP> <controlPort> <-l> <dataPort> \nOR \n python client.py <localhost/ip> <controlPort> <-g> <filename> <dataPort>\n" )
		sys.exit()

#checks for errors in the arguments before allowing the server-client connection to be established
def initialArgHandler():
	#If argment lenth is not 5 or 6 (the correct amount for -l and -g respectively, show an error message
	if len(sys.argv) !=5 and len(sys.argv) != 6:
		errorMessage()
	#if -g is the argment 3 and length is not 6 (which is correct for that command), show an error message
	if sys.argv[3] == "-g" and len(sys.argv) != 6:
		errorMessage()
	#if -l is the arg3 and length is not 5, show an error message
	if sys.argv[3] == "-l" and len(sys.argv) !=5: 
		errorMessage()

#send message to server for list command "-l"
def listSocket(commandSocket):
	print("ListCommandProtocol")
	commandSocket.send(sys.argv[4])
	#time.sleep(.2)
	commandSocket.send("-l")

#send message to server for the getFile Commnand "-g"
def getSocket(commandSocket):
	print("GetCommandProtocol")
	commandSocket.send(sys.argv[5])
	commandSocket.send("-g")
	time.sleep(.5)
	commandSocket.send(sys.argv[4])

#based on the number of args passed, bind the client and server on the port in the appropriate arg #
def clientDataSocket():
	dataSocket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
	print("Data Scoket Started")	
	if sys.argv[3] == "-l":
		dataSocket.bind(('', int(sys.argv[4])))

	elif len(sys.argv) == 5 and sys.argv[3] != "-l":
		dataSocket.bind(('', int(sys.argv[4])))
	else:
		dataSocket.bind(('', int(sys.argv[5])))

	dataSocket.listen(50)
	tempSocket = dataSocket.accept()

	buffer = tempSocket.recv(444444)
	print( "buffer on client" )
	print(buffer)
	error1 = "error: file does not exist\n"
	error2 = "error: invalid command entered\n"
	
	if sys.argv[3] == "-l":
		print("Server Directory Contents: " + buffer)
	if buffer == error1:
		print("error:" + sys.argv[4] + " not found\n")
	if buffer == error2:
		print("error: invalid command\n")

	if sys.argv[3] == "-g":
		print("file found: " + sys.argv[4])
		with open(sys.argv[4], 'w') as newFile:
			newFile.write(buffer)
	return dataSocket




if __name__ == '__main__':
	#make sure args passed to client.py are correct in form/number
	initialArgHandler()
	#set up initial socket with SERVER
	clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	clientSocket.connect((sys.argv[1], int(sys.argv[2])))
	
	if sys.argv[3] == "-g" and len(sys.argv) == 6:
		getSocket(clientSocket)

	elif sys.argv[3] == "-l" and len(sys.argv) == 5:
		listSocket(clientSocket)

	else:
		errorMessage()


	dataSocket = clientDataSocket()

	#close the client and data sockets and print message to console
	clientSocket.close()
	dataSocket.close()
	print("socket closed, client side terminated \n")

