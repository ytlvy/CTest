#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <list.h>

typedef struct wlist_node {
    char *word;
    int count;
    struct wlist_node *next;
}wordlistnode;

typedef struct wlist {
    int nwords;
    wordlistnode *head;
}wordlist;

wordlist *wl_alloc() {
    wordlist *tmp;

    tmp = (wordlist *)malloc(sizeof(wordlist));
    if(tmp == NULL) {
        printf("Unable to allocate wordlist;\n");
        exit(1);
    }

    tmp->nwords = 0;
    tmp->head = NULL;
    return tmp;
}

void wl_free(wordlist *list) {
    wordlistnode *tmpa, *tmpb;
    tmpa = list->head;

    while(tmpa != NULL) {
        tmpb = tmpa->next;
        free(tmpa->word);
        free(tmpa);
        tmpa = tmpb;
    }

    free(list);
}

wordlistnode *wl_lookup(wordlistnode *listhead, char *word) {
    wordlistnode *prev = NULL;
    wordlistnode *curr = listhead;

    while(curr != NULL && strcmp(curr->word, word) < 0) {
        prev = curr;
        curr = curr->next;
    }

    if(curr != NULL && strcmp(curr->word, word) == 0) {
        return curr;
    }
    return prev;
}

void wl_increment(wordlist *list, char *word) {
    wordlistnode *newword;
    wordlistnode *position = wl_lookup(list->head, word);

    //node exists
    if(position != NULL && strcmp(position->word, word) ==0) {
        position->count++;
        return;
    }

    //node not exist
    //add new word
    list->nwords++;
    newword = (wordlistnode *)malloc(sizeof(wordlistnode));
    if(newword == NULL) {
        printf("Unabale to mallocate wordlistnode in %s", __func__);
        exit(1);
    }
    newword->word = strdup(word);
    newword->count = 1;

    if(position == NULL) {
        newword->next = list->head;
        list->head = newword;
    }
    else {
        newword->next = position->next;
        position->next = newword;
    }
    
}


void wl_print(wordlist *list) {
    wordlistnode *curr = list->head;
    while(curr != NULL) {
        printf("%10d %s\n", curr->count, curr->word);
        curr = curr->next;
    }
    printf("There are %d unique words in the document\n", list->nwords);
}


void wl_print_numerical(wordlist *list) {
    printf("wl_print_numerical has not ben implememented");
}

