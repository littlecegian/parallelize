/*
  Algorithm to find kth smallest number in an array
  Input : array,k
  Output : kth smallest number in array
  array is genearated randomly 

  To Run - ./a.out  size k
               where, 
               size = size of random input data
               k = kth smallest number
      
Running time for  array size = 100000 and k value declining
ravi@ubuntu:~$ cc -fopenmp indexsort.c
ravi@ubuntu:~$ time ./a.out 100000 60000
 kth element is 47800
real	0m0.045s
ravi@ubuntu:~$ time ./a.out 100000 40000
 kth element is 13385 
real	0m0.041s
ravi@ubuntu:~$ time ./a.out 100000 10000
 kth element is 8384
real	0m0.031s

 Running time declining array size
 
 ravi@ubuntu:~$ time ./a.out 100000 6000
 kth element is 59524
real	0m0.022s
user	0m0.020s
sys	0m0.000s
ravi@ubuntu:~$ time ./a.out 10000 6000
 kth element is 4533
real	0m0.005s
user	0m0.004s
sys	0m0.000s
ravi@ubuntu:~$ time ./a.out 1000 600
 kth element is 438
real	0m0.003s
user	0m0.004s
sys	0m0.000s


Note - Repetition of values are taken care of. So, beyond a limit kth smallest value will not be found . In that case user is alerted 

      
                                        */ 
#include<stdio.h>
#include<stdlib.h>
//#include<omp.h>
int main(int argc,char *argv[])
{
int *a;
char x;
int s;
int i,k,iter[2]={0,0},ind;
if(argc<=1)
printf("enter k\n");
k=atoi(argv[2]);
s=atoi(argv[1]);
a=(int *)malloc(sizeof(int)*s);
int ii=0;
int tid;
int flag=0;

#pragma omp parallel num_threads(2)  private(ind) shared(a,k,i,flag,ii) 
{
#pragma omp for schedule(static,s/2)
for(i=0;i<s;i++)
	{
	ind=rand()%s;
	a[ind]=1;
	}
//tid=omp_get_thread_num();
#pragma omp for
for(i=0;i<s;i++)
	{
		if(ii==k)
		{
		flag=1;
		printf(" kth element is %d",i);
		exit(1);
		}
	
	if(a[i])
	#pragma omp critical
		{
		ii++;	
		}
	}
	
}

if(flag==0)
printf("%d th smallest element not available ",k);

return 0;
}
