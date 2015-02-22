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
    typedef struct { const char *name; u_int reg; u_int bit; } cpufeat_t;
    cpu_t cpu = { "unknown", 0 } ;

    do_cpuid(0, regs);

    if (regs[1] == 0x756e6547 && regs[2] == 0x6c65746e &&
        regs[3] == 0x49656e69) {
        cpu.vendor = "intel";
        cpu.type = INTEL;
    }

    if (regs[1] == 0x68747541 && regs[2] == 0x444d4163 &&
        regs[3] == 0x69746e65) {
        cpu.vendor = "amd";
        cpu.type = AMD;
    }

    if(cpu.type > 0) {
        printf("+%s\n=vendor=%s\n", cpu.vendor, cpu.vendor);
    }

    if(cpu.type != INTEL || cpu.type == 0) {
        return(0);
    }

    cpufeat_t cpu_features[] = {
        { "fpu",          EDX,  0 },
        { "vme",          EDX,  1 },
        { "de",           EDX,  2 },
        { "pse",          EDX,  3 },
        { "tsc",          EDX,  4 },
        { "msr",          EDX,  5 },
        { "pae",          EDX,  6 },
        { "mce",          EDX,  7 },
        { "cx8",          EDX,  8 },
        { "apic",         EDX,  9 },
        { "sep",          EDX, 11 },
        { "mtrr",         EDX, 12 },
        { "pge",          EDX, 13 },
        { "mca",          EDX, 14 },
        { "cmov",         EDX, 15 },
        { "pat",          EDX, 16 },
        { "pse-36",       EDX, 17 },
        { "psn",          EDX, 18 },
        { "clfsh",        EDX, 19 },
        { "ds",           EDX, 21 },
        { "acpi",         EDX, 22 },
        { "mmx",          EDX, 23 },
        { "fxsr",         EDX, 24 },
        { "sse",          EDX, 25 },
        { "sse2",         EDX, 26 },
        { "ss",           EDX, 27 },
        { "htt",          EDX, 28 },
        { "tm",           EDX, 29 },
        { "ia64",         EDX, 30 },
        { "pbe",          EDX, 31 },
        { "sse3",         ECX,  0 },
        { "pclmulqdq",    ECX,  1 },
        { "dtes64",       ECX,  2 },
        { "monitor",      ECX,  3 },
        { "ds-cpl",       ECX,  4 },
        { "vmx",          ECX,  5 },
        { "smx",          ECX,  6 },
        { "est",          ECX,  7 },
        { "tm2",          ECX,  8 },
        { "ssse3",        ECX,  9 },
        { "cnxt-id",      ECX, 10 },
        { "fma",          ECX, 12 },
        { "cx16",         ECX, 13 },
        { "xtpr",         ECX, 14 },
        { "pdcm",         ECX, 15 },
        { "pcid",         ECX, 17 },
        { "dca",          ECX, 18 },
        { "sse41",        ECX, 19 },
        { "sse42",        ECX, 20 },
        { "x2apic",       ECX, 21 },
        { "movbe",        ECX, 22 },
        { "popcnt",       ECX, 23 },
        { "tsc-deadline", ECX, 24 },
        { "aes",          ECX, 25 },
        { "xsave",        ECX, 26 },
        { "osxsave",      ECX, 27 },
        { "avx",          ECX, 28 },
        { "f16c",         ECX, 29 },
        { "rdrnd",        ECX, 30 },
        { "hypervisor",   ECX, 31 },
        {  NULL,          0,    0 }
    };

    do_cpuid(1, regs);

    int comma = 0;
    printf("@features= {");
    for (cpufeat_t *p = cpu_features; p->name != NULL; ++p) {
        if((regs[p->reg] & (1 << p->bit)) != 0) {
            printf("%s'%s'", comma ? ", " : " ", p->name);
        }
        comma = 1;
    }
    printf(" }\n");

    return(0);
}
