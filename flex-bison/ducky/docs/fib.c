#include <stdio.h>
int recursive_fib(int n)
{
	int ret = n;
	if(ret >= 2)
		ret = recursive_fib(n-1) + recursive_fib(n-2);
	return ret; 
}

int iterative_fib(int n)
{
	int first = 0;
	int second = 1;
	int tmp = 0;
	while(n--)
	{
		tmp = first + second;
		first = second;
		second = tmp;
	}
	return first;
}

int main(int argc, char** argv)
{
	printf("%d\n", recursive_fib(10));
	printf("%d\n", iterative_fib(10));
}
