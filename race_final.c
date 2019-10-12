#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<errno.h>

#define KEY1 10

int main(){
struct node{
 int value;
	
	};


int status,id;
struct node* ptr_shma;

 int  shm_id1=shmget(KEY1,sizeof(struct node),IPC_CREAT|0600);


if(shm_id1<0 && errno!=EEXIST){

perror("error in creating the shared memory ");
exit(1);

}

ptr_shma=shmat(shm_id1,0,0);

ptr_shma->value=600000;


int ret=fork();
int flag_unsuccessful=0,flag_abnormal=0;
if(ret==0){
int count;


printf("the attached address is 0x%x\n", ptr_shma);
printf("the amount of shm memory used is %d\n",sizeof(count));


int i;
for( i=0;i<600000;i++){


//printf("I am in child line---1");
//printf("I am in child line---2");
//printf("I am in child line---3");
//printf("I am in child line---4");
//printf("I am in child line---5");



ptr_shma->value--;
//printf("the value of count in process 1 %d\n",ptr_shma->value);

                          }


}

if(ret>0){

int count;
	
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
for(i=0;i<=600000;i++){



ptr_shma->value--;
}








}

if(ret==0) {


         // shmctl(id,IPC_RMID,0);
          printf("shared memory is destroyed\n");
           //destroy the shared memory object !!!
 printf("final value of shared counter is %d\n",ptr_shma->value);
shmctl(id,IPC_RMID,0);          
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

