/* Example of using sigaction() to setup a signal handler with 3 arguments
 * including siginfo_t.
 * -fsanitize=undefined-trap -fsanitize-undefined-trap-on-error -ftrap-function=abort
 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <mach/mach.h>
#include <execinfo.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

static int caught = 0; // check if the signal was caught and stop looping

static void getsymbols() {
    void* callstack[128];
    const int numFrames = backtrace(callstack, 128);
    char **symbols = backtrace_symbols(callstack, numFrames);
    printf("symbols num: %d\n", numFrames);
    for (int i = 0; i < numFrames; ++i)
    {
        printf("%s\n", symbols[i]);
    }
}

static void death_handler (int signum, siginfo_t *siginfo, void *context)
{
    printf("Received %s, %p\n", sys_signame[signum], context);

    switch (signum) {
        case SIGINT:
            printf("Caught SIGINT, exiting now\n");
            exit(0);
        default:
            fprintf(stderr, "=====Caught signal: %d\n", signum);
    }

    getsymbols();

    printf ("Sending PID: %ld, UID: %ld\n",
            (long)siginfo->si_pid, (long)siginfo->si_uid);

    signal (signum, SIG_DFL); // restore default signal handler of signum
    kill (getpid(), signum); // kill itself using signum
}

// handler of SIGTSTP and SIGINT
static void stop_handler (int signum, siginfo_t* sigdata, void* unused)
{
    caught = 1;
    printf ("Signal %d received\n", signum);

    // return to exit gracefully
    return;
}

// handler for SIGALRM
static void alarm_handler (int signum)
{
    caught = 1;
    printf ("Signal %d received\n", signum);

    // return to exit gracefully
    return;
}

static void termination_handler (int signum)
{
    void* callstack[128];
    const int numFrames = backtrace(callstack, 128);
    char **symbols = backtrace_symbols(callstack, numFrames);
    for (int i = 0; i < numFrames; ++i)
    {
        printf("%s\n", symbols[i]);
    }

  printf ("Sending PID:");
  exit(1);
  // raise(signum);
}


static const int g_fatalSignals[] =
{
    SIGABRT,
    SIGBUS,
    SIGFPE,
    SIGILL,
    SIGPIPE,
    SIGSEGV,
    SIGSYS,
    SIGTRAP,
};
static struct sigaction* g_previousSignalHandlers = NULL;
static stack_t g_signalStack = {0};

// install signal handlers
static void InstallSignalHandlers()
{
    // 1
    // define and initialize signal set
    sigset_t signalset;
    sigfillset (&signalset);

    // define signal handler "action"
    struct sigaction action;
    action.sa_sigaction = &stop_handler;
    // make sa_sigaction (not sa_handler) to handle signals
    action.sa_flags = SA_SIGINFO;
    // block signals in signalset
    action.sa_mask = signalset;

    // install SIGTSTP and SIGINIT handlers to "action" using sigaction()
    sigaction (SIGTSTP, &action, NULL); // ctrl-z
    sigaction (SIGINT, &action, NULL); // ctrl-c

    // 2
    if(g_signalStack.ss_size == 0) {
        g_signalStack.ss_size = SIGSTKSZ;
        g_signalStack.ss_sp = malloc(g_signalStack.ss_size);
    }

    if(sigaltstack(&g_signalStack, NULL) != 0) {
        printf("signalstack: error");
        exit(1);
    }

    struct sigaction new_action, old_action;
    new_action.sa_sigaction = &death_handler;
    new_action.sa_mask =  signalset;
    new_action.sa_flags =  SA_SIGINFO | SA_ONSTACK;//

    for (int i = 0 ; i<8; i++) {
        sigaction(g_fatalSignals[i], NULL, &old_action);
        if(old_action.sa_sigaction != death_handler){
            if(sigaction(g_fatalSignals[i], &new_action, NULL) !=0){
                printf ("add signal error!");
            }
        }
    }

    //3
    // register SIGALRM handler using signal() ***not recommended***
    signal (SIGALRM, alarm_handler); // alarm(secs)

}

int main (int argc, char *argv[])
{

    // install signal handlers
    InstallSignalHandlers();

    // set alarm
    // alarm(atoi(2));

    // get pid
    int pid = getpid();
    strcpy(0, "bla");
    ((char *)NULL)[1] = 0;

    // loop to wait signal
    for (int second = 1; caught !=1; second++)
    {
        sleep(1);
        printf ("process %d started %d seconds\n", pid, second);
    };

    // going to exit
    printf ("exiting...\n");

    ((char *)NULL)[1] = 0;

    return 0;
}
