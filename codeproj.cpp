 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 50
#define MAX_CARS 100

struct Car {
    char ID[MAX_STRING_LENGTH];
    char Marque[MAX_STRING_LENGTH];
    char NomUtilisateur[MAX_STRING_LENGTH];
    char Modele[MAX_STRING_LENGTH];
    char TypeCarburant[MAX_STRING_LENGTH];
    char NbrePlaces[MAX_STRING_LENGTH];
    char Transmission[MAX_STRING_LENGTH];
    float PrixLocationJour;
    char Disponibilite[MAX_STRING_LENGTH];
};

void ajouterVoiture(struct Car cars[], int *nbreCars, FILE *fichier) {
    rewind(fichier);

    // Skip the header line
    char header[1024];
    fgets(header, sizeof(header), fichier);

    // Move the file pointer to the end of the file for appending new data
    fseek(fichier, 0, SEEK_END);

    printf("ID: ");
    scanf("%s", cars[*nbreCars].ID);
    printf("Marque: ");
    scanf("%s", cars[*nbreCars].Marque);
    printf("NomUtilisateur: ");
    scanf("%s", cars[*nbreCars].NomUtilisateur);
    printf("Modele: ");
    scanf("%s", cars[*nbreCars].Modele);
    printf("TypeCarburant: ");
    scanf("%s", cars[*nbreCars].TypeCarburant);
    printf("NbrePlaces: ");
    scanf("%s", cars[*nbreCars].NbrePlaces);
    printf("Transmission: ");
    scanf("%s", cars[*nbreCars].Transmission);
    printf("PrixLocationJour: ");
    scanf("%f", &cars[*nbreCars].PrixLocationJour);
    printf("Disponibilite: ");
    scanf("%s", cars[*nbreCars].Disponibilite);

    fprintf(fichier, "%s,%s,%s,%s,%s,%s,%s,%.2f,%s\n", cars[*nbreCars].ID, cars[*nbreCars].Marque, cars[*nbreCars].NomUtilisateur, cars[*nbreCars].Modele, cars[*nbreCars].TypeCarburant, cars[*nbreCars].NbrePlaces, cars[*nbreCars].Transmission, cars[*nbreCars].PrixLocationJour, cars[*nbreCars].Disponibilite);

    *nbreCars = *nbreCars + 1;
}

void afficherVoiture(FILE *fichier) {
    rewind(fichier);
    char line[1024];
    while (fgets(line, sizeof(line), fichier)) {
        printf("%s", line);
    }
}
void modifierVoiture(struct Car cars[], int nbreCars, FILE *fichier) {
    char id[MAX_STRING_LENGTH];
    printf("ID de la voiture à modifier: ");
    scanf("%s", id);

    // Modifier les données et sauvegarder les modifications dans le fichier
    for (int i = 0; i < nbreCars; i++) {
        if (strcmp(cars[i].ID, id) == 0) {
            printf("Marque: ");
            scanf("%s", cars[i].Marque);
            printf("NomUtilisateur: ");
            scanf("%s", cars[i].NomUtilisateur);
            printf("Modele: ");
            scanf("%s", cars[i].Modele);
            printf("TypeCarburant: ");
            scanf("%s", cars[i].TypeCarburant);
            printf("NbrePlaces: ");
            scanf("%s", cars[i].NbrePlaces);
            printf("Transmission: ");
            scanf("%s", cars[i].Transmission);
            printf("PrixLocationJour: ");
            scanf("%f", &cars[i].PrixLocationJour);
            printf("Disponibilite: ");
            scanf("%s", cars[i].Disponibilite);

            // Réécrire toutes les données dans un fichier temporaire
            FILE *temp = fopen("temp.csv", "w");
            if (temp == NULL) {
                printf("Erreur lors de la création du fichier temporaire\n");
                return;
            }

            // Réécrire l'en-tête
            fprintf(temp, "ID,Marque,NomUtilisateur,Modele,TypeCarburant,NbrePlaces,Transmission,PrixLocationJour,Disponibilite\n");

            // Réécrire toutes les données de voiture
            for (int j = 0; j < nbreCars; j++) {
                fprintf(temp, "%s,%s,%s,%s,%s,%s,%s,%.2f,%s\n", cars[j].ID, cars[j].Marque, cars[j].NomUtilisateur, cars[j].Modele, cars[j].TypeCarburant, cars[j].NbrePlaces, cars[j].Transmission, cars[j].PrixLocationJour, cars[j].Disponibilite);
            }

            fclose(temp);

            // Remplacer le fichier original par le fichier temporaire
            if (remove("cars.csv") != 0) {
                printf("Erreur lors de la suppression du fichier original\n");
                return;
            }

            if (rename("temp.csv", "cars.csv") != 0) {
                printf("Erreur lors du renommage du fichier temporaire\n");
                return;
            }

            printf("Les modifications ont été enregistrées avec succès.\n");
            return;
        }
    }

    printf("Aucune voiture trouvée avec cet ID.\n");
}


void supprimerVoiture(struct Car cars[], int *nbreCars) {
    char id[MAX_STRING_LENGTH];
    printf("ID de la voiture à supprimer: ");
    scanf("%s", id);

    for (int i = 0; i < *nbreCars; i++) {
        if (strcmp(cars[i].ID, id) == 0) {
            for (int j = i; j < *nbreCars - 1; j++) {
                cars[j] = cars[j + 1];
            }
            *nbreCars = *nbreCars - 1;
            break;
        }
    }
}

void rechercherVoitureParDisponibilite(struct Car cars[], int nbreCars) {
    char disponibilite[MAX_STRING_LENGTH];
    printf("Disponibilite: ");
    scanf("%s", disponibilite);

    for (int i = 0; i < nbreCars; i++) {
        if (strcmp(cars[i].Disponibilite, disponibilite) == 0) {
            printf("ID: %s\n", cars[i].ID);
            printf("Marque: %s\n", cars[i].Marque);
            printf("NomUtilisateur: %s\n", cars[i].NomUtilisateur);
            printf("Modele: %s\n", cars[i].Modele);
            printf("TypeCarburant: %s\n", cars[i].TypeCarburant);
            printf("NbrePlaces: %s\n", cars[i].NbrePlaces);
            printf("Transmission: %s\n", cars[i].Transmission);
            printf("PrixLocationJour: %.2f\n", cars[i].PrixLocationJour);
            printf("Disponibilite: %s\n", cars[i].Disponibilite);
            printf("\n");
        }
    }
}

void rechercherVoitureParMarque(struct Car cars[], int nbreCars) {
    char marque[MAX_STRING_LENGTH];
    printf("Marque: ");
    scanf("%s", marque);

    for (int i = 0; i < nbreCars; i++) {
        if (strcmp(cars[i].Marque, marque) == 0) {
            printf("ID: %s\n", cars[i].ID);
            printf("Marque: %s\n", cars[i].Marque);
            printf("NomUtilisateur: %s\n", cars[i].NomUtilisateur);
            printf("Modele: %s\n", cars[i].Modele);
            printf("TypeCarburant: %s\n", cars[i].TypeCarburant);
            printf("NbrePlaces: %s\n", cars[i].NbrePlaces);
            printf("Transmission: %s\n", cars[i].Transmission);
            printf("PrixLocationJour: %.2f\n", cars[i].PrixLocationJour);
            printf("Disponibilite: %s\n", cars[i].Disponibilite);
            printf("\n");
        }
    }
}

void trier_par_marque(struct Car cars[], int nbreCars) {
    struct Car temp;
    for (int i = 0; i < nbreCars - 1; i++) {
        for (int j = i + 1; j < nbreCars; j++) {
            if (strcmp(cars[i].Marque, cars[j].Marque) > 0) {
                temp = cars[i];
                cars[i] = cars[j];
                cars[j] = temp;
            }
        }
    }
}


void trier_par_prix(struct Car cars[], int nbreCars) {
    struct Car temp;
    for (int i = 0; i < nbreCars - 1; i++) {
        for (int j = i + 1; j < nbreCars; j++) {
            if (cars[i].PrixLocationJour > cars[j].PrixLocationJour) {
                temp = cars[i];
                cars[i] = cars[j];
                cars[j] = temp;
            }
        }
    }
}

int main() {
    FILE *fichier = fopen("cars.csv", "a+");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        return 1;
    }
    // make sure the csv file contains the fields of the structure Car
    fprintf(fichier, "ID,Marque,NomUtilisateur,Modele,TypeCarburant,NbrePlaces,Transmission,PrixLocationJour,Disponibilite\n");

    struct Car cars[MAX_CARS];
    int nbreCars = 0;

    char choix;
    do {
        printf("1. Ajouter voiture\n");
        printf("2. Afficher voiture\n");
        printf("3. Modifier voiture\n");
        printf("4. Supprimer voiture\n");
        printf("5. Rechercher voiture par disponibilite\n");
        printf("6. Rechercher voiture par marque\n");
        printf("7. Trier par marque\n");
        printf("8. Trier par prix\n");
        printf("9. Quitter\n");
        printf("Choix: ");
        scanf(" %c", &choix);

        switch (choix) {
            case '1':
                ajouterVoiture(cars, &nbreCars, fichier);
                break;
            case '2':
                afficherVoiture(fichier);
                break;
            case '3':
                modifierVoiture(cars, nbreCars, fichier);
                break;
            case '4':
                supprimerVoiture(cars, &nbreCars);
                break;
            case '5':
                rechercherVoitureParDisponibilite(cars, nbreCars);
                break;
            case '6':
                rechercherVoitureParMarque(cars, nbreCars);
                break;
            case '7':
                trier_par_marque(cars, nbreCars);
                break;
            case '8':
                trier_par_prix(cars, nbreCars);
                break;
            case '9':
                break;
            default:
                printf("Choix invalide\n");
        }
    } while (choix != '9');

    fclose(fichier);
    return 0;
}
