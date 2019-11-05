#Zack Williams
#chatserv.py
# Description: creates a listen to create a socket that is specified in chatclient.c
#
#Last Modified 11/4/19i
#Course CS372-400
#


from socket import * 
import sys



#startUP() gets the soerver ready and takes the port # from teh user argument to make the bind cll
#pre cond: none
#post cond: returns a connectionSocket object to use in recievemessage()
def startup():
	serverport = int(sys.argv[1])
	host = gethostname()
	ip = gethostbyname(host)
	serverSocket = socket(AF_INET,SOCK_STREAM)
	serverSocket.bind(('',serverport))
	serverSocket.listen(1)
	print("server ready")
	connectionSocket, addr = serverSocket.accept()
	return connectionSocket

#receives message from connectionSocket from client
#pre cond: connectionSocket object from startup() function
#post cond: none

def receiveMessage(server):
	sentence = server.recv(1024)
	print("SERVER RECEIVED: " + sentence)
	endString = '/quit'
	if sentence == endString:
		print("SERVER: Client Requested End")

	if sentence == "":
		print("SERVER: no blank strings please")
		errorCount = errorCount +1
		if errorCount >= 5:
			return	

	else:
#		inputString = input(str(userB + " > "))
#		print(inputString)
		capSent = sentence.upper()
		good = server.send(capSent)
		
#calls start up and receievemessage functoins, closes socket when while loop with receive message is no longer true or client requests connection closed
#pre cond: none
#post copnd: none
def main():
	errorCount = int(0)
	server = startup()
	print("Socket created")
	userB = "Traveler"
	
	while True:	
		receiveMessage(server)

	
	connectionSocket.close()

if __name__ == '__main__':
	main()
