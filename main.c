#include <stdio.h>

int test(int a, int b);

int main(void)
{
	int c;
	c = test(1, 3);
	printf("c: %d\n", c);
	return 0;
}
