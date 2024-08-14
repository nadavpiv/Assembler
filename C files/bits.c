#include "structs.h"
#include "constants.h"
#include "main.h"

/* this method turn on in the number that transfered to her the bit that transfered. */ 
void setbit (long* a, int k)
{
    int pos = k % 32;
    unsigned int flag = 1;
    flag = flag << pos;
    *a = *a | flag;
}

/* this method check if the bit is turn on. */
int testbit (long a,int k)
{
    if ((a & (1 << (k % 32))) != 0)       
         return 1;
    else
        return 0; 
}

/* this method turn on specific bits according to the numbers that transfered to her. */
/* this method help in the encoding. */
void bitsOperations (long* binary, int start, int sum, int number)
{
    int i = 0,check = 0;
    while (i < sum)
    {
        check = testbit (number,i);
        if (check == 1)
            setbit (binary,start);
        i++;
        start++;
    }
}
