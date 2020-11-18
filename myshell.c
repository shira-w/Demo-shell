#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

int state=0;//varible to save if I am father, background_child or foreground_child
pid_t saved_pid=0;//varible to save the pid to put in waitpid

void control_c()//kill when we want
{

    struct sigaction control_c_handler;
    memset(&control_c_handler, 0, sizeof(control_c_handler));
    control_c_handler.sa_handler = SIG_DFL;
    control_c_handler.sa_flags =0;
	sigaction(SIGINT, &control_c_handler,NULL);
}
int prepare(void)
{
	printf("welcome to my shell! the simulator of LINOX-shell\n");
    struct sigaction control_c_handler;//control c to ignore
    memset(&control_c_handler, 0, sizeof(control_c_handler));
    control_c_handler.sa_handler = SIG_IGN;
    control_c_handler.sa_flags =0;
	sigaction(SIGINT, &control_c_handler,NULL);
    return 0;
}
int split=0;//varible to save the place of pipe "|" in the arglist
int process_arglist(int count, char** arglist)
{
    int fd[2]; //to use with pipe
    for (int i = 0; i < count; i++)
	{
        if(strcmp(arglist[i],"|")==0)
		{
            split=i;
		}
	}
    pid_t pid;
	pid=fork();
    if (pid < 0){
        fprintf(stderr,"fork error");
        return 0;
    }

	if(pid==0)//child
    {

	    if(split==0)
	    {
	    if(strcmp(arglist[count-1],"&")==0)//background child
	    {
	        signal(SIGCHLD,SIG_IGN);
	        arglist[count-1]=NULL;
	        execvp(arglist[0],arglist);

	    }
	    else{
	        control_c();
	    }
	    saved_pid=getpid();
	    execvp(arglist[0],arglist);
	    fprintf(stderr,"Command not found in PATH\n");
	    exit(1);
	    }

	}
	else//father
	{
       if(split==0)//there is no pipe
       {

            if (strcmp(arglist[count-1], "&")!=0)//foreground child
            {
                int status;
                pid_t wait_pid = waitpid(saved_pid,& status, 0);//wait to foreground
                if (wait_pid == -1)
                {
                    fprintf(stderr, "father can't wait to child,be careful of zombie \n");
                    return 0;
                }
            }
        }
       else
        {
			 control_c();
			 if(pipe(fd)==-1)
			     fprintf(stderr, "pipe failed");
			 pid_t pid2=fork();
			 if (pid2 < 0){

                        printf("error");
                     fprintf(stderr,"fork error");
                     return 0;
                }

	            if(pid2==0)//child
                    {

	                 printf("wyes also here");
	                 close(fd[0]);
	                 dup2(fd[1],STDOUT_FILENO);
				     close(fd[1]);
				     arglist[split]=NULL;
				        execvp(arglist[0],arglist);
				        exit(0);

                    fprintf(stderr,"Command not fou88888888888nd in PATH\n");
                    //exit(1);

	                }
	            else
	             {
                   pid_t pid3=fork();//generate the second command of pipe
                   if (pid3 < 0){
                       printf("error");
                       fprintf(stderr,"fork error");
                       exit(1);
                    }
			       if(pid3==0)//second command of pipe
			       {
                        printf("$$$$$$$$$$$$$$$$$$$$");
			            saved_pid=getpid();
			            close(fd[1]);
			            dup2(fd[0],STDIN_FILENO);
			            close(fd[0]);
			            execvp(arglist[split+1],arglist+split+1);

                        fprintf(stderr,"Command 000000000000000not found in PATH\n");
                        exit(1);//pipe and err in one of them
			        }
			       else
			           {
                       close(fd[1]);
                        close(fd[0]);

			            int status;
                        pid_t wait_pid = waitpid(saved_pid,& status, 0);//wait to foreground
                       if (wait_pid == -1)
                        {
                            fprintf(stderr, "father can't wait to child,be careful of zombie \n");
                            return 0;
                         }
                       return 1;
			           }

			      }


           }

	}
	return 1;
}

// prepare and finalize calls for initialization and destruction of anything required
int finalize(void)
{
    printf("GOOD Bye\n");// can i clean the struct?
    return 0;
}