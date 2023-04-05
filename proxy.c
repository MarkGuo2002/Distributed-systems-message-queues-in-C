#include "servidor.h"
#include "common.h"

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

mqd_t queue_server;
pthread_mutex_t mutex_request;
int request_not_copied = 1;
pthread_cond_t cond_request;

void treat_request(struct request *request){
    struct request request_copy;
    pthread_mutex_lock(&mutex_request);
    request_copy = *request;
    request_not_copied = 0;
    pthread_cond_signal(&cond_request);
    pthread_mutex_unlock(&mutex_request);


    mqd_t queue_cliente;
    struct reply reply;
    queue_cliente = mq_open(request_copy.q_name, O_WRONLY);
    if(queue_cliente==-1){
        perror("Error opening client queue in proxy.c\n");
        }
    switch(request_copy.op){
        case 0:
            printf("///////////Treating init()///////////////\n");
            if (init() != 0){
                perror("Init not succesfull\n");
            }
            reply.success = 1;
            if(mq_send(queue_cliente, (char *)&reply, sizeof(reply), 0) < 0){
                perror("Sending not successful\n");
            }
            printf("Init successful from server\n");
            

            break;
        case 1:
            printf("///////////Treating set_value()///////////////\n");
            if (set_value(request_copy.key, request_copy.value1, request_copy.value2, request_copy.value3) != 0){
                perror("Set_value not succesfull\n");
                reply.success = 0;
            }else{
            reply.success = 1;
            }
            printf("Set value from server\n");
            if(mq_send(queue_cliente, (char *)&reply, sizeof(reply), 0) < 0){
                perror("Sending not successful\n");
            }
            break;
        case 2:
            printf("///////////Treating get_value()///////////////\n");
            if (get_value(request_copy.key, s_value1, &s_value2, &s_value3) != 0){
                perror("Get_value not succesfull\n");
                reply.success = 0;
            }else{
            reply.success = 1;
            strcpy(reply.value1, s_value1);
            reply.value2 = s_value2;
            reply.value3 = s_value3;
            }
            if(mq_send(queue_cliente, (char *)&reply, sizeof(reply), 0) < 0){
                perror("Sending not successful\n");
            }
            break;
        case 3:
            printf("///////////Treating modify_value()///////////////\n");
            if (modify_value(request_copy.key, request_copy.value1, request_copy.value2, request_copy.value3) == -1){
                perror("Key does not exist, use set_value instead\n");
                reply.success = 0;
            }else{
            reply.success = 1;
            }
            if(mq_send(queue_cliente, (char *)&reply, sizeof(reply), 0) < 0){
                perror("Sending not successful\n");
            }
            break;
        case 4:
            printf("///////////Treating delete_key()///////////////\n");
            if (delete_key(request_copy.key) != 0){
                perror("Delete_key not succesfull. Key does not exist\n");
                reply.success = 0;
            }else{
            reply.success = 1;
            }
            if(mq_send(queue_cliente, (char *)&reply, sizeof(reply), 0) < 0){
                perror("Sending not successful\n");
            }
            break;
        case 5:
        printf("///////////Treating exists()///////////////\n");
            if (exists(request_copy.key) == 0){
                perror("Key does not exist\n");
                reply.success = 0;
            }else{
            reply.success = 1;
            }
            if(mq_send(queue_cliente, (char *)&reply, sizeof(reply), 0) < 0){
                perror("Sending not successful\n");
            }
            break;
        case 6:
        printf("///////////Treating copy_key()///////////////\n");
            if (copy_key(request_copy.key, request_copy.key2) != 0){
                perror("Copy_key not succesfull\n");
                reply.success = 0;
            }else{
            reply.success = 1;
            }
            if(mq_send(queue_cliente, (char *)&reply, sizeof(reply), 0) < 0){
                perror("Sending not successful\n");
            }
            break;

        default:
            printf("Error: invalid operation.");
            break;
    }
    mq_close(queue_cliente);
    mq_unlink(request_copy.q_name);
    printf("Request treated!\n\nCurrent List:\n");
    printList();
    printf("=========================================================\n");
    pthread_exit(NULL);
    
}

int main(){
    printf("entered server main\n");
    struct request request;
    struct mq_attr attr;
    attr.mq_msgsize = sizeof(struct request);
    attr.mq_maxmsg = 10;
    //concurrency
    pthread_attr_t thread_attr;
    pthread_t thid;

    pthread_mutex_init(&rd_mutex, NULL);
    sem_init(&wrt, 0, 1);
    readers = 0;
    
    //initialize the server queue
    queue_server = mq_open("/SERVIDOR", O_CREAT|O_RDONLY, 0700, &attr);
    if (queue_server == -1){
        perror("Error creating server queue");
        return 1;
    }

    pthread_mutex_init(&mutex_request, NULL);
    pthread_cond_init(&cond_request, NULL);
    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
    
    while (1){
        printf("Waiting for requests...\n");
        // mq_receive writes in request
        if(mq_receive(queue_server, (char *) &request, sizeof(request), 0) < 0){
            perror("Error receiving requests\n");
            return -1;
        }
        printf("Message received from queue %s\n", request.q_name);
        
        if (pthread_create(&thid, &thread_attr, (void *)treat_request, (void *)&request) == 0){
            pthread_mutex_lock(&mutex_request);
            while(request_not_copied == 1){
                pthread_cond_wait(&cond_request, &mutex_request);
            }
            request_not_copied = 1;
            pthread_mutex_unlock(&mutex_request);
        }
        
    }
    return 0;
}