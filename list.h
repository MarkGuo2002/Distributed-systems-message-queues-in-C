#ifndef LIST_H
#define LIST_H

struct List *list;

// a node stores a key and its value, both are strings, maybe could include a strtol function
//to return int version of value property.
struct Node{
	int key;
	char value1[256];
    int value2;
    double value3;
	struct Node *next;
};

struct List{
    struct Node *head;
    struct Node *tail;
    int size;
};

#endif