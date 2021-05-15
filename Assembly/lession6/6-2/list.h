#ifndef LIST_H
#define LIST_H

/*
Define an opaque type, name wordlist
*/
typedef struct wlist wordlist;

/* wl_alloc allocates and initializes a new list */
wordlist* wl_alloc();

/* wl_free frees all the storage used by a wordlist*/
void wl_free(wordlist *wl);

/*
wl_increment adds one to the count of the given word.
If the word is not in the list, then it is added with
a count of one
*/
void wl_increment(wordlist *list, char *word);


/*
wl_print prints a table showing the number 
of occurences for each word, followed by the word.
*/
void wl_print(wordlist *list);

/*
wl_print_numerical prints a table showing the number
of occurrences for each word, followed by the word,
sorted in reverse order of occurence.
*/
void wl_print_numerical(wordlist *list);

#endif