#include <stdio.h>
#include <unistd.h>     // fork()
#include <sys/types.h>  // pid_t
#include <sys/wait.h>   // wait()

int main() {
    pid_t pid;

    pid = fork();   // create a new process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        printf("24SJPCCSL407 ");
    }
    else {
        // Parent process
        wait(NULL);   // wait for child to finish
        printf("Operating Systems Lab\n");
    }

    return 0;
}
