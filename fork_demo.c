#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<stdio.h>

int main(){

int ret,status;
int i=0;
while(i++<5){

	ret =fork();
if(ret<0){
perror("error in fork ");
printf("the final value of i is %u\n",i);
exit(1);
         }

if(ret>0){
printf("I am in Parent Process context\n");
printf("in parent...ppid is %lu...and pid is %lu\n ",getppid(),getpid());

continue;
}

if(ret==0){
printf("I am in  child process context\n");
printf("in child ...ppid is %lu...and pid is %lu\n", getppid(),getpid());


if(i==1||i==2){
	printf("i=%d",i);
	exit(0);
              }
if(i==3){
	printf("i=%d",i);
	exit(1);
                 

}
while(1);

break;

}
}

if(ret>0){
while(1){
	ret=waitpid(-1,&status,0); //waitpid() system call suspends the the current process until one of its children terminates..
	                           //By defult waitpid() waits only for terminated children..but this can be modified using parameter
				   //< -1 	meaning wait for any child process whose process group ID is equal to the absolute value of pid.
                                  //-1 	meaning wait for any child process.
                                   //0 	meaning wait for any child process whose process group ID is equal to that of the calling process.
                                  //> 0 	meaning wait for the child whose process ID is equal to the value of pid. 
				   //waitpid(): on success, returns the process ID of the child whose state has changed; on error, -1 is returned; if                                    // WNOHANG was specified and no child(ren) specified by pid has yet changed state, then 0 is returned.
				   //
				   //
				 
	if(ret>0){
	
	if(WIFEXITED(status)){  //waitpid() will collect and copy the status code in param2 and also returns the pid value of the 
	                        //cleaned up process
		                //WIFEXITED(status) will provide 0,if the child completed sucessfully and invoked exit(0)
        	if(WEXITSTATUS(status)){
    		printf("terminated with exit(1)i.e abnormal termination and pid=%d \n",ret);
	        }
	
		else{
		printf("terminated with exit(0)i.e normal termination and pid =%d \n",ret);
	        }
	
	}//WIFEXITED(status)
	
	else{
	printf("abnormal and unsucessfully\n ");
	}
} //ret>0
        //waitpid() returns -1, when all the processes are cleaned-up and there are no childeren processes	
	
if(ret<0){  //this block of code will terminate the parent process sucessfully
printf("Parent has cleared all the child processes");
	exit(0);
}
}
}
return 0;
}

