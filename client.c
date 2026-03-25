#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    //creer socket
    int sockClient;
    struct sockaddr_in serv_addr;
    char buffer[1024];
    char message[1024];
    sockClient = socket(AF_INET, SOCK_STREAM, 0);

      if (sockClient < 0) {
        perror("Erreur création socket");
        return 1;
    }

    //creer adresse serveur
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT)
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    //gestion erreur connexion
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Erreur connexion");
        return 1;
    }

    printf("Connecté au serveur Broker !\n");

    while(1) { printf("\nCommande (INFO, ACHAT, VENTE, DECONNEXION): ");
        fgets(message, sizeof(message), stdin);

        // enlever \n
        message[strcspn(message, "\n")] = 0;

        // envoyer au serveur
        send(sock, message, strlen(message), 0);

        // se déconnecter
        if (strcmp(message, "DECONNEXION") == 0) {
            printf("Déconnexion...\n");
            break;}
          memset(buffer, 0, sizeof(buffer));
          read(sock, buffer, sizeof(buffer));

      printf("Réponse serveur : %s\n", buffer);
}
//fermer socket
 int close(int fd);
 return 0;

}