/*
   Floyd-Warshall Algorithm
   Purpose : To determine Shortest Paths between nodes in O(V^3) time complexity
                  Path Reconstruction is a MUST -- After all, we must know what path to take ;)  

   Usage : ./a.out filename source_node dest_node num_processors
   
   Sample Input     :   ravi@ubuntu:~/Desktop$ ./a.out data100 1 9 4
   Sample Output  :   Shortest Distance : 30 
                               Shortest Path     : 1 71 58 9 
                               Time   : 018111
*/

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <sys/time.h>
#include <omp.h>

using namespace std;

// MACROS

#define MAXS 500         // Maximum no of nodes -- Dynamism is unnecessary overhead for input specified
#define H_VAL 50000                                   // in problem statement !!

// SUMMARY
/*
   SPEEDUP  ~=    2.18        for 100x100 dataset
   TIME        ~=    19 ms      ( with path reconstruction )  
                 ~=     10 ms      ( no path reconstuction )
*/


// ANALYSIS
/*
No of nodes       --    10            20            50           100
Parallel             --   144          430          4484       18980       ( in microseconds)
Sequential         --   174          610          7982       41378           
Speedup            --   1.21        1.42          1.78        2.18

  The variation is "non-linear" as the "data level parallelism" varies with size of input,
thus improving speedup.

  The speedup effect is more profound as graph size increases, but obviously tends to
"saturate" to 3 or 4 depending on the number of cores used ! Beyond a point, synchronising
them will itself be a big overhead. 

 So, I should expect a resonable speedup of 4 for large input sets like 10000*10000 etc. 
*/

// MAJOR OPTIMIZATIONS :
/* 
  1) EXPANDED ARRAY REFERENCING and used a 1-D array for all conceptually 2-D matrices 
  2) Works for Any datatype as main type mat_t is TYPEDEFINED
  3) Displayed the path too using PATH RECONSTRUCTION matrix
  4) Code can parse files of any size ( no need to specify NO OF NODES)
  5) Parallelization using OpenMP done
  6) Flexible code using MACROS 
  7) INPUT VALIDATION performed to avoid Seg Faults 
  8) REGISTER INT used for loop iterators of FLOYD-WARSHALL code
*/ 



//SPEEDUP
/*
ravi@ubuntu:~/Desktop/Now$ ./a.out data10 3 9 2                       // DUAL CORE MACHINE
Shortest Distance : 31                                                           
Shortest Path     : 3 4 9  
Time   : 000144                                                                       
ravi@ubuntu:~/Desktop/Now$ ./a.out data20 3 9 2
Shortest Distance : 29 
Shortest Path     : 3 0 9 
Time   : 000430
ravi@ubuntu:~/Desktop/Now$ ./a.out data50 3 9 2
Shortest Distance : 56 
Shortest Path     : 3 38 7 9 
Time   : 004484
ravi@ubuntu:~/Desktop/Now$ ./a.out data100 3 9 2
Shortest Distance : 24 
Shortest Path     : 3 81 71 58 9 
Time   : 018980


ravi@ubuntu:~/Desktop/Now$ ./a.out data10 3 9 1
Shortest Distance : 31 
Shortest Path     : 3 4 9 
Time   : 000174
ravi@ubuntu:~/Desktop/Now$ ./a.out data20 3 9 2
Shortest Distance : 29 
Shortest Path     : 3 0 9 
Time   : 000610
ravi@ubuntu:~/Desktop/Now$ ./a.out data50 3 9 1
Shortest Distance : 56 
Shortest Path     : 3 38 7 9 
Time   : 007982
ravi@ubuntu:~/Desktop/Now$ ./a.out data100 3 9 1
Shortest Distance : 24 
Shortest Path     : 3 81 71 58 9 
Time   : 041378

*/


// OUTPUT (3,9)        ----------  WITH PATH RECONSTRUCTION
/*
 ravi@ubuntu:~/Desktop/Now$ ./a.out data10 3 9
         Shortest Distance : 31 
         Shortest path : 3 4 9 
ravi@ubuntu:~/Desktop/Now$ ./a.out data20 3 9
         Shortest Distance : 29 
         Shortest path : 3 0 9 
ravi@ubuntu:~/Desktop/Now$ ./a.out data50 3 9
         Shortest Distance : 56 
         Shortest path : 3 38 7 9 
ravi@ubuntu:~/Desktop/Now$ ./a.out data100 3 9
         Shortest Distance : 24 
         Shortest path : 3 81 71 58 9 
*/

  

typedef int mat_t;

// Floyd-Warshall algorithm

mat_t  c_mat[MAXS*MAXS],dist_mat[MAXS*MAXS],pred_mat[MAXS*MAXS];
int  n1,n2,p;

/*
  Purpose : To determine Shortest Paths between nodes in O(V^3) time complexity
  Logic     : Simply update d[i][j] if d[i][k]+d[k][j]<d[i][j] for some k (Basic)
  
  nn - number of nodes in graph
  n1 - source node
  n2 - dest    node
 
  c_mat - connection matrix  ( 0 -- disconnected )
  dist_mat - distance matrix
  pred_mat - predecessor matrix ( for path reconstruction)
*/

void fwarsh(int nn,int n1,int n2,int p)
{
  register int i,j,k;

  //setenv OMP_NESTED TRUE -- not needed
  #pragma omp omp_set_num_threads=p;                     // change num_threads as available !!         

  if(n1==n2)
  {
   printf("Shortest Path : %d\n",n1);
   return;
  }

  // Initializing Distance Matrix 
  #pragma omp parallel for                               
  for (i=0; i < nn; i++) {
    #pragma omp parallel for                                
    for (j=0; j < nn; j++){
      if (c_mat[i*nn+j] != 0)
	      dist_mat[i*nn+j] = c_mat[i*nn+j];
      else
	      dist_mat[i*nn+j] = H_VAL; // Disconnected is approximated by  MACRO H_VAL

      if (i==j)  // Diagonal
      	dist_mat[i*nn+j] = 0;

      if ((dist_mat[i*nn + j] > 0) && (dist_mat[i*nn+j] < H_VAL))
	      pred_mat[i*nn+j] = i;
    }
  }
 
  // Core part of the algorithm
  #pragma omp parallel for                                
  for (k=0; k < nn; k++) {
    #pragma omp parallel for                                
    for (i=0; i < nn; i++) {
      #pragma omp parallel for                                 
      for (j=0; j < nn; j++){
	    if (dist_mat[i*nn+j] > (dist_mat[i*nn+k] + dist_mat[k*nn+j])){
	     dist_mat[i*nn+j] = dist_mat[i*nn+k] + dist_mat[k*nn+j];
	     pred_mat[i*nn+j] = k; 
	    }
     }
    }
  }

  //Display  the results table of shortest distances
  /*for (i=0; i < nn; i++){
    for (j=0; j < nn; j++)
      printf("%d ", dist_mat[i*nn+j]);
    printf("\n");
  } 
  */
 //Display the intermediate nodes 
 /* for (i=0; i < nn; i++){
    for (j=0; j < nn; j++)
      printf("%d ", pred_mat[i*nn+j]);
    printf("\n");
  }
  */
  //printf("Nodes : %d %d\n",n1,n2);
 
  // Reconstructing Shortest Path  
  printf("Shortest Distance : %d \n",dist_mat[n1*nn+n2]);

  printf("Shortest Path     : ");
  printf("%d ",n1);
  while(pred_mat[n1*nn+n2]!=n1)
  {
    n1=pred_mat[n1*nn+n2]; 
    printf("%d ",n1);
  } 
  printf("%d \n",n2);

} 

int main(int argc,char* argv[])
{
 FILE* fp;
 struct timeval t1,t2;
 long int i,j;
 int k; char c;
 
 if(argc!=5)
 {
  printf("Usage : ./a.out filename source_node dest_node num_processors\n");
  return 0;
 }
 fp=fopen(argv[1],"r");
 if(fp==NULL)
 {
  printf("File not opened..\n");
  return 0;
 }
 
 k=0; 
 while(fscanf(fp,"%d%c",&c_mat[k++],&c)!=EOF);
 k=(int)sqrt((double)(k+1));
 //printf("Size : %d",k);

 n1=atoi(argv[2]);
 n2=atoi(argv[3]);
 p=atoi(argv[4]);
  

 if(n1<0 || n2<0 || n1>=k || n2>=k)                         // SIMPLE VALIDATION -- saves lot of Seg Faults ;)
 {
  printf("Invalid Nodes passed :)\n");
  return 0;
 }

 gettimeofday(&t1,NULL);                                                                     // timestamp in microseconds
 fwarsh(k,n1,n2,p); 
 gettimeofday(&t2,NULL);
 
 i=t1.tv_usec;
 j=t2.tv_usec;
 printf("Time   : %.6ld\n",j-i);

 fclose(fp);
 return 0;
}
