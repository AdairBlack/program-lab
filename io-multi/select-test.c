#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>

#define MAX_BUFFER 1024

int main(void) {
    int pipefds1[2], pipefds2[2];
    int ret;
    char buf[MAX_BUFFER];
    fd_set inputs, temp;

    if (pipe(pipefds1) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefds2) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // write something to the pipes
    write(pipefds1[1], "Hello pipe1", 12);
    write(pipefds2[1], "Hello pipe2", 12);

    FD_ZERO(&inputs);
    FD_SET(pipefds1[0], &inputs);
    FD_SET(pipefds2[0], &inputs);

    while(1) {
        temp = inputs;
        ret = select(FD_SETSIZE, &temp, NULL, NULL, NULL);

        if(ret < 0) {
            perror("select");
            exit(EXIT_FAILURE);
        }

        if(FD_ISSET(pipefds1[0], &temp)) {
            read(pipefds1[0], buf, MAX_BUFFER);
            printf("Read from pipe 1: %s\n", buf);
            FD_CLR(pipefds1[0], &inputs);
        }

        if(FD_ISSET(pipefds2[0], &temp)) {
            read(pipefds2[0], buf, MAX_BUFFER);
            printf("Read from pipe 2: %s\n", buf);
            FD_CLR(pipefds2[0], &inputs);
        }

        // if both pipes have been read, break the loop
        if (!FD_ISSET(pipefds1[0], &inputs) && !FD_ISSET(pipefds2[0], &inputs))
            break;
    }

    return 0;
}
