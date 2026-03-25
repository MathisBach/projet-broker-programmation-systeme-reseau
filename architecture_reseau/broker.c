
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

#define PORT 12345

void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
    int received_bytes;
    char buffer[1024];
    char *response = "Message bien reçu";

    FILE *log_file = fopen("log.txt", "a");
    if (log_file == NULL) {
        perror("Erreur ouverture log");
        close(client_socket);
        pthread_exit(NULL);
    }

    received_bytes = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (received_bytes == -1) {
        perror("Erreur recv");
        fprintf(log_file, "Erreur recv\n");
        close(client_socket);
        fclose(log_file);
        pthread_exit(NULL);
    }

    if (received_bytes == 0) {
        printf("Le client s'est déconnecté.\n");
        fprintf(log_file, "Client déconnecté\n");
        close(client_socket);
        fclose(log_file);
        pthread_exit(NULL);
    }

    buffer[received_bytes] = '\0';
    printf("Message reçu : %s\n", buffer);
    fprintf(log_file, "Message reçu : %s\n", buffer);

    if (send(client_socket, response, strlen(response), 0) == -1) {
        perror("Erreur send");
        fprintf(log_file, "Erreur send\n");
        close(client_socket);
        fclose(log_file);
        pthread_exit(NULL);
    }

    fprintf(log_file, "Client déconnecté\n");

    close(client_socket);
    fclose(log_file);
    pthread_exit(NULL);
}

int main() {
    int server_socket;
    int client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Erreur socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Erreur bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) == -1) {
        perror("Erreur listen");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Serveur Broker en attente de connexions sur le port %d...\n", PORT);

    while (1) {
        client_addr_len = sizeof(client_addr);

        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("Erreur accept");
            continue;
        }

        printf("Client connecté.\n");

        pthread_t thread_id;

        if (pthread_create(&thread_id, NULL, handle_client, (void *)&client_socket) != 0) {
            perror("Erreur pthread_create");
            close(client_socket);
            continue;
        }

        pthread_detach(thread_id);
    }

    close(server_socket);
    return 0;
}
