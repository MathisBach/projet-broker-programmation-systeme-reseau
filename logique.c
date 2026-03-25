// Fonction pour initialiser le marché au lancement du serveur
#include "logique.h" // inclussion 
void initialiser_broker() {
    strcpy(catalogue[0].nom, "AAPL"); catalogue[0].prix = 150.0; catalogue[0].quantite_broker = 100;
    strcpy(catalogue[1].nom, "TSLA"); catalogue[1].prix = 200.0; catalogue[1].quantite_broker = 50;
    strcpy(catalogue[2].nom, "GOOG"); catalogue[2].prix = 100.0; catalogue[2].quantite_broker = 200;
}

// BONUS : Fonction simple d'offre et de demande (Variation dynamique)
void mettre_a_jour_prix(int id_produit, int est_un_achat, int quantite) {
    // Si achat (demande monte), le prix augmente de 1% par action achetée
    if (est_un_achat == 1) {
        catalogue[id_produit].prix = catalogue[id_produit].prix * (1.0 + (0.01 * quantite));
    } 
    // Si vente (offre monte), le prix baisse de 1% par action vendue
    else {
        catalogue[id_produit].prix = catalogue[id_produit].prix * (1.0 - (0.01 * quantite));
    }
}

// Fonction d'achat par le client
// Retourne 1 si succès, 0 si erreur (fonds ou stock insuffisants)
int client_achete(int index_client, int id_produit, int quantite_demandee) {
    float cout_total = catalogue[id_produit].prix * quantite_demandee;

    // Règle 1 : Le broker a-t-il assez de stock ?
    if (catalogue[id_produit].quantite_broker < quantite_demandee) {
        printf("Erreur : Le Broker n'a pas assez de produit.\n");
        return 0; 
    }

    // Règle 2 : Le client a-t-il les fonds ?
    if (liste_clients[index_client].solde_fonds < cout_total) {
        printf("Erreur : Le Client n'a pas les fonds suffisants.\n");
        return 0;
    }

    // Transaction acceptée : Mise à jour des données
    liste_clients[index_client].solde_fonds -= cout_total;
    liste_clients[index_client].inventaire[id_produit] += quantite_demandee;
    
    fonds_broker += cout_total;
    catalogue[id_produit].quantite_broker -= quantite_demandee;

    // Bonus : Mise à jour du prix
    mettre_a_jour_prix(id_produit, 1, quantite_demandee);
    
    return 1;
}

// Fonction de vente par le client
int client_vend(int index_client, int id_produit, int quantite_a_vendre) {
    float gain_total = catalogue[id_produit].prix * quantite_a_vendre;

    // Règle 1 : Le client a-t-il assez de ce produit ?
    if (liste_clients[index_client].inventaire[id_produit] < quantite_a_vendre) {
        printf("Erreur : Le client ne possède pas assez de ce produit.\n");
        return 0;
    }

    // Règle 2 : Le broker a-t-il les fonds pour lui racheter ?
    if (fonds_broker < gain_total) {
        printf("Erreur : Le Broker n'a pas les fonds pour racheter.\n");
        return 0;
    }

    // Transaction acceptée : Mise à jour des données
    liste_clients[index_client].solde_fonds += gain_total;
    liste_clients[index_client].inventaire[id_produit] -= quantite_a_vendre;
    
    fonds_broker -= gain_total;
    catalogue[id_produit].quantite_broker += quantite_a_vendre;

    // Bonus : Mise à jour du prix
    mettre_a_jour_prix(id_produit, 0, quantite_a_vendre);

    return 1;
}