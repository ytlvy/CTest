#include <stdio.h>

void ReverseString(char *s, int from, int to) {
    while (from < to) {
        char t = s[from];
        s[from++] = s[to];
        s[to--] = t; 
    }
}

void leftRotateString(char *str, int length, int leftNum) {
    leftNum = length % leftNum;
    
    ReverseString(str, 0, leftNum-1);
    ReverseString(str, leftNum, length-1);
    ReverseString(str, 0, length-1);
}


int main(int argc, char const *argv[]) {
    
    char oriStr[] = "abcdefg";
    leftRotateString(oriStr, 7, 4);
    printf("%s\n", oriStr);
    
    return 0;
}