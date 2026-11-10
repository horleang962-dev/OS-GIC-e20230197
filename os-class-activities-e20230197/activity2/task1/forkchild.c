/* forkchild.c — Process creation with fork() and exec() */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    printf("Parent process (PID: %d) — creating child...\n", getpid());
    fflush(stdout);  /* flush before fork so the line is not duplicated */

    pid = fork();

    if (pid < 0) {
        /* fork failed */
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        /* ---- CHILD PROCESS ---- */
        printf("Child process (PID: %d, Parent PID: %d)\n", getpid(), getppid());

        /*
         * Sleep for 30 seconds so you have time to observe
         * the parent-child process tree in another terminal.
         */
        printf("Child: sleeping 30s — observe the process tree now!\n");
        sleep(30);

        printf("Child: now executing 'ls -la'...\n");
        fflush(stdout);  /* flush before exec, otherwise these lines are lost */

        /* Replace this process with "ls -la" */
        execlp("ls", "ls", "-la", NULL);

        /* If execlp returns, it means it failed */
        perror("execlp");
        exit(EXIT_FAILURE);
    }
    else {
        /* ---- PARENT PROCESS ---- */
        int status;
        printf("Parent: waiting for child (PID: %d) to finish...\n", pid);
        fflush(stdout);

        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Parent: child exited with status %d\n", WEXITSTATUS(status));
        }
        printf("Parent: done.\n");
    }

    return 0;
}
