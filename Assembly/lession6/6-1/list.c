#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/*
The wordlistnode type is a linked list of words and
the number of times each word has occurred.
*/
typedef struct wlist_node {
    char *word;
    int count;
    struct wlist_node *next;
}wordlistnode;

/*
The wordlist type holds a pointer to the linked list
and keeps track of the number of nodes in the list
*/
typedef struct wlist {
    int nwords;
    wordlistnode *head;
}wordlist;

/* wl_alloc allocates and initialize a new word list */
wordlist *wl_alloc() {
    wordlist *tmp;
    tmp = (wordlist *)malloc(sizeof(wordlist));
    if(tmp == NULL) {
        printf("Unable to allocate wordlist\n");
        exit(1);
    }

    tmp->nwords = 0;
    tmp->head = NULL;
    return tmp;
}

/* wl_free fress all storage used by wordlist */
void wl_free(wordlist *wl) {
    wordlistnode *tmpa, *tmpb;
    tmpa = wl->head;
    while (tmpa != NULL) {
        tmpb = tmpa;
        tmpa = tmpa->next;
        free(tmpb->word);
        free(tmpb);
    }
    
    free(wl);
}

/*
wln_lookup is used internally to search the list of
words. It returns a pointer to the wordlistnode. If
the word is not in the list, then it returns a pointer
to the place where the word should be inserted. If
the insertion point is the head of the list, then it
return NULL
*/
wordlistnode *wl_lookup(wordlistnode *lst, char *word) {
    wordlistnode *prev = NULL;
    while(lst != NULL && strcmp(lst->word, word) < 0) {
        prev = lst;
        lst = lst->next;
    }

    if(lst != NULL && strcmp(lst->word, word) == 0) {
        return lst;
    }
    else {
        return prev;
    }
}

/*
wl_increment adds one to the count of the given word.
If the word is not in the list, then it is added with
a count of one
*/
void wl_increment(wordlist *list, char *word) {

    wordlistnode *newword;
    wordlistnode *wlst = wl_lookup(list->head, word);
    //word not exists add a new
    if(wlst == NULL || strcmp(wlst->word, word) != 0) {
        list->nwords++;
        newword = (wordlistnode *)malloc(sizeof(wordlistnode));
        if(newword == NULL) {
            printf("Unable to allocate wordlistnode");
            exit(2);
        }
        newword->word = strdup(word);
        newword->count = 1;

        if(wlst == NULL) { //need to insert in head
            newword->next = list->head;
            list->head = newword;
        }
        else {
            newword->next = wlst->next;
            wlst->next = newword;
        }
    }
    else {
        wlst->count++;
    }
}

/*
wl_print prints a table showing the number 
of occurences for each word, followed by the word.
*/
void wl_print(wordlist *list) {
    wordlistnode *wlist = list->head;
    while (wlist != NULL) {
        printf("%10d %s\n", wlist->count, wlist->word);
        wlist = wlist->next;
    }
    printf("There are %d unique words in the document.\n",
        list->nwords);
}

/*
wl_print_numerical prints a table showing the number
of occurrences for each word, followed by the word,
sorted in reverse order of occurence.
*/
// void wl_print_numerical(wordlist *list) {
//     printf("wl_print_numerical has not implemented");
// }