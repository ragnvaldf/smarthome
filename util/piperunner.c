#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int pipeFd;
    char *pipePath;
    if (argc < 3 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        printf("%s <pipePath> <path to pipe writer program> [param, ...]\n", argv[0]);
	exit(1);
    }

    pipePath = argv[1]; // First parameter, pipePath is relative path to where fifo should be created

    if (mkfifo(pipePath, 0644) == -1) { // RW to user, RO to group and world
        printf("error creating pipe");
	exit(1);
    }

    pipeFd = open(pipePath, O_WRONLY); // This will block until someone opens fifo RO
    if (pipeFd == -1) {
        unlink(pipePath); // Unlink fifo from filesystem
	printf("error opening pipe");
	exit(1);
    }
    sleep(2); // Allow a two second grace time before
    unlink(pipePath); // unlinking fifo from filesystem

    int i;
    for (i = 0; i < argc - 2; i++) { // Shift argv contents by two,
       argv[i] = argv[i + 2]; // erasing the first two indexes
    }
    argv[i] = NULL;

    dup2(pipeFd, 1); // Make stdout write to fifo 
    
    if (execv(argv[0], argv) == -1) { // Replace process with pipe writer program
        printf("error executing program");
	exit(1);
    }
    exit(1);
}


