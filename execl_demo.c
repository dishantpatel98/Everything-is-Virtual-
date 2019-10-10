#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
int ret,pid,status,flag_unsuccessful=0,flag_abnormal=0;
   unsigned long int i=0;
   int signal; 
    pid=getpid();
    printf("processid  = %d\n",pid);

    while(++i<5){
    ret=fork();
    if(ret<0){
    perror("error in fork"); 
           printf("the final value of i is %lu\n", i);
           exit(1); 
    
    }
    if(ret>0)
   {
	   printf("I am in parent process context\n");
           printf("in parent .. ppid is %lu...and child is %lu\n\n",
		   getppid(),getpid());
           continue;
   }
    if(ret==0){
    printf("I am in the child process context\n");
    if(i==1){
    printf("in child context pid is %d and ppid is %d\n",getpid(), getppid());
    ret = execl("/usr/bin/gcc","gcc","a1.c","-o","a1",NULL);
    if(ret==-1) { perror("error in execl"); exit(33); }
            }

    if(i==2) //block3
	{
	printf("in child context pid is %d and ppid is %d\n",getpid(), getppid());
ret = execl("/usr/bin/gcc","gcc","a2.c","-o","a2",NULL);
  	if(ret<0) { perror("error in execl"); exit(33); }
	}//block3 ends here
	if(i==3)//block4
	{
	printf("in child context pid is %d and ppid is %d\n",getpid(), getppid());

ret = execl("/usr/bin/gcc","gcc","a3.c","-o", "a3",NULL);
  	if(ret<0) { perror("error in execl"); exit(33); }
	}//block4 ends here
	if(i==4)//block5
	{
	printf("in child context pid is %d and ppid is %d\n",getpid(), getppid());

	ret = execl("/usr/bin/gcc","gcc","a4.c","-o","a4",NULL);
  	if(ret<0) { perror("error in execl"); exit(33); }
	}//block5 ends here
	if(i==5)//block6
	{
	printf("in child context pid is %d and ppid is %d\n",getpid(), getppid());

	ret = execl("/usr/bin/gcc","gcc","a5.c","-o","a5",NULL);
  	if(ret<0) { perror("error in execl"); exit(33); }
	}//block6 ends here
   
    }
    
   }

    if(ret>0){
    
    while(1){
   ret = waitpid(-1,&status,0);
  if(ret>0){
  printf("Child with id %d terminated\n",ret);
  if(WIFEXITED(status)){
  printf("wifexited");
  if(WEXITSTATUS(status)==0){
  printf("wexitstatus\n");
  }
  else{
  flag_unsuccessful=1;
  printf("unsucessfull");
  }
  
  
  }
  else{
  signal=WTERMSIG(status);
  flag_abnormal=1;
 }
 } 
 
if(ret<0){
if(flag_unsuccessful||flag_abnormal){
printf("error in compiling the object file\n");
exit(1);
}
else break;
}




}
    
   }
i=0;
while(i++<5){
ret=fork();
if(ret<0){
 printf("I am in parent process context\n");
           printf("in parent .. ppid is %lu...and child is %lu\n\n",
		   getppid(),getpid());
           continue;


}
if(ret==0){
printf("I am in the child process context\n");
if(i==1){
printf("in child context pid is %d and ppid is %d\n",getpid(), getppid());
ret = execl("/home/desd/dishant/a1","a1",NULL);
if(ret==-1) { perror("error in execl"); exit(33); }
       }



if(i==2){
printf("in child context pid is %d and ppid is %d\n",getpid(), getppid());
ret = execl("/home/desd/dishant/a2","a2",NULL);
if(ret==-1) { perror("error in execl"); exit(33); }
       }


if(i==3){
printf("in child context pid is %d and ppid is %d\n",getpid(), getppid());
ret = execl("/home/desd/dishant/a3","a3",NULL);
if(ret==-1) { perror("error in execl"); exit(33); }
       }



if(i==4){
printf("in child context pid is %d and ppid is %d\n",getpid(), getppid());
ret = execl("/home/desd/dishant/a4","a4",NULL);
if(ret==-1) { perror("error in execl"); exit(33); }
       }



if(i==5){
printf("in child context pid is %d and ppid is %d\n",getpid(), getppid());
ret = execl("/home/desd/dishant/a5","a5",NULL);
if(ret==-1) { perror("error in execl"); exit(33); }
       }


}




}
if(ret>0){
while(1){
ret=waitpid(-1,&status,0);
if(ret>0){
printf("child with id %d termination\n",pid);
if(WIFEXITED(status)){
printf("wifexited\n");
                     }
else {
flag_unsuccessful = 1;
printf("unsuccessful\n");
}
}
else{
if(flag_unsuccessful || flag_abnormal) {printf("error in compiling an object file\n"); exit(1); }
              flag_abnormal = 1;

}

if(ret<0){
break;

}
}



}


}







