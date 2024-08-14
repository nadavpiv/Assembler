#ifndef MAIN_H
#define MAIN_H

/* transition functions. */
void first_transition (FILE*,char[],int);
void second_transition (struct mix*,ptr*,int,int,char[]);

/* secondEncoding functions. */
void jCoding (ptr,char[],long*);
int iCoding (ptr,char[],long*);
void entryCoding (ptr,char[]);

/* checkCommands functions. */
int checkDirective (char[],directives,int);
int checkGuidance (char[],guidences,int);
int checkRAcommand (char[],int,char[],int,int,long*,directives,int);
int checkRCcommand (char[],int,char[],int,int,long*,directives,int);
int checkIcommand (char[],int,char[],int,int,long*,directives,int);
int checkJcommand (char[],int,char[],int,int,long*,directives,int);
int checkD (char[],int,char[],int,int,int[],int,int);
int checkStr (char[],int,char[],int,int,char[],int);
int checkEntry (char[],int,char[],int,int,int);
int checkExtern (char[],int,char[],int,int,char[],int,int);

/* tablesAbits functions. */
void addSymbol (ptr*,struct data*, struct memory*, int,int,int);
void union_images (struct mix*,struct memory*,struct data*,int,int);
int searchSymbol (ptr,char[]);
void changeSymbol (ptr p,char arr[]);
void setbit (long*,int);
int testbit (long, int);
void bitsOperations (long*,int, int, int);
int checkMultiSymbol1 (ptr p,memory_image* brr,int index);
int checkMultiSymbol2 (ptr p,data_image* arr,int index);
#endif