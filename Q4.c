#include <stdio.h>
#include <stdlib.h>
#include<time.h>
		
int main()
{
	int a, b, n, c, d, m;
	srand((unsigned) time(NULL));
	a = 1 + rand() % 6;	/* Result is defined from random and then summed */
	b = 1 + rand() % 6;
	n = a + b;
	printf("First number is: %d\n",n);
	
	if ((n==7)||(n==11))				/* System of 'if' Checks */
		printf("Player wins!\n");
	else if ((n==2)||(n==3)||(n==12))
		printf("Player loses!\n");
	else{
		printf("Player rolls again:\n");	/* Doesnt fufill criteria */
		do 									/* Reroll until Point */
		{
			c = (1 +rand() % 6);
			d = (1 + rand()% 6);
			m = c + d;
			printf("Roll: %d\n", m);
			if (m == 7)
			{
				printf("Player loses!\n");
				return 0;
			}
		}
		while (!(n==m));	/* Stop when point is made */
		printf("Player wins!\n");
		}
return 0;
}

