#include <list>
#include <setjmp.h>
#include <stdio.h>

extern long* Stack_Bottom;
extern long* Return_Value;

class Continuation
{
    public:
        int n;
        long* stack;
        jmp_buf registers;
    public:
        Continuation() : n(0), stack(0) {}
        Continuation(long* pbos, long*ptos)
        {
            n = pbos-ptos;
            stack = new long[n];
            for (int i = 0; i<n; ++i) {
                stack[i] = pbos[-i];
            }
        }
        ~Continuation()
        {
            if(stack != 0) delete stack;
        }

        void operator () (long* ret_val)
        {
            Return_Value = ret_val;
            (*this)(false);
        }

        void operator () (bool once_more)
        {
            long padding[12];
            long tos;
            int i,n;
            if(stack != 0)
            {
                /*
                 * Make sure there's enough room on the stack
                 */
                if ( (Stack_Bottom - n) < (&tos) ) {
                    printf("Making room\n");
                    (*this)(true);
                    printf("Done making room\n");
                }

                if (once_more) {
                    printf("Calling one more time\n");
                    (*this)(false);
                    printf("done calling one more time\n");
                }

                /*
                 * Copy stack back out from continuation
                 */
                for (i = 0; i < n; ++i) {
                    printf("copying byte\n");
                    printf("%d\n",Stack_Bottom);
                    Stack_Bottom[i] = stack[i];
                    printf("done copying byte\n");
                }
            }
            printf("jumping back\n");
            longjmp(registers,1);
        }
};

long* Stack_Bottom = 0;
long* Return_Value = 0;
std::list<Continuation*> Continuations;

int save_context(Continuation* c)
{
    Continuations.push_back(c);
    return setjmp(c->registers);
}

void restore_context(long* ret_val)
{
    Continuation* c = Continuations.back();
    Continuations.pop_back();
    printf("Jumping back to main\n");
    (*c)(ret_val); // Call the continuation
    printf("Should not print\n");
}

#define CALL_CC(a) if(! save_context( new Continuation() ) ) { a; }
#define RETURN(a)  restore_context( (long*)a )

void max(int a,int b)
{
    printf("beginning of max\n");
    int* ret = new int;
    *ret = (a > b) ? a : b;
    printf("Before return\n");
    RETURN( ret );
    printf("This should never print\n");
}

int main(int argc, char** argv)
{
    long bottom;
    Stack_Bottom = &bottom;
    printf("%d\n", Stack_Bottom);
    printf("Calling max\n");
    CALL_CC( max(1,2); );
    printf("Done calling max\n");
    printf("%d\n",*Return_Value);
}
