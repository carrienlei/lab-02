/* A simple server in the internet domain using TCP
 * Answer the questions below in your writeup
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    /* 1. What is argc and *argv[]?
     *  Argc is an integer that counts how many arguments were entered
     on the command line and that will be pointed to by argv. Argv are 
     pointers which points to arrays of characters. 
     */
    int sockfd, newsockfd, portno;
    /* 2. What is a UNIX file descriptor and file descriptor table?
     *  A UNIX file descriptor is an identifier of type unsigned integer 
     that is used to identify an open file. A file descriptor table 
     collects all the descriptors in the form of an array; pointers are 
     used to access the table entries.
     */
    socklen_t clilen;

    struct sockaddr_in serv_addr, cli_addr;
    /* 3. What is a struct? What's the structure of sockaddr_in?
     *  A struct in C is a way to group similar variables together
     in one location. It can contain multiple data types unlike an 
     array. The structure of sockaddr_in is that it contains a short
     for the address family, an unsigned short for the port number,
     an unsigned long with the address, and a char. 
     */
    
    int n;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    /* 4. What are the input parameters and return value of socket()
     *  The input parameters of socket() are: an integer for the 
     domain used for communication, a communication type - eg tcp or udp,
     and a protocol value for internet protocol (IP). The function then
     returns an integer (named sockfd) that is a descriptor for the 
     socket. 
     */
    
    if (sockfd < 0) 
        error("ERROR opening socket");
        bzero((char *) &serv_addr, sizeof(serv_addr));
        portno = atoi(argv[1]);
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = INADDR_ANY;
        serv_addr.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
        sizeof(serv_addr)) < 0) 
        error("ERROR on binding");
    /* 5. What are the input parameters of bind() and listen()?
     *  The input parameters for bind() are an integer for the socketfd,
     the server address pointed to by the sockaddr struct, and the length
     of the server address.

     For listen(), the input parameters are an integer for the socketfd, 
     and an integer for the backlog which defines the max length the sockfd 
     can grow pending on connections.
     */
    
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    
    while(1) {
        /* 6.  Why use while(1)? Based on the code below, what problems might occur if there are multiple simultaneous connections to handle?
        *   We use while(1) because the server is always ready to accept a message from 
        the client to create and bind to the new socket. Problems that might occur if there
        are multiple simultaneous connections are delays and missed packages. For instance,
        while the server is reading and processing a package from one connection, it 
        will miss / not be able to simultaneously handle an incoming package from another connection.
        */
        
	char buffer[256];
        newsockfd = accept(sockfd, 
                    (struct sockaddr *) &cli_addr, 
                    &clilen);
	/* 7. Research how the command fork() works. How can it be applied here to better handle multiple connections?
         * The command fork() is a way to duplicate the calling process -- it creates both a parent process
         (which is the original) and a child process (the duplication). The function does not have any 
         parameters and returns an integer: 0 for when the child process is successfully created, a positive
         value to the parent process that contains the ID, and a negative value when the child process fails.

         In this case, we could use fork() to better handle multiple connections by forking the newsockfd = accept() function.
         This way, there can be multiple sockets created simultaneously and accept multiple connections at once. 
         */
        
	if (newsockfd < 0) 
             error("ERROR on accept");
	bzero(buffer,256);
        
	n = read(newsockfd,buffer,255);
        if (n < 0) 
            error("ERROR reading from socket");
        printf("Here is the message: %s\n",buffer);
        n = write(newsockfd,"I got your message",18);
        if (n < 0) 
            error("ERROR writing to socket");
        close(newsockfd);
    }
    close(sockfd);
    return 0; 
}
  
/* This program makes several system calls such as 'bind', and 'listen.' What exactly is a system call?
 *  A system call is a request to the operating system to do something for the program.
 */