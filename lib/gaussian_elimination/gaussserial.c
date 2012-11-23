#include <stdio.h>
#include<stdlib.h>
int n;
float a[10][11];
void print()
{
int i,j;
for (i = 0; i < n; ++i) 
	{
		for (j = 0; j < n + 1; ++j)
			printf("%5.2f\t", a[i][j]);
		printf("\n");
	}
	printf("\n\n");
}
int main(int argc, char *argv[]) 
{
	int i, j,k,max;

	int fd=open("gauss.txt",2);
	struct timeval start ,end;
		gettimeofday( &end, NULL );
	close(0);
	dup2(fd,0);
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		for (j = 0; j < n + 1; j++)
			scanf("%f", &a[i][j]);
			
	close(fd);
	float t;
	for (i = 0; i < n; ++i)  // i loop for the column which we are making zero to progress 2wards echleon form
	{
		for (j = n; j >= i; --j)  //j loop to perform the operation for all the column pertaining to a row
		{	t=a[i][j]/a[i][i];
			for (k = i + 1; k < n; ++k) // to perform the op downwards towards the last row for each column
				{
				a[k][j] -= a[k][i]*t;
				}
		
	         }
	
        }	

	for (i = n - 1; i >= 0; --i) 
	{
		a[i][n] = a[i][n] / a[i][i]; //compute the var which is been brought to the form a[i][i]*var = a[i][n]
		a[i][i] = 1; 		     //	set the co-efficient of the variable as 1 
		for (j = i - 1; j >= 0; j--) 
		{
			a[j][n] -= a[j][i] * a[i][n]; // substitute all other variables that has been found till now and sub em
			a[j][i] = 0;                  // after subst and subtract replace the co-efficients with 0
		}
	}        
	print();
	gettimeofday( &end, NULL );
	unsigned long long micros = (end.tv_sec*1000000+end.tv_usec) - (start.tv_sec*1000000 +start.tv_usec );	
	printf("\nTime Taken:%lld micros\n",micros);

	return 0;
}


