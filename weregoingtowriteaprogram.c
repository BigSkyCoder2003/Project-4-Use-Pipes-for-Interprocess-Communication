#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//Daniel Lounsbury

int main(int argc, char *argv[]){

int pipe_fd[2];
char *directory;
if (argc > 1){
directory = argv[1]; 
}
else{
directory = ".";
}

if (pipe(pipe_fd) == -1)
{
perror("no pipe for u");
exit(EXIT_FAILURE);
}

pid_t pid;

pid = fork();

if (pid == -1){
perror("no fork for u");
exit(EXIT_FAILURE);
}

if (pid == 0){
close(pipe_fd[1]);
dup2(pipe_fd[0], STDIN_FILENO);
close(pipe_fd[0]);
execlp("wc", "wc", "-l", NULL);
perror("no execlp for u");
exit(EXIT_FAILURE);
}
else{
close(pipe_fd[0]);
dup2(pipe_fd[1], STDOUT_FILENO);
close(pipe_fd[1]);
execlp("ls", "ls", "-1a", directory, NULL);
perror("no execlp for u");
exit(EXIT_FAILURE);


}

wait(NULL);

return 0;

}