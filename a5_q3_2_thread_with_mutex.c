#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

/*Just as every process has a process ID, every thread has a thread ID. Unlike the process ID, which is unique in the system, 
  the thread ID has significance only within the context of the process to which it belongs.
A thread ID is represented by the pthread_t data type. Implementations are allowed to use a structure to represent the pthread_t data type,
so portable implementations can’t treat them as integers.
Linux 3.2.0 uses an unsigned long integer for the pthread_t data type. Solaris 10 represents the pthread_t data type as an unsigned integer. FreeBSD 8.0 and Mac OS X 10.6.8 use a pointer to the pthread structure for the pthread_t data type.
Hence in our case  data type of pthread_t is unsigned long int 
 
 */


/*printf("%d",sizeof(unsigned long int ));
printf("%d",sizeof(pthread_t )); */



/*       int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg);
-->       pthread_create() - create a new thrad
-->First parameter represent the thread id of that thread
--> The pthread_create() function starts a new thread in the calling process.  The new thread
       starts execution by invoking start_routine(); 
-->  Second argument The attr argument points to a pthread_attr_t structure whose contents are used at  thread
       creation  time  to determine attributes for the new thread; this structure is initialized
       using pthread_attr_init(3) and related functions.  If attr is NULL, then  the  thread  is
       created with default attributes.
--> Third argument is pointer "start_routine is a pointer to the function which takes void pointer as a argument and returns void pointer "
-->Fourth parameter is the argument to the thread

       
 */


pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
int count=500000;

void *start_routine1(void*value){
printf("In thread1\n");    
     pthread_mutex_lock(&mutex);
	for(int i=0;i<100000;i++){
	count--;
	}
pthread_mutex_unlock(&mutex);

}

void *start_routine2(void*value){
        printf("In thread2\n");
pthread_mutex_lock(&mutex);
        for(int i=0;i<100000;i++){
        count--;
        }
pthread_mutex_unlock(&mutex);

}

void *start_routine3(void*value){
        printf("In thread3\n");
pthread_mutex_lock(&mutex);
        for(int i=0;i<100000;i++){
        count--;
        }
pthread_mutex_unlock(&mutex);

}
void *start_routine4(void*value){
        printf("In thread4\n");
pthread_mutex_lock(&mutex);
        for(int i=0;i<100000;i++){
        count--;
        }
pthread_mutex_unlock(&mutex);

}
void *start_routine5(void*value){
        printf("In thread5\n");
pthread_mutex_lock(&mutex);
        for(int i=0;i<100000;i++){
        count--;
        }
pthread_mutex_unlock(&mutex);

}



     


int main(int argc,char *argv[]){

/*printf("%d",sizeof(unsigned long int ));
printf("%d",sizeof(pthread_t )); */




pthread_t thread_pid1,thread_pid2,thread_pid3,thread_pid4,thread_pid5;//declaring the thread variable of the unsigned long int woth will hold the id of the thread
                 //basically typedef is used in pthread.h for thread variable
                 

printf("This is the main thread\n");
 
 

pthread_create(&thread_pid1,NULL,start_routine1,NULL);
pthread_create(&thread_pid2,NULL,start_routine2,NULL);
pthread_create(&thread_pid3,NULL,start_routine3,NULL);
pthread_create(&thread_pid4,NULL,start_routine4,NULL);
pthread_create(&thread_pid5,NULL,start_routine5,NULL);

pthread_join(thread_pid1,NULL);
pthread_join(thread_pid2,NULL);
pthread_join(thread_pid3,NULL);
pthread_join(thread_pid4,NULL);
pthread_join(thread_pid5,NULL);
  

printf("Final value of counter is %d\n",count);
exit(0);




}
