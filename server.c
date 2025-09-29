#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> // For close()

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    FILE *fp;
    char buffer[BUFFER_SIZE] = {0};
    char *filename = "test_file.txt"; // File to send

    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }

    // Open the file to send
    fp = fopen(filename, "rb"); // Open in binary read mode
    if (fp == NULL) {
        perror("Error opening file");
        close(sock);
        return -1;
    }

    // Send the filename to the server (optional, for server to know what to save as)
    send(sock, filename, strlen(filename), 0);
    printf("Sending filename: %s\n", filename);

    // Read file content and send to server
    ssize_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, fp)) > 0) {
        if (send(sock, buffer, bytes_read, 0) == -1) {
            perror("Error sending file data");
            break;
        }
    }

    printf("File sent successfully.\n");

    fpclose(fp);
    close(sock);

    return 0;
}

scp user1@host1.com:/files/test.txt user2@host2.com:/files

