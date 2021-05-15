#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define MAX(x,y) (x<y?y:x)

/*
The wordlistnode type is a linked list of words and
the number of times each word has occurred.
*/
typedef struct wlist_node {
    char *word;
    int count;
    struct wlist_node *left, *right;
    int height;
}wordlistnode;

/**
 * @description: allocates and initilizes a wordlistnode
 * @param {char} *word
 * @return {wordlistnode *}
 * @author: Y.t
 */
wordlistnode *wln_alloc(char *word) {
    wordlistnode *newword;
    newword = (wordlistnode *)malloc(sizeof(wordlistnode));
    if(newword == NULL) {
        printf("Unable to allocate wordlistnode\n");
        exit(1);
    }

    newword->word = strdup(word);
    newword->count = 1;
    newword->left = NULL;
    newword->right = NULL;
    newword->height = 1;
    return newword;
}

/**
 * @description: frees the storage of a wordlistnode
 * @param {wordlistnode} *node
 * @return {*}
 * @author: Y.t
 */
void wln_free(wordlistnode *node) {
    if(node == NULL) {
        return;
    }

    free(node->word);
    wln_free(node->left);
    wln_free(node->right);
    free(node);
}

/**
 * @description: used to search the tree of words. It 
 *  returns a pointer to the wordlistnode. If the word is
 *  not in the list, then it return NULL
 * @param {wordlistnode} *root
 * @param {char} *word
 * @return {*}
 * @author: Y.t
 */
wordlistnode *wln_lookup(wordlistnode *root, char *word) {
    int cmp;
    if(root != NULL) {
        cmp = strcmp(word, root->word);
        if(cmp < 0) {
            root = wln_lookup(root->left, word);
        }
        else if(cmp > 0) {
            root = wln_lookup(root->right, word);
        }
    }
    return root;
}

/**
 * @description: finds the height of a node and returns
 * zero if the pointer is NULL
 * @param {wordlistnode} *node
 * @return {*}
 * @author: Y.t
 */
int wln_height(wordlistnode *node) {

    return node != NULL ?  node->height : 0;
}

/**
 * @description: 
 * @param {wordlistnode} *node
 * @return {*}
 * @author: Y.t
 */
int wln_balance(wordlistnode *node) {
    return node != NULL ? wln_height(node->left) - 
        wln_height(node->right) : 0;
}


/**
 * @description: 
 * @param {*}
 * @return {*}
 * @author: Y.t
 */
void wln_update_height(wordlistnode *node) {
    if(node == NULL) {
        return;
    }

    node->height = MAX(wln_height(node->left), wln_height(node->right)) + 1;
}

/**
 * @description: rotates couterclockwise
 * @param {wordlistnode} *rt
 * @return {*}
 * @author: Y.t
 */
wordlistnode *wln_rotate_left(wordlistnode *rt) {
    wordlistnode *nrt = rt->right;
    rt->right = nrt->left;
    nrt->left = rt;
    wln_update_height(rt);
    wln_update_height(nrt);
    return nrt;
}

/**
 * @description: rotates clockwise
 * @param {wordlistnode} *rt
 * @return {*}
 * @author: Y.t
 */
wordlistnode *wln_rotate_right(wordlistnode *rt) {
    wordlistnode *nrt = rt->left;
    rt->left = nrt->right;
    nrt->right = rt;
    wln_update_height(rt);
    wln_update_height(nrt);
    return nrt;
}

/**
 * @description: performs a tree insertion and re-balances
 * @param {wordlistnode} *root
 * @param {wordlistnode} *node
 * @return {*}
 * @author: Y.t
 */
wordlistnode *wln_insert(wordlistnode *root, wordlistnode *node) {
    int balance;
    if(root == NULL) {
        return node;
    }

    // recursively search for insertion point, and perform the insertion
    if(strcmp(node->word, root->word) < 0) {
        root->left = wln_insert(root->left, node);
    }
    else {
        root->right = wln_insert(root->right, node);
    }

    // as we return from the recursive calls, recalculate the heights
    // and perform rotations as necessary to re-balance the tree
    wln_update_height(root);

    //caculate the balance factor
    balance = wln_balance(root);
    if(balance > 1) {
        //the tree is deeper on the left than on the right
        //通过node的word判定 node是插在 左下的 那个子树下方
        if(strcmp(node->word, root->left->word) <= 0) {
            root = wln_rotate_right(root);
        }
        else {
            root->left = wln_rotate_left(root->left);
            root = wln_rotate_right(root);
        }
    }
    else if(balance < -1) {
        //the tree is deeper on the right than on the left
        if(strcmp(node->word, root->right->word) >= 0) {
            root = wln_rotate_left(root);
        }
        else {
            root->right = wln_rotate_right(root->right);
            root = wln_rotate_left(root);
        }
    }

    return root;
}

/**********************************************************************/

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
    wln_free(wl->head);
    free(wl);
}


/*
wl_increment adds one to the count of the given word.
If the word is not in the list, then it is added with
a count of one
*/
void wl_increment(wordlist *list, char *word) {

    wordlistnode *newword;
    wordlistnode *wlst = wln_lookup(list->head, word);
    //word not exists add a new
    if(wlst == NULL || strcmp(wlst->word, word) != 0) {
        list->nwords++;
        newword = wln_alloc(word);
        list->head = wln_insert(list->head, newword);
    }
    else {
        wlst->count++;
    }
}


/**
 * @description: wln_print is an internal function to print a table 
 * showing the number of occurences for each word, followed 
 * by the word.
 * @param {wordlistnode} *list
 * @return {*}
 * @author: Y.t
 */
void wln_print(wordlistnode *list) {
    if(list != NULL) {
        wln_print(list->left);
        printf("%10d, '%s' \n", list->count, list->word);
        wln_print(list->right);
    }
}

/**
 * @description: wln_print prints a table showing the number 
 * of occurences for each word, followed by the word.
 * @param {wordlist} *list
 * @return {*}
 * @author: Y.t
 */
void wl_print(wordlist *list) {
    wln_print(list->head);
    printf("There are %d unique words in the document.\n",
        list->nwords);
}
#define USE_ASM
#ifndef USE_ASM
/*
wl_print_numerical prints a table showing the number
of occurrences for each word, followed by the word,
sorted in reverse order of occurence.
*/
void wl_print_numerical(wordlist *list) {
    printf("wl_print_numerical has not implemented");
}
#endif