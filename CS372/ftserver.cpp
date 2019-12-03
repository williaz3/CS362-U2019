#include <signal.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <fcntl.h>
#include <fstream>
#include <unistd.h>

using namespace std;


//Initial variable declarations
int controlPortNumber = 0;
struct sockaddr_in hostAddress;
int controlSocket, dataSocket;
int initialSocket = 0;
int dataPort = 0;
char commandLine[5];


//Function to clear contents of char item passed to it, generally the arguments to set up the sockets
/*pre-param: char * object
 * Post: cleared char* object with no data
 * */

void clearChars(char *contents){
	memset(contents, 0, sizeof(contents));
}//end void reset()


/*tkaes int signal ctrl+c for sigint and closes both sockets as it should be a kill comamand, displays sockets closed by this process
 * pre param: int
 *post params: none
 * */
void signalController(int params){
	close(controlSocket);
	close(dataSocket);
	cout << "Kill Signal Recieved, Ports" << controlSocket << " " << dataSocket << " closed" << endl;
	exit(1);

}//end signalController


/* creates socket connection
 *pre-params: none
 * post-paramas: none
 *
 * From lecture and CS344 Project 
 * */
int createSocket(){

struct sockaddr_in address;
int connectChecker = -4;
int ipChecker = 0;
int dataConnection;

unsigned int addressSize = sizeof(address);

address.sin_port = htons(dataPort);

dataConnection = socket(AF_INET, SOCK_STREAM, 0);

	if(dataConnection == -1){
		cout << "Error: in creating a a socket " << endl;
		exit(1);
	}//end error check dataconnection

	while(connectChecker == -4){
		connectChecker = connect(dataConnection, (struct sockaddr *) &address, sizeof(address));
	
	}//end while loop

return dataConnection;



}//end createSocket()


/* gets the port number from user input
 *pre-params: none
 *post-params: int representation of the port number submitt4ed by user
 * */
int determineIncomingPortNumber(){
clearChars(commandLine);

recv(controlSocket, commandLine, sizeof(commandLine), 0);
char temp[500];
memcpy(temp, commandLine, sizeof(temp));
int dp = atoi(temp);

return dp;

}//end incomingport()



/* list the contents of the directory
 *pre=params: none
 *post-params: none
*
*based around www.tutorialspoint.com/How-can-I-get-the-list-of-files-in-a-directory-using-C-Cplusplus/
 * */
void listOutput(){
DIR * dir = opendir("./");
struct dirent *entry;
string message;

cout << "list contents to port: " << dataPort << endl;

dataSocket = createSocket();

if (dir == NULL){
return;

}//end if

while ((entry = readdir(dir)) != NULL){
message = entry->d_name; 
message += "\n";

cout << "message" << message << endl;
//convert string to char* buffer for sned function
const char* buffer = message.c_str();
//cout << buffer << endl;
send(dataSocket, buffer, strlen(buffer), 0);



//cout << entry->d_name << endl;
}


closedir(dir);

	clearChars(commandLine);
	close(controlSocket);
	close(dataSocket);

}//end listOutput()




/* returns a message if a file is in the current directory with the contents of that file, 
 * if file not found or file unable to be opened, print error instead
 *pre=params: none
 *post-params:none

based on CS344 Linux Project 
 * */
void getFile(){

//intial variable delcaration
int fileOpenCheck;
char fileName[500];
bool fileUnableOpen = false;

//clear fileName variable and recv filename from the socket, since it is being sent via the client's input
memset(fileName, 0, sizeof(fileName));
recv(controlSocket, fileName, sizeof(fileName), 0);
cout << "File " << fileName << " requested, sending via port on " << dataPort << endl;

//Error Handling: check that file was found and able to be opened, if either the file isn't found or can't be opened, print an error and close the dataSocket(secondary socket)
fileOpenCheck = open(fileName, O_RDONLY);
	if(fileOpenCheck == -1){
		const char* fileErrorMsg = "Error: File not found\n";
		send(dataSocket, fileErrorMsg, strlen(fileErrorMsg), 0);
		close(dataSocket);
		cout << fileErrorMsg << endl;
		fileUnableOpen = true;
	}//end file open error handling if

	//If there were no errors, read the contents of a file into the bufferOut and 
	if(fileUnableOpen == false){
		//initial variable declaration for file and buffer
		FILE *f;	
		char *bufferOut;

		//open the file and get the size/length of it
		f = fopen(fileName, "rb");
		fseek(f, 0, SEEK_END);
		long fileSize = ftell(f);
		
		//go to beginning of file and write to bufferOut		
		fseek(f, 0, SEEK_SET);
		bufferOut = (char*)malloc(fileSize + 1);
		fread(bufferOut, fileSize, 1, f);
		bufferOut [fileSize] = '\0';

		//write contenets of bufferOut to other end of socket, close the file, and free the memory in the bufferOut
		write(dataSocket, bufferOut, strlen(bufferOut));
		fclose(f);
		free(bufferOut);
		}//end if

	clearChars(commandLine);
	close(dataSocket);
}//end getFile()



/* Initiate connection between server and client
 *pre: none
 *post: none
 * */

void connectionSet(){
	
	clearChars(commandLine);

	while(1){
		controlSocket = accept(initialSocket, (struct sockaddr*) NULL, NULL);
		cout << "Server: Connectin on control port" << controlPortNumber << endl;
		dataPort = determineIncomingPortNumber();
		cout << "SERVER: DataPort " << dataPort << endl;
		clearChars(commandLine);
	
		recv(controlSocket, commandLine, sizeof(commandLine), 0);
		if(strcmp(commandLine, "-l") == 0){
			listOutput();
		}//end list if
		else if(strcmp(commandLine, "-g") == 0){
			getFile();
		}//end get if
		
		else{
			dataSocket = createSocket();
			const char* errorInvalidMsg = "Error: Invalid Command used\n";
			send(dataSocket, errorInvalidMsg, strlen(errorInvalidMsg), 0);
			close(dataSocket);
			cout << errorInvalidMsg << endl;

		}//end else

		close(controlSocket);
		close(dataSocket);
		cout << "SERVER: control and DataSocket closed" << endl;
	}//end while


}//end connectionSet()






/*handles the initial connection of client-server and listens on the user provided port #
 * pre: command line args
 * post: none
 *
 * */
int main (int argc, char *argv[]){
//Error handling 
if (argc != 2){
cout << "ERROR: Server // Incorrect # arguments // server <port#> &" << endl;
}

//hanldes signal SIGINT and ends connections when received
signal(SIGINT, signalController);


//Get Initial Client-Server Connection Port Number
controlPortNumber = atoi(argv[1]);

//initial Socket set up
initialSocket = socket(AF_INET, SOCK_STREAM, 0);
memset(&hostAddress, '0', sizeof(hostAddress));
hostAddress.sin_addr.s_addr = htonl(INADDR_ANY);
hostAddress.sin_port = htons(controlPortNumber);
hostAddress.sin_family = AF_INET;

//bind and listen to the socket passed in from argv[1]
bind(initialSocket, (struct sockaddr*)&hostAddress, sizeof(hostAddress));
listen(initialSocket, 10);
cout << "SERVER: Listening on PORT: " << controlPortNumber << endl;

//connectionSet() handles additional error checking and processing of further argv[] items
connectionSet();



return 0;

}//end main














