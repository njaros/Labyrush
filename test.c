#include <sys/time.h>
#include <stdio.h>

int	rand(int seed, int range)
{
	printf("%d\n", seed % range);
	return (2);
}

int	main (void)
{
	struct timeval	t1;
	int				seed;
	int				range;
	int				i = 0;

	gettimeofday(&t1, NULL);
	seed = t1.tv_usec;
	range = 4;
	while (++i < 200)
	{
		if (seed / range == 0)
		{
			gettimeofday(&t1, NULL);
			seed = t1.tv_usec;
		}
		seed /= rand(seed, range);
	}
	return (0);
}
