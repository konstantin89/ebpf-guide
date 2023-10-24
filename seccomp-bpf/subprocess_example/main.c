#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <seccomp.h>

#include <sys/sysinfo.h>
#include <sys/wait.h>

int main() 
{
    // Initialize a seccomp filter context.
    scmp_filter_ctx ctx;

    // Default action: allow syscall
    ctx = seccomp_init(SCMP_ACT_ALLOW);

    if (!ctx) 
    {
        perror("seccomp_init");
        return 1;
    }

    // Allow the write() system call.
    if (seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(sysinfo), 0) != 0) 
    {
        perror("seccomp_rule_add");
        return 1;
    }

    // Load the filter into the kernel.
    if (seccomp_load(ctx) != 0) 
    {
        perror("seccomp_load");
        return 1;
    }

    pid_t child_pid = fork();
    if (child_pid == 0) 
    {
        printf("[V] child process - created\n");

        sleep(1);

        struct sysinfo si;
        sysinfo (&si); // Child process will crash here.

        printf("[V] child process - sysinfo succeed \n");

        return 0;

    } 
    else if (child_pid > 0) 
    {
        printf("[V] parent process \n");

        int status;
        
        printf("[V] parent process - waiting for child process\n");
        waitpid(child_pid, &status, 0);
        printf("[V] parent process - child process done with status [%d] \n", WEXITSTATUS(status));
    } 
    else 
    {
        printf("[X] error, fork failed \n");
    }
    // Cleanup the Seccomp filter.
    seccomp_release(ctx);

    return 0;
}


