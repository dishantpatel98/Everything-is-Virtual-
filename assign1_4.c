#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{

   int ret,pid,status,flag_unsuccessful=0,flag_abnormal=0;
   unsigned long int i=0;
   int signal; 
    pid=getpid();
    printf("processid  = %d\n",pid);

 //in the parent process block, create multiple children
//processes, for different jobs 
//in these samples, one active application instance
//is managed using multiple processes - 
//meaning, multiple processes are 
//used to implement multitasking, in a given active
//application instance  
//- in this context, each new process is used to 
//do a specific job, for an active instance of
//the  application 
//block1 

  while(i++<5){
   ret = fork();
   
   if(ret<0)
   { 
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
   //this is a child process context and a code block
   //executed, in a each child context  
   if(ret==0) //in a child process context/instance 
   { 
	   printf("I am in child process context\n"); 
        //in a child process context, this is the first 
        //child instance- it is the execution context of
        //the first child process instance 
        //in each  child process instance, we are doing 
        //a specific job, using execl() 
        //in the execl(), we are compiling a module and 
        //generating an intermediate object file
        	   
	if(i==1)//first child process context/instance 
                //block2
	{
	printf("in child context pid is %d and ppid is %d\n",getpid(), getppid()); 
       	//this is a job, in this child process context/instance   
        //in this context, gcc is loaded, in the child process 
        //and gcc will be used to compile a module/intermediate 
        //object file
        //in this context, gcc may complete successfully 
         //there will be a normal termination of child process
         //- the other possibility is gcc will not 
         //complete its job
         //successfully and there is a normal termination of
         //child process 
         //- another possibility is that execl() fails and
         //due to this the child process terminates normally, 
         //but unsuccessful  
ret = execl("/usr/bin/gcc","gcc","-c","a1.c","-o","a1.o",NULL);  
	//ret = execl("/home/desd/w1.out","w1.out",NULL);  
//	ret = execl("/home/desd/ex1","ex1","1000",NULL);  
	//ret = execl("/home/dac/ex2","ex2","2000",NULL);  
  	//execl() will never return, if successful 
        //execl() will return, only on failure 
        if(ret==-1) { perror("error in execl"); exit(33); }       
	}//block2 ends here 

        //this is the second instance of the child process
        //it is assigned another jobs, using execl() 
        //gcc is used to compile another object file 	
	if(i==2) //block3
	{
	printf("in child context pid is %d and ppid is %d\n",getpid(), getppid()); 
ret = execl("/usr/bin/gcc","gcc","-c","a2.c","-o","a2.o",NULL);  
  	if(ret<0) { perror("error in execl"); exit(33); }       
	}//block3 ends here
	if(i==3)//block4
	{
	printf("in child context pid is %d and ppid is %d\n",getpid(), getppid()); 
	   
ret = execl("/usr/bin/gcc","gcc","-c","a3.c","-o", "a3.o",NULL);  
  	if(ret<0) { perror("error in execl"); exit(33); }     
	}//block4 ends here 
	if(i==4)//block5 
	{
	printf("in child context pid is %d and ppid is %d\n",getpid(), getppid()); 
	   
	ret = execl("/usr/bin/gcc","gcc","-c","a4.c","-o","a4.o",NULL);  
  	if(ret<0) { perror("error in execl"); exit(33); }       
	}//block5 ends here 
	if(i==5)//block6
	{
	printf("in child context pid is %d and ppid is %d\n",getpid(), getppid()); 
	   
	ret = execl("/usr/bin/gcc","gcc","-c","a5.c","-o","a5.o",NULL);  
  	if(ret<0) { perror("error in execl"); exit(33); }      
	}//block6 ends here 
   }
  } //while loop ends here 
 //block7 - this block will be executed, by the parent 
 //         process 
 if(ret>0) //this block of code will execute, in the parent's context only 
 {
   while(1)
   {
     //if waitpid() has cleaned-up a child process, 
     //ret will be set to a +ve value/pid of the child process
     //
     //however, if all the children processes are already cleaned-up, 
     //the return value will be set to -1 

     //once the return value is +ve, we need to extract and interpret 
     //the termination status code stored, in the status field of the 
     //waitpid() system call API 
     //
     //param1 - if set to -1, clean-up any terminated child process
     //of this parent process

     //param2 - to collect termination status code/exit code of 
    //          the cleaned-up child process 
 
    //param3  - flags - typically, unused and set to 0 
     ret = waitpid(-1,&status,0);
     if(ret>0) //in this context, a child has been cleaned-up 
     {
            printf("child with id %d terminated\n",ret);
       //WIFEXITED() macro checks, if the termination was normal or 
       //abnormal - "if the termination was normal, return TRUE" 
       //and 
       //"false", when the termination of the process was
       //abnormal
       //do not print the values, as there is no meaning, 
       //but specific fields have meanings and use the 
       //macro to extract the specific fields  
       if(WIFEXITED(status))
       {
            printf("wifexited\n");
           //if the child process terminated normally, we need to 
           //check the "exit status code" of the child process,
           // using WEXITSTATUS() - 
           //WEXITSTATUS(status) will return 0, if the "exit status 
           //code" of the child process was 0, meaning child 
           //was terminated by invoking exit(0) - 
           //meaning, the child process terminated 
           //normally and successfully completed its job 
           if(WEXITSTATUS(status) == 0)
           { 
              printf("wexitstatus\n");       
           }
           else  //this condition is, when the child process terminated 
                 //normally, but unsuccessful completion of job
                 //based on these conditions, we may set certain 
                 //variables, which can be used, in the application 
                //code - the child was terminated by invoking 
                //exit(n)  
           {
            //there is a normal termination, but unsuccessful completion
            //of the job, so we set a flag, which will be used, in 
            //further processing 
               flag_unsuccessful = 1;
               printf("unsuccessful\n");
           }
       }
       else //this block will execute, when the child process terminated 
            //abnormally / was a forced termination
       {
            //if the child process terminated abnormally, using WTERMSIG(status), 
            //we can extract the signal no. that caused the abnormal termination 
            //of the child process - this can help debug 
            //the problem 
            signal = WTERMSIG(status);
            flag_abnormal = 1;
       }
     }
     //this block of code will execute, when all the children processes 
     //are cleaned-up and no more child process is currently 
     //present , in the system, for this parent process 
     if(ret<0)
     {   
        //what is this block of code doing , in this context ???
        //if the children processes and their jobs are 
        //completed successfully, the parent can continue
        //its processing 
        //however, if one or more children processes did 
        //not complete their jobs, it will be treated 
        //as an error of the application and the 
        //the parent process terminates, unsuccessfully ??? 
        if(flag_unsuccessful || flag_abnormal) 
          {printf("error in compiling an object file\n"); 
           exit(1); }
        else break; //if all the children processes have 
                   //completed their jobs successfully, 
                   //break out of the while loop of waitpid() ???
            //in this active application instance, if the 
            //children processes have completed their 
            //jobs successfully, we will reach here and
            //the parent process of the active application 
            //can continue its further jobs/code blocks  
     }

   }//second while

  }//second parent block if

  //you must fork and create another child only after checking that 
  //every exit status info of every  child process is normal and 
  //successful - otherwise, you cannot link the object files, if
  //there is error in one object file's compilation !!!
  //use waitpid() to check the exit status code of every child process
  //here and then proceed, if all are successfully terminated !!!
  
  //we are in the parent's context of execution and the parent 
  //is managing the children processes and the application's logic ?? 

   ret = fork(); //the parent creates another child process, for 
                 //linking the object files and generating a 
                 //final binary ???
   
   if(ret<0)
   { 
           perror("error in fork"); 
           printf("the final value of i is %lu\n", i);
           exit(1); 
   }
   if(ret>0)
   { 
	   printf("I am in parent process context\n"); 
           printf("in parent .. ppid is %lu...and child is %lu\n\n", getppid(),getpid());
   }

   if(ret==0) 
   { 
	   printf("I am in    COMBINING     child process context\n"); 
           printf("in child .. ppid is %lu ...and pid is %lu\n",getppid(),getpid());           	   
	ret = execl("/usr/bin/gcc","gcc","a5.o","a4.o",
                        "a3.o","a2.o","a1.o","-o", "final",NULL);  
  	   if(ret<0) { perror("error in execl"); exit(33); }      
   }

 flag_unsuccessful = 0;
 flag_abnormal =0; 

 //again, waitpid() is used to clean-up a child process and 
 //check the termination status code/exit code, for the application 
 if(ret>0)
 {
   while(1)
   {
/home/desd/dishant
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



 //you must verify that the linking child process completed 
 //successfully and then go far loading/launching 
 //the compiled new program
   
 //once the above jobs are done, with the help of children processes, 
 //one more child process is created, for loading/launching the 
 //new compiled/linked binary file 
 ret = fork();

       
   if(ret<0)
   { 
           perror("error in fork"); 
           printf("the final value of i is %lu\n", i);
           exit(1); 
   }

   if(ret>0)
   { 
	   printf("I am in parent process context\n"); 
           printf("in parent .. ppid is %lu...and child is %lu\n",getppid(),getpid());

	   
   }

   if(ret==0) 
   { 
	   printf("I am in   RUNNING  child process context\n"); 
           printf("in child .. ppid is %lu ...and pid is %lu\n",getppid(),getpid());	   
      //ret=execl("/usr/bin/final","final",NULL);  //wrong  !!!
      ret=execl("/home/desd/ex1","ex1","1000",NULL);  //correct !!!
      //ret=execl("/usr/bin/gcc","gcc","ex1","1000", NULL);  //wrong !!!
      //ret=execl("/home/dssd/final","final",NULL);  //correct !!!
      //ret=execl("/home/dac/Downloads/final","final","-c", "final.c, "-o", "final.o",NULL);  wrong !!!
      ret=execl("/home/dac/Downloads/final","final",NULL);  //correct !!!
      //ret=execl("/home/dac/Downloads/ex2","ex2","1000", NULL);  //correct !!!
      //ret=execl("/home/dac/Downloads/w1","w1","1000", NULL);  //correct !!!
      if(ret<0) { perror(" my error in execl"); exit(33); }	   
   }final


//the below code must be before creating children for linking and loading 
//compiled program !!! see the the comments above !!!


 
  //sleep(10);


 //return 0; //equivalent to exit(0);

 exit(0);
   
}

