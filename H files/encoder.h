#ifndef ENCODER_H
#define ENCODER_H

/* encode check functions. */
int return_funct (char arr[],directives brr);
int return_op (char arr[],directives brr);

#define START_NOT_USED 0
#define BITS_NOT_USED 6

#define START_OP 26
#define BITS_OP 6

#define START_FUNCT 6
#define BITS_FUNCT 5

#define START_RT 16
#define BITS_RT 5

#define START_RS 21
#define BITS_RS 5

#define START_RD 11
#define BITS_RD 5

#define START_IMMED 0
#define BITS_IMMED 16

#define START_REG 25
#define BITS_REG 1

#define START_ADRESS 0
#define BITS_ADRESS 25

#endif
