#ifndef COMMON_H
#define COMMON_H
#define MAX 256

int request_op;
int request_key;
int request_key2;
char request_value1[MAX];
int request_value2;
double request_value3;

int reply_success;
char reply_value1[MAX];
int reply_value2;
double reply_value3;

void parseRequest(char *buf);
void parseReply(char *buf);

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