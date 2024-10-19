nop
r1
start:
    mv r1, 0x10
    mv r2, 20
    add r1, r1, r2
    j add_3

add_3:
    addi r1, 0x3