//Created by AndreiZ0R on 3/3/2022
#include <stdio.h>
#include <stdlib.h>
#include "DoublyLinkedXORList.h"

/* start of help functions */

static XNODE* Bitwise_XOR(XNODE* a, XNODE* b)
{
    return (XNODE*)((uintptr_t)(a) ^ (uintptr_t)(b));
}// bitwise XOR of two nodes

static XNODE* Linker(XNODE* x)
{
    return Bitwise_XOR(x->link, NULL);
}// function to link first/last element of the list in insertion

static XNODE* giveXNODE(int Value)
{
    XNODE* newNode = (XNODE*)malloc(sizeof(XNODE));
    if (NULL == newNode)
    {
        printf("[NODE_CREATOR] Malloc failed\n");
        free(newNode);
        return NULL;
    }
    newNode->key = Value;
    newNode->link = NULL;

    return newNode;
}// function to create and return a node with the given value

static int getPos(XLIST list, int searchedKey)
{
    int pos = 0;
    XNODE* left = list.head;

    XNODE* nextLEFT = NULL;
    XNODE* prevLEFT = NULL;

    while (left != NULL)
    {
        if (left->key == searchedKey)
            return pos;

        //moving left ->>>
        nextLEFT = Bitwise_XOR(prevLEFT, left->link);
        prevLEFT = left;
        left = nextLEFT;

        pos++;
    }
    return -1;
} // function to give the position of the given key in the list

/* end of help functions */


void InitXList(XLIST* list)
{
    if (list->state == Init)
    {
        printf("[INIT] List already initialised!\n");
    }
    else
    {
        list->head = NULL;
        list->tail = NULL;
        list->state = Init;
        printf("[INIT] List initialised!\n");
    }
}

XNODE* searchList(XLIST list, int searchedKey)
{
    if (NULL == list.head || NULL == list.tail)
    {
        printf("[SEARCH] List is empty!\n");
        return NULL;
    }

    XNODE* left = list.head;
    XNODE* right = list.tail;

    XNODE* nextLEFT = NULL;
    XNODE* prevLEFT = NULL;

    XNODE* nextRIGHT = NULL;
    XNODE* prevRIGHT = NULL;

    if (NULL != left && NULL != right)
    {
        while (NULL != left || NULL != right)
        {
            if (left->key == searchedKey)
                return left;
            if (right->key == searchedKey)
                return right;

            if (NULL != left)
            {
                //moving left ->>>
                nextLEFT = Bitwise_XOR(prevLEFT, left->link);
                prevLEFT = left;
                left = nextLEFT;
            }

            if (NULL != right)
            {
                //<<<- right moving
                prevRIGHT = Bitwise_XOR(nextRIGHT, right->link);
                nextRIGHT = right;
                right = prevRIGHT;
            }
        }
    }
    return NULL;
}

void insert_first(XLIST* list, int key)
{
    if (list->state == Destroyed)
    {
        printf("[INSERT] List uninitialised! Couldn't add key %d.\n", key);
    }
    else
    {
        XNODE* newNode = giveXNODE(key);
        newNode->link = Bitwise_XOR(list->head, NULL);

        if (NULL == list->head)
        {
            newNode->link = NULL;
            list->head = newNode;
            list->tail = newNode;
        }
        else
        {
            newNode->link = Bitwise_XOR(NULL, list->head);
            list->head->link = Bitwise_XOR(newNode, Linker(list->head));
            list->head = newNode;
        }
    }

}

void insert_last(XLIST* list, int key)
{
    if (list->state == Destroyed)
    {
        printf("[INSERT] List uninitialised! Couldn't add key %d.\n", key);
    }
    else
    {
        XNODE* newNode = giveXNODE(key);
        if (NULL == list->head || NULL == list->tail)
        {
            insert_first(list, key);
        }
        else
        {
            newNode->link = Bitwise_XOR(list->tail, NULL);
            list->tail->link = Bitwise_XOR(newNode, Linker((list->tail)));
            list->tail = newNode;
        }
    }

}

void insert_after_key(XLIST* list, int afterKey, int Value)
{
    if (list->state == Destroyed)
    {
        printf("[INSERT_AFTER] List uninitialised! Couldn't add key %d.\n", Value);
    }
    else if (NULL == list->head || NULL == list->tail)
    {
        printf("[INSERT_AFTER] Empty list!\n");
    }
    else
    {
        int position = getPos(*list, afterKey);
        int backPos = getPos(*list, list->tail->key);

        if (position < 0 || position > backPos)
        {
            printf("[INSERT_AFTER] Couldn't add after key %d!\n", afterKey);
        }
        else if (position == backPos)
        {
            insert_last(list, Value);
        }
        else if (list->head == NULL)
        {
            printf("[INSERT_AFTER] List empty, cannot insert after a key!\n");
        }
        else
        {
            int pos = 0;
            XNODE* itr = list->head;
            XNODE* prev = NULL;
            XNODE* next = Bitwise_XOR(prev, itr->link);
            while (next != NULL && pos < position)
            {
                prev = itr;
                itr = next;
                next = Bitwise_XOR(prev, itr->link);
                pos++;
            }
            if (pos == position)
            {
                XNODE* newNode = giveXNODE(Value);
                XNODE* aux = Bitwise_XOR(itr->link, next);
                itr->link = Bitwise_XOR(aux, newNode);
                if (next != NULL)
                {
                    next->link = Bitwise_XOR(newNode, Bitwise_XOR(next->link, itr));
                }
                newNode->link = Bitwise_XOR(itr, next);
                newNode->key = Value;
            }
        }
    }

}

void print_xorList_forward(XLIST list)
{
    if (list.state == Destroyed)
    {
        printf("[FORWARD_PRINT] List uninitialised!\n");
    }
    else
    {
        // itr = itr->next traversal
        XNODE* itr = list.head;
        XNODE* prev = NULL;
        XNODE* next = NULL;

        printf("[FORWARD_PRINT] ");
        if (NULL != list.head)
        {
            while (itr != NULL)
            {
                printf("%d -> ", itr->key);
                next = Bitwise_XOR(prev, itr->link);
                prev = itr;
                itr = next;
            }
            printf("NULL\n");
        }
        else
            printf("Empty list!\n");
    }
}

void print_xorList_backwards(XLIST list)
{
    if (list.state == Destroyed)
    {
        printf("[BACKWARDS_PRINT] List uninitialised!\n");
    }
    else
    {
        //itr = itr->prev traversal
        XNODE* itr = list.tail;
        XNODE* next = NULL;
        XNODE* prev = NULL;

        printf("[BACKWARDS_PRINT] ");
        if (NULL != list.tail)
        {
            while (itr != NULL)
            {
                printf("%d -> ", itr->key);
                prev = Bitwise_XOR(next, itr->link);
                next = itr;
                itr = prev;
            }
            printf("NULL\n");
        }
        else
            printf("Empty list!\n");
    }

}

void delete_first(XLIST* list)
{
    if (list->state == Destroyed)
    {
        printf("[DELETE] List uninitialised!\n");
    }
    else if (NULL == list->head)
    {
        printf("[DELETE_FIRST] Empty list!\n");
    }
    else
    {
        XNODE* del = list->head;
        XNODE* next = Bitwise_XOR(NULL, del->link);
        if (NULL == next)
        {
            list->tail = NULL;
        }
        else
        {
            next->link = Bitwise_XOR(del, Linker(next));
        }
        list->head = next;
        free(del);
        del = NULL;
    }
}

void delete_last(XLIST* list)
{
    if (list->state == Destroyed)
    {
        printf("[DELETE] List uninitialised!\n");
    }
    else if (NULL == list->head || NULL == list->tail)
    {
        printf("[DELETE_LAST] Empty list!\n");
    }
    XNODE* del = list->tail;
    XNODE* prev = Bitwise_XOR(del->link, NULL);
    if (NULL == prev)
    {
        list->head = NULL;
    }
    else
    {
        prev->link = Bitwise_XOR(del, Linker(prev));
    }
    list->tail = prev;
    free(del);
    del = NULL;
}

void delete_key(XLIST* list, int deleteKey)
{
    if (list->state == Destroyed)
    {
        printf("[DELETE] List uninitialised! Couldn't delete key %d.\n", deleteKey);
    }
    else
    {
        XNODE* finder = searchList(*list, deleteKey);
        if (NULL == finder)
        {
            printf("[DELETE_KEY] Key %d not found!\n", deleteKey);
            free(finder);
        }
        else if (finder == list->head)
        {
            delete_first(list);
        }
        else if (finder == list->tail)
        {
            delete_last(list);
        }
        else
        {
            XNODE* itr = list->head;
            XNODE* prev = NULL;
            XNODE* next = NULL;
            XNODE* last = NULL;

            int flag = 1;
            while (itr != NULL && itr->key != deleteKey)
            {
                next = Bitwise_XOR(prev, itr->link);
                prev = itr;
                if (flag == 1)
                    last = itr;
                itr = next;
                flag = -flag;
            }
            next = Bitwise_XOR(prev, itr->link);
            XNODE* auxPrev = itr;
            XNODE* auxItr = next;
            XNODE* auxNext = Bitwise_XOR(auxPrev, auxItr->link);

            prev->link = Bitwise_XOR(last, next);        // prev -> next = prev->next->next
            next->link = Bitwise_XOR(prev, auxNext);     // next -> prev = next->prev->prev;
        }
    }
}

void clear_list(XLIST* list)
{
    if (list->state == Destroyed)
    {
        printf("[CLEAR] List uninitialised!\n");
    }
    else if (NULL == list->head || NULL == list->tail)
    {
        printf("[CLEAR] List already cleared! \n");
    }
    else
    {
        int backPos = getPos(*list, list->tail->key);
        for (int i = 0; i <= backPos; i++)
        {
            delete_first(list);
        }
    }
}

void DestroyXList(XLIST* list)
{
    if (NULL == list->head || NULL == list->tail)
    {
        printf("[DESTROY] List already destroyed!\n");
    }
    else
    {
        clear_list(list);
        free(list->head);
        free(list->tail);
        list->head = NULL;
        list->tail = NULL;
        list->state = Destroyed;
        list = NULL;
        printf("[DESTROY] List destroyed successfully!\n");
    }
}