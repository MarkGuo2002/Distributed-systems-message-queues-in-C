/*Implementation of a singly linked list*/
#include "servidor.h"
#include "list.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



//There is going to be only one writer at the same time
void deleteList(){
    struct Node *aux = list->head;
    struct Node *prev = NULL;
    while (aux != NULL){
        prev = aux;
        aux = aux->next;
        free(prev);
    }
    free(list);
}

int init(){
     //writer
    //sem_wait(&wrt);
    if (list != NULL){
        deleteList();
    }
    // Queda por implementar si la lista ya existe y tiene que borrar
    list = (struct List *) malloc(sizeof(struct List));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    //sem_post(&wrt);
	return 0;
}

int set_value(int key, char* value1, int value2, double value3){
    //writer

	//Checking: strlen excluye \0
    if (strlen(value1) > 255){
        printf("value1 is too long, max length is 255 characters.");
        return -1;
    }
    // case when the key already exists? ERROR
    if (exist(key) == 1){
        printf("Key already exists, use modify_value to modify its values.");
        return -1;
    }
    

	//define the node and allocate memory for it
	struct Node *nodeptr;
	nodeptr = (struct Node *) malloc(sizeof(struct Node));
	
	
    nodeptr->key = key;
	strcpy(nodeptr->value1, value1);
    nodeptr->value2 = value2;
    nodeptr->value3 = value3;
	
	//if the list is empty, it's just a head insertion
    sem_wait(&wrt);
	if (list->size == 0){
		//make node.next = null and *l(current node pointer) = current node
		nodeptr->next = NULL;
		list->head = nodeptr;
        list->tail = nodeptr;
        list->size += 1;
	}
	//if list already contains elements, then make a tail insertion like normal lists.
	else{
        list->tail->next = nodeptr;
        list->tail = nodeptr;
        //set the new tail's next to null
        list->tail->next = NULL;
        list->size += 1;
	}
    sem_post(&wrt);
	return(0);
}

int get_value(int key, char* value1, int *value2, double *value3){
    //reader
    //lock the reader mutex to increment the number of readers
    pthread_mutex_lock(&rd_mutex);
    readers++;
    //case first reader enters to read, lock the writer.
    if (readers == 1){
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&rd_mutex);

	struct Node *aux = list->head;
	while (aux != NULL){
		if (aux->key == key){
			strcpy(value1, aux->value1);
            *value2 = aux->value2;
            *value3 = aux->value3;
            //lock the reader mutex to decrement the number of readers
            pthread_mutex_lock(&rd_mutex);
            readers--;
            //when the last reader leaves, let the writer in.
            if (readers == 0){
                sem_post(&wrt);
            }
            pthread_mutex_unlock(&rd_mutex);
			return 0;
		}
		aux = aux->next;
	}
    //lock the reader mutex to decrement the number of readers
    pthread_mutex_lock(&rd_mutex);
    readers--;
    //when the last reader leaves, let the writer in.
    if (readers == 0){
        sem_post(&wrt);
    }
    pthread_mutex_unlock(&rd_mutex);
    //if the key doesn't exist, return -1
	return -1;
}

// En este se le pasan  valores a cuales queremos modificar
int modify_value(int key, char* value1, int value2, double value3){
    //writer
    sem_wait(&wrt);
    struct Node *aux = list->head;
	while (aux != NULL){
		if (aux->key == key){
			strcpy(aux->value1, value1);
            aux->value2 = value2;
            aux->value3 = value3;
            sem_post(&wrt);
			return 0;
		}
		aux = aux->next;
	}
    sem_post(&wrt);
    //if the key doesn't exist, return -1
	return -1;
}


int delete_key(int key){
    //writer
    struct Node *prev = NULL; //auxiliar pointer to the previous node of aux
    sem_wait(&wrt);
    struct Node *aux = list->head; //auxiliar pointer to the head of the list
    while (aux != NULL){
        if (aux->key == key){
            //if the node to delete is the head
            if (prev == NULL){
                list->head = aux->next;
                free(aux);
                list->size -= 1;
                sem_post(&wrt);
                return 0;
            }
            //if the node to delete is the tail
            else if (aux->next == NULL){
                prev->next = NULL;
                list->tail = prev;
                free(aux);
                list->size -= 1;
                sem_post(&wrt);
                return 0;
            }
            //if the node to delete is in the middle
            else{
                prev->next = aux->next;
                free(aux);
                list->size -= 1;
                sem_post(&wrt);
                return 0;
            }
        }
        prev = aux;
        aux = aux->next;
    }
    sem_post(&wrt);
    //if the key doesn't exist, return -1
    return -1;

}

int exist(int key){
    //reader
    pthread_mutex_lock(&rd_mutex);
    readers++;
    //case first reader enters to read, lock the writer.
    if (readers == 1){
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&rd_mutex);

    struct Node *aux = list->head;
    while (aux != NULL){
        if (aux->key == key){
            pthread_mutex_lock(&rd_mutex);
            readers--;
            //when the last reader leaves, let the writer in.
            if (readers == 0){
                sem_post(&wrt);
            }
            pthread_mutex_unlock(&rd_mutex);
            return 1;
        }
        aux = aux->next;
    }
    //if the key doesn't exist, return 0
    pthread_mutex_lock(&rd_mutex);
    readers--;
    //case first reader enters to read, lock the writer.
    if (readers == 0){
        sem_post(&wrt);
    }
    pthread_mutex_unlock(&rd_mutex);
    return 0;

}

int copy_key(int key1, int key2){
//writer but no need to care because all the funtions that it calls are already implementing the writer.
//Create and insert key2 with the values of key1, if key1 doesn't exist, return -1. if key2 exists, modify its values. return 0 on success.
    int existKey1 = exist(key1);
    int existKey2 = exist(key2);
    if (existKey1 == 0){
        sem_post(&wrt);
        return -1;
    }
    else{
        char tmpvalue1[256];
        int tmpvalue2;
        double tmpvalue3;
        get_value(key1, tmpvalue1, &tmpvalue2, &tmpvalue3);
        if (existKey2 == 0){
            set_value(key2, tmpvalue1, tmpvalue2, tmpvalue3);
        }
        else{
            modify_value(key2, tmpvalue1, tmpvalue2, tmpvalue3);
        }
        return 0;
    }
}

void printList(){
    struct Node *aux = list->head;
    if (aux == NULL){
        printf("List is empty\n");
        return;
    }
    while (aux != NULL){
        printf("Key: %d, Value1: %s, Value2: %d, Value3: %f\n", aux->key, aux->value1, aux->value2, aux->value3);
        aux = aux->next;
    }
}   

