/*
** EPITECH PROJECT, 2019
** print.c
** File description:
** manage all print function
*/

#include "my.h"

int *print_player_move(int stick, int line, int *table)
{
    my_putstr("Player removed ");
    my_put_nbr(stick);
    my_putstr(" match(es) from line ");
    my_put_nbr(line);
    my_putchar('\n');
    return (table);
}

void print_game(int *table, int line)
{
    int space = line - 1;
    int aft_space;
    int j;

    for (int i = 0; i < line * 2 + 1; i += 1)
        my_putchar('*');
    for (j = 0; table[j] != -1; j += 1) {
        aft_space = space + (j * 2 + 1) - table[j];
        my_putstr("\n*");
        for (int i = 0; i < space; i += 1)
            my_putchar(' ');
        for (int i = 0; i < table[j]; i += 1)
            my_putchar('|');
        for (int i = 0; i < aft_space; i += 1)
            my_putchar(' ');
        my_putchar('*');
        space -= 1;
    }
    print_last_line(line);
}

void print_last_line(int line)
{
    my_putchar('\n');
    for (int i = 0; i < line * 2 + 1; i += 1)
        my_putchar('*');
    my_putchar('\n');
}

void print_ia_move(int stick, int line)
{
    my_putstr("AI removed ");
    my_put_nbr(stick);
    my_putstr(" match(es) from line ");
    my_put_nbr(line + 1);
    my_putchar('\n');
}

int *print_error_msg(int error, int max_stick, int *table, int line)
{
    if (error == 1) {
        my_putstr("Error: this line is out of range\n");
        return (player_play(table, max_stick, line));
    } else if (error == 2) {
        my_putstr("Error: invalid input (positive number expected)\n");
        return (player_play(table, max_stick, line));
    }
    if (error == 3) {
        my_putstr("Error: you cannot remove more than ");
        my_put_nbr(max_stick);
        my_putstr(" matches per turn\n");
        return (player_play(table, max_stick, line));
    } else if (error == 4) {
        my_putstr("Error: not enough matches on this line\n");
        return (player_play(table, max_stick, line));
    }
    my_putstr("Error: you have to remove at least one match\n");
    return (player_play(table, max_stick, line));
}
