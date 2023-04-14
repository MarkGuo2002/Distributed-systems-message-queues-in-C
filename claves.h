// Declaration of variables and functions for a singly linked list
#ifndef CLAVES_H
#define CLAVES_H


#define MAX 256

// op = 0
int init(); //exito: 0, error: -1
// op = 1
int set_value(int key, char* value1, int value2, double value3); //return 0 on success, -1 fail.
// op = 2
int get_value(int key, char* value1, int *value2, double *value3); //the values are returned to the pointers, o exito, -1 error
// op = 3
int modify_value(int key, char* value1, int value2, double value3);//0 exito, -1 error
// op = 4
int delete_key(int key);//return 0 on success, -1 fail or key doesn't exist.
// op = 5
int exist(int key);//return 1 if key exists, 0 if it doesn't and -1 if there's an error
// op = 6
int copy_key(int key1, int key2);
//Create and insert key2 with the values of key1::: if key1 doesn't exist, return -1. if key2 exists, modify its values. return 0 on success.
#endif
