#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_DIRECTIVE_LEN 81
#define DIRECTIVE_NUMBER 28
#define MAX_LENGTH_DIRECTIVE 6
#define GUIDENCE_NUMBER 6
#define MAX_GUIDENCE_LENGTH 8

/* for the parsing. */
enum status {start, directive_op, guidance_op, white, stopRow};

typedef struct directive_system
{
    char directives[DIRECTIVE_NUMBER][MAX_LENGTH_DIRECTIVE];
    int kind [DIRECTIVE_NUMBER];
    int op[DIRECTIVE_NUMBER];
    int func[DIRECTIVE_NUMBER];
}directives;

typedef struct guidence_system
{
    char guidence[GUIDENCE_NUMBER][MAX_GUIDENCE_LENGTH];
    int kind[GUIDENCE_NUMBER];
}guidences;

/* symbols table. */
typedef struct node1 * ptr;
typedef struct node1
{
    char type [MAX_DIRECTIVE_LEN];
    int memory;
    char attribute [MAX_DIRECTIVE_LEN];
    ptr next;
}symbols_table;

/* data image. */
typedef struct data
{
    int symbol;
    int dataSymbol;
    int memory_adress;
    char symbolName [MAX_DIRECTIVE_LEN];
    char operands [MAX_DIRECTIVE_LEN];
    long binary;
}data_image;

/* memory image. */
typedef struct memory
{
    int symbol;
    int memory_adress;
    char symbolName [MAX_DIRECTIVE_LEN];
    char operands [MAX_DIRECTIVE_LEN];
    long binary;
}memory_image;

/* union image. */
typedef struct mix
{
    int symbol;
    int dataSymbol;
    int memory_adress;
    char symbolName [MAX_DIRECTIVE_LEN];
    char operands [MAX_DIRECTIVE_LEN];
    long binary;
}mix_images;

#endif
