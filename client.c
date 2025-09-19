#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // For close()

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    FILE *fp;
    char received_filename[256];

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Listen on all available interfaces
    address.sin_port = htons(PORT);

    // Bind the socket to the specified port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // Accept a new connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    // Receive the filename from the client
    memset(received_filename, 0, sizeof(received_filename));
    if (recv(new_socket, received_filename, sizeof(received_filename) - 1, 0) == -1) {
        perror("Error receiving filename");
        close(new_socket);
        close(server_fd);
        return -1;
    }
    printf("Receiving file: %s\n", received_filename);

    // Open a file to write the received data
    fp = fopen(received_filename, "wb"); // Open in binary write mode
    if (fp == NULL) {
        perror("Error opening file for writing");
        close(new_socket);
        close(server_fd);
        return -1;
    }

    // Receive file content and write to file
    ssize_t bytes_received;
    while ((bytes_received = recv(new_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, bytes_received, fp);
    }

    printf("File received successfully.\n");

    fclose(fp);
    close(new_socket);
    close(server_fd);

    return 0;
}
