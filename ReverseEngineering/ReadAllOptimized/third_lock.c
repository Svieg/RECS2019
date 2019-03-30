#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

void usage() {

    printf("Usage: ./lock_two_service\n");

}

int main(int argc, char* argv[]) {

    if (argc != 1) {
        usage();
        return EXIT_FAILURE;
    }

    printf("ENTER KEY TO UNLOCK: \n");

    char key[10];

    read(0, key, 256);

    return 0;

}
