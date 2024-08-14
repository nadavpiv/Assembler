#include "structs.h"
#include "encoder.h"
#include "constants.h"
#include "main.h"

/* this method encoded the adress bits in J directives. (if the adress is symbol). */
void jCoding (ptr p,char arr[], long* binary)
{
    char *symbol;
    int firstWordFlagEnd = 0;
    int  i = 0,j = 0;
    int adress, c;
    symbol = (char*) calloc (MAX_SYMBOL_LEN,sizeof(char));
    while ((c = arr[i++]) != '\0')
    {
        if (isspace (c))
            firstWordFlagEnd = 1;
        if (isalpha(c) && firstWordFlagEnd == 1) /* we skip on the first word and go directly to the symbol. */
        {
            
            symbol [j++] = c;
            while ((c = arr[i++]) != '\0' && !isspace(c))
                symbol[j++] = c; /* collect symbol. */
            adress = searchSymbol (p,symbol); /* check if the symbol is exists. */
            if (adress != 0)
                bitsOperations(binary,START_ADRESS,BITS_ADRESS,adress); /* adress encoded. */
        }
    }
    free (symbol);
}

/* this method find the immed in I directives (if this is branching of directive). */
int iCoding (ptr p,char arr[], long* binary)
{
    char *symbol;
    int firstWordFlagEnd = 0;
    int i = 0, j = 0;
    int adress, c;
    symbol = (char*) calloc (MAX_SYMBOL_LEN,sizeof(char));
    if (!symbol)
    {
        fprintf (stdout,"memory allocation failed\n");
        exit (0);
    }
    while ((c = arr[i++]) != '\0')
    {
        if (isspace (c))
            firstWordFlagEnd = 1;
        else if (isalpha(c) && firstWordFlagEnd == 1) /* we skip on the first word and go directly to the symbol. */
        {
            
            symbol [j++] = c;
            while ((c = arr[i++]) != '\0' && !isspace(c))
                symbol[j++] = c; /* collect symbol. */
            adress = searchSymbol (p,symbol); /* check if the symbol exists in the symbols table. */
        }
    }
    free (symbol);
    return adress;
}

/* this method change the attribute of the symbol in the second transition to "entry" if this entry symbol. */
void entryCoding (ptr p, char arr[])
{
    char *symbol;
    int firstWordFlagEnd = 0;
    int i = 0, j = 0, c;
    symbol = (char*) calloc (MAX_SYMBOL_LEN,sizeof(char));
    if (!symbol)
    {
        fprintf (stdout,"memory allocation failed\n");
        exit(0);
    }
    while ((c = arr[i++]) != '\0')
    {
        if (isspace (c))
            firstWordFlagEnd = 1;
        else if (isalpha(c) && firstWordFlagEnd == 1) /* we skip on the first word and go directly to the symbol. */
        {
            
            symbol [j++] = c;
            while ((c = arr[i++]) != '\0' && !isspace(c))
                symbol[j++] = c; /* collect the symbol. */
            changeSymbol (p,symbol); /* change the symbol attribute. */
        }
    }
    free (symbol);
}
