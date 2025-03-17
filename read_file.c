/*
** EPITECH PROJECT, 2025
** B-PSU-100-MAR-1-1-mysudo-kyllian.garcia
** File description:
** read_file
*/

#include "my.h"

char *get_hashed_password(char *username)
{
    FILE *shadow = fopen("/etc/shadow", "r");
    char *hashed_password;
    char line[256];
    char *user;

    if (!shadow) {
        perror("fopen");
        return NULL;
    }
    while (fgets(line, sizeof(line), shadow)) {
        user = strtok(line, ":");
        if (strcmp(user, username) == 0) {
            hashed_password = strtok(NULL, ":");
            fclose(shadow);
            return strdup(hashed_password);
        }
    }
    fclose(shadow);
    return NULL;
}

int search_user(char *str)
{
    FILE *fichier;
    char ligne[256];
    char *user;
    char *uid_str;

    fichier = fopen("/etc/passwd", "r");
    if (fichier == NULL)
        return -1;
    while (fgets(ligne, sizeof(ligne), fichier)) {
        user = strtok(ligne, ":");
        if (strcmp(user, str) == 0) {
            strtok(NULL, ":");
            uid_str = strtok(NULL, ":");
            fclose(fichier);
            return atoi(uid_str);
        }
    }
    fclose(fichier);
    return -1;
}

int search_group(char *str)
{
    FILE *file = fopen("/etc/group", "r");
    char line[256];
    char *group;

    if (!file)
        return -1;
    while (fgets(line, sizeof(line), file)) {
        group = strtok(line, ":");
        if (strcmp(group, str) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}
