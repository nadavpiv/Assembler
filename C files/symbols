#include "structs.h"
#include "constants.h"
#include "main.h"

/* this method build the symbols table. */
void addSymbol (ptr* pointer,data_image* arr, memory_image * brr, int dataCounter,int memoryCounter,int fileCounter)
{
    ptr p,temp;
    int symbolFlag = 0, checkMulti;
    int i = 0;
    p = (ptr) (*pointer);
    while (i < memoryCounter) /* scan the memory image. */
    {
        if(brr[i].symbol == 1) /* if this symbol. */
        {
            if (symbolFlag == 0)
                symbolFlag = 1;
            else
                 checkMulti = checkMultiSymbol1((ptr) (*pointer),brr,i);
            if(checkMulti == ERROR)
                fprintf (stdout,"File number: %d Symbol name: %s <Duplication of symbols>\n",fileCounter,brr[i].symbolName);
            else
            {
                strcpy (p -> type,brr[i].symbolName);
                p -> memory = brr[i].memory_adress;
                strcpy (p -> attribute, "code");
                temp = (ptr) calloc (1,sizeof(symbols_table));
                if (!temp)
                {
                    fprintf (stdout,"allocation memory failed");
                    exit (0);
                }
                p -> next = temp;
                p = p -> next;
            }
        }
        i++;
    }
    i = 0; /* initialize i to the scan of the data image. */
    while (i < dataCounter) /* scan the data image. */
    {
        if(arr[i].symbol == 1) /* if this is symbol. */
        {
            
            int checkMulti = checkMultiSymbol2((ptr) (*pointer),arr,i);
            if(checkMulti == ERROR)
                fprintf (stdout,"File number: %d Symbol name: %s <Duplication of symbols>\n",fileCounter,arr[i].symbolName);
            else
            {
                strcpy (p -> type,arr[i].symbolName);
                p -> memory = arr[i].memory_adress + (DIRECTIVE_LENGTH*memoryCounter) + 100; /* 100 for IC. */
                strcpy (p -> attribute, "data");
                temp = (ptr) calloc (1,sizeof(symbols_table));
                if (!temp)
                {
                    fprintf (stdout,"allocation memory failed");
                    exit (0);
                }
                p -> next = temp;
                p = p -> next;
            }
        }
        else if (arr[i].symbol == EXTERN_SYMBOL)
        {
            strcpy (p -> type,arr[i].symbolName);
            p -> memory = 0;
            strcpy (p -> attribute, "extern");
            temp = (ptr) calloc (1,sizeof(symbols_table));
            if (!temp)
            {
                fprintf (stdout,"allocation memory failed");
                exit (0);
            }
            p -> next = temp;
            p = p -> next;
        }
        i++;
    }
    free (temp);
}

/* this method build the union image of data image and memory image. */
void union_images (struct mix* crr, struct memory* arr, struct data* brr , int memoryC, int dataC)
{
    int i = 0, j = 0;
    while (i < memoryC)
    {
        crr[i].symbol = arr[i].symbol;
        crr[i].memory_adress = arr[i].memory_adress;
        strcpy(crr[i].symbolName,arr[i].symbolName);
        strcpy(crr[i].operands,arr[i].operands);
        crr[i].binary = arr[i].binary;
        i++;
    }
    while (j < dataC)
    {
        if (brr[j].symbol == 0 || brr[j].symbol == 1)
        {
            crr[i].symbol = brr[j].symbol;
            crr[i].memory_adress = brr[j].memory_adress + (DIRECTIVE_LENGTH*memoryC) + 100;
            strcpy(crr[i].symbolName,brr[j].symbolName);
            strcpy(crr[i].operands,brr[j].operands);
            crr[i].binary = brr[j].binary;
            crr[i].dataSymbol = brr[j].dataSymbol;
        }
        else /* if this is entry or extern guidance. */
        {
            crr[i].symbol = brr[j].symbol;
            crr[i].memory_adress = brr[j].memory_adress;
            strcpy(crr[i].symbolName,brr[j].symbolName);
            strcpy(crr[i].operands,brr[j].operands);
        }
        i++;
        j++;
    }
}

/* this method checks if the symbol that transfered to her exits in the symbols table. */
int searchSymbol (ptr p,char arr[])
{
    while (p)
    {
        if (strcmp(p ->type, arr) == 0)
            return p ->memory;
        p = p -> next;
    }
    return 0;
}

/* this method change the attribute of the symbol to "entry". */
void changeSymbol (ptr p,char arr[])
{
    while (p)
    {
        if (strcmp(p ->type, arr) == 0)
            strcpy (p -> attribute,"entry");
        p = p -> next;
    }
}

int checkMultiSymbol1 (ptr p,memory_image* brr,int index)
{
    while (p)
    {
        if(strcmp(p -> type,brr[index].symbolName) == 0)
            return ERROR;
        p = p -> next;
    }
    return OK;
}

int checkMultiSymbol2 (ptr p,data_image* arr,int index)
{
    while (p)
    {
        if(strcmp(p -> type,arr[index].symbolName) == 0)
            return ERROR;
        p = p -> next;
    }
    return OK;

}
