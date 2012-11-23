/*
GAUSSIAN ELIMINATION :

gaussian elimination involves two steps 
1. Forward substitution
2. Reverse Elimination

Forward  substitution aims @ bringing down the matrix 2 echleon form 
echleon form is one in which all elements below the lead diagonal is made 2 be zero 
This is done by elementry row operations 
R2= R2-constant1 * R1
R3= R3-constant2 * R1
R3= R3-constant3 * R2
the constant is chosen such a way that first element of R2 ,first and second of R3  are made zero .

2 Reverse Elimination

   This is process of finding the elements from the echleon form.
   The last row is taken first which is of the form z * co-eff = constant
   Hence z is found  which is substituted is other rows so that now the row immediately above is of the form y * co-eff=constant
   the process is carried up towards til the first row.
   The resultant matrix carries 1 in diagonal and the values corresponding to the unknown in the last column
   
   
 Techiques Used :
 
 1. Root node assigns each row to  a process  starting from 1 . The process is bound to work on tat row only with respect to 		different references .
 2. At first the row 0 is sent using which as a reference other processes brings their x value 2 zero
    .The matrix is updated @ root. Then second row is sent as a ref to rows below second.The process continues
 3. Simple send and recieve was sufficient  but dynamically deciding the number of sends and recieves was taken care of by the 	   process id's. That is why it is insisted that  no of processes and no of unknowns be same . it may not work otherwise
 OPTIMISATION MADE :
 
 1. Input file has been read from the file using system calls dup instead of  parsing through buffer or fscanf.
 2. factor is computed for each row so that number of memory references reduces
 3. Use of Register Variables
 4. Variable declarations has been done in order of memory they take up. This is done so as to decrease cache latency
 
 
 Example input :
 2  1 -1  8
-3 -1  2 -11
-2  1  2 -3

 
 expected output for the given input
 1.00	 0.00	 0.00	 2.00	
 0.00	 1.00	 0.00	 3.00	
 0.00	 0.00	 1.00	-1.00	

USAGE :
mpicc filename.c
mpirun -np 3 ./a.out

System Config:
Core 2 duo @ 1.83 Ghz


TIME FACTOR :

*/


#include <stdio.h>
#include<stdlib.h>
#include<mpi.h>
int n;
float a[10][11];
float ref[11];
float local[11];
void print() // print the array
{
int i,j; //local variables
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
	register int j, k,temp; //iteration variables
	int i;
	int *refvar; // reference variable used to send row by row value to processes
	int rank,np,tag=1,source,dest,no,nor,limit;
	struct timeval start, end;
	gettimeofday( &start, NULL );
	
	MPI_Status stat;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	int fd=open("gauss.txt",2);
	close(0);
	dup2(fd,0);
	scanf("%d", &n);
	if(n!=np)
	{
	printf("------------- Error----------------->\n Number of processs must match number of unknown variables\n Number of process %d \n Number of unknowns %d \n",np,n);
	goto exitline; // to make sure all processes invokes MPI_Finalize();
	}
	temp=n+1;
	for (i = 0; i < n; i++) 
		for (j = 0; j < n + 1; j++)
			scanf("%f", &a[i][j]);
	close(fd);
	int cnt,loc;
	if(rank==0)
	{
	float getback[11];
	int iter3=0;
	for(dest=1;dest<n;dest++)
	{
		refvar=&a[dest][0];
		MPI_Send(refvar,temp,MPI_FLOAT,dest,tag,MPI_COMM_WORLD);
	}

	for(i=0;i<n-1;i++)
	{
	//printf("\n\niteration number is %d \n checkin pass value 2 b corect",i+1);
	refvar=&a[i][0];
	for(dest=i+1;dest<n;dest++)
		{
		MPI_Send(&i,1,MPI_INT,dest,tag,MPI_COMM_WORLD);
		MPI_Send(refvar,temp,MPI_FLOAT,dest,tag,MPI_COMM_WORLD);
		}
	for(dest=i;dest<n-1;dest++)
		{	
		MPI_Recv(&getback,n+1,MPI_FLOAT,dest+1,tag,MPI_COMM_WORLD,&stat);
/*		printf("getback in sender \n");
		for(iter3=0;iter3<n+1;iter3++) // printing the received updated  value
		printf("%f ",getback[iter3]);*/
		for(iter3=0;iter3<n+1;iter3++)
		a[dest+1][iter3]=getback[iter3];
		}
		
		/*printf("print is goin 2 b called \n");
		print();*/
	}
	}
	else
	{
	int iter=0,iter1=0;
	MPI_Recv(&local,temp,MPI_FLOAT,0,tag,MPI_COMM_WORLD,&stat);
	/*printf("local in rank %d \n",rank);
	for(iter=0;iter<temp;iter++)
	printf("%f ",local[iter]); */
	iter=0;
	for(iter1=0;iter1<rank;iter1++)
	{
	//printf("iter and rank is %d and %d \n",iter1,rank);
	MPI_Recv(&loc,1,MPI_INT,0,tag,MPI_COMM_WORLD,&stat);
	//printf("loc  in rank %d is  %d \n",rank,loc);
	MPI_Recv(&ref,temp,MPI_FLOAT,0,tag,MPI_COMM_WORLD,&stat);
	j=rank;
	//for(iter1=0;iter1<n;iter1++)
	//printf("ref in rank %d \n",rank);
	/*for(iter=0;iter<temp;iter++)
	printf("%f ",ref[iter]); 
	printf("\n");
	*/
	float factor=local[loc]/ref[loc]; // the factor with which each elememt of local array is modified
	//printf("the factor is %f \n",factor);
	for (k=loc;k<4;k++) // to perform the op downwards towards the last row for each column
		{
		local[k]=local[k]-factor*ref[k];
		}
	//printf("after first iter \n");
	/*for(iter=0;iter<n+1;iter++)
	printf("%f ",local[iter]); */
	iter=0;
	printf("\n");
	MPI_Send(&local,n+1,MPI_FLOAT,0,tag,MPI_COMM_WORLD);
	//printf("%d row update sent .waitin for next row \n",iter+1);
	}
		
	}

if(rank==0)
{
		 
/* REVERSE ELIMINATION - this part of the code has not been parallelised because of the data level dependency which is a tedious process . for eg only when thread 3 computes z , thread 1  and thread 0 can compute y only after which thread 0 can compute x. Although it is possible to compute partial values @ each step which means every thread ll not be idle , but the problem is @most only one computation can be done in each thread for which doing a send and recieve is utter waste of processing power as far as i perceive. Hence i jus let the master alone do the reverse elimination */
	
	for (i = n - 1; i >= 0; --i) 
	{
	a[i][n] = a[i][n] / a[i][i]; //compute the var of the form a[i][i]*var = a[i][n] ie.,all other coeff's has been handled
	a[i][i] = 1; 		     //	set the co-efficient of the variable as 1 
	for (j = i - 1; j >= 0; j--) 
		{
		a[j][n] -= a[j][i] * a[i][n]; // substi all other variables that has been found till now & sub em 4m the constant
		a[j][i] = 0;                  // after subst and subtract replace the co-efficients with 0
		}
	}
print();
gettimeofday( &end, NULL );
unsigned long long micros = (end.tv_sec*1000000+end.tv_usec) - (start.tv_sec*1000000 +start.tv_usec );	
printf("\nTime Taken:%lld micros \n",micros);
}
exitline:
MPI_Finalize();
return 0;
}


