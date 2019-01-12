/*
** EPITECH PROJECT, 2019
** play.c
** File description:
** play
*/

#include "my.h"

int play(int *table, int max_stick, int line)
{
    while (1) {
        print_game(table, line);
        if (detect_lose(table, 0))
            return (1);
        my_putstr("\nYour turn:\n");
        table = player_play(table, max_stick, line);
        print_game(table, line);
        if (detect_lose(table, 1))
            return (2);
        my_putstr("\nAI's turn...\n");
        table = ia_play(table, max_stick);
    }
}

int *ia_play(int *table, int max_stick)
{
    int ia_line;
    int stick = 0;
    int mult;
    int j = 0;

    for (int i = 0; table[i] != -1; i += 1)
        j += table[i];
    mult = j - ((j / (max_stick + 1)) * (max_stick + 1) + 1);
    mult = (mult == -1)?max_stick:mult;
    for (int i = 0; table[i] != -1; i += 1) {
        if (table[i] > 0 && (!stick || (table[i] >= mult && stick < mult))) {
            stick = ((table[i] - mult < 0 && table[i] > 0) || !mult)?1:mult;
            ia_line = i;
        }
    }
    print_ia_move(stick, ia_line);
    table[ia_line] -= stick;
    return (table);
}

int detect_lose(int *table, int player)
{
    int stick = 0;

    for (int i = 0; table[i] != -1; i += 1) {
        if (table[i] >= 0)
            stick += table[i];
    }
    if (!stick && player) {
        my_putstr("You lost, too bad...\n");
        return (2);
    } else if (!stick && !player) {
        my_putstr("I lost... snif... but I'll get you next time!!\n");
        return (1);
    }
    return (0);
}
