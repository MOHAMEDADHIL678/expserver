#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_PORT 8080
#define SERVER_ADDR "127.0.0.1"
#define BUFF_SIZE 10000

int main() {
  // Creating sock
  int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

  // Creating an object of struct socketaddr_in
  struct sockaddr_in server_addr;

  // Setting up server addr
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(SERVER_PORT);
  server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

  // Connecting to server
  if(connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0) {
    printf("[ERROR] Connection failed\n");
    exit(1);
  }else{
    printf("[INFO] Connected to tcp server\n");
  }
  

    while (1) {

        // Get message from client terminal
        char *line = NULL;
        size_t line_len = 0;
        ssize_t read_n;

        read_n = getline(&line, &line_len, stdin);

        /* send message to tcp server using send() */
        send(sock_fd, line, read_n, 0);
        printf("Sent: %s", line);

        /* create a char buffer of BUFF_SIZE and memset to 0 */
        char buff[BUFF_SIZE];
        memset(buff, 0, BUFF_SIZE);

        // Read message from client to buffer
        read_n = recv(sock_fd, buff, sizeof(buff), 0);

        /* close the connection and exit if read_n <= 0 */
        if (read_n <= 0) {
            printf("[INFO] Server disconnected. Closing client\n");
            close(sock_fd);
            exit(1);
        }

        // Print message from cilent
        printf("[SERVER MESSAGE] %s\n", buff);

        // break;
    }

    close(sock_fd);

    return 0;

}

