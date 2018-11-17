#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

// Child process instructions:
//     At the end print a message that it is finished
// Parent process instructions
//     Once a child has finished, print out the pid of the completed child as well as how many seconds it was asleep for.
//     Print a message that the parent is done and then end the program

int main(){
  srand(time(0));
  int r0 = rand();
  int c0 = 0;
  int c1 = 0;
  int status;

  printf("pid parent: %d\n", getpid());
  int r1 = rand();

  c0 = fork();

  if(c0){
    c1 = fork();
  }

  int first = wait(&status);

  if(!c1){
    printf("pid children: %d\n", getpid());
    if(!c0){
      int sleep_time0 = r0%3+5;
      sleep(sleep_time0);
      printf("%s\n", "done sleep");
      exit(sleep_time0);
    }
    else{
      srand(getpid());
      int sleep_time1 = r1%3+5;
      sleep(sleep_time1);
      printf("%s\n", "done sleep");
      exit(sleep_time1);
    }
  }

  printf("pid of first exit: %d, time slept: %d\n", first, WEXITSTATUS(status));
  exit(0);

  return 0;
}
