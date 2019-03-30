#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define AUTH_CHECKSUM 338
#define MAX_AUTH_KEY_LENGTH 1024

int calculate_checksum(char auth_key[]) {

    int i;
    char temp_key[MAX_AUTH_KEY_LENGTH];

    strncpy(temp_key, auth_key, MAX_AUTH_KEY_LENGTH);

    // inc_data = [chr(ord(c)+1) for c in user_data]
    for (i = 0; i < strlen(temp_key); i++) {
        char current_char = temp_key[i];
        current_char++;
        temp_key[i] = current_char;
    }

    int checksum = 0;

    // for i in range(len(inc_data)//2):
    //     checksum += ord(inc_data[i]) ^ ord(inc_data[i+1])
    for (i = 0; i < strlen(temp_key)/2; i++) {
        checksum = checksum + (temp_key[i*2] ^ temp_key[(i*2)+1]);
    }
    return checksum;

}

int send_to_auth_server(char auth_key[]) {

    printf("Key verification succeeded, sending to server.\n");
    //https://gist.github.com/suyash/2488ff6996c98a8ee3a84fe3198a6f85#file-client-c
    const char* server_name = "35.245.13.199";
    const int server_port = 2019;

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;

    // creates binary representation of server name
    // and stores it as sin_addr
    // http://beej.us/guide/bgnet/output/html/multipage/inet_ntopman.html
    inet_pton(AF_INET, server_name, &server_address.sin_addr);

    // htons: port in network order format
    server_address.sin_port = htons(server_port);

    // open a stream socket
    int sock;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("could not create socket\n");
        return -1;
    }

    // TCP is connection oriented, a reliable connection
    // **must** be established before any data is exchanged
    if (connect(sock, (struct sockaddr*)&server_address,
                sizeof(server_address)) < 0) {
        printf("could not connect to server\n");
        return -1;
    }

    // send
    send(sock, auth_key, strlen(auth_key), 0);

    // receive

    int n = 0;
    int len = 0, maxlen = 100;
    char buffer[maxlen];
    char* pbuffer = buffer;

    // will remain open until the server terminates the connection
    while ((n = recv(sock, pbuffer, maxlen - 1, 0)) > 0) {
        pbuffer += n;
        maxlen -= n;
        len += n;

        buffer[len] = '\0';
        printf("Received: '%s'\n", buffer);
    }

    // close the socket
    close(sock);
    return 0;
}

void usage() {

    printf("Usage: auth_client <AUTH_KEY>\n");

}


int main(int argc, char* argv[]) {

    if (argc != 2) {
        usage();
        return -1;
    }

    if (strlen(argv[1]) >= MAX_AUTH_KEY_LENGTH) {
        return -1;
    }

    if(calculate_checksum(argv[1]) == AUTH_CHECKSUM) {
        return send_to_auth_server(argv[1]);
    }
    else {
        return -1;
    }
    return 0;
}
