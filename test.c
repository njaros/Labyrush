#include <sys/time.h>
#include <stdio.h>

int	main (void)
{
	short c = 0xf;

	c -= 1 << 4;
	printf("%c\n", c);
}
