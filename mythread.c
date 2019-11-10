/*nclude<stdio.h>
#include<pthread.h>


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

/*The  pthread_join()  function waits for the thread specified by thread to terminate.  If that thread has already terminated, then pthread_join() returns immediately.
       The thread specified by thread must be joinable.

       If retval is not NULL, then pthread_join() copies the exit status of the target thread (i.e., the value that the target thread supplied to pthread_exit(3)) into  the
       location pointed to by retval.  If the target thread was canceled, then PTHREAD_CANCELED is placed in the location pointed to by retval.


  */

void *start_routine(void*value){
	 printf("I am in the second thread:\n");
	 int *num=(int *)value;
         printf("The value is %d\n",*num);
return NULL;
}
int main(int argc,char *argv[]){

/*printf("%d",sizeof(unsigned long int ));
printf("%d",sizeof(pthread_t )); */




pthread_t thread_pid;//declaring the thread variable of the unsigned long int woth will hold the id of the thread
                 //basically typedef is used in pthread.h for thread variable
                 
printf("This is the main thread\n");
 int num=123;

 pthread_create(&thread_pid,NULL,start_routine,&num);
 pthread_join(thread_pid,NULL);







}
