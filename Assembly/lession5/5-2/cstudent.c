/*
clang -S -arch arm64 cstudent.c
*/
#include <string.h>

struct student {
    char first_name[30];
    char last_name[30];
    unsigned char class;
    int grade;
};

int main(void) {

    struct student nstudent;
    strcpy(nstudent.first_name, "Sam");
    strcpy(nstudent.last_name, "Smith");
    nstudent.class = 2;
    nstudent.grade = 88;

    return 0;
}