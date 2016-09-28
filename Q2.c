#include <stdio.h>
#include <math.h>
#define SIZE 10

int main()
{
	float a[SIZE]={27.5,13.4,53.8,29.2,74.5,87.0,39.9,47.7,8.1,63.2};
	float d[SIZE];
	float x, sum = 0.0, std, z = 0.0;
	int i;
	for (i=0; i<SIZE; i++)  /* Sum of the array */
		sum += a[i];
	x = (sum / SIZE);		/* Mean of the array */
	
	printf("Sum of values is: %f\n\n", sum);
	printf("Mean value is: %f\n\n", x);
	for (i=0; i<SIZE; i++)
	{
		d[i] = a[i] - x;   /* How far is the number from the mean */
		printf("Deviation of %f from mean = %f\n", a[i], d[i]);
	}
	
	printf("\n");
	
	for (i = 0; i < SIZE; i++)
		z += pow(d[i], 2);
	z = z/SIZE;   /* Sum of the deviations squared divided by the size of array */
	
	std = sqrt(z);
	
	printf("Standard Deviation:  %f\n", std);
		
	return 0;
}

