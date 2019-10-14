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
 int value1;
int value2;
int value3;
int value4;
int value5;
int value6;
int value7;
int value8;
int value9;
int value10;
         };


int status,id;
struct node* ptr_shma;

 int  shm_id1=shmget(KEY1,sizeof(struct node),IPC_CREAT|0600);


if(shm_id1<0 && errno!=EEXIST){

perror("error in creating the shared memory ");
exit(1);

}

ptr_shma=shmat(shm_id1,0,0);

ptr_shma->value1=6000000;
ptr_shma->value2=6000000;
ptr_shma->value3=6000000;
ptr_shma->value4=6000000;
ptr_shma->value5=6000000;
ptr_shma->value6=6000000;
ptr_shma->value7=6000000;
ptr_shma->value8=6000000;
ptr_shma->value9=6000000;
ptr_shma->value10=6000000;




int ret=fork();
int flag_unsuccessful=0,flag_abnormal=0;
if(ret>0){



printf("the attached address is 0x%x\n", ptr_shma);
//printf("the amount of shm memory used is %d\n",sizeof(count));


int i;
for( i=0;i<3000000;i++){


//printf("I am in child line---1");
//printf("I am in child line---2");
//printf("I am in child line---3");
//printf("I am in child line---4");
//printf("I am in child line---5");


ptr_shma->value1--;
ptr_shma->value2--;
ptr_shma->value3--;
ptr_shma->value4--;
ptr_shma->value5--;
ptr_shma->value6--;
ptr_shma->value7--;
ptr_shma->value8--;
ptr_shma->value9--;
ptr_shma->value10--;




//printf("the value of count in process 1 %d\n",ptr_shma->value);

 
}
//ptr_shma->value=600000;

}

if(ret==0){

int count;
	
//printf("I am in parent line---1");
//printf("I am in parent line---2");
//printf("I am in parent line---3");
//printf("I am in parent line---4");
//printf("I am in parent line---5");
//printf("I am in parent line---6");
printf("the attached address is 0x%x\n", ptr_shma);
//printf("the amount of shm memory used is %d\n",sizeof(count));


int i;
for(i=0;i<3000000;i++){



ptr_shma->value1--;
ptr_shma->value2--;
ptr_shma->value3--;
ptr_shma->value4--;
ptr_shma->value5--;
ptr_shma->value6--;
ptr_shma->value7--;
ptr_shma->value8--;
ptr_shma->value9--;
ptr_shma->value10--;



}


//ptr_shma->value=600000;





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
 printf("final value of shared counter is %d\n",ptr_shma->value1);
 printf("final value of shared counter is %d\n",ptr_shma->value2);
 printf("final value of shared counter is %d\n",ptr_shma->value3);
 printf("final value of shared counter is %d\n",ptr_shma->value4);
 printf("final value of shared counter is %d\n",ptr_shma->value5);
 printf("final value of shared counter is %d\n",ptr_shma->value6);
 printf("final value of shared counter is %d\n",ptr_shma->value7);
 printf("final value of shared counter is %d\n",ptr_shma->value8);

 printf("final value of shared counter is %d\n",ptr_shma->value9);
 printf("final value of shared counter is %d\n",ptr_shma->value10);

	     
	     shmctl( shm_id1,IPC_RMID,0);
int x;
 if(x==-1){
printf("shared memory is not  destroyed");
exit(0);
}

else{
printf("Shared memory is destroyed");
exit(1);
}
 exit(1);

    }

   }//second while

  }//second parent block if 








}
