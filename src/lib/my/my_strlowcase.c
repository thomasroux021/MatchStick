/*
** EPITECH PROJECT, 2018
** my_strlowcase.c
** File description:
** tranform upper in lowcase
*/

#include "lib.h"

char *my_strlowcase(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] >= 65 && str[i] <= 90)
            str[i] = str[i] + 32;
        i += 1;
    }
    return (str);
}
