// SPDX-License-Identifier: BSD-2-Clause

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR_READ   65536
#define MAX_ARRAY_SIZE  300000

int main(int argc, char **argv) {
    if (argc < 2 || strcmp(argv[1], "--h") == 0) {
        fprintf(stdout, "Brainfuck Interpreter\nAuthor: rilysh\n\nUsage: %s [input]\n", argv[0]);
        exit(0);
    }
    unsigned char ptr[MAX_ARRAY_SIZE]; // temporary buffer of the file in an array
    unsigned char arr[MAX_ARRAY_SIZE]; // temporary buffer, used when instructions are being moved, increment, decrement
    int poi; // array index for ptr
    int idx; // another array index for array
    int stack[MAX_CHAR_READ]; // temporary buffer array
    int stackp = 0; // array index for stack, see: https://i.postimg.cc/zXnFtf87/Screenshot-2022-09-11-12-48-58.png
    int targets[MAX_CHAR_READ]; // another temporary array, used for rewind after "]"

    FILE *fp;
    fp = fopen(argv[1], "r");
    int length;
    length = fread(ptr, 1, MAX_CHAR_READ, fp);
    fclose(fp);

    for (poi = 0; poi < length; poi++) {
        if (ptr[poi] == '[') stack[stackp++] = poi;
        if (ptr[poi] == ']') {
            stackp--; // matched and now decrement the stack pointer for rewind which is inside "[]"
            targets[poi] = stack[stackp]; // temporary save it
            targets[stack[stackp]] = poi; // match it with poi
        }
    }

    for (poi = 0; poi < length; poi++) {
        switch (ptr[poi]) {
            case '>': idx++; break;
            case '<': idx--; break;
            case '+': arr[idx]++; break;
            case '-': arr[idx]--; break;
            case '.': putc_unlocked(arr[idx], stdout); fflush_unlocked(stdout); break;
            case ',': arr[idx] = (unsigned int)getc_unlocked(stdin); break;
            case '[': if (!arr[idx]) poi = targets[poi]; break;
            case ']': if (arr[idx]) poi = targets[poi]; break;
        }
    }
}
