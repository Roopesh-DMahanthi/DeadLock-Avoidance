
#include<stdio.h>
#include<stdlib.h>
#include<curses.h>
#include<string.h>
int m,n,qsn;
int *avail;
int **max;
int **alloc;
int **need;
int *seq;
int *wrk;
int **req;
int *ord;
int *prch;
int *res,*tot;
int *oavail;
int *oalloc;
int *oneed;
int pr;
bool *check;
void input();
void input2();
void disp();
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
        int i=0;
        
        max=(int**)calloc(m+1,sizeof(int));
        max[0] = (int *)calloc(n+1 , sizeof(int));
        for (i=1; i<=m; i++){ 
            max[i] = (int *)calloc(n+1 , sizeof(int));
	    for(int j=1;j<=n;j++)
	    {
		max[i][j]=i;
	    }
	} 
	
	alloc=(int**)calloc(m+1,sizeof(int));
	alloc[0] = (int *)calloc(n+1 , sizeof(int));
	for (i=1; i<=m; i++){ 
            alloc[i] = (int *)calloc(n+1 , sizeof(int));
		for(int j=1;j<=n;j++)
	    {
		alloc[i][j]=i;
		
	    } 
	} 
	
	need=(int**)calloc(m+1,sizeof(int));
	need[0] = (int *)calloc(n+1 , sizeof(int)); 
	for (i=1; i<=m; i++){ 
            need[i] = (int *)calloc(n+1 , sizeof(int)); 
		for(int j=1;j<=n;j++)
	    {
		need[i][j]=i;
		
	    } 
	
        }
	avail=(int*)calloc(n+1,sizeof(int));
	seq=(int*)calloc(m+1,sizeof(int));
        check=(bool*)calloc(n+1,sizeof(bool));
        wrk=(int*)calloc(n,sizeof(int));
        /*for(i=0;i<m;i++){
                *(seq + i)=i;
                printf("%d ",*(seq + i));
        }*/
        if(qsn==2)
                input2();
        input();
	disp();
        printf("\n\n");
        bool val=safestate();
        if(val==true)
        {
                printf("\t\tSystem is in Safe State\n\tSafe Sequence: ");
                for(int i=1;i<=m-1;i++)
                        printf("P%d --> ",seq[i]);
                printf("P%d\n",seq[m]);
        }
        else
                printf("\t\tSystem is not in Safe State\n\n");
	/*if(qsn==2)
		return 0;*/
        printf("\n\n");
	int temp;
	printf("Continue with Resource Requesting?(Yes-1/No-0): ");
	scanf("%d",&temp);
	if(temp==1){
	printf("Enter Number of Processes requesting resources: ");
	scanf("%d",&pr);
	ord=(int*)malloc(pr+1*sizeof(int));
	prch=(int*)malloc(pr+1*sizeof(int));
	for(i=1;i<=pr;i++)
	{
		printf("Enter Process number requesting resources: ");
		scanf("%d",&ord[i]);
		prch[i]=0;
	}
	req=(int**)calloc(pr+1,sizeof(int));
	req[0]=(int*)calloc(n+1,sizeof(int));
	for(i=1;i<=pr;i++)
        {
		req[i]=(int*)calloc(n+1,sizeof(int));
		for(int j=1;j<=n;j++){
		        printf("\nEnter Requested Instances for Resource %c: of P%d: ",(char)j+64,ord[i]);
		        scanf("%d",&req[i][j]);
		}
        }
	int l=0;
	i=1;
	oavail=(int*)calloc(n+1,sizeof(int));
	oalloc=(int*)calloc(n+1,sizeof(int));
	oneed=(int*)calloc(n+1,sizeof(int));
	printf("one\n");
	while(l<pr)
	{
      		if(i>pr)
			i=1;
		if(prch[i]==-2 || prch[i]==-1)
		{
			i++;
			continue;
		}
		printf("two\n%d %d\nthree",i,ord[i]);
		int val=request(i,ord[i]);
		//printf("\ni=%d,val=%d\n",i-1,val);
		if(val==0)
		{
			printf("\nRequest for P%d cannot be Processed since exceeded Maximum Claim.....\n",ord[i-1]);
			
			prch[i]=-1;
			l++;
		}
		else if(val==1)
		{
			printf("\nRequest for P%d cannot be Processed with Available Resources....Request carried to later processing....\n",ord[i-1]);
			prch[i]+=1;
		}
		else if(val==2)
		{
			disp();
			printf("\nRequest for P%d is Successfully Processed and System in Safe State....\n",i-1);
			printf("\t\tSystem is in Safe State\n\tNew Safe Sequence: ");
		        for(int j=1;j<=m-1;j++)
		                printf("P%d --> ",seq[j]);
			printf("P%d\n",seq[m]);
		        //printf("Continuing with other Requests");
			prch[i]=-2;
			l++;
		}
		else
		{
			printf("\nRequest for P%d is not Successfully Processed as System goes into Un-Safe State....\n",i-1);
			prch[i]=-2;
			l++;
		}
		if(prch[i]>pr-l)
		{
			printf("Requests cannot be processed for all remaining Processes....");
			l=pr+1;
		}
		else if(l<pr)
			printf("\nContinuing with other Requests....\n");
		i++;
	}
	printf("\nDone with Given Requests...\n");
	}
	int t;
	printf("Exit Process? (Yes -1/Return Main Menu - 0): ");
	scanf("%d",&t);
	system("clear");
	if(t==0)
		main();
}

void input2()
{
        max[1][1]=0;
        max[1][2]=0;
        max[1][3]=1;
        max[1][4]=2;
        max[2][1]=1;
        max[2][2]=7;
        max[2][3]=5;
        max[2][4]=0;
        max[3][1]=2;
        max[3][2]=3;
        max[3][3]=5;
        max[3][4]=6;
        max[4][1]=0;
        max[4][2]=6;
        max[4][3]=5;
        max[4][4]=2;
        max[5][1]=0;
        max[5][2]=6;
        max[5][3]=5;
        max[5][4]=6;
        alloc[1][1]=0;
        alloc[1][2]=0;
        alloc[1][3]=1;
        alloc[1][4]=2;
        alloc[2][1]=1;
        alloc[2][2]=0;
        alloc[2][3]=0;
        alloc[2][4]=0;
        alloc[3][1]=1;
        alloc[3][2]=3;
        alloc[3][3]=5;
        alloc[3][4]=4;
        alloc[4][1]=0;
        alloc[4][2]=6;
        alloc[4][3]=3;
        alloc[4][4]=2;
        alloc[5][1]=0;
        alloc[5][2]=0;
        alloc[5][3]=1;
        alloc[5][4]=4;
        for(int i=1;i<=m;i++)
        {
                for(int j=1;j<=n;j++)
                {
                        need[i][j]=max[i][j]-alloc[i][j];
                }
        }
}

void input()
{
        res=(int*)calloc(n+1,sizeof(int));
        tot=(int*)calloc(n+1,sizeof(int));
        int i=0,j=0;
        if(qsn==1){
        for(i=1;i<=n;i++)
        {
                printf("\nEnter Total Number of Instances for Resource %c: ",(char)i+64);
                scanf("%d",&res[i]);
        }
        for(i=1;i<=m;i++)
        {
                for(j=1;j<=n;j++)
                {
                        printf("\nEnter Maximum Number of Instances of Resource %c For Process P%d: ",(char)j+64,i-1);
                        scanf("%d",&max[i][j]);
                }
                for(j=1;j<=n;j++)
                {
                        printf("\nEnter Allocated Number of Instances of Resource %c For Process P%d: ",(char)j+64,i-1);
                        scanf("%d",&alloc[i][j]);
			printf("\t%d %d\n",alloc[0][0],need[0][0]);
                        tot[j]+=alloc[i][j];
                        need[i][j]=max[i][j]-alloc[i][j];
			printf("\t%d %d\n",alloc[0][0],need[0][0]);
                }
        }
        }
	else{
        res[1]=3;
        res[2]=14;
        res[3]=12;
        res[4]=12;
        for(int i=1;i<=m;i++)
        {
                for(int j=1;j<=n;j++)
                {
                        tot[j]+=alloc[i][j];
                }
        }
        }
	for(j=1;j<=n;j++)
	{
		avail[j]=res[j]-tot[j];
		printf("%d ",avail[j]);
	}
        //printf("%d %d\n%d %d",&alloc[0][0],&need[0][0],&max[4][0],&alloc[4][0]);
        
}

void disp()
{
	int i,j;
	system("clear");
        printf("\t\tDisplaying Details Entered In Tabular Format\n");
        printf("\nEnter Total Number of Instances:\n");
        for(i=1;i<=n;i++)
        {
                printf("%c = ",(char)i+64);
                printf("%d\n",res[i]);
        }
        if(n>=4)
                printf("\n\nProcesses\t\tAllocated\t\tMaximum\t\t\tNeed\t\t\tAvailable\n\t\t\t");
        else
                printf("\n\nProcesses\t\tAllocated\tMaximum\t\tNeed\t\tAvailable\n\t\t\t");
        for(j=1;j<=4;j++){
        for(i=1;i<=n;i++)
        {
                printf("%c ",(char)i+64);
        }
        printf("\t\t");
        }
        for(i=1;i<=m;i++)
        {
                printf("\nP%d\t\t\t",i-1);
                for(j=1;j<=n;j++)
                {
                        printf("%d ",alloc[i][j]);
                }
                printf("\t\t");
                for(j=1;j<=n;j++)
                {
                        printf("%d ",max[i][j]);
                }
                printf("\t\t");
                for(j=1;j<=n;j++)
                {
                        printf("%d ",need[i][j]);
                }
                if(i==1)
                {
			printf("\t\t");
			for(j=1;j<=n;j++)
			{
				//avail[j]=res[j]-tot[j];
				//wrk[j]=avail[j];
				printf("%d ",avail[j]);
			}
		}
	}

}

bool safestate()
{       
        int i=1,flag=1,x=0,c=0,lc=1,ct=0,cc=0;
	for(i=1;i<=n;i++){
                check[i]=false;
		wrk[i]=avail[i];
        }
	/*for(i=1;i<=n;i++)
	{
				printf("(%d)",i);
				printf("%d %d %d\n",avail[i],alloc[2][i],need[2][i]);
	}*/
	i=1;
        while(flag==1)
        {
		           
                if(i>m){
                         i=1;
                        continue;
                }
                if(lc>=m+1)
                {
                        flag=0;
                        break;
                }
                if(check[i]==false)
                                c=1;
                else{
			c=0;
                        //continue;
                }
                if(c==1)
                {
                        for(x=1;x<=n;x++)
                        {
                                if(need[i][x]<=wrk[x])
                                        c=1;
                                else
                                {
                                        c=0;
                                        x=m+1;
                                }
                        }
                }
		//printf("i:%d,lc:%d,c:%d,cc:%d--",i,lc,c,cc);     
                if(c==1)
                {
                        check[i]=true;
                        for(x=1;x<=n;x++)
                        {
                                wrk[x]+=alloc[i][x];
                                //printf("%d ",*(wrk + x));
                        } 
                        seq[lc]=i-1;
                        printf("\nP%d -->",i-1);
                        lc++;
                        i++;
                        /*if(i>m)
                                i=1;
                        continue;*/


                }
		else{
			cc++;
			c=0;
                i+=1;
		}
                //printf("c=%d,cc=%d,i=%d",c,cc,i-1);
                if(cc>=m)
                        break;
                
        }
        if(flag==0)
                return true;
        else if(flag==1)
                return false;
}

int request(int i1,int i2)
{
	printf("i2=%d\n",i2);
	i2++;
	printf("i2=%d\n",i2);
	int fl=0,i=0;
	
	for(i=1;i<=n;i++)
        {
		if(req[i1][i]<=need[i2][i]){
			fl=1;
		}
		else{
			fl=0;
			printf("i1:%d i2:%d i:%d need:%d\n",i1,i2,i,need[i2][i]);
			break;
		}
        }
	printf("fl:%d",fl);
	if(fl==0)
		return 0;
	else
	{
		for(i=1;i<=n;i++)
        	{
			if(req[i1][i]<=avail[i]){
				fl=1;
			}
			else{
				fl=0;
				break;
			}
        	}
		if(fl==0)
			return 1;
		else
		{	
			printf("test\n");
			for(i=1;i<=n;i++)
			{
				printf("(%d)",i);
				oavail[i]=avail[i];
				avail[i]-=req[i1][i];
				oalloc[i]=alloc[i2][i];
				alloc[i2][i]+=req[i1][i];
				oneed[i]=need[i2][i];
				need[i2][i]-=req[i1][i];
				printf("%d %d %d\n",avail[i],alloc[i2][i],need[i2][i]);
			}
			bool val;
			val=safestate();
			if(val==true){
				return 2;
			}
			else
			{
				for(i=1;i<=n;i++)
				{
					avail[i]=oavail[i];
					alloc[i2][i]=oalloc[i];
					need[i2][i]=oneed[i];
					
				}
				return 3;
			}
		}
	}
}


