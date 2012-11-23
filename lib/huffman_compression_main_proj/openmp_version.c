#include<omp.h>
#include<stdio.h>
#include<string.h>#include<stdlib.h>
#include<fcntl.h>
#include<math.h>
#define MAX 256 // for 256 ascii characters 
struct link
{
	    float freq;
	    char ch[MAX];
	    struct link* right;
	    struct link* left;
};                                    // structure for storing each node in huffman
struct code
{
	char ch[10];
	int len;
	int codeword[MAX];    //structure to store codewords for each letter
}codes[MAX];
typedef struct link node;
int si=0;
int z=0;
 node* create(char * a, float x)
{
    node* ptr;
    ptr = (node*)malloc(sizeof(node));
    ptr->freq = x;
    strcpy( ptr->ch , a);                  //creates a node with given string a and the corresponding frequency x
    ptr->right = ptr->left = NULL;         // assingns the node as  a leaf initially
    return(ptr);
}
  void sort(node ** a, int n) // function that sorts the array of nodes based on the frequency
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
   void sright(node ** a, int n)  //merges two  nodes into one , insert it into the nodelist and then sort and . shift right the structure once
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
	codes[si].len=n;                    // Recursive procedure call that assigns 1 to left node and 0 to right node.
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

    node *ptr,*head;
    int i, n,no, total = 0,count,counter,count1,c[30],l,m,output[100],freq1[256]={0};
    float u;
    char str[MAX],input[MAX],temp[1000];
    node* a[MAX];
    float freq;
    printf("Huffman Algorithm\n");
      int fin=open(argv[1],O_RDONLY);
       i=0;
      int ls=lseek(fin,0,2);
     char cf[ls];
      bzero(&cf,ls);
      bzero(&freq1,256);
      lseek(fin,0,0);
      int rd=read(fin,cf,ls);
      cf[rd]='\0';
      int j;
       #pragma omp parallel for shared(i,cf,freq1) private(j)
     for(i=0;i<rd;i++)
    {
      j=cf[i];
      freq1[j]++;                                                       //calculatng frequency from file
    }      
      #pragma omp parallel for 
       for(i=0;i<256;i++)
      {
           if(freq1[i]>0)
         {
           temp[0]=i;
           temp[1]='\0';
	   a[z++] = create(temp, (float)freq1[i]/ls);               //creatimng nodes for symbols having freq greater than 0
        }
    }
     n=z;
     no=z;
    while(n > 1)
    {
	sort(a,n);
	u = a[0]->freq + a[1]->freq;                                   //taking 2 elememnts and insert into tree after sorting all
	strcpy(str,a[0]->ch);                                             //elements and inserting the total freq into the array
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
   int byte[100000];
   int boolptr=0;
   int f=open("out.txt",O_RDWR);
   unlink(f);
   int fout=open("out1.txt",O_RDWR|O_TRUNC|O_CREAT,0666);
    struct code * c1 = Assign_Code(a[0], c, 0);                        //assigning codes
printf("si is %d \n",si);             
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
printf("no of bytes in the array 2 be encoded is %d \n:",boolptr);
i=4-boolptr%4;
for(j=boolptr+1;j<boolptr+i;j++)
byte[j]=0;                                                            //converted into bytes 
boolptr+=i;
char hex[6]={'A','B','C','D','E','F'};
char val[100000];
int eightfourtwoone[4]={8,4,2,1};
int cnt=0;
int valptr=0;
j=0;
 int chunk,st,end,tid,val1;
#pragma omp parallel shared(val)
{
tid=omp_get_thread_num();
val1=tid*boolptr/8;                                                      ///into hex
#pragma omp for private(cnt,j) lastprivate(val,valptr) 	 	
for(i=0;i<boolptr;i++)
{
if(cnt==4)
	{
	cnt=0;
	
	if(j<10)
	
	sprintf(&val[val1+valptr],"%d",j);
	else
		{
		j-=10;
		val[val1+valptr]=hex[j];
		}
	
	j=0;
        valptr++;
	}
if(byte[i])
j+=eightfourtwoone[i%4];
cnt++;
}
}
printf("hi boolptr %d\n",boolptr);
valptr=boolptr/4;for(i=0;i<valptr;i++)
printf("%c",val[i]);
printf("i is %d",valptr);                                    
return 1;
}
