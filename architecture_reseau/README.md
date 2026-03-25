
# Partie Architecture Réseau – Broker (Alae Ddine AFRAKLA)

## 1. Objectif du projet

Dans ce projet, j’ai réalisé la partie serveur. Mon objectif était de créer un point central pour gérer les connexions des clients et permettre leur communication.

## 2. Choix d'architecture

J'ai mis en place un broker centralisé pour gérer les clients. Côté réseau, j'ai préféré utiliser **TCP** pour avoir une connexion stable et sans perte de données.

## 3. Fonctionnement du serveur

Le cycle de vie de mon serveur suit les étapes standards en C :

1. Création du socket avec `socket()`
2. Association au port avec `bind()`
3. Mise en écoute avec `listen()`
4. Acceptation des clients avec `accept()`

Une fois le client connecté, le serveur lit son message avec `recv()`, l’affiche, puis lui envoie une réponse avec `send()`.

## 4. Gestion de plusieurs clients

Pour gérer plusieurs clients en même temps sans bloquer le serveur, j’ai utilisé les threads avec la bibliothèque `pthread`. 
Chaque client est traité dans un thread séparé. Ainsi, le serveur reste toujours disponible pour accepter de nouvelles connexions.

## 5. Gestion des logs

Pour garder une trace de l'activité, le serveur enregistre les actions importantes dans un fichier `log.txt`.

## 6. Lancement et test

J'ai compilé et testé ce projet sur un terminal Linux (WSL).

### Compilation

```bash
gcc broker.c -o broker -pthread
gcc client_test.c -o client_test

```
### Lancer le serveur _ Terminal 1

./broker

### Lancer le client _ Terminal 2

./client_test
