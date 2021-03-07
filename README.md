# memloader
Load file to memory and execute using anonymous file descriptor

This repo contains source for two binaries. `memloader` will load and execute a local binary to memory. `memloadern` will download a binary using curl directly to memory and execute. 

Requires libcurl

# Installation
memloader: 
```make``` 

memloadern:
```make memloadern```

# Usage
``` 
    memloader [binary] 
    example: memloader /bin/python
```
    
``` 
    memloadern [url] [process name]
    example: memloadern localhost:80/bin /sbin/sshd
```

# More info
An anonymous file descriptor is created in memory using `memfd_create()`. The file can be executed in the first stage while the file descriptor is still open by accessing `/proc/<PID>/fd/<FD>`. Pressing `return` will execute the file and close file descriptor. The second argument to the `execl(2)` function will determine the process name. 
