#include "structs.h"
#include "encoder.h"
#include "constants.h"
#include "main.h"
#include "write.h"
extern directives directives_array;
extern guidences guidences_array;

/* initiliaze all the tables. */
data_image* dataImage;
memory_image* memoryImage;
mix_images* mixImages;
ptr p, temp;

/* this function get a file and make first transition for the assembler. */
void first_transition (FILE* f,char fileName[],int fileCounter)
{
    int c, error = 0;
    long binary;
    enum status state;
    int IC = 100, DC = 0; /* counters memory. */
    int word2Index, strIndex, word1Index = 0;
    int directiveChecker, guidanceChecker, internalGuidanceChecker;
    int lineCounter = 0, dataCounter = 0, memoryCounter = 0;
    int directiveIndex = 0, guidenceIndex = 0;
    int flagSymbol, directiveFlag, guidanceFlag, entryFlag, externFlag, numbersFlag, strFlag;
    char *str, *word1, *word2, *string;
    int *numbers;
    str = (char*) calloc (MAX_DIRECTIVE_LEN,sizeof(char));
    p = (ptr) malloc(sizeof (symbols_table)); /* initailize the symbols table. */
    dataImage = (data_image*) calloc (MAX_DATA_CMD,sizeof(data_image));
    memoryImage = (memory_image*) calloc (MAX_MEMORY_CMD,sizeof (memory_image));
    mixImages = (mix_images*) calloc (MAX_UNION_IMAGE,sizeof(mix_images));
    if (!p || !dataImage || !memoryImage || !mixImages)
    {
        fprintf (stdout,"allocation memory failed\n");
        exit (0);
    }
    while (fgets (str,MAX_DIRECTIVE_LEN,f) != NULL) /* read every line from the file. */
    {
        lineCounter++; /* count lines. */
        word2Index = 0, strIndex = 0, binary = 0;
        flagSymbol = 0, directiveFlag = 0, guidanceFlag = 0, entryFlag = 0, externFlag = 0;
        numbersFlag = 0, strFlag = 0;
        /* initialize all the dynamic arrays for this parsing of this line. */
        word1 = (char*) calloc (MAX_LENGTH , sizeof(char));
        word2 = (char*) calloc (MAX_LENGTH , sizeof(char));
        numbers = (int*) calloc (MAX_LENGTH , sizeof(char));
        string = (char*) calloc (MAX_LENGTH,sizeof(char));
        if (!word1 || !word2 || !numbers || !string)
        {
            fprintf (stdout,"memory allocation failed\n");
            exit (0);
        }
        state = start;
        if (str[0] == ';') /* if this is comment line. */
            continue;
        while ((c = str[strIndex++]) != '\0') /* read till the end of the line. */
        {
            switch (state)
            {
                case start:
                    if (isspace (c)) /* skip on the spaces at the start of the line. */
                        break;
                    else if (isalpha (c))
                    {
                        state = directive_op; /* check the directive. */
                        word2[word2Index++] = c;
                        break;
                    }
                    else if (c == '.')
                    {
                        state = guidance_op; /* check the guidance. */
                        word2[word2Index++] = c;
                        break;
                    }
                    else if (isdigit(c))
                    {
                        fprintf (stdout,"File number: %d Line:%d <illegal symbol>\n",fileCounter,lineCounter);
                        error = ERROR;
                        state = stopRow;
                    }
                    break;

                case directive_op:
                    if (c == ':') /* we read symbol till now. */
                    {
                        if (strlen(word2) > MAX_SYMBOL_LEN)
                        {
                            fprintf (stdout,"File number: %d Line:%d <illegal symbol>\n",fileCounter,lineCounter);
                            state = stopRow;
                        }
                        else if (checkDirective(word1,directives_array,lineCounter) != ERROR)
                        {
                            fprintf (stdout,"File number: %d Line:%d <illegal symbol>\n",fileCounter,lineCounter);
                            state = stopRow;
                        }
                        else if (checkGuidance(word1,guidences_array,lineCounter) != ERROR)
                        {
                            fprintf (stdout,"File number: %d Line:%d <illegal symbol>\n",fileCounter,lineCounter);
                            state = stopRow;
                        }
                        flagSymbol = 1; /* turn on flag symbol. */
                        strcpy (word1,word2); /* word1 keep the symbol. */
                        /* initialize word2 for continue check. */
                        free (word2);
                        word2 = (char*) calloc (50, sizeof(char));
                        word2Index = 0;
                        if (!(isspace(str[strIndex++]))) /* check that there is a space after symbol. */
                        {
                            fprintf (stdout,"File number: %d Line:%d <illegal directive>\n",fileCounter,lineCounter);
                            state = stopRow;
                            break;
                        }
                        state = white; /* for skipping the spaces till the directive. */
                        break;
                    }
                    else if (isspace(c))
                    {
                        directiveChecker = checkDirective (word2,directives_array,lineCounter); /* check which kind of directive. */
                        if (directiveChecker == ERROR)
                        {
                            fprintf (stdout,"File number: %d Line:%d <illegal directive>\n",fileCounter,lineCounter);
                            state = stopRow;
                            error = ERROR; /* don't continue to second transition. */
                        }
                        else
                        {
                            directiveFlag = 1; /* turn on directive flag. */
                            /* check if the line is legal, build the memory image and encoder. */ 
                            if (directiveChecker == RA)
                                checkRAcommand (str,strIndex,word2,word2Index,lineCounter,&binary,directives_array,fileCounter);
                            else if (directiveChecker == RC)
                                checkRCcommand (str,strIndex,word2,word2Index,lineCounter,&binary,directives_array,fileCounter);
                            else if (directiveChecker == I || directiveChecker == ICC)
                                checkIcommand (str,strIndex,word2,word2Index,lineCounter,&binary,directives_array,fileCounter);
                            else
                                checkJcommand (str,strIndex,word2,word2Index,lineCounter,&binary,directives_array,fileCounter);
                            state = stopRow;
                            break;
                        }
                    }
                    word2[word2Index++] = c; /* collect chars for the operands of memory image. */
                    break;

                case guidance_op:
                    if (isspace (c))
                    {
                        guidanceChecker = checkGuidance (word2,guidences_array,lineCounter); /* check if the guidance is valid. */
                        if (guidanceChecker == ERROR)
                        {
                            fprintf (stdout,"File number: %d Line:%d <illegal guidence>\n",fileCounter,lineCounter);
                            state = stopRow;
                            error = ERROR; /* don't continue to second transition. */
                        }
                        else
                        {
                            guidanceFlag = 1; /* turn on guidance flag. */
                            word2[word2Index++] = '\t';
                            /* check if the line is legal, build the data image and encoder. */ 
                            if (guidanceChecker == DW || guidanceChecker == DH || guidanceChecker == DB)
                            {
                                internalGuidanceChecker = checkD (str,strIndex,word2,word2Index,lineCounter,numbers,fileCounter,guidanceChecker);
                                numbersFlag = 1; /* turn on number flag. */
                            }
                            else if (guidanceChecker == ASCIZ)
                            {
                                internalGuidanceChecker = checkStr (str,strIndex,word2,word2Index,lineCounter,string,fileCounter);
                                strFlag = 1; /* turn on str flag. */
                            }
                            else if (guidanceChecker == ENTRY)
                            {
                                entryFlag = 1; /* turn on entry flag. */
                                internalGuidanceChecker = checkEntry (str,strIndex,word2,word2Index,lineCounter,fileCounter);
                            }
                            else if (guidanceChecker == EXTERN)
                            {
                                externFlag = 1; /* turn on extern flag. */
                                internalGuidanceChecker = checkExtern (str,strIndex,word2,word2Index,lineCounter,word1,word1Index,fileCounter);
                            }
                            state = stopRow;
                            break;
                        }
                    }
                    word2[word2Index++] = c; /* collect chars for the operands of data image. */
                    break;
                    
                case white:
                    if (isspace(c))
                        break;
                    else if (isalpha(c))
                    {
                        word2 [word2Index++] = c;
                        state = directive_op; /* check the directive. */
                        break;
                    }
                    else if (c == '.')
                    {
                        state = guidance_op; /* check the guidance. */
                        word2 [word2Index++] = c;
                        break;
                    }
                    break;

                case stopRow: /* this case on if we get error and want to skip on the line. */
                    break;
            }
        }

        if (directiveFlag == 1) /* put the data that we collected in the memory image (index i). */
        {
            memoryCounter++;
            memoryImage[directiveIndex].symbol = flagSymbol;
            memoryImage[directiveIndex].memory_adress = IC;
            if (flagSymbol == 1)
                strcpy (memoryImage[directiveIndex].symbolName, word1);
            strcpy (memoryImage[directiveIndex].operands, word2);
            memoryImage[directiveIndex].binary = binary;
            IC += 4;
            directiveIndex++;
        }
        else if (guidanceFlag == 1 || entryFlag == 1 || externFlag == 1)
        {
            int j = 0;
            if (entryFlag == 1)
            {
                dataImage[guidenceIndex].symbol = ENTRY_SYMBOL;
                dataImage[guidenceIndex].memory_adress = 0;
                strcpy (dataImage[guidenceIndex].operands, word2);
                guidenceIndex++;
                dataCounter++;
            }
            else if (externFlag == 1)
            {
                dataImage[guidenceIndex].symbol = EXTERN_SYMBOL;
                dataImage[guidenceIndex].memory_adress = 0; 
                strcpy (dataImage[guidenceIndex].operands, word2);
                strcpy (dataImage[guidenceIndex].symbolName, word1);
                guidenceIndex++;
                dataCounter++;
            }
            else /* if the guidance is .asciz,.dw,.dh or .db */
            {
                dataImage[guidenceIndex].symbol = flagSymbol;
                if (flagSymbol == 1)
                    strcpy (dataImage[guidenceIndex].symbolName, word1);
                strcpy (dataImage[guidenceIndex].operands, word2);
                if (numbersFlag == 1)
                {
                    while (numbers[j]) /* put the data (the numbers) in the data image. */
                    {
                        bitsOperations (&binary,0,guidanceChecker*8,numbers[j]);
                        dataImage[guidenceIndex].binary = binary;
                        dataImage[guidenceIndex].memory_adress = DC;
                        dataImage[guidenceIndex].dataSymbol = guidanceChecker;
                        DC += guidanceChecker;
                        dataCounter++;
                        binary = 0;
                        guidenceIndex++;
                        j++;
                    }
                }
                if (strFlag == 1)
                {
                    while (string[j]) /* put the data (the chars) in the data image. */
                    {
                        bitsOperations (&binary,0,__CHAR_BIT__,string[j]);
                        dataImage[guidenceIndex].binary = binary;
                        dataImage[guidenceIndex].memory_adress = DC;
                        DC += 1;
                        dataImage[guidenceIndex].dataSymbol = guidanceChecker;
                        dataCounter++;
                        binary = 0;
                        guidenceIndex++;
                        j++;
                    }
                    /* put the last char '\0' in the data image. */
                    bitsOperations (&binary,0,__CHAR_BIT__,0);
                    dataImage[guidenceIndex].binary = binary;
                    dataImage[guidenceIndex].memory_adress = DC;
                    dataImage[guidenceIndex].dataSymbol = guidanceChecker;
                    DC += 1;
                    dataCounter++;
                    guidenceIndex++;

                }
            }
        }
        /* free all the dynamic memory for the next line and initialize str. */
        free (str);
        free (word1);
        free (word2);
        free (numbers);
        free (string);
        str = (char*) calloc (MAX_DIRECTIVE_LEN,sizeof(char));
    }
    free (str);
    addSymbol (&p,dataImage,memoryImage, dataCounter,memoryCounter,fileCounter); /* build the symbols table. */
    union_images (mixImages,memoryImage,dataImage,memoryCounter,dataCounter); /* build the union image. */
    /* if the file is valid we continue to the second transition. */
        if (error != ERROR && internalGuidanceChecker != ERROR)
            second_transition (mixImages,&p,dataCounter,memoryCounter,fileName);
        free (p);
        free (mixImages);
        free (dataImage);
        free(memoryImage);
}

void second_transition (struct mix* arr,ptr* p,int dataCounter,int memoryCounter,char fileName[])
{
    int i = 0, sum, c, strIndex;
    int directiveIndex, directiveChecker, directiveFlag, guidanceFlag;
    int adress,immedRes;
    char *str, *directive;
    sum = dataCounter + memoryCounter;
    while (i < sum)
    {
        directiveIndex = 0, strIndex = 0;
        directiveFlag = 0, guidanceFlag = 0;
        str = (char*) calloc (MAX_DIRECTIVE_LEN,sizeof(char));
        directive = (char*) calloc (10,sizeof(char));
        if (!str || !directive)
        {
            fprintf (stdout,"allocation memory failed\n");
            exit (0);
        }
        strcpy (str,mixImages[i].operands);
        /* check if this is guidance or directive line. */
        if (str[0] == '.')
            guidanceFlag = 1;
        else if (isalpha(str[0]))
            directiveFlag = 1;
        while ((c = str[strIndex++]))
        {
            if (isspace(c)) /* skipping the spaces at the start of the line. */
                break;
            directive[directiveIndex++] = c;
        }   
            if (directiveFlag == 1)
                directiveChecker = checkDirective (directive,directives_array,0); /* check which directive. */
            else if (guidanceFlag == 1)
                directiveChecker = checkGuidance (directive,guidences_array,0); /* check which guidance. */
        if (directiveChecker == J)
            jCoding (*p,str,&(arr[i].binary)); /* encoded the adress in J directive. */
        else if (directiveChecker == ICC)
        {
            adress = iCoding (*p,str,&(arr[i].binary)); /* check what is the adress of the symbol for the immed. */
            immedRes = mixImages[i].memory_adress - adress;
            immedRes = immedRes * (-1); /* the distance between the commands. */
            bitsOperations (&(arr[i].binary),START_IMMED,BITS_IMMED,immedRes); /* encoded the immed. */
        }
        else if (directiveChecker == ENTRY)
            entryCoding (*p,str); /* change the attribute of the symbol to "entry". */
        i++;
        free (str);
        free (directive);
    }
    /* write the files. */
    writeMemoryFile (arr,p, dataCounter, memoryCounter,fileName);
    writeEntryFile (arr,*p,fileName);
    writeExternFile (arr,*p,dataCounter,memoryCounter,fileName);
}
