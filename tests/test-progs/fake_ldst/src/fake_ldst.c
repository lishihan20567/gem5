#include <stdint.h>
#include <stdio.h>

#define FAKE_LOAD(dst, base, imm) \
    __asm__ volatile (".insn i 0x0b, 3, %0, %1, " #imm "\n" \
                      : "=r"(dst) : "r"(base) : "memory")

#define FAKE_STORE(base, val, imm) \
    __asm__ volatile (".insn s 0x2b, 3, %0, %1, " #imm "\n" \
                      : : "r"(base), "r"(val) : "memory")

int main(void)
{
    uint64_t data[2] = {0, 0};
    uint64_t v0 = 0, v1 = 0, v2 = 0;

    printf("[fake-test] begin\n");

    FAKE_STORE(data, 0x1122334455667788ull, 0);
    FAKE_LOAD(v0, data, 0);
    printf("[fake-test] after first pair: 0x%016llx\n", (unsigned long long)v0);

    FAKE_STORE(data, 0xaabbccddeeff0011ull, 8);
    FAKE_LOAD(v1, data, 8);
    printf("[fake-test] after second pair: 0x%016llx\n", (unsigned long long)v1);

    FAKE_LOAD(v2, data, 0);
    printf("[fake-test] fallback load: 0x%016llx\n", (unsigned long long)v2);

    printf("[fake-test] end\n");
    return (v0 == 0x1122334455667788ull &&
            v1 == 0xaabbccddeeff0011ull &&
            v2 == 0x1122334455667788ull) ? 0 : 1;
}
