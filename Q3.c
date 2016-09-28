#include <stdio.h>
#include <math.h>

int main()
{
	int i, j, A[6][8], X[8]={1,-8,3,-6,5,-4,7,-2}, Y[6];
	printf("Array A is: \n");
	for (i = 0; i < 6; ++i) /* Loading Array A with pattern */
		{
			for (j = 0; j < 8; ++j)
			{
				A[i][j] = i+j+1;
				printf ("%d	", A[i][j]); /* print array A to terminal */
			}
			printf("\n");
		}
	printf("Array X is:\n");
	for (i =0; i < 8; ++i) /* print array X to terminal */
		printf("%d \n", X[i]);
		
	printf("Array Y is:\n");
	for (i = 0; i < 6; ++i)
		{
		Y[i]=0;
		for (j = 0; j < 8; ++j)
			Y[i] += (A[i][j] * X[j]); /* Sum of the result to fill Array Y */ 
		printf("%d\n",Y[i]); /* Print to terminal */
		}
	return 0;
}
			

