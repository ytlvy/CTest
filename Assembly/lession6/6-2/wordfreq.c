#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <list.h>

/*
remove_punctuation copies the input string to a new
string, but omits any punctuation characters
*/
char *remove_punctuation(char *source) {
    char *newword = (char *)malloc(strlen(source) + 1);
    char *curdst = newword;
    char *cursrc = source;

    while (*cursrc != 0) {
        if(strchr(",.\"!$()\\[]", *cursrc) == NULL) {
            *curdst = tolower(*cursrc);
            curdst++;
        }
        cursrc++;
    }

    *curdst = 0;
    return newword;
}

/*
the main function reads whitespace separated words
from stdin, removes punctuation, and generates a word
frequency list.
*/
int main(void) {
    int kMaxWordLength = 1024;
    char *nextword, *cleanword;
    wordlist *list;

    nextword = (char *)malloc(kMaxWordLength*sizeof(char));
    list = wl_alloc();
    while(scanf("%s", nextword) == 1) {                          // EOF end ctr+D
        cleanword = remove_punctuation(nextword);
        if(strlen(cleanword) > 0) {
            wl_increment(list, cleanword);
        }
        free(cleanword);
    }

    printf("Alphabetical List\n");
    wl_print(list);
    printf("\nNumberical List\n");
    wl_print_numerical(list);
    wl_free(list);

    return 0;
}