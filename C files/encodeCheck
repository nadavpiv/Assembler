#include "structs.h"
#include "constants.h"
#include "encoder.h"
#include <string.h>

/* this function check and return the func number of the directive. */
int return_funct (char arr[],directives brr)
{
    int index = 0;
    while (index <= NUM_FUNC_DRECTIVES)
    {
        if(strcmp(arr,brr.directives[index]) == 0)
            return brr.func[index];
        index++;
    }
    return 0;
}

/* this function check and return the op number of the directive. */
int return_op (char arr[],directives brr)
{
    int index = 0;
    while (index <= NUM_OP_DIRECTIVES)
    {
        if(strcmp(arr,brr.directives[index]) == 0)
            return brr.op[index];
        index++;
    }
    return 0;
}
