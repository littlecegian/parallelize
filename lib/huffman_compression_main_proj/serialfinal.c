#include<stdio.h>
#include<string.h>#include<stdlib.h>
#include<fcntl.h>
#include<math.h>
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
	//printf("hi ");
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
    //a=malloc(z*sizeof(struct link));
    for (i = 0; i < n - 1; i++)
	for (j = 0; j < i; j++)
            
	   if (a[i]->freq < a[j]->freq)
	    {
                   //printf("%d %d ",i,j);
           	//printf("%f  %f %d %d\n",a[i]->freq,a[j]->freq,i,j);
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
    node *ptr,*head;
    int i, n,no, total = 0,count,counter,count1,c[30],l,m,output[100],freq1[256]={0};
    float u;
    char str[MAX],input[MAX],temp[1000];
    node* a[MAX];
    float freq;
    printf(  "Huffman Algorithm\n");
    int fin=open(argv[1],O_RDONLY);
    i=0;
    int ls=lseek(fin,0,2);
     char cf[ls];
      bzero(&cf,ls);
      bzero(&freq1,256);
      lseek(fin,0,0);
      printf("\n String:");      int rd=read(fin,cf,ls);
	printf("read no of bytes %d \n"   ,rd);
  cf[rd]='\0';
      int j;
    for(i=0;i<rd;i++)
   {
      j=cf[i];
      freq1[j]++;
   }
                
for(i=0;i<256;i++)
{
	if(freq1[i])
	printf("freq of %c is %d \n",i,freq1[i]);
}

       for(i=0;i<256;i++)
      {
           if(freq1[i]>0)
         {
               		//printf("%d ",i);
           temp[0]=i;
           temp[1]='\0';
	   a[z++] = create(temp, (float)freq1[i]/ls);
        }
    }
     n=z;
     no=z;
printf(" z is %d\n",z);

    while(n > 1)
    {//exit(1);
	sort(a,n);
	//exit(1);
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
   int byte[100000];
   int boolptr=0;
   int f=open("out.txt",O_RDWR);
   unlink(f);
   int fout=open("out.txt",O_RDWR|O_TRUNC|O_CREAT,0666);
    struct code * c1 = Assign_Code(a[0], c, 0);   
printf("si is %d \n",si);

     for(i=0;i<si;i++)
      {
            printf("%d:",c1[i].ch[0]);
              for(j=0;j<c1[i].len;j++)
                 printf("%d",c1[i].codeword[j]);
                  printf("\n");
      }


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
//exit(1);
//snippet to print the bit string that represents the entire file
i=4-boolptr%4;
for(j=boolptr+1;j<i;j++)
byte[j]=0;
boolptr+=i;


/*
for(i=0;i<boolptr;i++)
printf("%d",byte[i]);
*/
char hex[6]={'A','B','C','D','E','F'};
char val[100000];
int eightfourtwoone[4]={8,4,2,1};
int cnt=0;
int valptr=0;
j=0;
for(i=0;i<=boolptr;i++,cnt++)
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
/*
printf("hi boolptr %d\n",boolptr);for(i=0;i<valptr;i++)
printf("%c",val[i]);
*/
int wr=write(fout,val,valptr);
printf("\n%d bytes written 2 file",wr);
close(fout);
close(fin);
fflush(stdin);
fflush(stdout);

int fd=open("out.txt",O_RDWR);
int newls= lseek(fd,0,2);
lseek(fin,0,0);
char valback[newls];
int newrd= read(fd,valback,newls);
//printf("%s",valback);
close(fd);

return 1;
}
