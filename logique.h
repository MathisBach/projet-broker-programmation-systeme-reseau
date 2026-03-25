#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUITS 3
#define MAX_CLIENTS 5

// 1. Définition du Produit
struct Produit {
    char nom[20];
    float prix;
    int quantite_broker; // Ce que le broker possède
};

// 2. Définition du Client (Son portefeuille)
struct Client {
    int id_socket;       // On utilise l'ID du socket (vu dans le Chapitre 2) pour l'identifier
    float solde_fonds;   // L'argent du client
    int inventaire[MAX_PRODUITS]; // Les actions du client (index aligné sur le catalogue)
};

// 3. Variables globales du Broker (Mémoire centrale du serveur)
struct Produit catalogue[MAX_PRODUITS];
struct Client liste_clients[MAX_CLIENTS];
float fonds_broker = 50000.0; // Le broker a une limite de fonds prévue à l'avance