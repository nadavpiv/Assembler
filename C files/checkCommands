#include "structs.h"
#include "encoder.h"
#include "constants.h"
#include "main.h"
#include <math.h>

/* this function checks that the directive is valid. */
int checkDirective (char directive_name[],directives directives_array,int lineCounter)
{
    int index = 0;
    while (index <= 26)
    {
        if(strcmp(directive_name,directives_array.directives[index]) == 0)
            return directives_array.kind[index];
        index++;
    }
    return ERROR;
}

/* this function checks that the guidance is valid. */
int checkGuidance (char guidence_name[],guidences guidence_array,int lineCounter)
{
    int index = 0;
    while (index <= 5)
    {
        if(strcmp(guidence_name,guidence_array.guidence[index]) == 0)
            return guidence_array.kind[index];
        index++;
    }
    return ERROR;
}

/* this function check that the command is legal and make first encoding */
int checkRAcommand (char row_str[], int rowStrIndex, char operands_str[], int operandsStrIndex,int lineCounter,long* binaryNum,directives directives_array,int fileCounter)
{
    char *registers;
    int convert,c;
    int registersIndex = 0, registerFlag = 0, registerCounter = 0;
    registers = (char*) calloc (MAX_SIZE_OF_REG,sizeof(char)); /* keeps the number of the register. */
    /* encode the dircetive */
    bitsOperations(binaryNum,START_NOT_USED,BITS_NOT_USED,0);
    bitsOperations(binaryNum,START_FUNCT,BITS_FUNCT,return_funct(operands_str,directives_array));
    operands_str[operandsStrIndex++] ='\t';
    while ((c = row_str[rowStrIndex++]) != '\0')
    {
        if (isspace(c)) /* skipping the spaces at the start of the line. */
            continue;
        else if (c == '$') /* if we met register. */
        {
            registerFlag = 1; /* turn on register flag. */
            registerCounter++;
            operands_str[operandsStrIndex++] = c;
        }
        else if (isdigit (c) || c == '-')
        {
            if (registerFlag == 0) /* number before register in this directive is illegal. */
            {
                fprintf (stdout,"File number: %d Line:%d <illegal char>\n",fileCounter,lineCounter);
                return ERROR;
            }
            registers[registersIndex++] = c; /* collect the register number. */
            operands_str[operandsStrIndex++] = c;
        }
        else if (c == ',')
        {
            convert = atoi (registers);
            if (convert > MAX_NUM_OF_REG || convert < 0) /* check that this is valid register. */
            {
                fprintf (stderr,"File number: %d Line:%d <illegal register>\n",fileCounter,lineCounter);
                return ERROR;
            }
            else
            {
                /* check where to encdoe, and encoder. */
                if (registerCounter == 1) /* first register of the command */
                    bitsOperations(binaryNum,START_RS,BITS_RS,convert);
                else if (registerCounter == 2) /* second register of the command. */
                    bitsOperations(binaryNum,START_RT,BITS_RT,convert);
                operands_str[operandsStrIndex++] = '\t';
                /* initialize register for next register. */
                registersIndex = 0; 
                free (registers);
                registers = (char*) calloc (MAX_SIZE_OF_REG,sizeof(char));
            }
        }
    }
    /* for the last register that there is not semicolon after him. */
    convert = atoi (registers);
    if (convert > MAX_NUM_OF_REG || convert < 0)
    {
        fprintf (stdout,"File number: %d Line:%d <illegal register>\n",fileCounter,lineCounter);
        return ERROR;
    }
    else
    {
        if (registerCounter != NUM_REG_OF_RA_CMD) /* this directive need to get 3 registers. */
        {
            fprintf (stdout,"File number: %d Line:%d <illegal number of registers\n",fileCounter,lineCounter);
            return ERROR;
        }
        bitsOperations(binaryNum,START_RD,BITS_RD,convert); /* encoder register. */
    }
    free (registers);
    return OK;
}

int checkRCcommand (char row_str[], int rowStrIndex, char operands_str[], int operandsStrIndex,int lineCounter,long *binaryNum,directives directives_array,int fileCounter)
{
    char *registers;
    int convert, c;
    int registersIndex = 0, registerCounter = 0, registerFlag = 0;
    registers = (char*) calloc (MAX_SIZE_OF_REG,sizeof(char));

    /* encode the dircetive */
    bitsOperations(binaryNum,START_NOT_USED,BITS_NOT_USED,0);
    bitsOperations(binaryNum,START_RT,BITS_RT,0);
    bitsOperations(binaryNum,START_OP,BITS_OP,return_op(operands_str,directives_array));
    bitsOperations(binaryNum,START_FUNCT,BITS_FUNCT,return_funct(operands_str,directives_array));
    operands_str[operandsStrIndex++] ='\t';
    while ((c = row_str[rowStrIndex++]) != '\0')
    {
        if (isspace(c)) /* skipping the spaces at the start of the line. */
            continue;
        else if (c == '$') /* if we met register. */
        {
            registerFlag = 1; /* turn on register flag. */
            registerCounter++;
            operands_str[operandsStrIndex++] = c;
        }
        else if (isdigit (c) || c == '-')
        {
            if (registerFlag == 0) /* number before register in this directive is illegal. */
            {
                fprintf (stdout,"File number: %d Line:%d <illegal char>\n",fileCounter,lineCounter);
                return ERROR;
            }
            registers [registersIndex++] = c; /* collect the register number. */
            operands_str[operandsStrIndex++] = c;
        }
        else if (c == ',')
        {
            
            convert = atoi (registers);
            if (convert > MAX_NUM_OF_REG || convert < 0) /* check that this is valid register. */
            {
                fprintf (stdout,"File number: %d Line:%d <illegal register>\n",fileCounter,lineCounter);
                return ERROR;
            }
            else
            {
                bitsOperations(binaryNum,START_RS,BITS_RS,convert); /* encoder register. */
                operands_str[operandsStrIndex++] = '\t';
                /* initialize the array for next register. */
                registersIndex = 0;
                free (registers);
                registers = (char*) calloc (MAX_SIZE_OF_REG,sizeof(char));
            }
        }
    }
    /* for the last register that there is not semicolon after him. */
    convert = atoi (registers);
    if (convert > MAX_NUM_OF_REG || convert < 0)
    {
        fprintf (stdout,"File number: %d Line:%d <illegal register>\n",fileCounter,lineCounter);
        return ERROR;
    }
    else
    {
        if (registerCounter != NUM_REG_OF_RC_CMD) /* this directive need to get 2 registers. */
        {
            fprintf (stdout,"File number: %d Line:%d <illegal number of registers>\n",fileCounter,lineCounter);
            return ERROR;
        }
    }
    bitsOperations(binaryNum,START_RD,BITS_RD,convert); /* encoder register. */
    free (registers);
    return OK;
}

/* this function check that the command is legal and make first encoding */
int checkIcommand (char row_str[],int rowStrIndex,char operands_str[],int operandsStrIndex,int lineCounter,long* binarynum,directives directives_array,int fileCounter)
{
    char *registers, *number;
    int convert, c;
    int registerIndex = 0, registerCounter = 0, numberIndex = 0;
    int immedCounter = 0;
    registers = (char*) calloc (MAX_SIZE_OF_REG, sizeof(char));
    number = (char*) calloc (MAX_LEN_NUM,sizeof(char));

    /* encode the dircetive */
    bitsOperations(binarynum,START_OP,BITS_OP,return_op(operands_str,directives_array));
    operands_str[operandsStrIndex++] ='\t';
    while ((c = row_str[rowStrIndex++]) != '\0')
    {
        if (isspace(c)) /* skipping the spaces at the start of the line. */
            continue;
        else if (c == '$') /* if we met register. */
        {
            registerCounter++;
            operands_str[operandsStrIndex++] = c;
            while ((c = row_str[rowStrIndex++]) != ',' && c != '\0') /* scan till the end of the register number. */
            {
                operands_str[operandsStrIndex++] = c;
                registers[registerIndex++] = c; /* collect register number. */
            }
            convert = atoi(registers);
            /* check which register to encdoe. */
            if (registerCounter == 1) /* the first reg of the command. */
                bitsOperations(binarynum,START_RS,BITS_RS,convert);
            else if (registerCounter == 2) /* the second reg of the command. */
                bitsOperations(binarynum,START_RT,BITS_RT,convert);
            if (convert > MAX_NUM_OF_REG || convert < 0) /* check that this is valid register. */
            {
                fprintf (stdout,"File number: %d Line:%d <illegal register>\n",fileCounter,lineCounter);
                return ERROR;
            }
            operands_str[operandsStrIndex++] = '\t';
            /* initialize for the next register. */
            registerIndex = 0;
            free (registers);
            registers = (char*) calloc (MAX_SIZE_OF_REG,sizeof(char));
        }
        else if (isdigit(c) || c == '-' || c == '+') /* if the immed is a number. */
        {
            number[numberIndex++] = c; /* collect the number. */
            operands_str[operandsStrIndex++] = c;
            immedCounter++;
            while ((c = row_str[rowStrIndex++]) != ',' && c != '\0' && c != '$') /* scan till the end of the number. */
            {
                if (!isdigit(c) && c != '.')
                {
                    fprintf (stdout,"File number: %d Line:%d <illegal immed>\n",fileCounter,lineCounter);
                    return ERROR;
                }
                operands_str[operandsStrIndex++] = c; 
                number[numberIndex++] = c; /* collect the number */
            }
            convert = atoi(number);
            bitsOperations(binarynum,START_IMMED,BITS_IMMED,convert); /* encoder immed. */
            if (c == '$') /* if we stop the loop because we met register we step back to collect the register. */
                rowStrIndex--;
            operands_str[operandsStrIndex++] = '\t';
        }
        else if (isalpha(c)) /* if the immed is a symbol. */
        {
            operands_str[operandsStrIndex++] = c;
            immedCounter++;
            while ((c = row_str[rowStrIndex++]) != ',' && c != '\0') /* scan till we the end of the symbol. */
                operands_str[operandsStrIndex++] = c;
        }
    }
    if (registerCounter != NUM_REG_OF_I_CMD || immedCounter != NUM_IMMED_OF_I_CMD) /* this directive need 2 registers and immed. */
    {
        fprintf (stdout,"File number: %d Line:%d <illegal number of operands>\n",fileCounter,lineCounter);
        return ERROR;
    }
    free (registers);
    return OK;
}

/* this function check that the command is legal and make first encoding */
int checkJcommand (char row_str[],int rowStrIndex,char operands_str[],int operandsStrIndex,int lineCounter , long* binaryNum,directives directives_array,int fileCounter)
{
    char *registers;
    int registerFlag = 0, registerIndex = 0, registerCounter = 0;
    int convert, c, adressCounter = 0;
    registers = (char*) calloc (MAX_SIZE_OF_REG, sizeof(char));
    /* encode the dircetive */
    bitsOperations(binaryNum,START_OP,BITS_OP,return_op(operands_str,directives_array));
    operands_str[operandsStrIndex++] ='\t';
    while ((c = row_str[rowStrIndex++]) != '\0')
    {
        if (isspace(c)) /* skipping the spaces at the start of the line. */
            continue;
        else if (c == '$') /* if we met register. */
        {
            registerFlag = 1; /* turn on register flag. */
            registerCounter++;
            operands_str[operandsStrIndex++] = c;
            while ((c = row_str[rowStrIndex++]) != ',' && c != '\0') /* scan the number of the register. */
            {
                operands_str[operandsStrIndex++] = c;
                registers[registerIndex++] = c; /* collect the register number. */
            }
            convert = atoi(registers);
            if (convert > MAX_NUM_OF_REG || convert < 0) /* check if the register number is valid. */
            {
                fprintf (stdout,"File number: %d Line:%d <illegal register>\n",fileCounter,lineCounter);
                return ERROR;
            }
            bitsOperations(binaryNum,START_ADRESS,BITS_ADRESS,convert); /* encoder register. */
            setbit (binaryNum,25); /* turn on the reg bit. */
        }
        else if (isdigit(c) || c == '-')
        {
            operands_str[operandsStrIndex++] = c;
            if (registerFlag == 0) /* if there is a number before register its illegal. */
            {
                fprintf (stdout,"File number: %d Line:%d <illegal char>\n",fileCounter,lineCounter);
                return ERROR;
            }
            while ((c = row_str[rowStrIndex++]))
            {
                operands_str[operandsStrIndex++] = c;
                registers[registerIndex++] = c; /* collect the register number. */
            }
        }
        else if (isalpha(c)) /* if the adress is a symbol. */
        {
            operands_str[operandsStrIndex++] = c;
            adressCounter++;
            while ((c = row_str[rowStrIndex++]) != ',' && c != '\0') /* scan till the end of the symbol. */
                operands_str[operandsStrIndex++] = c;  
        }
    }
    if (registerFlag == 1)
    {
        convert = atoi (registers);
        if (convert > MAX_NUM_OF_REG || convert < 0) /* check that the register is valid. */
        {
            fprintf (stdout,"File number: %d Line:%d <illegal register>\n",fileCounter,lineCounter);
            return ERROR;
        }
    }
    free (registers);
    /* this directive get or one symbol or one register. */
    if ((registerCounter == 1 && adressCounter == 0) || (adressCounter == 1 && registerCounter == 0))
        return OK;
    return ERROR;
}

int checkD (char row_str[], int rowStrIndex, char operands_str[], int operandsStrIndex,int lineCounter,int numbers[],int fileCounter,int guidenceKind)
{
    int i = 0, c ,digitIndex = 0;
    int count = 0, convert;
    char *digit;
    digit = (char*) calloc (MAX_LEN_NUM, sizeof(char));
    while ((c = row_str[rowStrIndex++]) != '\0')
    {
        if (isspace(c)) /* skipping the spaces at the start of the line. */
            continue;
        else if (isdigit (c) || c == '-' || c == '+' || c == '.') /* if we met number. */
        {
            operands_str[operandsStrIndex++] = c;
            digit[digitIndex++] = c; /* collect the number. */
        }
        else if (c == ',') /* if we met end of number. */
        {
            convert = atoi(digit);
            if (convert > pow (2,(guidenceKind*8))/2 || convert < pow(2,(guidenceKind*8))/(-2))
            {
                fprintf (stdout,"File number: %d Line:%d <illegal number>\n",fileCounter,lineCounter);
                return ERROR;  
            }
            numbers[i++] = convert; /* put in the numbers array the number. */
            /* initialize for the next number. */
            digitIndex = 0;
            free(digit);
            digit = (char*) calloc (MAX_LEN_NUM,sizeof(char));
            count++; /* count numbers. */
            operands_str[operandsStrIndex++] = '\t';
        }
    }
    /* for the last number that there isnt a semicolon after him. */
    convert = atoi(digit);
    if (convert > pow (2,(guidenceKind*8))/2 || convert < pow(2,(guidenceKind*8))/(-2))
    {
        fprintf (stdout,"File number: %d Line:%d <illegal number>\n",fileCounter,lineCounter);
        return ERROR;  
    }
    numbers[i++] = convert; /* put in the numbers array the number. */
    free (digit);
    count++;
    return count;
}

int checkStr (char row_str[], int rowStrIndex, char operands_str[], int operandsStrIndex,int lineCounter,char str[],int fileCounter)
{
    int c, count = 0, strIndex = 0,srtingFlag = 0;
    while ((c = row_str[rowStrIndex++]) != '\0')
    {
        if (isspace(c)) /* skippining the first spaces at the start of the line. */
            continue;
        if (c == '"') /* if we met string. */
        {
            while ((c = row_str[rowStrIndex++])) /* scan till the end of the string. */
            {
                if (c == '"')
                {
                    srtingFlag = 1;
                    break;
                }
                str[strIndex++] = c; /* put the char in str array. */
                operands_str[operandsStrIndex++] = c;
                operands_str[operandsStrIndex++] = '\t';
                count++; /* count chars. */
            }
        }
    }
    if (srtingFlag == 0) /* check that we get the char " at the end of string to check if its valid string. */
    {
        fprintf (stdout,"File number: %d Line:%d <illegal string>\n",fileCounter,lineCounter);
        return ERROR;
    }
    count++; /* count the char '\0' at the end of the string. */
    return count;
}

int checkEntry (char row_str[],int rowStrIndex,char operands_str[],int operandsStrIndex,int lineCounter,int fileCounter)
{
    int c;
    while ((c = row_str[rowStrIndex++]) != '\0')
    {
        if (isspace(c)) /* skipping the spaces at the start of the line. */
            continue;
        if (!isalpha(c)) /* after .entry guidance we need to get symbol that start with char. */
        {
            fprintf (stdout,"File number: %d Line:%d <illegal entry name>\n",fileCounter,lineCounter);
            return ERROR;
        }
        if (isalpha(c))
        {
            operands_str[operandsStrIndex++] = c;
            while ((c = row_str[rowStrIndex++]) != '\0' && !isspace(c))
                operands_str[operandsStrIndex++] = c;
        }
    }
    return OK;
}

int checkExtern (char row_str[],int rowStrIndex,char operands_str[],int operandsStrIndex,int lineCounter,char symbol[],int symbolIndex,int fileCounter)
{
    int c;
    while ((c = row_str[rowStrIndex++]) != '\0')
    {
        if (isspace(c)) /* skipping spaces at the start of the line. */
            continue;
        if (!isalpha(c)) /* after .extern guidance we need to get symbol that start with char. */
        {
            fprintf (stdout,"File number: %d Line:%d <illegal extern name>\n",fileCounter,lineCounter);
            return ERROR;
        }
        if (isalpha(c))
        {
            operands_str[operandsStrIndex++] = c;
            symbol[symbolIndex++] = c;
            while ((c = row_str[rowStrIndex++]) != '\0' && !isspace(c))
            {
                operands_str[operandsStrIndex++] = c;
                symbol[symbolIndex++] = c;
            }
        }
    }
    return OK;
}
