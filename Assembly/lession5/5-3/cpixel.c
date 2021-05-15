/*
clang -S -arch arm64 cpixel.c
*/

#include <stdio.h>
#include <stdlib.h>

/* image size */
const int kImageWidth = 100;
const int kImageHeight = 100;

/* define structure for a pixel */
struct pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

int main (void) {

    struct pixel *image = malloc(kImageWidth * kImageHeight * sizeof(struct pixel));
    if( image == NULL ) {
        fprintf(stderr, "Error: out of memory. \n");
        return 1;
    }

    for (int j = 0; j < kImageHeight; j++) {
        for (int i = 0; i < kImageWidth; i++) {
            image[j*kImageHeight + i].red = 0;
            image[j*kImageHeight + i].green = 0;
            image[j*kImageHeight + i].blue = 0;
        }
    }
    
    free(image);
    return 0;
}
