#include<stdio.h>
#include<curses.h>
#include<string.h>

int avail[3]={0};
int max[3][3]={0};
int alloc[3][3]={0};
int need[3][3]={0};
int seq[3]={0,1,2};
bool check[3]={false,false,false};
void input();
bool safestate();
void request();
void swap(int ind);

int main()
{
	input();
	printf("\n\n");
	bool val=safestate();
	if(val==true)
	{
		printf("\t\tSystem is in Safe State\n\tSafe Sequence: ");
		printf("P%d --> P%d --> P%d\n",seq[0],seq[1],seq[2]);
	}
	else
		printf("\t\tSystem is not in Safe State\n\n");
}

void input()
{
	int res[3]={0},tot[3]={0};
	int i=0,j=0;
	for(i=0;i<3;i++)
	{
		printf("\nEnter Total Number of Instances for Resource %c: ",(char)i+65);
		scanf("%d",&res[i]);
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			printf("\nEnter Maximum Number of Instances of Resource %c For Process P%d: ",(char)j+65,i);
			scanf("%d",&max[i][j]);
		}
		for(j=0;j<3;j++)
		{
			printf("\nEnter Allocated Number of Instances of Resource %c For Process P%d: ",(char)j+65,i);
			scanf("%d",&alloc[i][j]);
			tot[j]+=alloc[i][j];
			need[i][j]=max[i][j]-alloc[i][j];
		}
	}
	system("clear");
	printf("\t\tDisplaying Details Entered In Tabular Format\n");
	printf("Processes\t\tAllocated\tMaximum\t\tNeed\t\tAvailable\n");
	printf("\t\t\tA B C\t\tA B C\t\tA B C\t\tA B C");
	for(i=0;i<3;i++)
	{
		printf("\nP%d\t\t\t",i);
		for(j=0;j<3;j++)
		{
			printf("%d ",alloc[i][j]);
		}
		printf("\t\t");
		for(j=0;j<3;j++)
		{
			printf("%d ",max[i][j]);
		}
		printf("\t\t");
		for(j=0;j<3;j++)
		{
			printf("%d ",need[i][j]);
		}
		if(i==0)
		{
			printf("\t\t");
			for(j=0;j<3;j++)
			{
				avail[j]=res[j]-tot[j];
				printf("%d ",avail[j]);
			}
		}
	}
}

void swap(int ind)
{
	int temp=seq[ind];
	for(int i=ind;i<2;i++)
	{
		seq[i]=seq[i+1];
	}
	seq[2]=temp;
}

bool safestate()
{
	/*int wrk[3]=(int[])avail.Clone();
	int maxt[3][3]=(int[][])max.Clone();
	int alloc[3][3]=(int[][])alloc.Clone();
	int needt[3][3]=(int[][])need.Clone();*/
	int wrk[3]={0};
	int maxt[3][3]={0};
	int alloct[3][3]={0};
	int needt[3][3]={0};
	/*clone1(&avail,&wrk);
	clone2(&max,&maxt);
	clone2(&alloc,&alloct);
	clone2(&need,&needt);*/
	memcpy(wrk,avail,sizeof(avail));
	memcpy(maxt,max,sizeof(max));
	memcpy(alloct,alloc,sizeof(alloc));
	memcpy(needt,need,sizeof(need));
	int i=0,flag=1;
	while(flag==1)
	{
		if(check[0]==true && check[1]==true && check[2]==true)
		{
			flag=0;
			break;
		}
		if(check[seq[i]]==false && needt[seq[i]][0]<=wrk[0] && needt[seq[i]][1]<=wrk[1] && needt[seq[i]][2]<=wrk[2])
		{
			check[seq[i]]=true;
			wrk[0]-=needt[seq[i]][0];
			wrk[1]-=needt[seq[i]][1];
			wrk[2]-=needt[seq[i]][2];
			wrk[0]+=alloct[seq[i]][0];
			wrk[1]+=alloct[seq[i]][1];
			wrk[2]+=alloct[seq[i]][2];
			alloct[seq[i]][0]=needt[seq[i]][0];
			alloct[seq[i]][1]=needt[seq[i]][1];
			alloct[seq[i]][2]=needt[seq[i]][2];
			i+=1;
		}
		else if(i==2)
		{
			flag=2;
			break;
		}
		else
			swap(i);
	}
	if(flag==0)
		return true;
	else if(flag==2)
		return false;
}
	


			
			
			
	


		
		
