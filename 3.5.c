#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

int main(void)
{
  int pipefds[2];
  int number;
  int i;
  int flag = 0;

    void sigint_handler(int sig);
    if(signal(SIGINT,sigint_handler) == SIG_ERR)
    {
      perror("signal");
      exit(1);
    }

  if(pipe(pipefds) == -1)
  {
    perror("pipe");
    exit;
  }

  pid_t pid = fork();

  if(pid == 0)
  {

    printf("Please enter a number:\n");
    scanf("%d",&number);

    close(pipefds[0]);
    write(pipefds[1],&number,sizeof(number));
    exit;
  }
  if (pid>0){
    wait(NULL);
    close(pipefds[1]);
    read(pipefds[0],&number,sizeof(number));

    for (i=2;i<=number/2;++i){
     if(number % i==0){
      flag =1;
      break;
      }
    }

    if(number==1){
       printf("1 is not a prime number.\n");
    }
    else{
       if(flag==0)
          printf("%d is a prime number.\n",number);
       else
          printf("%d is not a prime number.\n",number);
    }

    close(pipefds[0]);
  }
  return 0;
}
void sigint_handler(int sig){
  printf("Please try again!\n");
}
