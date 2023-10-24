#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <seccomp.h>

int main() 
{
    // Initialize a seccomp filter context.
    scmp_filter_ctx ctx;

    // Default action: kill the process
    // If we get system call that there is not rule for it, caller thread will be terminated.
    ctx = seccomp_init(SCMP_ACT_KILL);

    if (!ctx) 
    {
        perror("seccomp_init");
        return 1;
    }

    // Allow the write() system call.
    if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0) != 0) 
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

    // Now, only the write() system call is allowed. All other syscalls are denied.

    // Attempt to execute a system call that's not allowed (e.g., fork()).

    fork(); // This will kill the thread since we used SCMP_ACT_KILL

    // Cleanup the Seccomp filter.
    seccomp_release(ctx);

    return 0;
}


