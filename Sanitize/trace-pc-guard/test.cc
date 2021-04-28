//clang++ -g -fsanitize-coverage=trace-pc-guard test.cc -c
//clang++ trace-pc-guard.cc test.o -fsanitize=address
//
//
void foo() {}

int main(int argc, char **argv) {
    if(argc>1) {
        foo();
    }
    return 0;
}