#ifndef COMMON_H
#define COMMON_H
#define MAX 256


void parseRequest(char *buf, int *request_op, int *request_key, int *request_key2, char *request_value1, int *request_value2, double *request_value3);
void parseReply(char *buf, int *reply_success, char *reply_value1, int *reply_value2, double *reply_value3);

/*struct request{
    //op ranges from 0 to 6
    int op;
    int key;
    int key2;
    char value1[MAX];
    int value2;
    double value3;
    char q_name[MAX];
};

struct reply{
    int success;
    //char status;
    char value1[MAX];
    int value2;
    double value3;
};*/

#endif