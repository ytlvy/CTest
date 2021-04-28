//clang++ -g -fsanitize-coverage=trace-pc,indirect-calls test.cc -c
//clang++ trace-pc-indir.cc test.o -fsanitize=address 
//
//

void foo() {}

void bar(void(*fn)(void)) {
    fn();
}

int main(int argc, char **argv) {
    if(argc>1) {
        bar(&foo);
    }
    return 0;
}