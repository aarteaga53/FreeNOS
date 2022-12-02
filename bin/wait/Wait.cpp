#include "sys/wait.h"
#include <stdio.h>
#include <unistd.h>
#include "Wait.h"
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ProcessClient.h>

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Suspend the execution of the calling thread until a child specified by pid argument has changed state");
    parser().registerPositional("PROCESS_ID", "Suspend execution until the given pid argument changes state");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    const ProcessClient process;
    ProcessID pid = (atoi(arguments().get("PROCESS_ID")));
    
    ProcessClient::Info info;
    const ProcessClient::Result result = process.processInfo(pid, info);
    
    if (result == ProcessClient::Success) {
        waitpid(pid, 0, 0);        
    } else {
        // use FreeNOS convention for printing errors
        // (see Sleep.cpp:43,50 and ListFiles.cpp:88,98,140 for examples)
        ERROR("No process of ID '" << arguments().get("PROCESS_ID") << "' is found");
        return InvalidArgument;
    }
    
    // Done
    return Success;
}
