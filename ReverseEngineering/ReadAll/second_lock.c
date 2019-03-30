#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

void execute_command(const char command[]) {

    execve("/bin/sh", 0, 0);

}

void usage() {

    printf("Usage: ./lock_two_service\n");

}

int main(int argc, char* argv[]) {

    if (argc != 1) {
        usage();
        return EXIT_FAILURE;
    }

    char key[10];

    read(0, key, 128);

    //execute_command("/bin/sh");
    return 0;

}
