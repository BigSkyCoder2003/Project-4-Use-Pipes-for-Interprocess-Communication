#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

//Daniel Lounsbury

int main(int argc, char *argv[]){

if (argc < 3){
  fprintf(stderr, "%s bro did not type the command right", argv[0]);
  exit(EXIT_FAILURE);
}



int out = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0644);

if(dup2(out, STDOUT_FILENO) == -1){
   perror("Error redirecting output");
   close(out);
   exit(EXIT_FAILURE);
}

close(out);

execvp(argv[2], &argv[2]);

return 0;
}