#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

char*msg1=" I am in Producer";
char *msg2=" I am in Consumer";
pthread_mutex_t mutex2=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t can_produce=PTHREAD_COND_INITIALIZER; // signaled when items are removed
pthread_cond_t can_consume=PTHREAD_COND_INITIALIZER; // signaled when items are added



char buffer[20];
int count=0;

void *prod(){
while(1){	

	printf("I am in Producer\n");
	pthread_mutex_lock(&mutex2);
//sem_wait(&mutex);
//pthread_cond_wait(&can_produce,&mutex2);
//sprintf(buffer,"%s","1234");
printf("Please Enter the value you want to insert\n");
scanf("%s",buffer);
count=1;
//sem_post(&mutex);
pthread_cond_signal(&can_consume);
pthread_mutex_unlock(&mutex2);
	
}
}

void *cons(){
	
while(1){	
printf("I am in consumer\n");

pthread_mutex_lock(&mutex2);
//sem_wait(&mutex);

while(count==0){
printf("before Sleeping");
	pthread_cond_wait(&can_consume,&mutex2);
}


printf("Consumed value is %s\n",buffer);
//sem_post(&mutex);
pthread_cond_signal(&can_produce);

pthread_mutex_unlock(&mutex2);
}
}

pthread_t thread1,thread2;

int main(){
//sem_init(&mutex,0,1);

int ret=pthread_create(&thread2,NULL,prod,NULL);
if(ret){
printf("Consumer thread not created");
}
printf("Consumer thread created\n");
int ret2= pthread_create(&thread1,NULL,cons,NULL);
if(ret2){
printf("Producer thread not created");
}
printf("Both the thread created\n");
pthread_join(thread1,NULL);
pthread_join(thread2,NULL);
printf("All the thread are destroyed\n");


//sem_destroy(&mutexa);
}

