//clang++ -fsanitize-coverage=trace-pc -fsanitize=address -g trace-pc.cc -o trace
// ./trace
// ./trace foo

#include <stdint.h>
#include <stdio.h>
#import <dlfcn.h>
#include <sanitizer/coverage_interface.h>

extern "C" void __sanitizer_cov_trace_pc() {
    void *pc = __builtin_return_address(0);
    char PcDesr[1024];
    __sanitizer_symbolize_pc(pc, "%p %F %L", PcDesr, sizeof(PcDesr));
    printf("PC %s  ", PcDesr);

    Dl_info info = {0};
    dladdr(pc, &info);
    if (info.dli_sname) {
        printf("function %s\n", info.dli_sname);
    }
    printf("\n");
}

void foo() {}

int main(int argc, char **argv) {
    if(argc>1) {
        foo();
    }
    return 0;
}