#include "sauvegarde.h"
#include <stdio.h>

#define SAVE_FILE "save.txt"

bool save_progress(const GameContext *ctx) {
    FILE *file = fopen(SAVE_FILE, "w");
    if (!file) {
        perror("Impossible d'ouvrir le fichier de sauvegarde");
        return false;
    }

    // Sauvegarde des informations importantes du joueur dans le fichier
    fprintf(file, "OperateurName: %s, CurrentLevel: %i SurchargeLevel: %i",
            ctx->operator_name,
            ctx->current_level_idx,
            ctx->surcharge);
    
    fclose(file);
    return true;
}

bool load_progress(GameContext *ctx) {
    FILE *file = fopen(SAVE_FILE, "r");
    if (!file) {
        perror("Impossible de lire la sauvegarde");
        return false;
    }

    // Lecture des données sauvegardées dans le fichier
    // %49s limite la taille du nom lu pour éviter un dépassement de mémoire
    int result = fscanf(file, "OperateurName: %49s, CurrentLevel: %i SurchargeLevel: %i",
                        ctx->operator_name,
                        &ctx->current_level_idx,
                        &ctx->surcharge);

    fclose(file);

    // Si les 3 informations ont été correctement lues, le chargement réussit
    if (result == 3) {
        return true;
    } else {
        printf("Erreur : le fichier de sauvegarde est corrompu ou incomplet.\n");
        return false;
    }
}
