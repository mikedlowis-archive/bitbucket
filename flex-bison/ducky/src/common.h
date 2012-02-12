/******************************************************************************
 *  Copyright (C) 2011  Michael D. Lowis
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/
#ifndef COMMON_H
#define COMMON_H

#include "cork.h"

/******************************************************************************
 * Types
 *****************************************************************************/
//! Boolean enum definition
typedef enum
{
	TRUE = 1,
	FALSE = 0
} BOOL;

/**** Unsigned Integers ****/
//! 8-bit unsigned integer
typedef	unsigned char		U8;      

//! 16-bit unsigned integer 
typedef	unsigned short int	U16;     

//! 32-bit unsigned integer  
typedef	unsigned long		U32;     

/**** Signed Integers ****/
//! 8-bit signed integer 
typedef	signed char			S8;

//! 16-bit signed integer 
typedef	short int			S16;     

//! 32-bit signed integer  
typedef	long int			S32;     

//! 64-bit signed integer 
typedef long long int       S64;     

// Floating Point
//! 32-bit floating point number 
typedef	float				F32;     

//! 64-bit floating point number
typedef	double				F64;     

/**** String ****/
//! String definition
typedef char *              String;  

/******************************************************************************
 * Defines
 *****************************************************************************/

#ifdef TEST
	#define STATIC
#else
	#define STATIC static
#endif

#ifndef NULL
	#define NULL ((U8)0)
#endif
#define NULL_PTR ((void *)0u)

#define BIT_0   0x01u
#define BIT_1   0x02u
#define BIT_2   0x04u
#define BIT_3   0x08u
#define BIT_4   0x10u
#define BIT_5   0x20u
#define BIT_6   0x40u
#define BIT_7   0x80u

#define BIT_8   0x0100u
#define BIT_9   0x0200u
#define BIT_10  0x0400u
#define BIT_11  0x0800u
#define BIT_12  0x1000u
#define BIT_13  0x2000u
#define BIT_14  0x4000u
#define BIT_15  0x8000u

#define BIT_16  0x010000u
#define BIT_17  0x020000u
#define BIT_18  0x040000u
#define BIT_19  0x080000u
#define BIT_20  0x100000u
#define BIT_21  0x200000u
#define BIT_22  0x400000u
#define BIT_23  0x800000u

#define BIT_24  0x01000000u
#define BIT_25  0x02000000u
#define BIT_26  0x04000000u
#define BIT_27  0x08000000u
#define BIT_28  0x10000000u
#define BIT_29  0x20000000u
#define BIT_30  0x40000000u
#define BIT_31  0x80000000u

/******************************************************************************
 * Macros
 *****************************************************************************/

#define VERIFY_RANGE(x, Min, Max)                 ((((x)>=(Min)) && ((x)<=(Max)))? (TRUE) : (FALSE))
#define VERIFY_RANGE_VALUE(x, Default, Min, Max)  (VERIFY_RANGE((x), (Min), (Max))? (x) : (Default))
#define VERIFY_MAX_VALUE(x, Default, Max)         (((x)<=(Max)) ? (x) : (Default))
#define VERIFY_MIN_VALUE(x, Default, Min)         (((x)>=(Min)) ? (x) : (Default))
#define _ABS(x, type)                             (((x) < (type)0) ? (type)-(x):(x))
#define ABS(x)                                    (((x) < 0) ? -(x):(x))
#define MAX(a,b)                                  (((a) > (b)) ? (a):(b))
#define MIN(a,b)                                  (((a) < (b)) ? (a):(b))
#define SIGN(x,y)                                 (((y) < 0) ? (-(x)):(x))
#define NUM_ELEMENTS(x)	                          (sizeof(x)/sizeof(x[0]))
#define LIMIT_RANGE(x,Min,Max)                    (MAX(MIN((x),(Max)),(Min)))
#define LOW_BYTE(x)                               ((U8)((x) & 0x00FFu))
#define HIGH_BYTE(x)                              ((U8)(((x)>>8u) & 0x00FFu))
#define LOW_WORD(x)                               ((U16)((x) & 0x0000FFFFUL))
#define HIGH_WORD(x)                              ((U16)(((x)>>16) & 0x0000FFFFUL))
#define QUOTE(x)                                  #x

#endif
