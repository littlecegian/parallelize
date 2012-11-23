/*

levenshtein distance has been used to find the closest match as said
The levenshtein distance is found out using a algorithm that uses dynamic programming method.
Hence parallelising it is important since all the threads become dependent in a way that cannot be solved 
so, the algorithm is left untouched


Compilation mpicc filename.c
Run         mpirun -np (no of processes) ./a.out

Example output has been attached four 4 threads and 8 threads as seperate files and correspondingly the individual speed up and total speed up has been found out and is in speedup.ods . I did it for 16 threads also . All the three results wer around 2.6-2.8.
However 16 threads has not been added since it is all reduntant and makes the submission cumbersome.

 speed up for 4 threads is 
 
 system configuration :
 3GB RAM core 2 duo processor @ 1.83GHz.
 
 
 OPTIMISATIONS MADE :
1. input has been scanned directly from files instead of reading and parsing them.
2. Use of dup instead of fscanf gave me an additional saving over time
3. use of register integers inside for loops
4. Integer and floating point declarations has been arranged to see if they cud fit into a block , thereby reducing cache-memory 	accesses. sadly it dint seem to be much of an advantage. (Hope the declarations ought to be substantial to feel the 		difference )
5. Memory reference to the array of strings has been reduced using temporary strings.
6. All loop and iteration variables has been named with single alphabets ( not an optimisation. the point is made for ur 		understanding of the code ).

7. use of macros		

Observation      :  Too much data dependency prevents substantial parallelisation
  
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <fcntl.h>
#define STR 20
int leve(char *s,char*t);
int minimum(int a,int b,int c);
int leve(char *s,char*t)
{
  
  int k,i,j,n,m,cost,*d,distance;
  n=strlen(s); 
  m=strlen(t);
  if(n!=0&&m!=0)
  {
    d=malloc((sizeof(int))*(m+1)*(n+1));
    m++;
    n++;
    for(k=0;k<n;k++)
	d[k]=k;
    for(k=0;k<m;k++)
      d[k*n]=k;
    for(i=1;i<n;i++)
      for(j=1;j<m;j++)
	{
        if(s[i-1]==t[j-1])
          cost=0;
        else
          cost=1;
        d[j*n+i]=minimum(d[(j-1)*n+i]+1,d[j*n+i-1]+1,d[(j-1)*n+i-1]+cost);
      }
    distance=d[n*m-1];
    free(d);
    return distance;
  }
  else 
    return -1; 
}

int minimum(int a,int b,int c)
{
  int min=a;
  if(b<min)
    min=b;
  if(c<min)
    min=c;
  return min;
}
int main(int argc ,char *argv[])
{
long int tim[100],st,en;
int np,k,n,fd,flg=0,iter=0,i=0,leve_dist=0,threshtemp=0,low,high;
int suggestion=0,suggtemp=0,j=0;
int input_file_iter=0,dest,tag=1,source;
int sendbuf,recvbuf,suggestiter[100],flag[100];
float threshold=0.0;
char input[100][STR];
char word[STR];
char wordlist[5000][STR];
char ch[STR];
int rank;
float chunk;
char suggest[100][10][STR];  // a maximum of 100 input words with 10 suggestions each
struct timeval start,end;
recvbuf=0;
MPI_Status stat;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &np);
/*printf("%d",leve("programmer","procuctmmer"));
scanf("%s",ch);*/
fd=open("words.txt",2);
if(fd==-1)
	{
	printf("file doesnt exist\n");
	exit(0);
	}
close(0);
dup2(fd,0);
while(scanf("%s",wordlist[iter++])!=-1);
iter--;
close(fd);
fd=open("input.txt",2);
if(fd==-1)
	{
	printf("file doesnt exist\n");
	exit(0);
	}
close(0);
dup2(fd,0);
scanf("%f",&threshold);
scanf("%d",&suggestion);
threshold/=100;
while(scanf("%s",input[input_file_iter++])!=-1);
sendbuf=input_file_iter-1;

close(fd);
if(rank==0)
{
printf("send size is %d",sendbuf);
for(dest=1 ; dest<np ; dest++)
   MPI_Send(&sendbuf, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
   chunk=1.0*sendbuf/np;
 //  printf("chunk is %f",chunk);
   
   low=0;
   high=chunk;
 //  printf("low %d high %d \n",low,high);
for(j=low;j<high;j++)
	{
	flg=0;
	suggtemp=0;
	threshtemp=threshold*strlen(input[j])+1;	
	gettimeofday(&start,NULL);                                                   
	for(i=0;i<iter;i++)
		{
		leve_dist=leve(input[j],wordlist[i]);
		//printf("word is  %s worlist %s is leve is %d\n",input[j],wordlist[i],leve_dist);
			if(leve_dist<threshtemp)
			    {
			     if(suggtemp>=suggestion)
			       break; 
			          if(leve_dist==0)
				     {
					flg=1;                       
       					break;
				     }   
         			strcpy(suggest[j][suggtemp++],wordlist[i]);       
     				
    				}	
		}
	  gettimeofday(&end,NULL);                                                                 
	  st=start.tv_usec;
	  en=end.tv_usec;
  	  tim[j]=en-st; 
 
	suggestiter[j]=suggtemp;
	flag[j]=flg;
	
	}

}
else
{
MPI_Recv(&recvbuf, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &stat);
//printf("recvd %d in rank %d\n",recvbuf,rank);
chunk=1.0*recvbuf/np;
//printf("chunk is %f of %d \n",chunk,rank);
low=rank*chunk;
high=(rank+1)*chunk;
printf("low %d high %d \n",low,high);
if(low>=input_file_iter-1)
low=input_file_iter-1;
if(high>=input_file_iter-1)
high=input_file_iter-1;

//printf("low %d high %d \n",low,high);
}

for(j=low;j<high;j++)
	{
	flg=0;
	suggtemp=0;
	threshtemp=threshold*strlen(input[j])+1;	
		gettimeofday(&start,NULL);
	for(i=0;i<iter;i++)
		{
		leve_dist=leve(input[j],wordlist[i]);
		//printf("word is  %s worlist %s is leve is %d\n",input[j],wordlist[i],leve_dist);
			if(leve_dist<threshtemp)
			    {
			     if(suggtemp>=suggestion)
			       break; 
			          if(leve_dist==0)
				     {
					flg=1;                       
       					break;
				     }   
         			strcpy(suggest[j][suggtemp++],wordlist[i]);       
     				
    				}	
		}
	  gettimeofday(&end,NULL);                                                                 
	  st=start.tv_usec;
	  en=end.tv_usec;
  	  tim[j]=en-st; 
 
	suggestiter[j]=suggtemp;
	flag[j]=flg;
	
	}


for(i=low;i<high;i++)
{
printf("%s : \n",input[i]);
if(flag[i]==1)
printf(" word is correct \n ");
else
	{
	printf("word is incorrect \n");
	printf("suggestions are :  ");
	n=suggestiter[i];
	for(j=0;j<n;j++)
	printf("%s  ",suggest[i][j]);
	printf("\n");
	}
printf("\n");
}
for(i=low;i<high;i++)
{
		printf("process time of %s is %ld \n",input[i],tim[i]);	
}
MPI_Finalize();
return 0;
}


