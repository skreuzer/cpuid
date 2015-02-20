#include <stdio.h>
#include <sys/types.h>

#define EAX 0
#define EBX 1
#define ECX 2
#define EDX 3

#define INTEL 1
#define AMD   2

static __inline void
do_cpuid(u_int ax, u_int *p) {
    __asm __volatile("mov %%ebx, %%esi\n\t"
        "cpuid\n\t"
        "xchg %%esi, %%ebx"
        : "=a" (p[0]), // eax
          "=S" (p[1]), // ebx
          "=c" (p[2]), // ecx
          "=d" (p[3])  // edx
        : "a" (ax)
    );
}

int
main(int argc, char *argv[]) {
    u_int regs[4];
    typedef struct { char *vendor; int type; } cpu_t;
    cpu_t cpu = { "unknown", 0 } ;

    do_cpuid(0, regs);

    if (regs[1] == 0x756e6547 && regs[2] == 0x6c65746e && regs[3] == 0x49656e69) {
        cpu.vendor = "intel";
        cpu.type = INTEL;
    }

    if (regs[1] == 0x68747541 && regs[2] == 0x444d4163 && regs[3] == 0x69746e65) {
        cpu.vendor = "amd";
        cpu.type = AMD;
    }

    if(cpu.type > 0) {
        printf("+%s\n=vendor=%s\n", cpu.vendor, cpu.vendor);
    }

    return(0);
}
