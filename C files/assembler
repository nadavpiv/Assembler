#include "structs.h"
#include "main.h"

int main (int argc, char *argv[])
{
    int i = 1;
    int fileCounter = 1;
    FILE *f;
    printf ("\n");
    while (argv[i] != NULL) /* read all the files. */
    {
        if (!strstr(argv[i],".as")) /* check that this is valid file. */
        {
            fprintf(stdout,"file number:%d <Illegal file>\n",fileCounter);
            i++;
            continue;
        }
        f = fopen (argv[i], "r");
        if (!f)
            fprintf (stderr,"sorry cant open the file\n");
        else
        {
            fseek(f, 0, SEEK_END); 
            if (ftell(f) == 0) /* if the file is empty we continue to the next file. */
            {
                i++;
                continue;
            }
            rewind(f); /* point to the first of the file. */
            first_transition (f,argv[i],fileCounter);
        }
        i++;
        fileCounter++;
    }
    return 0;
}
