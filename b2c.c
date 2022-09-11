// SPDX-License-Identifier: BSD-2-Clause

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY_SIZE  300000

int main(int argc, char **argv) {
    if (argc < 3 || strcmp(argv[1], "--h") == 0) {
        fprintf(stdout, "Brainfuck2C\nAuthor: rilysh\n\nUsage: %s [input] [output]\n", argv[0]);
        exit(0);
    }
    char data[MAX_ARRAY_SIZE]; // temporary buffer of the file in an array
    int size; // size of the input file
    int i = 0; // increment value each time according to the charecters length 
    int length; // charecters length

    int plus = 0; // store the count(s) of the "+" instruction
    int minus = 0; // store the count(s) of the "-" instruction
    int next = 0; // store the count(s) of the ">" instruction
    int prev = 0; // store the count(s) of the "<" instruction

    FILE *ofp; // open file pointer
    FILE *wfp; // write file pointer
    ofp = fopen(argv[1], "r");
    if (ofp == NULL) {
        fprintf(stdout, "error: can't open input file\n");
        exit(1);
    }
    wfp = fopen(argv[2], "w");
    if (wfp == NULL) {
        fprintf(stdout, "error: can't open output file\n");
        exit(1);
    }
    fseek(ofp, 0, SEEK_END);
    size = ftell(ofp);
    rewind(ofp);
    length = fread(data, 1, size, ofp);
    fclose(ofp);

    // now here's the messy part begins, to know about this translation, see the commands section at https://en.wikipedia.org/wiki/Brainfuck
    fprintf(wfp, "#include <stdio.h>\n");
    fprintf(wfp, "int main() {\n");
    fprintf(wfp, "    int size = 30000;\n");
    fprintf(wfp, "    unsigned char tape[size];\n");
    fprintf(wfp, "    int i = 0;\n");
    fprintf(wfp, "    for (i = 0; i < size; i++)\n");
    fprintf(wfp, "         tape[i] = 0;\n");
    fprintf(wfp, "    int ptr = 0;\n\n");

    for (; i < length; i++) {
        switch (data[i]) {
            case '>': 
                next += 1;
                prev != 0 ? (fprintf(wfp, "    ptr -= %d;\n", prev), prev = 0) :
                plus != 0 ? (fprintf(wfp, "    tape[ptr] += %d;\n", plus), plus = 0) :
                minus != 0 ? (fprintf(wfp, "    tape[ptr] -= %d;\n", minus), minus = 0) :
                0;
                break;

            case '<':
                prev += 1;
                next != 0 ? (fprintf(wfp, "    ptr += %d;\n", next), next = 0) :
                plus != 0 ? (fprintf(wfp, "    tape[ptr] += %d;\n", plus), plus = 0) :
                minus != 0 ? (fprintf(wfp, "    tape[ptr] -= %d;\n", minus), minus = 0) :
                0;
                break;

            case '+':
                plus += 1;
                prev != 0 ? (fprintf(wfp, "    ptr -= %d;\n", prev), prev = 0) :
                next != 0 ? (fprintf(wfp, "    ptr += %d;\n", next), next = 0) :
                minus != 0 ? (fprintf(wfp, "    tape[ptr] -= %d;\n", minus), minus = 0) :
                0;
                break;

            case '-':
                minus += 1;
                prev != 0 ? (fprintf(wfp, "    ptr -= %d;\n", prev), prev = 0) :
                next != 0 ? (fprintf(wfp, "    ptr += %d;\n", next), next = 0) :
                plus != 0 ? (fprintf(wfp, "    tape[ptr] += %d;\n", plus), plus = 0) :
                0;
                break;

            case '.':
                prev != 0 ? (fprintf(wfp, "    ptr -= %d;\n", prev), prev = 0) :
                next != 0 ? (fprintf(wfp, "    ptr += %d;\n", next), next = 0) :
                plus != 0 ? (fprintf(wfp, "    tape[ptr] += %d;\n", plus), plus = 0) :
                minus != 0 ? (fprintf(wfp, "    tape[ptr] -= %d;\n", minus), minus = 0) :
                0;
                fprintf(wfp, "    putc_unlocked(tape[ptr], stdout);\n");
                break;

            case ',':
                prev != 0 ? (fprintf(wfp, "    ptr -= %d;\n", prev), prev = 0) :
                next != 0 ? (fprintf(wfp, "    ptr += %d;\n", next), next = 0) :
                plus != 0 ? (fprintf(wfp, "    tape[ptr] += %d;\n", plus), plus = 0) :
                minus != 0 ? (fprintf(wfp, "    tape[ptr] -= %d;\n", minus), minus = 0) :
                0;
                fprintf(wfp, "    tape[ptr] = getc_unlocked(stdin);\n");
                break;

            case '[':
                prev != 0 ? (fprintf(wfp, "    ptr -= %d;\n", prev), prev = 0) :
                next != 0 ? (fprintf(wfp, "    ptr += %d;\n", next), next = 0) :
                plus != 0 ? (fprintf(wfp, "    tape[ptr] += %d;\n", plus), plus = 0) :
                minus != 0 ? (fprintf(wfp, "    tape[ptr] -= %d;\n", minus), minus = 0) :
                0;
                fprintf(wfp, "    while (tape[ptr] != 0)\n");
                fprintf(wfp, "    {\n");
                break;
                
            case ']':
                prev != 0 ? (fprintf(wfp, "    ptr -= %d;\n", prev), prev = 0) :
                next != 0 ? (fprintf(wfp, "    ptr += %d;\n", next), next = 0) :
                plus != 0 ? (fprintf(wfp, "    tape[ptr] += %d;\n", plus), plus = 0) :
                minus != 0 ? (fprintf(wfp, "    tape[ptr] -= %d;\n", minus), minus = 0) :
                0;
                fprintf(wfp, "    ");
                fprintf(wfp, "}\n");
                break;
        }
    }
    fprintf(wfp, "}\n");
    fflush_unlocked(wfp);
    fclose(wfp);
}
