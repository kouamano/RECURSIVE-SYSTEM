#include <stdio.h>

int fib(int n)
{
	switch (n) {
		case 0: return 0;
		case 1: return 1;
		default:
		return fib(n-1) + fib(n-2);
	}
}

int main()
{
	int n = 38;
	printf("%d",fib(n));
}
