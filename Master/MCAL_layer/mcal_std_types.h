/* 
 * Author: Moaaz  elmahi
 *
 * Created on 02 August 2023, 21:41
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/* includes */
#include "compiler.h"
#include "std_libraries.h"

/* Data types declarations */
typedef  unsigned char  uint8;
typedef unsigned short  uint16;
typedef unsigned long    uint32;
typedef signed char     sint8;
typedef signed short    sint16;
typedef signed long      sint32;

typedef uint8  STD_ReturnType;


/* Macros declarations */
#define STD_HIGH  0x01
#define STD_LOW   0x00

#define STD_ON    0x01
#define STD_OFF   0x00

#define E_OK          (STD_ReturnType)0x01
#define E_NOT_OK      (STD_ReturnType)0x00
 
#define E_Zero_Init          0   

#define config_Enable   1
#define config_disable  0

/* MACROS Functions declarations */



/* Functions declarations */



#endif	/* MCAL_STD_TYPES_H */

