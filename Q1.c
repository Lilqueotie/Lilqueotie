#include <stdio.h>

int main()
{
	int n, k;
	printf("The primes between 1 and 100 are: \n");
	for (n= 2; n < 100; n++)
		{
			for (k = 2; k < n; k++)
			{
			if (n % k == 0) /* Check whether the number */
				break;	  	/* is divisible with no remainder*/  		
			}
			if (k == n)		/* if divisible and itself then prime */
				printf("%d ", n);
		}
	return 0;
}

