#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseRequest(char *buf, int *request_op, int *request_key, int *request_key2, char *request_value1, int *request_value2, double *request_value3) {
    //receives a string like: "2,3,5,hello,5,2.5" 6 tokens
    char *token = strtok(buf, ",");
    int count = 0;
    while (token != NULL) {
        switch (count) {
            case 0:
                *request_op = atoi(token);
                break;
            case 1:
                *request_key = atoi(token);
                break;
            case 2:
                *request_key2 = atoi(token);
                break;
            case 3:
                strcpy(request_value1, token);
                break;
            case 4:
                *request_value2 = atoi(token);
                break;
            case 5:
                *request_value3 = atof(token);
                break;
            default:
                break;
        }
        token = strtok(NULL, ",");
        count++;
    }
}
void parseReply(char *buf, int *reply_success, char *reply_value1, int *reply_value2, double *reply_value3) {
    //receives a string like: "2,3.5,a" 3 tokens
    char *token = strtok(buf, ",");
    int count = 0;
    while (token != NULL) {
        switch (count) {
            case 0:
                *reply_success = atoi(token);
                break;
            case 1:
                strcpy(reply_value1, token);
                break;
            case 2:
                *reply_value2 = atoi(token);
                break;
            case 3:
                *reply_value3 = atof(token);
                break;
            default:
                break;
        }
        token = strtok(NULL, ",");
        count++;
    }
}
/*
int main() {
    int request_op;
int request_key;
int request_key2;
char request_value1[MAX];
int request_value2;
double request_value3;

int reply_success;
char reply_value1;
int reply_value2;
double reply_value3;
    printf("request_op: %d\n", request_op);
    printf("request_key: %d\n", request_key);
    printf("request_key2: %c\n", request_key2);
    printf("request_value1: %s\n", request_value1);
    printf("request_value2: %d\n", request_value2);
    printf("request_value3: %f\n", request_value3);
    printf("reply_success: %d\n", reply_success);
    printf("reply_value1: %d\n", reply_value1);
    printf("reply_value2: %d\n", reply_value2);
    printf("reply_value3: %f\n", reply_value3);

    char buffer[100];
    strcpy(buffer, "2,3,5,hello,5,2.5");
    //receives a string like: "2,3,5,hello,5,2.5" 6 tokens
    parseRequest(buffer, &request_op, &request_key, &request_key2, request_value1, &request_value2, &request_value3);

    strcpy(buffer, "2,a,19,2.3");
    parseReply(buffer, &reply_success, &reply_value1, &reply_value2, &reply_value3);

    printf("request_op: %d\n", request_op);
    printf("request_key: %d\n", request_key);
    printf("request_key2: %c\n", request_key2);
    printf("request_value1: %s\n", request_value1);
    printf("request_value2: %d\n", request_value2);
    printf("request_value3: %f\n", request_value3);
    printf("reply_success: %d\n", reply_success);
    printf("reply_value1: %d\n", reply_value1);
    printf("reply_value2: %d\n", reply_value2);
    printf("reply_value3: %f\n", reply_value3);
    return 0;
}

*/
