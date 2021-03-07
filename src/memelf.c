/* Uses an anonymous file descriptor in order to load an ELF from memory.
 * The memfd_create(2) function is used to create a file descriptor in memory
 * to which the specified file is copied to.
 *
 * More info: http://gg.gg/ok98c 
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>


// creates anonymous file descriptor
int create_afd(void) {
    int afd;
   
    afd = memfd_create("", MFD_CLOEXEC); // closes file descriptor on execution

    if (afd < 0) {
        fprintf(stderr, "error creating file descriptor");
        exit(-1);
     }

    return afd;
}

// copy file to anonymous file descriptor
int copy_to_mem(int afd, char *file) {
    int fd;
    off_t sz;
    struct stat st;

    fd = open(file, 0);

    // get size of binary and use the value for buffer size 
    fstat(fd, &st); 
    sz = (long long int)st.st_size;
    char *buf[sz];

    read(fd, buf, sz);
    write(afd, buf, sz);

    close(fd);
}

int main(int argc, char *argv[]) {
    
    int afd;
    pid_t pid;
    char *path;
    char ch;
    
    if (argc < 2) {
       printf("usage: memload [binary]");
       exit(-1);
    }

    afd = create_afd();

    copy_to_mem(afd, argv[1]);

    // get path to anonymous file descriptor
    pid = getpid();
    asprintf(&path, "/proc/self/fd/%i", afd);
    
    /*wait for user input to continue.
     *leaving the program in this state will keep the file descriptor open and
     *allow you to execute the binary from memory.
     */
    printf("Created process with PID: %d\n", pid);
    printf("Binary: /proc/%d/fd/%i\n", pid, afd);
    ch = getchar();
    
    /*Execute binary closing file descriptor, process name will be second 
     *argument of execl(). 
     */
    execl(path, "/bin/date", NULL);

    return 0;
 }

