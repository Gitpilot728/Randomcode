#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd;
    char buffer[100];
    const char *data = "This is sample text for file operations in Linux.\n";

    // 1. Open a file, write into it, and read back
    fd = open("original.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening original.txt");
        exit(1);
    }

    // Write data to the file
    if (write(fd, data, strlen(data)) == -1) {
        perror("Error writing to original.txt");
        close(fd);
        exit(1);
    }

    // Move file pointer to the beginning to read
    lseek(fd, 0, SEEK_SET);

    // Read back the written data
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("Error reading from original.txt");
        close(fd);
        exit(1);
    }
    buffer[bytes_read] = '\0'; // Null-terminate the string

    printf("Data read from original.txt:\n%s\n", buffer);
    close(fd);

    // 2. Open 4 files and copy the same data into them
    const char *files[] = {"copy1.txt", "copy2.txt", "copy3.txt", "copy4.txt"};
    int fds[4];

    for (int i = 0; i < 4; i++) {
        fds[i] = open(files[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
        if (fds[i] == -1) {
            perror("Error opening destination file");
            // Close any already opened files before exiting
            for (int j = 0; j < i; j++) close(fds[j]);
            exit(1);
        }

        // Write the same data into each file
        if (write(fds[i], data, strlen(data)) == -1) {
            perror("Error writing to destination file");
            for (int j = 0; j <= i; j++) close(fds[j]);
            exit(1);
        }

        printf("Data copied to %s successfully.\n", files[i]);
    }

    // Close all files
    for (int i = 0; i < 4; i++) {
        close(fds[i]);
    }

    printf("All file operations completed successfully.\n");
    return 0;
}
