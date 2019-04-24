#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<string.h>
int m,n;
int *avail;
int *max;
int *alloc;
int *need;
int *seq;
bool *check;
void input();
bool safestate();
void request();
void swap(int ind);
int fac(int f);
int main()
{
	printf("Enter No of Processes : ");
	scanf("%d",&m);
	printf("Enter No of Resources : ");
	scanf("%d",&n);
	avail=(int*)malloc(n*sizeof(int));
	max=(int*)malloc(m*n*sizeof(int));
	alloc=(int*)malloc(m*n*sizeof(int));
	need=(int*)malloc(m*n*sizeof(int));
	seq=(int*)malloc(m*sizeof(int));
	check=(bool*)malloc(n*sizeof(bool));
	int i=0;
	for(i=0;i<m;i++){
		*(seq + i)=i;
		printf("%d ",*(seq + i));
	}
	for(i=0;i<n;i++)
		*(check + i)=false;
	input();
	printf("\n\n");
	bool val=safestate();
	if(val==true)
	{
		printf("\t\tSystem is in Safe State\n\tSafe Sequence: ");
		for(int i=0;i<m;i++)
			printf("P%d --> ",*(seq + i));
	}
	else
		printf("\t\tSystem is not in Safe State\n\n");
}

void input()
{
	int *res=(int*)malloc(n*sizeof(int));
	int *tot=(int*)malloc(n*sizeof(int));
	int i=0,j=0;
	for(i=0;i<n;i++)
	{
		printf("\nEnter Total Number of Instances for Resource %c: ",(char)i+65);
		scanf("%d",(res + i));
	}
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("\nEnter Maximum Number of Instances of Resource %c For Process P%d: ",(char)j+65,i);
			scanf("%d",(max + i*m + j));
		}
		for(j=0;j<n;j++)
		{
			printf("\nEnter Allocated Number of Instances of Resource %c For Process P%d: ",(char)j+65,i);
			scanf("%d",(alloc + i*m + j));
			*(tot + j)+=*(alloc + i*m + j);
			*(need + i*m + j)=*(max + i*m + j)-*(alloc + i*m + j);
			//printf("%d ",*(need + i*m + j));
		}
	}
	system("clear");
	printf("\t\tDisplaying Details Entered In Tabular Format\n");
	printf("Processes\t\tAllocated\tMaximum\t\tNeed\t\tAvailable\n");
	//printf("\t\t\tA B C\t\tA B C\t\tA B C\t\tA B C");
	for(i=0;i<m;i++)
	{
		printf("\nP%d\t\t\t",i);
		for(j=0;j<n;j++)
		{
			printf("%d ",*(alloc + i*m + j));
		}
		printf("\t\t");
		for(j=0;j<n;j++)
		{
			printf("%d ",*(max + i*m + j));
		}
		printf("\t\t");
		for(j=0;j<n;j++)
		{
			printf("%d ",*(need + i*m + j));
		}
		if(i==0)
		{
			printf("\t\t");
			for(j=0;j<n;j++)
			{
				*(avail + j)=(*(res + j))-(*(tot + j));
				printf("%d ",*(avail + j));
			}
		}
	}
}

void swap(int ind)
{
	int temp=*(seq + ind);
	for(int i=ind;i<m-1;i++)
	{
		*(seq + i)=*(seq + (i+1));
	}
	*(seq + (m-1))=temp;
}

int fac(int f)
{
	int val=1;
	for(int i=2;i<=f;i++)
		val*=i;
	return val;
}

bool safestate()
{
	int *wrk=(int*)malloc(n*sizeof(int));
	int *maxt=(int*)malloc(m*n*sizeof(int));
	int *alloct=(int*)malloc(m*n*sizeof(int));
	int *needt=(int*)malloc(m*n*sizeof(int));
	memcpy(wrk,avail,sizeof(avail));
	memcpy(maxt,max,sizeof(max));
	memcpy(alloct,alloc,sizeof(alloc));
	memcpy(needt,need,sizeof(need));
	
	int i=0,flag=1,x=0,c,lc=0;
	while(lc<fac(m-i))
	{
		for(x=0;x<m;x++)
		{
			if(*(check + *(seq + x))==true)
				c=1;
			else
			{
				c=0;
				break;
			}
		}
			
		if(c==1)
		{
			flag=0;
			break;
		}
		if(*(check + *(seq + i))==false)
				c=1;
		if(c==1)
		{
			for(x=0;x<m;x++)
			{
				if(*(needt+ (*(seq + i))*m + x)<=*(wrk + *(seq + x)))
					c=1;
				else
				{
					c=0;
					break;
				}
			}
		}
			
		if(c==1)
		{
			
			*(check + *(seq + x))=true;
			/*for(x=0;x<m;x++)
			{
				*(wrk + *(seq + x))-=*(needt+ (*(seq + i))*m + x);
			}*/
			for(x=0;x<m;x++)
			{
				*(wrk + *(seq + x))+=*(alloct+ (*(seq + i))*m + x);
			}
			for(x=0;x<m;x++)
			{
				*(alloct+ (*(seq + x))*m + x)=*(needt+ (*(seq + i))*m + x);
			}
			i+=1;
			lc=0;
			printf("P%d --> ",*(seq + i));
			if(i+1==m)
			{
				flag=0;
				break;
			}
			
		}
		else
		{
			if(i!=m-1)
				swap(i);
			lc+=1;
		}
	}
	if(flag==0)
		return true;
	else if(flag==1)
		return false;
}
			
			
			
	


		
		
