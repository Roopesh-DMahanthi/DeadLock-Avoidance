
#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<string.h>
int m,n,qsn;
int *avail;
int *max;
int *alloc;
int *need;
int *seq;
int *wrk;
int *req;
int *ord;
int *prch;
int pr;
bool *check;
void input();
void input2();
bool safestate();
int request(int i1,int i2);
int main()
{
        printf("Question 1 or 2: ");
        scanf("%d",&qsn);
        if(qsn==1){
        printf("Enter No of Processes : ");
        scanf("%d",&m);
        printf("Enter No of Resources : ");
        scanf("%d",&n);
        }
        else
        {
                m=5;
                n=4;
        }
        avail=(int*)malloc(n*sizeof(int));
        max=(int*)malloc(m*n*sizeof(int));
        alloc=(int*)malloc(m*n*sizeof(int));
        need=(int*)malloc(m*n*sizeof(int));
        seq=(int*)malloc(m*sizeof(int));
        check=(bool*)malloc(n*sizeof(bool));
        wrk=(int*)malloc(n*sizeof(int));
        int i=0;
        /*for(i=0;i<m;i++){
                *(seq + i)=i;
                printf("%d ",*(seq + i));
        }*/
        for(i=0;i<n;i++){
                *(check + i)=false;
        }
        if(qsn==2)
                input2();
        input();
        printf("\n\n");
        bool val=safestate();
        if(val==true)
        {
                printf("\t\tSystem is in Safe State\n\tSafe Sequence: ");
                for(int i=0;i<m-1;i++)
                        printf("P%d --> ",*(seq + i));
                printf("P%d\n",*(seq + m-1));
        }
        else
                printf("\t\tSystem is not in Safe State\n\n");
        printf("\n\n");
	int temp;
	printf("Continue with Resource Requesting?(Yes-1/No-0): ");
	scanf("%d",&temp);
	if(temp==1){
	printf("Enter Number of Processes requesting resources: ");
	scanf("%d",&pr);
	ord=(int*)malloc(pr*sizeof(int));
	prch=(int*)malloc(pr*sizeof(int));
	for(i=0;i<pr;i++)
	{
		printf("Enter Process number requesting resources: ");
		scanf("%d",(ord + i));
		*(prch + i)=0;
	}
	req=(int*)malloc(pr*n*sizeof(int));
	for(i=0;i<pr;i++)
        {
		for(int j=0;j<n;j++){
		        printf("\nEnter Requested Instances for Resource %c: of P%d: ",(char)j+65,*(ord + i));
		        scanf("%d",(req + pr*i + j));
		}
        }
	int l=0;
	i=0;
	
	while(l<pr)
	{
		if(i>=pr)
			i=0;
		if(*(prch + i)==-2 || *(prch + i)==-1)
		{
			i++;
			continue;
		}
		int val=request(i,*(ord + i));
		printf("\ni=%d,val=%d\n",i,val);
		if(val==0)
		{
			printf("\nRequest for P%d cannot be Processed since exceeded Maximum Claim.... Continuing with other Requests..\n",i);
			*(prch + i)=-1;
			l++;
		}
		else if(val==1)
		{
			printf("\nRequest for P%d cannot be Processed with Available Resources....Request carried to later processing.... Continuing with other Requests..\n",i);
			*(prch + i)+=1;
		}
		else
		{
			printf("\nRequest for P%d is Successfully Processed and System in Safe State....\n",i);
			printf("\t\tSystem is in Safe State\n\tSafe Sequence: ");
		        for(int j=0;i<m-1;j++)
		                printf("P%d --> ",*(seq + j));
		        printf("P%d\nContinuing with other Requests",*(seq + m-1));
			*(prch + i)=-2;
			l++;
		}
		if(*(prch + i)>=pr-l)
		{
			printf("Requests cannot be processed for all remaining Processes....");
			l=pr+1;
		}
		i++;
	}
	}
}
void input2()
{
        *(max+0)=0;
        *(max+1)=0;
        *(max+2)=1;
        *(max+3)=2;
        *(max+1*m+0)=1;
        *(max+1*m+1)=7;
        *(max+1*m+2)=5;
        *(max+1*m+3)=0;
        *(max+2*m+0)=2;
        *(max+2*m+1)=3;
        *(max+2*m+2)=5;
        *(max+2*m+3)=6;
        *(max+3*m+0)=0;
        *(max+3*m+1)=6;
        *(max+3*m+2)=5;
        *(max+3*m+3)=2;
        *(max+4*m+0)=0;
        *(max+4*m+1)=6;
        *(max+4*m+2)=5;
        *(max+4*m+3)=6;
        *(alloc+0)=0;
        *(alloc+1)=0;
        *(alloc+2)=1;
        *(alloc+3)=2;
        *(alloc+1*m+0)=1;
        *(alloc+1*m+1)=0;
        *(alloc+1*m+2)=0;
        *(alloc+1*m+3)=0;
        *(alloc+2*m+0)=1;
        *(alloc+2*m+1)=3;
        *(alloc+2*m+2)=5;
        *(alloc+2*m+3)=4;
        *(alloc+3*m+0)=0;
        *(alloc+3*m+1)=6;
        *(alloc+3*m+2)=3;
        *(alloc+3*m+3)=2;
        *(alloc+4*m+0)=0;
        *(alloc+4*m+1)=0;
        *(alloc+4*m+2)=1;
        *(alloc+4*m+3)=4;
        for(int i=0;i<m;i++)
        {
                for(int j=0;j<n;j++)
                {
                        *(need + i*m + j)=*(max + i*m + j)-*(alloc + i*m + j);
                }
        }
}

void input()
{
        int *res=(int*)malloc(n*sizeof(int));
        int *tot=(int*)malloc(n*sizeof(int));
        int i=0,j=0;
        if(qsn==1){
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
                }
        }
        }
        else{
        *(res+0)=3;
        *(res+1)=14;
        *(res+2)=12;
        *(res+3)=12;
        for(int i=0;i<m;i++)
        {
                for(int j=0;j<n;j++)
                {
                        *(tot + j)+=*(alloc + i*m + j);
                }
        }
        }
        system("clear");
        printf("\t\tDisplaying Details Entered In Tabular Format\n");
        printf("\nEnter Total Number of Instances:\n");
        for(i=0;i<n;i++)
        {
                printf("%c = ",(char)i+65);
                printf("%d\n",*(res + i));
        }
        if(n>=4)
                printf("\n\nProcesses\t\tAllocated\t\tMaximum\t\t\tNeed\t\t\tAvailable\n\t\t\t");
        else
                printf("\n\nProcesses\t\tAllocated\tMaximum\t\tNeed\t\tAvailable\n\t\t\t");
        for(j=0;j<4;j++){
        for(i=0;i<n;i++)
        {
                printf("%c ",(char)i+65);
        }
        printf("\t\t");
        }
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
				*(wrk + j)=*(avail + j);
				printf("%d ",*(avail + j));
			}
		}
	}
}

bool safestate()
{       
        int i=0,flag=1,x=0,c=0,lc=0,ct=0,cc=0;

        while(flag==1)
        {
                c=0;
                if(i>=m){
                         i=0;
                        continue;
                }
                if(lc==m)
                {
                        flag=0;
                        break;
                }
                if(*(check + i)==false)
                                c=1;
                else{
                        i++;
                        continue;
                }
                if(c==1)
                {
                        for(x=0;x<n;x++)
                        {
                                if(*(need+ i*m + x)<=*(wrk + x))
                                        c=1;
                                else
                                {
                                        c=2;
                                        x=m+1;
                                }
                        }
                }

                if(c==1)
                {
                        cc=0;
                        *(check + i)=true;
                        for(x=0;x<n;x++)
                        {
                                *(wrk + x)+=*(alloc+ i*m + x);
                                //printf("%d ",*(wrk + x));
                        } 
                        *(seq + lc)=i;
                        //printf("\nP%d -->",i);
                        lc++;
                        i++;
                        if(i>=m)
                                i=0;
                        continue;


                }
                i+=1;
                //printf("c=%d,cc=%d,i=%d",c,cc,i-1);
                if(c==0 || c==2)
                        cc++;
                if(cc==m-lc)
                        break;
                
        }
        if(flag==0)
                return true;
        else if(flag==1)
                return false;
}

int request(int i1,int i2)
{

	int fl=0,i=0;
	for(i=0;i<n;i++)
        {
		if(*(req + pr*i1 +  i)<=*(need + m*i2 + i))
			fl=1;
		else{
			fl=0;
			break;
		}
        }
	if(fl==0)
		return 0;
	else
	{
		for(i=0;i<n;i++)
        	{
			if(*(req + pr*i1 + i)<=*(avail + m*i2 +  i))
				fl=1;
			else{
				fl=0;
				break;
			}
        	}
		if(fl==0)
			return 1;
		else
		{	
			int *oavail=(int*)malloc(n*sizeof(int));
			int *oalloc=(int*)malloc(n*sizeof(int));
			int *oneed=(int*)malloc(n*sizeof(int));
			for(i=0;i<n;i++)
			{
				*(oavail + i)=*(avail + m*i2 +  i);
				*(avail + m*i2 +  i)-=*(req + pr*i1 +  i);
				*(oalloc + i)=*(alloc + m*i2 +  i);
				*(alloc + m*i2 +  i)+=*(req + pr*i1 +  i);
				*(oneed + i)=*(need + m*i2 +  i);
				*(need + m*i2 +  i)-=*(req + pr*i1 +  i);
			}
			if(safestate()==true)
				return 2;
			else
			{
				for(i=0;i<n;i++)
				{
					*(avail + m*i2 +  i)=*(oavail + i);
					*(alloc + m*i2 +  i)=*(oalloc + i);
					*(need + m*i2 +  i)=*(oneed + i);
					return 3;
				}
			}
		}
	}
}


