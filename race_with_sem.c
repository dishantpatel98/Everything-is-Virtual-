#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<errno.h>
#include<sys/sem.h>
#define KEY1 10

int main(){
struct node{ //object which is shared by both the processes
 int value;
	
	};


int status,id;
struct node* ptr_shma;
struct sembuf sb1;
 int  shm_id1=shmget(KEY1,sizeof(struct node),IPC_CREAT|0600);


if(shm_id1<0 && errno!=EEXIST){

perror("error in creating the shared memory ");
exit(1);

}

ptr_shma=shmat(shm_id1,0,0);

ptr_shma->value=600000;

int sem_id2=semget(KEY1,1,IPC_CREAT | 0600);  //this system call will create the set of semaphore..in this case  it is only one.
                                              //parameter 1 defines the key of the private space for which the semaphore is created
					      //paramerter 2 defines the number of semaphore we want to create in this set
					      //parameter 3 is the read write permision
					      //it will return the  semaphore id of that set
                                              //f a semaphore set with the same ID already existed, we would get access to the existing set,  
					      //rather then a new set be created.
					      //
                                               
if(sem_id2<0){
perror("error in semget");
exit(2);
}

                                                                      /*union semun{
                                    				       int val;     Value for SETVAL 
                                                                       struct semid_ds *buf;     Buffer for IPC_STAT, IPC_SET 
                                                                       unsigned short  *array;   Array for GETALL, SETALL 
                                                                       struct seminfo  *__buf;   Buffer for IPC_INFO
                                                                                   }   */

union semun{				                                      
int val;
unsigned short *array;
};

//unsigned short ary[]={50,1,0};
//union semun u1;
//u1.val=1;
int ret1=semctl(sem_id2,0,SETVAL,1);                             /*semctl() system call is called semaphore control..paramter 1 is the id of the semaphore set
                                                                   int semctl(int semid, int semnum, int cmd, ...);
                                                                   -->senum is the number of the semaphore in the set...in this case 0th semaphore
								   
								   -->semctl() performs the control operation specified by cmd on the System V semaphore
                                                                   set identified by semid, or on the semnum-th semaphore of that  set.   (The  sema‐
                                                                    phores in a set are numbered starting at 0.)
                                                                   -->  This function has three or four arguments, depending on cmd.  When there are four,
                                                                        the fourth has the type union semun. 
                                                                   GETVAL-->Return the value of semval for the semnum-th semaphore of the set.The
                                                                            calling process must have read permission on the semaphore set.
                                                                  SETVAL--> Set the value of semval to arg.val for the semnum-th semaphore of the set 
								 

							           On failure, semctl() returns -1 with errno indicating the error.

      
								   Otherwise, the system call returns a nonnegative value depending on cmd as follows:

     
								   GETNCNT   the value of semncnt.

      
								   GETPID    the value of sempid.

      
								   GETVAL-->    RETURN CURRENT the value of semval.

                                                                    GETZCNT   the value of semzcnt.-->NO OF PROCESSES WAITING FOR THE SEMAPHORE TO BECOME 0

 	  

									  
									  
									  
									  
									
                                                                                                                            */									  
if(ret1<0){perror("error in semctl settings");exit(4);   };                                                              
ret1=semctl(sem_id2,0,GETVAL);  //getting the semaphore values                                                       

if(ret1<0){perror("error in semctl setting"); exit(5);  };



int ret=fork();
int flag_unsuccessful=0,flag_abnormal=0;
if(ret>0){
int count;


printf("the attached address is 0x%x\n", ptr_shma);
printf("the amount of shm memory used is %d\n",sizeof(count));


   int i;
   
ret1=semctl(sem_id2,0,GETVAL);
 printf("VALUE OF SEM IN  PARENT BEFORE DECREMENT IS %d\n",ret1);




    sb1.sem_num = 0;  //semaphore instance no.
    sb1.sem_op = -1;  //decrement operation
    sb1.sem_flg = 0;  //not using flags
    ret1=semctl(sem_id2,0,GETVAL);
printf("VALUE OF SEM IN PARENT AFTER DECREMENT IS %d\n",ret1);



    semop(sem_id2,&sb1,1);
    

for( i=0;i<600000;i++){


//printf("I am in child line---1");
//printf("I am in child line---2");
//printf("I am in child line---3");
//printf("I am in child line---4");
//printf("I am in child line---5");



ptr_shma->value--;
//printf("the value of count in process 1 %d\n",ptr_shma->value);

 
}
ptr_shma->value=600000;
ret1=semctl(sem_id2,0,GETVAL);  
printf("VALUE OF SEM IN PARENT BEFORE INCREMENT IS %d\n",ret1);


    sb1.sem_num = 0;  //we are operating on the  semaphore
    sb1.sem_op = +1;  //increment
    sb1.sem_flg = 0;
    

    ret1=semctl(sem_id2,0,GETVAL);  
printf("VALUE OF SEM IN PARENT AFTER INCREMENT IS %d\n",ret1);

semop(sem_id2,&sb1,1);


}

if(ret==0){

int count;
int ret2;	
//printf("I am in parent line---1");
//printf("I am in parent line---2");
//printf("I am in parent line---3");
//printf("I am in parent line---4");
//printf("I am in parent line---5");
//printf("I am in parent line---6");
//printf("the attached address is 0x%x\n", ptr_shma);
//printf("the amount of shm memory used is %d\n",sizeof(count));

//ptr_shma->value =8;
int i;

ret2=semctl(sem_id2,0,GETVAL); 




printf("VALUE OF SEM IN  CHILD BEFORE DECREMENT IS %d\n",ret2);

    sb1.sem_num = 0;  //semaphore instance no.
    sb1.sem_op = -1;  //decrement operation
    sb1.sem_flg = 0;  //not using flags
    ret2=semctl(sem_id2,0,GETVAL);

printf("VALUE OF SEM IN  CHILD AFTER DECREMENT IS %d\n",ret2);

    
semop(sem_id2,&sb1,1);


for(i=0;i<=600000;i++){



ptr_shma->value--;
}


ptr_shma->value=600000;

ret2=semctl(sem_id2,0,GETVAL);

printf("VALUE OF SEM IN  CHILD BEFORE INCREMENT IS %d\n",ret2);
 sb1.sem_num = 0;  //we are operating on the second semaphore
    sb1.sem_op = +1;  //increment
    sb1.sem_flg = 0;
    
 ret2=semctl(sem_id2,0,GETVAL);

printf("VALUE OF SEM IN  CHILD  AFTER INCREMENT IS %d\n",ret2);


    
    semop(sem_id2,&sb1,1);

 




}

if(ret==0) {


        
         
           //destroy the shared memory object !!!
 printf("final value of shared counter is %d\n",ptr_shma->value);
shmctl(id,IPC_RMID,0);   
printf("shared memory is destroyed\n");
 exit(0);

    }













if(ret>0)
 {
   while(1)
   {

     ret = waitpid(-1,&status,0);
     if(ret>0)
     {
            printf("child with id %d terminated\n",ret);

       if(WIFEXITED(status))
       {
            printf("wifexited\n");
           if(WEXITSTATUS(status) == 0)
           { 
              printf("wexitstatus\n");       
           }
           else
           {
               flag_unsuccessful = 1;
               printf("unsuccessful\n");
           }
       }
       else
       {
	      if(flag_unsuccessful || flag_abnormal) {printf("error in compiling an object file\n"); exit(1); }
              flag_abnormal = 1;
       }
     }

     if(ret<0)
     {   
        break;  //you must check conditions properly   
     }

   }//second while

  }//second parent block if 








}

