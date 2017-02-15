/**
 * gcc -shared -fPIC unrandom.c -o unrandom.so
 * LD_PRELOAD=$PWD/unrandom.so ./random_num
 */
int rand(){
    return 42; //the most random number in the universe
}
