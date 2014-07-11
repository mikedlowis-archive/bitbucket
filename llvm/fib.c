//#include <stdio.h>

int count(int x, int n)
{
    if( x == n )
    {
        return x;
    }
    else
    {
        return count( x+1, n );
    }
}

int main(int argc, char** argv)
{
    int ret = 0;
    if( 2 == argc )
    {
        printf( "%d\n", count( 0, atoi( argv[1] ) ) );
    }
    else
    {
        printf( "Usage: %s <n>\n", argv[0] );
        ret = 1;
    }
    return ret;
}
