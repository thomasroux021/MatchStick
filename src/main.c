/*
** EPITECH PROJECT, 2019
** src/main.c
** File description:
** main
*/

#include "my.h"

int *generate_table(int line)
{
    int *table = malloc(sizeof(int) * (line + 1));
    int stick = 1;
    int i;

    if (table == NULL)
        return (NULL);
    for (i = 0; i < line; i += 1) {
        table[i] = stick;
        stick += 2;
    }
    table[i] = -1;
    return (table);
}

int *player_play(int *table, int max_stick, int line)
{
    int size = 0;
    char buffer[1001];
    int line_put;

    my_putstr("Line: ");
    size = read(0, buffer, 1000);
    if (size == -1)
        return (NULL);
    (buffer[size - 1] == '\n')?(buffer[size - 1] = '\0'):(buffer[size] = '\0');
    if (size > 8 || (line_put = my_getnbr(buffer)) > line || !line_put)
        return (print_error_msg(1, max_stick, table, line));
    if (line_put == -1)
        return (print_error_msg(2, max_stick, table, line));
    my_putstr("Matches: ");
    return (player_play_matches(table, max_stick, line, line_put));
}

int *player_play_matches(int *table, int max_stick, int line, int line_put)
{
    int size = 0;
    char buffer[1001];
    int stick;

    size = read(0, buffer, 1000);
    if (size == -1)
        return (NULL);
    (buffer[size - 1] == '\n')?(buffer[size - 1] = '\0'):(buffer[size] = '\0');
    if (size > 8 || (stick = my_getnbr(buffer)) > max_stick)
        return (print_error_msg(3, max_stick, table, line));
    if (stick > table[line_put - 1])
        return (print_error_msg(4, max_stick, table, line));
    if (stick == -1)
        return (print_error_msg(2, max_stick, table, line));
    if (!stick)
        return (print_error_msg(5, max_stick, table, line));
    table[line_put - 1] -= stick;
    print_player_move(stick, line_put);
    return (table);
}

int main(int ac, char **av)
{
    int line;
    int max_stick;
    int *table;

    if (ac != 3)
        return (84);
    line = my_getnbr(av[1]);
    max_stick = my_getnbr(av[2]);
    if (line == -1 || max_stick == -1 || line >= 100 || !line || !max_stick)
        return (84);
    table = generate_table(line);
    if (table == NULL)
        return (84);
    return (play(table, max_stick, line));
}
