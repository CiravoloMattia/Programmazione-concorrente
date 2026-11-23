#include <stdlib.h> // exit
#include <stdio.h> // printf
#include <unistd.h> // getpid, getppid, fork, sleep, execl

int main(int argc, char *argv[])
{
printf("\n[INIZIO] - Prima della fork - pid=%d, pid padre=%d\n\n", getpid(), getppid());

int pid=fork();
if (pid == 0) { // Processo figlio
printf("[Figlio] - pid=%d, pid padre=%d\n", getpid(), getppid());
execl("/bin/lsssssssss", "ls", "-a", (char *)0) ;
printf("exec fallita!\n");
exit (112) ;}
}
