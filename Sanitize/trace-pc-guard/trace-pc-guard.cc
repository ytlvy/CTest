#include <stdint.h>
#include <stdio.h>
#include <dlfcn.h>
#include <sanitizer/coverage_interface.h>

extern "C" void __sanitizer_cov_trace_pc_guard_init(uint32_t *start,
                                         uint32_t *stop) {
    static uint32_t N;  // Counter for the guards.
    if (start == stop || *start) return;  // Initialize only once.
    printf("INIT: %p %p\n", start, stop);
    for (uint32_t *x = start; x < stop; x++)
        *x = ++N;  // Guards should start from 1.
}

// This callback is inserted by the compiler on every edge in the
// control flow (some optimizations apply).
// Typically, the compiler will emit the code like this:
//    if(*guard)
//      __sanitizer_cov_trace_pc_guard(guard);
// But for large functions it will emit a simple call:
//    __sanitizer_cov_trace_pc_guard(guard);
extern "C" void __sanitizer_cov_trace_pc_guard(uint32_t *guard) {
    if (!*guard) {
        return;
    }
    // If you set *guard to 0 this code will not be called again for this edge.
    // Now you can get the PC and do whatever you want:
    //   store it somewhere or symbolize it and print right away.
    // The values of `*guard` are as you set them in
    // __sanitizer_cov_trace_pc_guard_init and so you can make them consecutive
    // and use them to dereference an array or a bit vector.
    // *guard = 0;
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