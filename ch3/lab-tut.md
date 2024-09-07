Lab tutorials

Sending signals to processes. Start five processes in the
background (these are processes that will just sleep for ten minutes
and then terminate unless we signal them)

`for i in {1..5}; do sleep 600 & done`
See them running as processes in your shell and that they are child
processes of your shell

`ps
pstree | grep -C 5 sleep`

> -C 5 means add the five lines before and after the result from grep

List the Process-ID (PID) of all processes named sleep

`pgrep sleep`
Send a signal to terminate one of them

kill PID_OF_ONE_THEM
Send a signal to terminate the rest of them

`killall sleep`
