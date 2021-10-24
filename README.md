# client_server_signal_talk
Communication of processes using signals.  
Only two signals are used: SIGUSR1 and SIGUSR2

Compile: `make`    
Run: `./server`  
Run: `./client [PID] [string]`  
The client take as parameters:  
* The server PID.
* The string that should be sent.

![terminal](https://github.com/hyoghurt/client_server_signal_talk/raw/master/terminal.png)
