//
// Created by AndreiZ0R on 3/3/2022.
//

#ifndef DOUBLYLINKEDXORLIST_H
#define DOUBLYLINKEDXORLIST_H

typedef enum _STATE                                         // values to check if the list is initialised or destroyed
{
    Init, Destroyed
} STATE;


typedef struct _XNODE                                       // structure for internal nodes
{
    int key;
    struct _XNODE* link;
} XNODE;

typedef struct _ListXor                                     // structure for the list itself
{
    XNODE* head;
    XNODE* tail;
    STATE state;
} XLIST;

void InitXList(XLIST* list);                                //initialises the list's pointers, first and last

XNODE* searchList(XLIST list, int searchedKey);             //searches the list for the given key

void insert_first(XLIST* list, int key);                    //inserts a key at the head of the list

void insert_last(XLIST* list, int key);                     //inserts a key at the back of the list

void insert_after_key(XLIST* list, int afterKey, int Value);//inserts a ker after a given key (positional)

void print_xorList_forward(XLIST list);                     //prints the elements from first to last

void print_xorList_backwards(XLIST list);                   //prints the elements from last to first

void delete_first(XLIST* list);                             //deletes the first key of the list

void delete_last(XLIST* list);                              //deletes the last key of the list

void delete_key(XLIST* list, int deleteKey);                //deletes a given key

void clear_list(XLIST* list);                               //deletes all keys, clearing the list

void DestroyXList(XLIST* list);                             //destroys the list and it's content


#endif //DOUBLYLINKEDXORLIST_H
