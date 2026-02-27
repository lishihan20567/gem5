    .section .text
    .globl _start
_start:
    la t0, data_area

    li t1, 0x1122334455667788
    .word 0x0062b02b  # fake_store t1, 0(t0)
    .word 0x0002b38b  # fake_load  t2, 0(t0)

    li t3, 0x1122334455667788
    bne t2, t3, fail

    li t1, 0xaabbccddeeff0011
    .word 0x0062b42b  # fake_store t1, 8(t0)
    .word 0x0082b38b  # fake_load  t2, 8(t0)

    li t3, 0xaabbccddeeff0011
    bne t2, t3, fail

    .word 0x0002b38b  # fake_load t2, 0(t0)
    li t3, 0x1122334455667788
    bne t2, t3, fail

    la a1, msg_ok
    li a2, 17
    jal ra, write_stdout
    li a0, 0
    jal ra, exit_now

fail:
    la a1, msg_fail
    li a2, 17
    jal ra, write_stdout
    li a0, 1
    jal ra, exit_now

write_stdout:
    li a0, 1
    li a7, 64
    ecall
    ret

exit_now:
    li a7, 93
    ecall
    j .

    .section .rodata
msg_ok:
    .ascii "[fake-test] pass\n"
msg_fail:
    .ascii "[fake-test] fail\n"

    .section .bss
    .align 3
data_area:
    .space 16
