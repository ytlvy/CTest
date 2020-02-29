#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <list.h>

char *remove_punctuation(char *word) {
    char *newword = (char *)malloc(strlen(word)+1);
    char *curdst = newword;
    char *cursrc = word;

    while( *cursrc != 0 ) {
        if( strchr(",.\"!$();:{}\\[]", *cursrc) == NULL){
            *curdst = tolower(*cursrc);
            curdst++;
        }

        cursrc++;
    }
    *curdst = 0;

    return newword;
}

int main() {

    int MaxWordLength = 1024;
    char *nextword, *cleanword;
    wordlist *list;

    nextword = (char *)malloc(MaxWordLength * sizeof(char));
    list = wl_alloc();

    while(scanf("%s", nextword) == 1) {
        cleanword = remove_punctuation(nextword);
        if(strlen(cleanword)>0) {
            wl_increment(list, cleanword);
        }

        free(cleanword);
    }

    printf("Alphabetical list:\n");
    wl_print(list);

    printf("Alphabetical list:\n");
    wl_print_numerical(list);

    wl_free(list);

    return 0;
}