#include "servidor.h"
#include "common.h"
#include "lines.h"
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mqueue.h>
#include <pthread.h>
#define MAX 256

sem_t wrt;
pthread_mutex_t rd_mutex;
int readers;

char s_value1[MAX];
int s_value2;
double s_value3;

int request_op;
int request_key;
int request_key2;
char request_value1[MAX];
int request_value2;
double request_value3;

//pthread_mutex_t mutex_request;
//int request_not_copied = 1;
//pthread_cond_t cond_request;

void treat_request(char *buf){
    char bufCopy[MAX];
    //pthread_mutex_lock(&mutex_request);
    //request_copy = *request;
    strcpy(bufCopy, buf);
    //request_not_copied = 0;
    //pthread_cond_signal(&cond_request);
    //pthread_mutex_unlock(&mutex_request);
    //parseRequest(bufCopy, &request_op, &request_key, &request_key2, request_value1, &request_value2, &request_value3);
    switch(request_op){
        case 0:
            printf("///////////Treating init()///////////////\n");

            

            break;
        case 1:
        printf("hello\n");
            break;

    printf("Request treated!\n\nCurrent List:\n");
    printList();
    printf("=========================================================\n");
    pthread_exit(NULL);
    
}
}
int main(int argc, char *argv[]){
    printf("entered server main\n");
    if (argc != 2){
        printf("Usage: %s <server_port>\n", argv[0]);
        exit(1);
    }
    int port = atoi(argv[1]);
    int sd, newsd;
    socklen_t usersize;
	int val;
	int err;
// sockadd_in is a structure that contains the address of the socket of type IPv4
        struct sockaddr_in server_addr, client_addr;
//1.-create a socket for server, AF_INET for IPv4, SOCK_STREAM for TCP, IPPROTO_TCP for TCP | if UDP is wanted, use SOCK_DGRAM
        sd =  socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sd < 0) {
                perror("Error in socket");
                exit(1);
        }

        val = 1;
// setsockopt() is used to allow the local address to be reused when the server is restarted before the required wait time expires
        err = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *) &val, sizeof(int));
        if (err < 0) {
                perror("Error in option");
                exit(1);
        }


//2.-bind the socket to the server address, which means that the server will listen to the port 4200, a port is a process that handles specific port
//bzero() is used to set the server_addr to 0 in order to avoid errors
        bzero((char *) &server_addr, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
//server_addr.sin_addr.s_addr  means that the server will listen to any IP address that is connected to the server
        server_addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(sd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
                perror("Error in bind");
                exit(1);
        }

//3.-listen to the socket, SOMAXCONN is the maximum number of connections that can be queued, by default is 128.
        listen(sd, SOMAXCONN);
    
    while (1){
        printf("Waiting for requests...\n");
//4.- accept the connection, the server will wait until a client connects to the server, accept returns a new socket descriptor that is used to communicate with the client
            newsd=accept(sd, (struct sockaddr *)&client_addr, &usersize);
            if (newsd < 0){
                    printf("Error en accept");
            }
            printf("Conexion aceptada de IP: %s\nPuerto: %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            char buf[MAX];
            ssize_t bytes_read;
            while ((bytes_read = readLine(newsd, buf, MAX)) > 0) {
                    //buf[bytes_read] = '\0';
                    printf("Received: %s\n", buf);
                    treat_request(buf);
                    //strcpy(buf, "Bye!");
                    //sendMessage(newsd, buf, strlen(buf)+1);
            }
            
            close(newsd);
        }
        close (sd);
    
    return 0;
}