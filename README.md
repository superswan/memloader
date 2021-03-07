# memloader
Load file to memory and execute using anonymous file descriptor

# Installtion
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
An anonymous file descriptor is created in memory using `memfd_create()`. The file can be executed in the first stage while the file descriptor is still open by accessing /proc/<PID>/fd/<FD>. Pressing `return` will execute the file and close file descriptor. The second argument to the `execl(2)` will determine the process name. 
