#include <stdio.h>   // printf
#include <unistd.h>  // getpid, getppid, fork, sleep
#include <stdlib.h>  // exit
#include <sys/wait.h>// wait

int main(int argc, char **argv) {

  int wait_status;
  int wait_retvalue;
  
  wait_retvalue = wait(&wait_status);
  
  printf("[FINE] - wait_retvalue=%d, wait_status=%d\n", wait_retvalue, wait_status);
  printf("[FINE] - Termine del processo con pid=%d avente pid padre=%d\n",getpid(),getppid());
  printf("\n");
  
  exit(0);
}
