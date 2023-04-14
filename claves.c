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






int initializeSocket(){
    int sd;
    struct sockaddr_in server_addr;
    struct hostent *hp;
    char *ip;
    char *portEnv;
    int port;

    //get ip and port from environment variables
    ip = getenv("IP_TUPLAS");
    if (ip == NULL){
        perror("IP_TUPLAS not found\n");
        exit(1);
    }

    
    portEnv = getenv("PORT_TUPLAS");
    if (portEnv == NULL){
        perror("PORT_TUPLAS not found\n");
        exit(1);
    }
    
    printf("portEnv: %s\n", portEnv);
    
    port = atoi(portEnv);
    printf("Env read, ip: %s, port: %d\n", ip, port);

    // 1.-Create socket for client
    sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sd < 0){
        perror("Error in socket");
        exit(1);
    }

    hp = gethostbyname(ip);
    if (hp == NULL) {
        perror("Error en gethostbyname");
        exit(1);
    }

    bzero((char *)&server_addr, sizeof(server_addr));
    memcpy (&(server_addr.sin_addr), hp->h_addr, hp->h_length);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    //2.- Connect to the server
    printf("Connecting to server...\n");
    if (connect(sd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        perror("Error in connect");
        exit(1);
    }
    printf("Connected to server\n");

    return sd;
}



int init(){
    printf("init()\n");
    int reply_success;
    char reply_value1;
    int reply_value2;
    double reply_value3;
    int sd;
// 1.-Create socket for client
    sd = initializeSocket();


    char buf[MAX];
    strcpy(buf, "0");   
    if (sendMessage(sd, buf, strlen(buf)+1) < 0) {
        perror("Error sending message");
        return -1;
    }
    printf("enviado: %s\n", buf);

    if(readLine(sd, buf, MAX) < 0){
        perror("Error receiving message");
        return -1;
    }
    printf("recibido: %s\n", buf);
    //close socket

    close(sd);
    // now inside buf contains the reply from the server sth like "1,3,a,5"?
    parseReply(buf, &reply_success, &reply_value1, &reply_value2, &reply_value3);
    if (reply_success == 0){
        return 0;
    }
    return(-1);

    }


int set_value(int key, char* value1, int value2, double value3){

    printf("set_value()\n");
    if (strlen(value1) > 255){
        printf("message too long\n");
        return -1;
    }
    int reply_success;
    char reply_value1;
    int reply_value2;
    double reply_value3;

    int sd = initializeSocket();

//request: op, key, key2, value1, value2, value3
    char buf[MAX];
    sprintf(buf, "1,%d,0,%s,%d,%f", key, value1, value2, value3);
    if (sendMessage(sd, buf, strlen(buf)+1) < 0) {
        perror("Error sending message");
        return -1;
    }
    printf("enviado: %s\n", buf);

    if(readLine(sd, buf, MAX) < 0){
        perror("Error receiving message");
        return -1;
    }

    close(sd);
    // now inside buf contains the reply from the server sth like "1,3,a,5"?
    parseReply(buf, &reply_success, &reply_value1, &reply_value2, &reply_value3);
    printf("reply_success: %d\n", reply_success);
    printf("reply_value1: %s\n", &reply_value1);
    printf("reply_value2: %d\n", reply_value2);
    printf("reply_value3: %f\n", reply_value3);
    if (reply_success == 0){
        return 0;
    }
    return(-1);

    }

int get_value(int key, char* value1, int *value2, double *value3){
    //the values are returned to the pointers, 
    printf("get_value()\n");
    int reply_success;

    int sd = initializeSocket();


    //request: op, key, key2, char*value1, value2, value3
    char buf[MAX];
    sprintf(buf, "2,%d,0,0,0,0", key);
    if (sendMessage(sd, buf, sizeof(buf)+1) < 0) {
        perror("Error sending message");
        return -1;
    }
    printf("enviado: %s\n", buf);

    if(readLine(sd, buf, MAX) < 0){
        perror("Error receiving message");
        return -1;
    }

    close(sd);
    // now inside buf contains the reply from the server sth like "1,3,a,5"?
    parseReply(buf, &reply_success, value1, value2, value3);


    printf("reply_success: %d\n", reply_success);
    printf("reply_value1: %s\n", value1);
    printf("reply_value2: %d\n", *value2);
    printf("reply_value3: %f\n", *value3);
    if (reply_success == 0){
        return 0;
    }
    return(-1);

    }



int modify_value(int key, char* value1, int value2, double value3){
    printf("modify_value()\n");
    int reply_success;
    char reply_value1;
    int reply_value2;
    double reply_value3;

    int sd = initializeSocket();

//void parseRequest(char *buf, int *request_op, int *request_key, int *request_key2, char *request_value1, int *request_value2, double *request_value3);
//void parseReply(char *buf, int *reply_success, char *reply_value1, int *reply_value2, double *reply_value3);
    char buf[MAX];
    sprintf(buf, "3,%d,0,%s,%d,%f", key, value1, value2, value3);
    if (sendMessage(sd, buf, sizeof(buf)+1) < 0) {
        perror("Error sending message");
        return -1;
    }
    printf("enviado: %s\n", buf);

    if(readLine(sd, buf, MAX) < 0){
        perror("Error receiving message");
        return -1;
    }

    close(sd);
    // now inside buf contains the reply from the server sth like "1,3,a,5"?
    parseReply(buf, &reply_success, &reply_value1, &reply_value2, &reply_value3);
    if (reply_success == 0){
        return 0;
    }
    return(-1);
    }

int delete_key(int key){
    //return 0 on success, -1 fail or key doesn't exist.
    printf("delete_key()\n");
    int reply_success;
    char reply_value1;
    int reply_value2;
    double reply_value3;

    int sd = initializeSocket();

//request: op, key, key2, value1, value2, value3
    char buf[MAX];
    sprintf(buf, "4,%d,0,0,0,0", key);
    if (sendMessage(sd, buf, strlen(buf)+1) < 0) {
        perror("Error sending message");
        return -1;
    }
    printf("enviado: %s\n", buf);

    if(readLine(sd, buf, MAX) < 0){
        perror("Error receiving message");
        return -1;
    }

    close(sd);
    // now inside buf contains the reply from the server sth like "1,3,a,5"?
    parseReply(buf, &reply_success, &reply_value1, &reply_value2, &reply_value3);
    if (reply_success == 0){
        return 0;
    }
    return(-1);

    }

int exist(int key){
    //return 1 if key exists, 0 if it doesn't and -1 if there's an error
    printf("exist()\n");
    int reply_success;
    char reply_value1;
    int reply_value2;
    double reply_value3;

    int sd = initializeSocket();

//request: op, key, key2, value1, value2, value3
    char buf[MAX];
    sprintf(buf, "5,%d,0,0,0,0", key);
    if (sendMessage(sd, buf, strlen(buf)+1) < 0) {
        perror("Error sending message");
        return -1;
    }
    printf("enviado: %s\n", buf);

    if(readLine(sd, buf, MAX) < 0){
        perror("Error receiving message");
        return -1;
    }

    close(sd);
    // now inside buf contains the reply from the server sth like "1,3,a,5"?
    parseReply(buf, &reply_success, &reply_value1, &reply_value2, &reply_value3);
    if (reply_success == 0){
        return 0;
    }
    else if(reply_success == 1){
        return 1;
    }
    else{
        return -1;
    }
    }
int copy_key(int key1, int key2){
    printf("copy_key()\n");
    int reply_success;
    char reply_value1;
    int reply_value2;
    double reply_value3;

    int sd = initializeSocket();

//request: op, key, key2, value1, value2, value3
    char buf[MAX];
    sprintf(buf, "6,%d,%d,0,0,0", key1, key2);
    if (sendMessage(sd, buf, strlen(buf)+1) < 0) {
        perror("Error sending message");
        return -1;
    }
    printf("enviado: %s\n", buf);

    if(readLine(sd, buf, MAX) < 0){
        perror("Error receiving message");
        return -1;
    }

    close(sd);
    // now inside buf contains the reply from the server sth like "1,3,a,5"?
    parseReply(buf, &reply_success, &reply_value1, &reply_value2, &reply_value3);
    if (reply_success == 0){
        return 0;
    }
    return(-1);

    }
