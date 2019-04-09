#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
int size;
int val=0;
sem_t s;
pthread_mutex_t m;
pthread_mutex_t m1;
struct customer
{
	int *c_id;
	int *time;
};
struct barber
{
	int state;
}ptr2;
void mainfunc();
void *working1(void *args2);
void *sleep11(void *args1);
void *sleeping(void *args3);

void *check(void *args)
{
	pthread_t slept;
	int i;
	pthread_mutex_lock(&m);
	struct customer *ptr1=args;
	for(i=0;i<3;i++)
	{
		if(ptr1->c_id[i]!=0)
		{
			ptr2.state=1;
			break;	
		}
		if(ptr1->c_id[0]==ptr1->c_id[1]==ptr1->c_id[2]==0)
		{
			ptr2.state=0;
			goto j2;
		}
	}
	j2:	
		pthread_create(&slept,NULL,sleep11 ,NULL);
		pthread_join(slept,NULL);
	pthread_mutex_unlock(&m);
//	return 0;
}
void *sleep11(void *args1)
{
    	ptr2.state=0;
}
void *sleeping(void *args3)
{
	int i,a;
	printf("Enter 1 for new customer:\n");
	printf("\nBarber Sleeping: \n");
	pthread_mutex_lock(&m1);
	for(i=0;i<100;i++)
	{
		scanf("%d",&a);
		if(a==1)
		{
			goto j3;
		}
		sleep(i-(i-2));
	}
	j3:
		main();
	pthread_mutex_unlock(&m1);
	
}
void *working1(void *args2)
{
	int i,sum,a;
	pthread_t slept12;
	struct customer *ptr1=args2;
	ptr2.state=1;
	sem_wait(&s);
		printf("To Continue Press 0 and to go back Press1:\n");
		for(i=0;i<3;i++)
		{
			if(ptr1->c_id[i]!=0)
			{
			printf("Barber Teaching -->Stdudent ID :%d  for  %d seconds...\n",ptr1->c_id[i],ptr1->time[i]);
			sleep(ptr1->time[i]);
			scanf("%d",&a);
			if(a==1)
			{
				//mainfunc();
			}
			}
		}
		
	sem_post(&s);
		pthread_create(&slept12,NULL,sleeping ,NULL);
		pthread_join(slept12,NULL);
		
		
}
	int *chairs()
	{
		int *ptr;
		printf("Enter the number of chairs\n");
		scanf("%d",&size);
		ptr=&size;
		val++;
		return ptr;
	}
	
int main()
{
	int i,loop=0,var,time1=0,temp=0,remove,*temp1;
	pthread_t request,work;
	sem_init(&s,1,1);
	struct customer ptr1;

	while(val==0)
	{
		temp1=chairs();
	}
	int queue[*temp1];
	//struct barber ptr2;
	for(i=0;i<3;i++)
	{
		ptr1.c_id[i]=0;
		ptr1.time[i]=0;
	}

	void mainfunc()
	{
	
	while(loop==0)
	{
	printf("\nPlease ENTER The Following choices:\n");
	printf("1. ADD a new customer\n");
	printf("2. REMOVE an old customer\n");
	printf("3. DISPLAY current scenario\n");
	printf("4. EXIT\n");
	scanf("%d",&var);
	switch(var)
	{
		case 1:
			printf("\nEnter the ID of customer\n");
			scanf("%d",&temp);
			printf("Enter the time taken by customer in seconds\n");
			scanf("%d",&time1);
			for(i=0;i<3;i++)
			{
				if(queue[i]!=1)
				{
					queue[i]=1;
					goto j1;
				}
				else
				{
					printf("Chair %d id occupied\n",i);
				}
			}
			printf("\nSORRY WAIT FOR SOME TIME\n");
			break;
			j1:
			printf("\nThanks for your entry\n");
			ptr1.c_id[i]=temp;
			ptr1.time[i]=time1;
			pthread_create(&request,NULL,check ,&ptr1);
			pthread_join(request,NULL);
			break;
		case 2:
			printf("\ncustomer ID with Time:\n");
			for(i=0;i<3;i++)
			{
				printf("%d. Id:%d ->Time:%d\n",i,ptr1.c_id[i],ptr1.time[i]);
			}
			printf("\nEnter the ID of customer to be removed:\n");
			scanf("%d",&remove);
			for(i=0;i<3;i++)
			{
				if(ptr1.c_id[i]==remove)
				{
					ptr1.c_id[i]=0;
					ptr1.time[i]=0;
					queue[i]=0;
				}
			}
			pthread_create(&request,NULL,check ,&ptr1);
			pthread_join(request,NULL);
			break;
		case 3:
			printf("\nSCENARIO\n");
			for(i=0;i<3;i++)
			{
				printf("ID: %d  Time: %d\n",ptr1.c_id[i],ptr1.time[i]);
			}
			pthread_create(&work,NULL,working1 ,&ptr1);
			pthread_join(work,NULL);
			break;
		case 4:
			loop=1;
			break;
	}
	}
	}
	mainfunc();
}

