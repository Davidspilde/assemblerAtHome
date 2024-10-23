# cursed bubble sort of an array with 5 elements

li r0, 5 # array size
li r7, 0x1000 # array address

# All this creates an empty array :O
# commonly known as:
# 
li r1, 0 # start index
li r2, 0 # value to fill
intialize_array:
    # load zero into array in ram
    add r5, r1, r1 # index * 2 (word size)
    add r4, r7, r5 # address of array element
    st r4, r2 # store 0 at address in array

    # for loop logic
    addi r1, r1, 1 # increment index
    sub r3, r0, r1
    jnz r3, intialize_array

# Fill the array with 5 random values
fill_array:
    li r1, 3 # 
    stio r7, 0, r1 # store 3 at address 0
    li r1, 5 #
    stio r7, 2, r1 # store 5 at address 1
    li r1, 1 #
    stio r7, 4, r1 # store 1 at address 2
    li r1, 4 #
    stio r7, 6, r1 # store 4 at address 3
    li r1, 10 #
    stio r7, 8, r1 # store 10 at address 4

# r7 is the address of the array
# r0 is the size of the array

start:
    li r1, 0x10
    li r2, 20

    add r1, r1, r2
    jimm add_3

add_3:
    addi r1, r1, 0x3