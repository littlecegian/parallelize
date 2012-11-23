#include<stdio.h>
#include<string.h>#include<stdlib.h>
#include<fcntl.h>
#include<math.h>
#include<mpi.h>
#define MAX 256
struct link
{
	    float freq;
	    char ch[MAX];
	    struct link* right;
	    struct link* left;
};
struct code
{
	char ch[10];
	int len;
	int codeword[MAX];
}codes[MAX];
typedef struct link node;
int si=0;
int z=0;
 node* create(char * a, float x)
{
    node* ptr;
    ptr = (node*)malloc(sizeof(node));
    ptr->freq = x;
    strcpy( ptr->ch , a);
    ptr->right = ptr->left = NULL;
    return(ptr);
}
  void sort(node ** a, int n)
{
    int i, j;
    node * temp;
    for (i = 0; i < n - 1; i++)
	for (j = 0; j < i; j++)
            
	   if (a[i]->freq < a[j]->freq)
	    {
        	temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	   }
}
   void sright(node ** a, int n)
{
    int i;

    for (i = 1; i < n - 1; i++)
	a[i] = a[i + 1];

}
struct code * Assign_Code(node* tree, int * c, int n)
{
    int i;    
    if ((tree->left == NULL) && (tree->right == NULL))
    {
	for (i = 0; i < n; i++)
	{
	    codes[si].codeword[i]=c[i];
	}
	codes[si].len=n;
	strcpy(codes[si].ch,tree->ch);
	si++;
    }
    else
    {
	c[n] = 1;
	n++;
	Assign_Code(tree->left, c, n);
	      c[n - 1] = 0;
	Assign_Code(tree->right, c, n);
    }
  return codes;
}

 char  temp1[2];
 char * tochar(int m)
{
 
  if(m==0)
   temp1[0]='0';
 else
   temp1[0]='1';

   temp1[1]='\0';
return temp1;
  
}
 int main(int argc,char * argv[])
{
	char hex[6]={'A','B','C','D','E','F'};
	int eightfourtwoone[4]={8,4,2,1};
	int cnt=0;
	int valptr=0;
	int boolptr=0;
	char val1[100000];
	char val[100000];
	int chunk;
	int z4;
    int rank,size,rd,ls,rd1,rd2;
    char cf[100000],kf[100000];
     int i, n,no, total = 0,count,counter,count1,c[30],l,m,output[100],freq1[256]={0},fin,j,freq2[256];
         float u;
    char str[MAX],input[MAX],temp[1000];
    node* a[MAX];
    float freq;
    int hex1;

    
     int dest,fout;
  int k1[1000000];
  int byte[100000];
    node *ptr,*head;
    MPI_Status stat;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
 
         if(rank == 0)                               ///getting from file and split the file and send to all processors
   {
     fin=open(argv[1],O_RDONLY);
      i=0;
      ls=lseek(fin,0,2);
      bzero(&cf,ls);
      lseek(fin,0,0);      rd=read(fin,cf,ls);
      rd1=rd/size;
      
         for(dest=1;dest<size;dest++)
       MPI_Send(&rd1,1,MPI_INT,dest,1,MPI_COMM_WORLD);
    for(dest=1;dest<size;dest++)
      MPI_Send(&cf[dest*rd1],rd/size,MPI_CHAR,dest,1,MPI_COMM_WORLD);    
     	 for(i=0;i<rd1;i++)
     	 {	
     	 	j=cf[i];
     		freq2[j]++;
     	}
     hex1=rd-(rd%size);
     for(i=hex1;i<rd;i++)
	{
		j=cf[i];
		freq2[j]++;
		}
     
       }
     else
   { 
          MPI_Recv(&rd2,1,MPI_INT,0,1,MPI_COMM_WORLD,&stat);
          MPI_Recv(&kf,rd2,MPI_CHAR,0,1,MPI_COMM_WORLD,&stat);   //getting the number of elements and the elements
     for(i=0;i<rd2;i++)
     {
     	j=kf[i];
     	freq2[j]++;
     }
            	       
   }
 MPI_Reduce(&freq2,&freq1,256,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);         //reducing the freq from individuall thrreads into       

if(!rank)
{
     for(i=0;i<256;i++)
      {
           if(freq1[i]>0)
         {
           temp[0]=i;
           temp[1]='\0';
	   a[z++] = create(temp, (float)freq1[i]/ls);
        }
    }
     n=z;
     no=z;

    while(n > 1)
    {
	sort(a,n);
	u = a[0]->freq + a[1]->freq;
	strcpy(str,a[0]->ch);
	strcat(str,a[1]->ch);
	ptr = create(str, u);
	ptr->right = a[1];
	ptr->left = a[0];
	a[0] = ptr;
	sright(a, n);
	n--;
    }

   int u1=0,k,r; 	 				 	
   char ctemp;
   int k2=0,z1[ls];
   
   
   int f=open("out.txt",O_RDWR);
   unlink(f);
   int fout=open("out.txt",O_RDWR|O_TRUNC|O_CREAT,0666);
    struct code * c1 = Assign_Code(a[0], c, 0);   
         for(i=0;i<ls;i++,k2++)
       {
		ctemp=cf[i];
            for(j=0;j<si;j++)
           {  
              if(c1[j].ch[0] == ctemp )
             {
                   r=c1[j].len;
                     for(u1=0;u1<c1[j].len;u1++)
                   {
                       
                 byte[boolptr++]=c1[j].codeword[u1];            
                      
                    }    
		
                    break;

              }
       	    }
       }
//snippet to print the bit string that represents the entire file
i=4-boolptr%4;
for(j=boolptr+1;j<i;j++)
byte[j]=0;
boolptr+=i;

 
 
 z4=boolptr/size;
 
for(dest=1;dest<size;dest++)
{
 j=dest*boolptr/size;
 
 MPI_Send(&z4,1,MPI_INT,dest,1,MPI_COMM_WORLD);
 MPI_Send(&byte[j],z4,MPI_INT,dest,1,MPI_COMM_WORLD);                         //sending th byte stream binary values to all 
                                                                              //processors and changing into hex in all
}
j=0;
for(i=0;i<=z4;i++,cnt++)
{
if(cnt==4)
	{
	cnt=0;
	if(j<10)
	sprintf(&val[valptr++],"%d",j);
	else
		{
		j-=10;
		val[valptr++]=hex[j];
		}
	j=0;
	}
if(byte[i])
j+=eightfourtwoone[i%4];

}
   for(dest=1;dest<size;dest++)
   {
   chunk=z4/4;
   j=dest*chunk;
   MPI_Recv(&val[j],chunk,MPI_CHAR,dest,1,MPI_COMM_WORLD,&stat);                      //receiving all hex values from all proc
   }
}
 else 
 {
  
  MPI_Recv(&z4,1,MPI_INT,0,1,MPI_COMM_WORLD,&stat);
   MPI_Recv(&k1,z4,MPI_INT,0,1,MPI_COMM_WORLD,&stat);

  char hex[6]={'A','B','C','D','E','F'};
  char val[100000];
  int eightfourtwoone[4]={8,4,2,1};
  int cnt=0;
  int valptr=0;
  j=0;
  for(i=0;i<=z4;i++,cnt++)
{
  if(cnt==4)
	{
	cnt=0;
	if(j<10)
	sprintf(&val1[valptr++],"%d",j);
	else
		{
		j-=10;
		val1[valptr++]=hex[j];
		}
	j=0;
	}
    if(k1[i])
j+=eightfourtwoone[i%4];

}
   MPI_Send(&val1,valptr,MPI_CHAR,0,1,MPI_COMM_WORLD);
}
if(!rank)
{
 printf("Compresseda file \n");
 j=boolptr/4;
 for(i=0;i<j;i++)
  printf("%c",val[i]);
}
 
MPI_Finalize();
       
return 0;
}
