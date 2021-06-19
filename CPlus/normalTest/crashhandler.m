#include <execinfo.h>
#include <exception>

/************************************************************************/
/*                                                                      */
/*  Globals                                                             */
/*                                                                      */
/************************************************************************/

static NSString *GBug;

/************************************************************************/
/*                                                                      */
/*  Crash Reporter                                                      */
/*                                                                      */
/************************************************************************/

static NSString *GetBugReport()
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *dir = [paths objectAtIndex:0];
    return [dir stringByAppendingPathComponent:@"bug.txt"];
}

/*  UncaughtExceptionHandler
 *
 *      Handle uncaught exceptions
 */

static void UncaughtExceptionHandler(NSException *exception)
{
    /*
     *  Extract the call stack
     */

    NSArray *callStack = [exception callStackReturnAddresses];
    int i,len = [callStack count];
    void **frames = new void *[len];

    for (i = 0; i < len; ++i) {
        frames[i] = (void *)[[callStack objectAtIndex:i] unsignedIntegerValue];
    }
    char **symbols = backtrace_symbols(frames,len);

    /*
     *  Now format into a message for sending to the user
     */

    NSMutableString *buffer = [[NSMutableString alloc] initWithCapacity:4096];

    NSBundle *bundle = [NSBundle mainBundle];
    [buffer appendFormat:@"PComp version %@ build %@\n\n",
            [bundle objectForInfoDictionaryKey:@"CFBundleVersion"],
            [bundle objectForInfoDictionaryKey:@"CIMBuildNumber"]];
    [buffer appendString:@"Uncaught Exception\n"];
    [buffer appendFormat:@"Exception Name: %@\n",[exception name]];
    [buffer appendFormat:@"Exception Reason: %@\n",[exception reason]];
    [buffer appendString:@"Stack trace:\n\n"];
    for (i = 0; i < len; ++i) {
        [buffer appendFormat:@"%4d - %s\n",i,symbols[i]];
    }

    /*
     *  Get the error file to write this to
     */

    NSError *err;
    [buffer writeToFile:GetBugReport() atomically:YES encoding:NSUTF8StringEncoding error:&err];
    NSLog(@"Error %@",buffer);
    exit(0);
}

/*  SignalHandler
 *
 *      Handle uncaught signals
 */

void SignalHandler(int sig, siginfo_t *info, void *context)
{
    void *frames[128];
    int i,len = backtrace(frames, 128);
    char **symbols = backtrace_symbols(frames,len);

    /*
     *  Now format into a message for sending to the user
     */

    NSMutableString *buffer = [[NSMutableString alloc] initWithCapacity:4096];

    NSBundle *bundle = [NSBundle mainBundle];
    [buffer appendFormat:@"PComp version %@ build %@\n\n",
            [bundle objectForInfoDictionaryKey:@"CFBundleVersion"],
            [bundle objectForInfoDictionaryKey:@"CIMBuildNumber"]];
    [buffer appendString:@"Uncaught Signal\n"];
    [buffer appendFormat:@"si_signo    %d\n",info->si_signo];
    [buffer appendFormat:@"si_code     %d\n",info->si_code];
    [buffer appendFormat:@"si_value    %d\n",info->si_value];
    [buffer appendFormat:@"si_errno    %d\n",info->si_errno];
    [buffer appendFormat:@"si_addr     0x%08lX\n",info->si_addr];
    [buffer appendFormat:@"si_status   %d\n",info->si_status];
    [buffer appendString:@"Stack trace:\n\n"];
    for (i = 0; i < len; ++i) {
        [buffer appendFormat:@"%4d - %s\n",i,symbols[i]];
    }

    /*
     *  Get the error file to write this to
     */

    NSError *err;
    [buffer writeToFile:GetBugReport() atomically:YES encoding:NSUTF8StringEncoding error:&err];
    NSLog(@"Error %@",buffer);
    exit(0);
}
/*  TerminateHandler
 *
 *      C++ exception terminate handler
 */

void TerminateHandler(void)
{
    void *frames[128];
    int i,len = backtrace(frames, 128);
    char **symbols = backtrace_symbols(frames,len);

    /*
     *  Now format into a message for sending to the user
     */

    NSMutableString *buffer = [[NSMutableString alloc] initWithCapacity:4096];

    NSBundle *bundle = [NSBundle mainBundle];
    [buffer appendFormat:@"PComp version %@ build %@\n\n",
            [bundle objectForInfoDictionaryKey:@"CFBundleVersion"],
            [bundle objectForInfoDictionaryKey:@"CIMBuildNumber"]];
    [buffer appendString:@"Uncaught C++ Exception\n"];
    [buffer appendString:@"Stack trace:\n\n"];
    for (i = 0; i < len; ++i) {
        [buffer appendFormat:@"%4d - %s\n",i,symbols[i]];
    }

    /*
     *  Get the error file to write this to
     */

    NSError *err;
    [buffer writeToFile:GetBugReport() atomically:YES encoding:NSUTF8StringEncoding error:&err];
    NSLog(@"Error %@",buffer);
    exit(0);
}
/*  SetupUncaughtSignals
 *
 *      Set up the uncaught signals
 */

static void SetupUncaughtSignals()
{
    struct sigaction mySigAction;
    mySigAction.sa_sigaction = SignalHandler;
    mySigAction.sa_flags = SA_SIGINFO;

    sigemptyset(&mySigAction.sa_mask);
    sigaction(SIGQUIT, &mySigAction, NULL);
    sigaction(SIGILL, &mySigAction, NULL);
    sigaction(SIGTRAP, &mySigAction, NULL);
    sigaction(SIGABRT, &mySigAction, NULL);
    sigaction(SIGEMT, &mySigAction, NULL);
    sigaction(SIGFPE, &mySigAction, NULL);
    sigaction(SIGBUS, &mySigAction, NULL);
    sigaction(SIGSEGV, &mySigAction, NULL);
    sigaction(SIGSYS, &mySigAction, NULL);
    sigaction(SIGPIPE, &mySigAction, NULL);
    sigaction(SIGALRM, &mySigAction, NULL);
    sigaction(SIGXCPU, &mySigAction, NULL);
    sigaction(SIGXFSZ, &mySigAction, NULL);
}
- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 1) {
        /*
         *  Send an e-mail with the specified title.
         */

        NSMutableString *url = [NSMutableString stringWithCapacity:4096];
        [url appendString:@"mailto:bugs@nowhere.meh?subject=Bug%20Report&body="];
        [url appendString:[GBug stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]];
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:url]];
    }

    [GBug release];
}

- (void)sendBugsIfPresent
{
    NSError *err;
    NSString *path = GetBugReport();

    GBug = [[NSString stringWithContentsOfFile:path encoding:NSUTF8StringEncoding error:&err] retain];
    if (GBug == nil) return;
    [[NSFileManager defaultManager] removeItemAtPath:path error:&err];

    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Unexpected exception"
            message:@"An unexpected exception was caught the last time this program ran. Send the developer a bug report by e-mail?"
            delegate:self
            cancelButtonTitle:@"Cancel"
            otherButtonTitles:@"Send Report",nil];
    [alert show];
}
- (void)applicationDidFinishLaunching:(UIApplication *)application
{
... Other initialization here ...

    /* Register for uncaught exceptions, signals */
    NSSetUncaughtExceptionHandler(&UncaughtExceptionHandler);
    SetupUncaughtSignals();
    std::set_terminate(TerminateHandler);

    [self sendBugsIfPresent];
}
