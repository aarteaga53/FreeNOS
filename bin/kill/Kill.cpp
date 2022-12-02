#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "Kill.h"
#include <ProcessClient.h>

Kill::Kill(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Send a kill signal to a process");
    parser().registerPositional("PROCESS_ID", "Process id to kill");
}

Kill::~Kill()
{
}

Kill::Result Kill::exec() {
    const ProcessClient process;
    ProcessID pid = (atoi(arguments().get("PROCESS_ID")));
    
    ProcessClient::Info info;
    const ProcessClient::Result result = process.processInfo(pid, info);

    if (result == ProcessClient::Success) {
        kill(pid, SIGKILL);    
    } else {
        // use FreeNOS convention for printing errors
        // (see Sleep.cpp:43,50 and ListFiles.cpp:88,98,140 for examples)
        ERROR("No process of ID '" << arguments().get("PROCESS_ID") << "' is found");
        return InvalidArgument;
    }

    // Done
    return Success;
}
