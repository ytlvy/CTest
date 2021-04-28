#include <stdint.h>
#include <stdio.h>
#include <dlfcn.h>
#include <sanitizer/coverage_interface.h>

#define _HF_PERF_BITMAP_BITSZ_MASK 0x7FFFFFFULL

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

extern "C" void __sanitizer_cov_trace_pc_indir(uintptr_t callee) {
    size_t pos1 = (uintptr_t)__builtin_return_address(0)<<12;
    size_t pos2 = callee & 0xFFF;
    size_t pos = (pos1 | pos2) & _HF_PERF_BITMAP_BITSZ_MASK;
    printf("pos1 pos2 pos: %x %x %x\n", pos1, pos2, pos);
}