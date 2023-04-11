#include "common.h"
#include "claves.h"
#include "lines.h"
#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#define MAX 256

char buf[MAX];
int reply_success;
char reply_value1;
int reply_value2;
double reply_value3;


int init(){
    printf("init()\n");
    int sd;
        struct sockaddr_in server_addr;
        struct hostent *hp;

// 1.-Create socket for client
        sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sd < 0){
                perror("Error in socket");
                exit(1);
        }
        char *ip;
        char *portEnv;
        ip = getenv("IP_TUPLAS");
        if (ip == NULL){
                perror("IP_TUPLAS not found\n");
                exit(1);
        }
        hp = gethostbyname (ip);
        portEnv = getenv("PORT_TUPLAS");
        if (portEnv == NULL){
                perror("PORT_TUPLAS not found\n");
                exit(1);
        }
        int port = atoi(portEnv);
        printf("Env read, ip: %s, port: %d\n", ip, port);
    

	// Obtain Server address 
        bzero((char *)&server_addr, sizeof(server_addr));
        //gethostbyname() is used to obtain the IP address of the hostname of the server, which in this case would be localhost
        //gethostname obtains the the name of current host instead

        /*
        struct hostent {
                char    *h_name;        // official name of host
                char    **h_aliases;    // alias list
                int     h_addrtype;     // host address type
                int     h_length;       // length of address
                char    **h_addr_list;  // list of addresses
        }*/
        if (hp == NULL) {
                perror("Error en gethostbyname");
                exit(1);
        }

        /*
        struct sockaddr_in {
                short   sin_family;
                u_short sin_port;
                struct  in_addr sin_addr; this determines the IP address
                char    sin_zero[8];
        };*/
	memcpy (&(server_addr.sin_addr), hp->h_addr, hp->h_length);
        server_addr.sin_family = AF_INET;
        //htons converts a port number in host byte order to a port number in network byte order
        server_addr.sin_port = htons(port);

	// Complete.....
//2.- Connect to the server
        printf("Connecting to server...\n");
        if (connect(sd, (struct sockaddr *)&server_addr, sizeof(server_addr))<0){
                perror("Error in connect");
                exit(1);
        }
        printf("Connected to server\n");

//void parseRequest(char *buf, int *request_op, int *request_key, int *request_key2, char *request_value1, int *request_value2, double *request_value3) {
//receives a string like: "2,3,5,hello,5,2.5" 6 tokens
        char buf[MAX];
        strcpy(buf, "0");   
        if (sendMessage(sd, buf, sizeof(buf)+1) < 0) {
            perror("Error sending message");
            exit(1);
        }
        printf("enviado: %s\n", buf);
        //receive message from server using recvMessage
//        if (recvMessage(sd, buf, MAX_LINE) < 0) {
  //         perror("Error receiving message"); 
    //        exit(1);
        //}
        //printf("recibido: %s\n", buf);
        //receive reply from, the server
        if (recvMessage(sd, buf, MAX) < 0) {
            perror("Error receiving message"); 
        }

        close(sd);
        // now inside buf contains the reply from the server sth like "1,3,a,5"?
        parseReply(buf, &reply_success, &reply_value1, &reply_value2, &reply_value3);
        if (reply_success == 1){
            return 1;
        }
        return(0);

    }

int set_value(int key, char* value1, int value2, double value3){

    return 0;
    }

int get_value(int key, char* value1, int *value2, double *value3){
    //the values are returned to the pointers, 

    return 0;
    }


int modify_value(int key, char* value1, int value2, double value3){
    return 0;
    }

int delete_key(int key){
    //return 0 on success, -1 fail or key doesn't exist.
    return 0;
    }

int exist(int key){
    //return 1 if key exists, 0 if it doesn't and -1 if there's an error
    return 1;
    }
int copy_key(int key1, int key2){
    //Create and insert key2 with the values of key1, if key1 doesn't exist, return -1. if key2 exists, modify its values. return 0 on success.
    return 0;
    }
