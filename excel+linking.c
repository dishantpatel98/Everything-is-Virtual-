#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>


int main()
{

   int ret,pid,status,flag_unsuccessful=0,flag_abnormal=0,signal;
   unsigned long int i=0;

    pid=getpid();
    printf("processid  = %d\n",pid);

  

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
        	   
	if(i==1)//first child process context/instance 
                //block2
	{
	printf("in child context pid is %d and ppid is %d\n",getpid(), getppid()); 
       
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
    
     ret = waitpid(-1,&status,0);
     if(ret>0) //in this context, a child has been cleaned-up 
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
        
        if(flag_unsuccessful || flag_abnormal) 
          {printf("error in compiling an object file\n"); 
           exit(1); }
        else break; //if all the children processes have 
                   
     }

   }//second while

  }//second parent block if

 

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
 //     ret=execl("/home/desd/ex1","ex1","1000",NULL);  //correct !!!
      //ret=execl("/usr/bin/gcc","gcc","ex1","1000", NULL);  //wrong !!!
      //ret=execl("/home/dssd/final","final",NULL);  //correct !!!

      ret=execl("/home/desd/dishant/final","final",NULL);  //correct !!!
      //ret=execl("/home/dac/Downloads/ex2","ex2","1000", NULL);  //correct !!!
      //ret=execl("/home/dac/Downloads/w1","w1","1000", NULL);  //correct !!!
      if(ret<0) { perror(" my error in execl"); exit(33); }	   
   }


//the below code must be before creating children for linking and loading 
//compiled program !!! see the the comments above !!!


 
  //sleep(10);


 //return 0; //equivalent to exit(0);

 exit(0);
   
}

