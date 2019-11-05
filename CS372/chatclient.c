/*Author: Zack Williams
 *Program name: chatclient.c
 *Description: connects to a port/host address delcared in chatserver.py via socket, if connection
 *made allow user to input username for future messages, send a message to server, allows server
 * to send message back, continues till the client or server ends the connection
 *CS 372-400
 * Last MOdified 11/4/19
 *
 * Refereneces: basic program outline for chatclient.c is from the CS class for operating systems networking assignment with modifications for CS372 assignment
 *
 * */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>


void error(const char *msg){ perror(msg); exit(0); }//error function for reporting issues

//Global variable declarations
int socketFD, portNumber, charsWritten, charsRead;
struct sockaddr_in serverAddress;
struct hostent* serverHostInfo;
char buffer[256];
char username[10];

/* initiateContact() attempts to connect socket to server, displays errors as applicable
 * pre-conditions: socketFD msut be declared in main and passed as parameter
 * post-conditions: none, no return, 
 * */
void initiateContact(int socketFD){
	if (socketFD < 0) error("CLIENT: ERROR opening socket");

	//connect to server
	if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) //connect socket to address
	error("CLIENT: ERROR connecting");
}


/* sendMessage()takes the users input and sends it to the serve
 * pre-conditions; none
 * post-conditions: none
 * */
int sendMessage(){

	printf("%s> ", username);
	/*Preps Buffer to take user input */
	memset(buffer, '\0', sizeof(buffer));//clear out the buffer array
	fgets(buffer, sizeof(buffer) - 1, stdin); //get input form the user, trunc to buffer -1 char and leave the \0
	int blankCheck = (strcmp(buffer, ""));
	blankCheck = (strcmp(buffer,"\n"));	
//	printf("%d\n", blankCheck);
	if (blankCheck == 0){
		printf("can't send blank message, try again \n");
		return 1;
		}

	buffer[strcspn(buffer, "\n")] = '\0'; // remove the trailing \n that fgets adds
	/* testin */
	char killCommand[10] = "/quit";
	int endCheck = (strcmp(buffer,killCommand ));
	
	if (endCheck == 0){
		charsWritten = send(socketFD, killCommand, strlen(killCommand), 0);
		return 4;
	}
	

	/* end testing */

	/*Attempts to send client side message to server */
	charsWritten = send(socketFD, buffer, strlen(buffer), 0); //write to server
//	printf("Client:message sent \n");

	/* Error Handling Block */
	if (charsWritten < 0 ) error("CLIENT: ERROR writing to the socket");
	if (charsWritten < strlen(buffer)) printf("CLIENT: WARNING: not all datat written to teh socket!\n");
}

/* Recieve message() receives reply message from server
 * pre-cond: none
 * post-cond: none
 **/

void recieveMessage(){
	memset(buffer, '\0', sizeof(buffer)); //clear out buffera gain for reuse
	charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0); //read data from the socket, leaving \0 at end
	if (charsRead < 0) error("CLIENT:ERROR: reading from socket");
	printf("CLIENT: I received this from the server: \"%s\"\n", buffer);
}


/* userREady() gets userinformation for initial client ot server connection and for the ones
 * after the client discontinues their connection
 * pre-cond: none
 * post cond: none
 *
 * */
void userReady(){
memset(username, '\0', sizeof(memset));
printf("enter username, then hit enter: \n");
fgets(username, sizeof(username) -1, stdin);
username[strcspn(username, "\n")] = '\0';
}


int main( int argc, char *argv[]){
if (argc < 3) {fprintf(stderr, "USAGE: %s hostname port\n", argv[0]); } //check usage and args passed

//set up the server address struct
memset((char*)&serverAddress, '\0', sizeof(serverAddress)); //clear out the address struct
portNumber = atoi(argv[2]); //get the port nnumber, convert to an integer from a string
serverAddress.sin_family = AF_INET; //create a network-capable socket
serverAddress.sin_port = htons(portNumber); //store the port number
serverHostInfo = gethostbyname(argv[1]); // convert the macine name into a special form of address



if (serverHostInfo == NULL) { fprintf(stderr, "CLIENT: ERROR, no such host\n"); exit(0);}

memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length); //copy in the address

//set up the socket
socketFD = socket(AF_INET, SOCK_STREAM, 0); //create the socket
initiateContact(socketFD);
//if (socketFD < 0) error("CLIENT: ERROR opening socket");

//connect to server
//if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) //connect socket to address
//error("CLIENT: ERROR connecting");

/* Testing */

/*End TEsting */
userReady();

while(1){
int endCheck;

if (endCheck==4){
	userReady();
}

endCheck = sendMessage();

	if (endCheck == 4){
	continue;
	}

recieveMessage();

continue;
}//end while


close(socketFD); // close the socket
return 0;

} //end main





















