#ifndef LIST_H
#define LIST_H

typedef struct wlist wordlist;

wordlist* wl_alloc();

void wl_free(wordlist *wl);

void wl_increment(wordlist *list, char *word);

void wl_print(wordlist *list);

void wl_print_numerical(wordlist *list);

#endif