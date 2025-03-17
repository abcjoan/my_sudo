/*
** EPITECH PROJECT, 2024
** my.h
** File description:
** my header who contains all prototypes
*/

#ifndef MY_H
    #define MY_H
    #include <stdlib.h>
    #include <unistd.h>
    #include <utmp.h>
    #include <sys/types.h>
    #include <fcntl.h>
    #include <time.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <ctype.h>
    #include <string.h>
    #include <stdio.h>
    #include <pwd.h>
    #include <errno.h>
    #include <crypt.h>
    #include <termios.h>
void my_sudo(int argc, char **array);
int authenticate_user(char *username);
int search_user(char *str);
int search_group(char *str);
char *get_hashed_password(char *username);
#endif
