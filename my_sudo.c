/*
** EPITECH PROJECT, 2025
** my_sudo.c
** File description:
** my sudo
*/

#include "my.h"

void u_flag(int argc, char **array, uid_t target_uid, uid_t real_uid)
{
    if (argc < 4) {
        fprintf(stderr, "Error: Missing command after -u option\n");
        exit(1);
    }
    target_uid = search_user(array[2]);
    if (target_uid == -1) {
        fprintf(stderr, "Error: User %s not found\n", array[2]);
        exit(1);
    }
    if (setreuid(real_uid, target_uid) != 0) {
        perror("setreuid");
        exit(1);
    }
    execvp(array[3], &array[3]);
}

void g_flag(int argc, char **array, gid_t target_gid, gid_t real_gid)
{
    if (argc < 4) {
        fprintf(stderr, "Error: Missing command after -g option\n");
        exit(1);
    }
    target_gid = search_group(array[2]);
    if (target_gid == -1) {
        fprintf(stderr, "Error: Group %s not found\n", array[2]);
        exit(1);
    }
    if (setregid(real_gid, target_gid) != 0) {
        perror("setregid");
        exit(1);
    }
    execvp(array[3], &array[3]);
}

void my_sudo(int argc, char **array)
{
    uid_t real_uid = getuid();
    gid_t real_gid = getgid();
    uid_t target_uid;
    gid_t target_gid;

    if (strcmp(array[1], "-u") == 0)
        return u_flag(argc, array, target_uid, real_uid);
    if (strcmp(array[1], "-g") == 0)
        return g_flag(argc, array, target_gid, real_gid);
    if (setreuid(real_uid, 0) != 0) {
        perror("setreuid");
        exit(84);
    }
    execvp(array[1], &array[1]);
    perror("execvp");
    exit(84);
}

int wrong_argument(int argc, char **argv)
{
    if (argc > 1 && argv[1][0] == '-' &&
        strcmp(argv[1], "-u") != 0 &&
        strcmp(argv[1], "-g") != 0 &&
        strcmp(argv[1], "-h") != 0) {
        printf("sudo: invalid option -- '%c'\n", argv[1][1]);
        write(1, "usage: ./my_sudo -h\n", 21);
        write(1, "usage: ./my_sudo [-ugEs] [command [args ...]]\n", 47);
        return 84;
    }
    if (argc > 1 && (strcmp(argv[1], "-u") == 0 ||
        strcmp(argv[1], "-g") == 0)) {
        if (argc < 4) {
            printf("sudo: option requires an argument -- '%c'\n", argv[1][1]);
            write(1, "usage: ./my_sudo -h\n", 21);
            write(1, "usage: ./my_sudo [-ugEs] [command [args ...]]\n", 47);
            return 84;
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    char *username = getenv("USER");

    if (argc == 1 || argc == 2 && strcmp(argv[1], "-h") == 0){
        write(1, "usage: ./my_sudo -h\n", 21);
        write(1, "usage: ./my_sudo [-ugEs] [command [args ...]]\n", 47);
        return 0;
    }
    if (wrong_argument(argc, argv) == 84) {
        return 84;
    }
    if (!authenticate_user(username)) {
        printf("Authentication failed.\n");
        return 84;
    }
    my_sudo(argc, argv);
    return 0;
}
