#include <setjmp.h>
#include <malloc.h>

/******************************************************************************
 * Type Definitions
 *****************************************************************************/
/* Type definitions */
#ifdef C_SIXTY_FOUR
    typedef unsigned long Word;
#else
    typedef unsigned int Word;
#endif
typedef char Byte;

typedef struct
{
    Word header;
    Word[1] data;
} ObjectBlock;

typedef struct
{
    Word header;
    ObjectBlock* parent;
    Word* table;
} Prototype;

#ifdef C_SIXTY_FOUR
    # define C_INT_SIGN_BIT           0x8000000000000000L
    # define C_INT_TOP_BIT            0x4000000000000000L
    # define C_HEADER_BITS_MASK       0xff00000000000000L
    # define C_HEADER_TYPE_BITS       0x0f00000000000000L
    # define C_HEADER_SIZE_MASK       0x00ffffffffffffffL
    # define C_GC_FORWARDING_BIT      0x8000000000000000L   /* header contains forwarding pointer */
    # define C_BYTEBLOCK_BIT          0x4000000000000000L   /* block contains bytes instead of slots */
    # define C_SPECIALBLOCK_BIT       0x2000000000000000L   /* 1st item is a non-value */
    # define C_8ALIGN_BIT             0x1000000000000000L   /* data is aligned to 8-byte boundary */

    # define C_SYMBOL_TYPE            (0x0100000000000000L)
    # define C_STRING_TYPE            (0x0200000000000000L | C_BYTEBLOCK_BIT)
    # define C_PAIR_TYPE              (0x0300000000000000L)
    # define C_CLOSURE_TYPE           (0x0400000000000000L | C_SPECIALBLOCK_BIT)
    # define C_FLONUM_TYPE            (0x0500000000000000L | C_BYTEBLOCK_BIT | C_8ALIGN_BIT)
    /*       unused                   (0x0600000000000000L ...) */
    # define C_PORT_TYPE              (0x0700000000000000L | C_SPECIALBLOCK_BIT)
    # define C_STRUCTURE_TYPE         (0x0800000000000000L)
    # define C_POINTER_TYPE           (0x0900000000000000L | C_SPECIALBLOCK_BIT)
    # define C_LOCATIVE_TYPE          (0x0a00000000000000L | C_SPECIALBLOCK_BIT)
    # define C_TAGGED_POINTER_TYPE    (0x0b00000000000000L | C_SPECIALBLOCK_BIT)
    # define C_SWIG_POINTER_TYPE      (0x0c00000000000000L | C_SPECIALBLOCK_BIT)
    # define C_LAMBDA_INFO_TYPE       (0x0d00000000000000L | C_BYTEBLOCK_BIT)
    /*       unused                   (0x0e00000000000000L ...) */
    # define C_BUCKET_TYPE            (0x0f00000000000000L)
#else
    # define C_INT_SIGN_BIT           0x80000000
    # define C_INT_TOP_BIT            0x40000000
    # define C_HEADER_BITS_MASK       0xff000000
    # define C_HEADER_TYPE_BITS       0x0f000000
    # define C_HEADER_SIZE_MASK       0x00ffffff
    # define C_GC_FORWARDING_BIT      0x80000000
    # define C_BYTEBLOCK_BIT          0x40000000
    # define C_SPECIALBLOCK_BIT       0x20000000
    # define C_8ALIGN_BIT             0x10000000

    # define C_SYMBOL_TYPE            (0x01000000)
    # define C_STRING_TYPE            (0x02000000 | C_BYTEBLOCK_BIT)
    # define C_PAIR_TYPE              (0x03000000)
    # define C_CLOSURE_TYPE           (0x04000000 | C_SPECIALBLOCK_BIT)
    # ifdef C_DOUBLE_IS_32_BITS
    #  define C_FLONUM_TYPE           (0x05000000 | C_BYTEBLOCK_BIT)
    # else
    #  define C_FLONUM_TYPE           (0x05000000 | C_BYTEBLOCK_BIT | C_8ALIGN_BIT)
    # endif
    /*       unused                   (0x06000000 ...) */
    # define C_PORT_TYPE              (0x07000000 | C_SPECIALBLOCK_BIT)
    # define C_STRUCTURE_TYPE         (0x08000000)
    # define C_POINTER_TYPE           (0x09000000 | C_SPECIALBLOCK_BIT)
    # define C_LOCATIVE_TYPE          (0x0a000000 | C_SPECIALBLOCK_BIT)
    # define C_TAGGED_POINTER_TYPE    (0x0b000000 | C_SPECIALBLOCK_BIT)
    # define C_SWIG_POINTER_TYPE      (0x0c000000 | C_SPECIALBLOCK_BIT)
    # define C_LAMBDA_INFO_TYPE       (0x0d000000 | C_BYTEBLOCK_BIT)
    /*       unused                   (0x0e000000 ...) */
    # define C_BUCKET_TYPE            (0x0f000000)
#endif


/* Hooray for dynamic stack allocation */
#ifdef HAVE_ALLOCA_H
    #include <alloca.h>
#elif !defined(alloca)
    #error "Must have alloca support"
#endif

// Save 16K to prevent buffer overflows
#define AX_STACK_RESERVE 0x10000
#define AX_setjmp(a)     setjmp(a)
#define AX_alloca(n)     alloca(n)
#define AX_stack_pointer ((Word*)AX_alloca(0))

/* Global Variables */
Word* Stack_Limit;
unsigned int stack_size;
unsigned int stack_bottom;
jmp_buf restart_point;
Bool return_to_host;

//Word ax_run(void* toplevel)
//{
//    // Configure the stack size and pointers
//#if C_STACK_GROWS_DOWNWARD
//    Stack_Limit = (Word*)((Byte*)AX_stack_pointer - stack_size);
//#else
//    Stack_Limit = (Word*)((Byte*)AX_stack_pointer + stack_size);
//#endif
//    stack_bottom = AX_stack_pointer;
//
//    // Make note of our start point
//    AX_setjmp(restart_point);
//
//    // If we end up back here then check whether we restart or not
//    //if(!return_to_host)
//    //    (C_restart_trampoline)(C_restart_address);
//}

int main(int argc, char** argv)
{
    // Configure the stack size and pointers
#if C_STACK_GROWS_DOWNWARD
    Stack_Limit = (Word*)((Byte*)AX_stack_pointer - stack_size);
#else
    Stack_Limit = (Word*)((Byte*)AX_stack_pointer + stack_size);
#endif
    stack_bottom = AX_stack_pointer;

    while(1)
    {
        printf("%d\n", alloca(4));
    }
}
