/*
** EPITECH PROJECT, 2025
** authenticate_user.c
** File description:
** authenticate_user
*/

#include "my.h"

void disable_echo(struct termios *old, struct termios *new)
{
    tcgetattr(0, old);
    *new = *old;
    new->c_lflag &= ~ECHO;
    tcsetattr(0, 0, new);
}

int check_password(char *input, char *hashed_password)
{
    input[strcspn(input, "\n")] = '\0';
    return strcmp(crypt(input, hashed_password), hashed_password) == 0;
}

int authenticate_user(char *username)
{
    char *hashed_password = get_hashed_password(username);
    char input[128];
    struct termios old;
    struct termios new;

    for (int attempts = 0; attempts < 3; attempts++) {
        disable_echo(&old, &new);
        printf("[my_sudo] password for %s: ", username);
        fgets(input, sizeof(input), stdin);
        tcsetattr(0, 0, &old);
        printf("\n");
        if (check_password(input, hashed_password)) {
            free(hashed_password);
            return 1;
        }
        printf("Sorry, try again.\n");
    }
    return 0;
}
