#include "common.h"
#include "claves.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mqueue.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#define MAX 256


int init(){
    mqd_t queue_server;
    mqd_t queue_client;
    struct request request;
    struct reply reply;
    struct mq_attr attr;
    //initialize the client queue and the server queue
    attr.mq_maxmsg = 1;
    attr.mq_msgsize = sizeof(struct reply);
    
    
    char queue_name[MAX];
    sprintf(queue_name, "/CLIENTE_%d\n", getpid());

    queue_client = mq_open(queue_name, O_CREAT|O_RDONLY, 0700, &attr);
    if (queue_client == -1){
        perror("Error creating client queue\n");
        return -1;
    }
    queue_server = mq_open("/SERVIDOR", O_WRONLY);
    if (queue_server == -1){
        perror("Error opening server queue\n");
        return -1;
    }
    //filling sending request to server...
    strcpy(request.q_name, queue_name);
    request.op = 0;
    printf("Trying to send request...\n");
    //mq_send(mdq_t mqdes, char *msg_ptr, size_t msg_len, unsigned msg_prio)
    if (mq_send(queue_server, (char *) &request, sizeof(request), 0) < 0){
        printf("Error sending message: %s\n", strerror(errno));
        return -1;
    }


    if (mq_receive(queue_client, (char *) &reply, sizeof(reply), 0) < 0){
        perror("Error receiving request from server from Claves.c\n");
        return -1;
    }

    mq_close(queue_client);
    mq_close(queue_server);
    mq_unlink(queue_name);
    
    if(reply.success == 0){
        return -1;
    }
    return 0;
    }

int set_value(int key, char* value1, int value2, double value3){

    return 0;
    }

int get_value(int key, char* value1, int *value2, double *value3){
    //the values are returned to the pointers, 
    mqd_t queue_server;
    mqd_t queue_client;
    struct request request;
    struct reply reply;
    struct mq_attr attr;
    //set the values of the key
    attr.mq_maxmsg = 1;
    attr.mq_msgsize = sizeof(struct reply);
    
    
    char queue_name[MAX];
    sprintf(queue_name, "/CLIENTE_%d\n", getpid());

    queue_client = mq_open(queue_name, O_CREAT|O_RDONLY, 0700, &attr);
    if (queue_client == -1){
        perror("Error creating client queue\n");
        return -1;
    }

    queue_server = mq_open("/SERVIDOR", O_WRONLY);
    if (queue_server == -1){
        perror("Error opening server queue\n");
        return -1;
    }
    //filling sending request to server...
    strcpy(request.q_name, queue_name);
    request.op = 2;
    request.key = key;

    //mq_send(mdq_t mqdes, char *msg_ptr, size_t msg_len, unsigned msg_prio)
    if (mq_send(queue_server, (char *) &request, sizeof(request), 0) < 0){
        printf("Error sending message: %s\n", strerror(errno));
        return -1;
    }

    if (mq_receive(queue_client, (char *) &reply, sizeof(reply), 0) < 0){
        perror("Error receiving request from server from Claves.c\n");
        return -1;
    }

    mq_close(queue_client);
    mq_close(queue_server);
    mq_unlink(queue_name);


    if(reply.success == 0){
        return -1;
    }
    strcpy(value1, reply.value1);
    *value2 = reply.value2;
    *value3 = reply.value3;
    return 0;
    }


int modify_value(int key, char* value1, int value2, double value3){
    return 0;
    }

int delete_key(int key){
    //return 0 on success, -1 fail or key doesn't exist.
    return 0;
    }

int exists(int key){
    //return 1 if key exists, 0 if it doesn't and -1 if there's an error
    return 1;
    }
int copy_key(int key1, int key2){
    //Create and insert key2 with the values of key1, if key1 doesn't exist, return -1. if key2 exists, modify its values. return 0 on success.
    return 0;
    }
