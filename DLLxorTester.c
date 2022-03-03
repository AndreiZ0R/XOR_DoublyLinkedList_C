#include <stdio.h>
#include "DoublyLinkedXORList.h"

//Tester for the implemented functions

void run_tests()
{
    XLIST list;
    InitXList(&list);
    insert_first(&list, 2);
    insert_first(&list, 1);
    insert_first(&list, 3);
    insert_first(&list, 5);

    print_xorList_forward(list);
    print_xorList_backwards(list);

    delete_first(&list);
    delete_last(&list);

    print_xorList_forward(list);
    print_xorList_backwards(list);

    insert_last(&list, 4);
    insert_last(&list, 10);
    insert_last(&list, 15);
    insert_first(&list, 99);

    print_xorList_forward(list);
    print_xorList_backwards(list);

    /* search key test */
    int toSearch = 4;
    XNODE* finder = searchList(list, toSearch);
    if (NULL != finder)
    {
        printf("[SEARCH] Key %d found!\n", toSearch);
    }
    else
        printf("[SEARCH] Key %d not found!\n", toSearch);

    toSearch = 100;
    finder = searchList(list, toSearch);
    if (NULL != finder)
    {
        printf("[SEARCH] Key %d found!\n", toSearch);
    }
    else
        printf("[SEARCH] Key %d not found!\n", toSearch);

    /* delete key test */
    delete_key(&list, 1);
    delete_key(&list, 4);
    print_xorList_forward(list);
    print_xorList_backwards(list);

    /* insert after key test */
    insert_after_key(&list, 15, 777);
    insert_after_key(&list, 10, 888);
    insert_after_key(&list, 99, -15);
    print_xorList_forward(list);
    print_xorList_backwards(list);

    /* list clear test */
    clear_list(&list);
    print_xorList_forward(list);
    print_xorList_backwards(list);
    clear_list(&list);
    searchList(list, 25);

    /* reset test */
    insert_first(&list, 25);
    insert_first(&list, 30);
    print_xorList_forward(list);
    print_xorList_backwards(list);

    DestroyXList(&list);
    DestroyXList(&list);
    insert_first(&list, 2);
    print_xorList_forward(list);
}

int main()
{
    run_tests();


    //INFO: Always use the InitXList function before using the list.
    /*  Usage: 
            XLIST my_list;
            InitXList(&my_list);
            ...
            ...
            DestroyXList(&my_list);
    */
            return 0;
}
