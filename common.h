#ifndef COMMON_H
#define COMMON_H
#define MAX 256

struct request{
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
};
#endif