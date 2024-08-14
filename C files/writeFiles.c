#include "structs.h"
#include "encoder.h"
#include "constants.h"
#include "main.h"
#include "write.h"

/* this method write to .ob file the memory image. */
void writeMemoryFile (struct mix* arr,ptr* p,int dataCounter,int memoryCounter,char fileName[])
{
    FILE *f;
    int arrIndex = 0, numbersIndex = 0, i = 0;
    int count = 0, checkbit = 0, countMemory = 0;
    int adress = 100; /* starting point of the memory. */
    /* open file with end of ".ob" for writing the .ob file. */
    char file [MAX_FILE_LENGTH];
    int fileLength;
    strcpy (file,fileName);
    fileLength = strlen (file);
    file[fileLength-2] = 'o';
    file[fileLength-1] = 'b';
    f = fopen (file,"w+"); /* open file for writing. */
    fprintf (f,"\t%d %d\n", memoryCounter,dataCounter);

    while (i < memoryCounter) /* scan the memory image in the union image. */
    {
        checkbit = 0;
        numbersIndex = 0;
        if (arr[arrIndex].binary != 0 || arr[arrIndex].symbol == 0 || arr[arrIndex].symbol == 1)
        {
            long numbers [NUM_PRINT_IN_A_ROW]; /* every directive take 32 bits, we print them 8,8. */
            while (numbersIndex < DIRECTIVE_LENGTH) 
                numbers[numbersIndex++] = 0;
            numbersIndex = 0;
            fprintf (f,"%04d  ", adress); /* every line start with the adress of the memory. */
            while (checkbit < DIRECTIVE_BTIS)
            {
                if (testbit(arr[arrIndex].binary,checkbit) == 1)
                    setbit (&(numbers[numbersIndex]),count);
                checkbit++;
                count++;
                if (checkbit % 8 == 0) /* take every iteration 8 bits from the number and write to the file. */
                {
                    fprintf (f,"%02X ", (int)numbers[numbersIndex]);
                    count = 0;
                    numbersIndex++;
                    adress++;
                    countMemory++;
                }
            }
        }
        i++;
        fprintf (f,"\n"); /* after every 4 numbers (32 bits) we have to downline. */
        arrIndex++;
    }      
    writeDataFile (arr,p,dataCounter,memoryCounter,i,adress,countMemory,fileName,f);
}

/* this method write to ".ob" file the data image from the union images. */
/* the variable i is the index we are in it from the write memory method. */
void writeDataFile (struct mix* arr,ptr* p,int dataCounter,int memoryCounter,int i,int adress,int countMemory, char fileName[],FILE* f)
{
    int sum = dataCounter + memoryCounter;
    int countData = 0;
    fprintf (f,"%04d  ", adress);
    /* arr[i].memory_adress = 0 means that we are on statments line of extern and entry and we skip on the lines. */
    while (arr[i].memory_adress == 0)
        i++;
    while (i < sum)
    {
        /* every char or number have 8 bits. */
        if (arr[i].dataSymbol == ASCIZ || arr[i].dataSymbol == DB)
        {
            int counter = 0;
            long number = 0;
            while (counter < DB_BITS)
            {
                if (testbit(arr[i].binary,counter) == 1)
                        setbit (&number,counter);
                counter++;
                if (counter == DB_BITS) /* when we finish to build the number we write him on the file. */
                {
                    fprintf (f,"%02X ",(int)number);
                    adress++;
                    countData++;
                    if (adress % LINE_BREAK == 0) /* each double of adress we have to downline and print the memory adress. */
                    {
                        fprintf (f,"\n");
                        fprintf (f,"%04d  ", adress); 
                    }
                }
            }
        }
        /* every number have 16 bits. */
        else if (arr[i].dataSymbol == DH)
        {
            int counter = 0,checkBits = 0;
            long number = 0;
            while (checkBits <= DH_BITS)
            {
                if (testbit(arr[i].binary,checkBits) == 1)
                        setbit (&number,counter);
                counter++;
                checkBits++;
                if (counter == 8) /* take every iteration 8 bits from the number and write to the file. */
                {
                    fprintf (f,"%02X ",(int)number);;
                    adress++;
                    countData++;
                if (adress % LINE_BREAK == 0) /* each double of adress we have to downline and print the memory adress. */
                {
                    fprintf (f,"\n");
                    fprintf (f,"%04d  ",adress); 
                }
                    counter = 0;
                    number = 0;
                }
            }
        }
        /* every number have 32 bits. */
        else if (arr[i].dataSymbol == DW)
        {
            int counter = 0,checkBits = 0;
            long number = 0;
            while (checkBits < DW_BITS)
            {
                if (testbit(arr[i].binary,checkBits) == 1)
                        setbit (&number,counter);
                counter++;
                checkBits++;
                if (counter == 8)
                {
                    fprintf (f,"%02X ",(int)number);
                    adress++;
                    countData++;
                if (adress % LINE_BREAK == 0)
                {
                    fprintf (f,"\n");
                    fprintf (f,"%04d  ",adress); 
                }
                    counter = 0;
                    number = 0;
                }
            }
        }
        i++;
    }
    fprintf (f,"\n");
    rewind (f);
    /* write at the top of the file the number of memory cells and data cells. */
    fprintf (f,"\t%d %d\n",countMemory,countData);
}

/* this method write the entry file. */
void writeEntryFile (struct mix* arr,ptr p,char fileName[])
{
    FILE *f;
    /* open file with end of ".ent" for writing the .ent file. */
    char file [MAX_FILE_LENGTH];
    int fileLength;
    strcpy (file,fileName);
    fileLength = strlen (file);
    file[fileLength-2] = 'e';
    file[fileLength-1] = 'n';
    strcat (file,"t");
    f = fopen (file,"w+"); /* open file for writing. */
    while (p)
    {
        if (strcmp(p ->attribute, "entry") == 0) /* check every symbol in the symbols table if this is entry symbol. */
        {
            fprintf (f,"%s ", p ->type);
            fprintf (f,"%04d\n",p ->memory);
        }
        p = p -> next;
    }
}

/* this method write the extern file. */
void writeExternFile (struct mix* arr, ptr p, int dataCounter, int memoryCounter,char fileName[])
{
    FILE *f;
    /* open file with end of ".ext" for writing the .ext file. */
    char file [MAX_FILE_LENGTH];
    int fileLength, i, sum = dataCounter + memoryCounter;
    strcpy (file,fileName);
    fileLength = strlen (file);
    file[fileLength-2] = 'e';
    file[fileLength-1] = 'x';
    strcat (file,"t");
    f = fopen (file,"w+"); /* open file for writing. */
    while (p)
    {
        i = 0;
        if (strcmp(p ->attribute, "extern") == 0) /* check every symbol in the symbols table if this is entry symbol. */
        {
            while (i < sum)
            {
                /* check in the union images table which adresses use this extern symbol. */
                if (strstr(arr[i].operands,p -> type) && arr[i].memory_adress != 0)
                {
                    fprintf (f,"%s ", p ->type);
                    fprintf (f,"%04d\n",arr[i].memory_adress);
                }
                i++;
            }
        }
        p = p -> next;
    }
}
