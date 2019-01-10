/*
** EPITECH PROJECT, 2019
** src/main.c
** File description:
** main
*/

int *generate_table(int line)
{
    int *table = malloc(sizeof(int) * (line + 1));
    int stick = 1;
    int i;

    for (i = 0; i < line; i += 1) {
        table[i] = stick;
        stick += 2;
    }
    table[i] = -1;
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
        aft_space = space;
        my_putstr("\n*");
        for (int i = 0; i < space; i += 1)
            my_putchar(' ');
        for (int i = 0; i < table[j]; i += 1)
            my_putchar('|');
        aft_space += (j * 2 + 1) - table[j];
        for (int i = 0; i < aft_space; i += 1)
            my_putchar(' ');
        my_putchar('*');
        space -= 1;
    }
    my_putchar('\n');
    for (int i = 0; i < line * 2 + 1; i += 1)
        my_putchar('*');
    my_putchar('\n');
}

int detect_lose(int *table, int player)
{
    int stick = 0;

    for (int i = 0; table[i] != -1; i += 1) {
        if (table[i] >= 0)
            stick += table[i];
    }
    if (stick > 0)
        return (0);
    if (!stick && player) {
        my_putstr("You lost, to bad...\n");
        return (2);
    } else if (!stick && !player) {
        my_putstr("I lost... snif... but I'll get you next time!!\n");
        return (1);
    }
}

int *player_play(int *table, int max_stick, int line)
{
    int size = 0;
    char buffer[20];
    int stick;
    int line_put;

    my_putstr("Line: ");
    size = read(0, buffer, 20);
    buffer[size - 1] = '\0';
    if (size > 8 || (line_put = my_getnbr(buffer)) > line || !line_put) {
        my_putstr("Error: this line is out of range\n");
        return (player_play(table, max_stick, line));
    } else if (line_put == -1) {
        my_putstr("Error: invalid input (positive number expected)\n");
        return (player_play(table, max_stick, line));
    }
    my_putstr("Matches: ");
    size = read(0, buffer, 20);
    buffer[size - 1] = '\0';
    if (size > 8 || (stick = my_getnbr(buffer)) > max_stick) {
        my_putstr("Error: you cannot remove more than ");
        my_put_nbr(max_stick);
        my_putstr(" matches per turn\n");
        return (player_play(table, max_stick, line));
    } else if (stick > table[line_put - 1]) {
        my_putstr("Error: not enough matches on this line\n");
        return (player_play(table, max_stick, line));
    }
    if (stick == -1) {
        my_putstr("Error: invalid input (positive number excepted)\n");
        return (player_play(table, max_stick, line));
    } else if (!stick) {
        my_putstr("Error: you have to remove at least one match\n");
        return (player_play(table, max_stick, line));
    }
    table[line_put - 1] -= stick;
    my_putstr("Player removed ");
    my_put_nbr(stick);
    my_putstr(" match(es) from line ");
    my_put_nbr(line_put);
    my_putchar('\n');
    return (table);
}
int *ia_play(int *table, int max_stick, int line)
{
    int ia_line;
    int stick = 0;
    int mult;
    int j = 0;

    for (int i = 0; table[i] != -1; i += 1)
        j += table[i];
    mult = j - ((j / (max_stick + 1)) * (max_stick + 1) + 1);
    mult = (mult == -1)?3:mult;
    for (int i = 0; table[i] != -1; i += 1) {
        if (table[i] > 0 && (!stick || (table[i] >= mult && stick < mult))) {
            stick = ((table[i] - mult < 0 && table[i] > 0) || !mult)?1:mult;
            ia_line = i;
        }
    }
    my_putstr("AI removed ");
    my_put_nbr(stick);
    my_putstr(" match(es) from line ");
    my_put_nbr(ia_line + 1);
    my_putchar('\n');
    table[ia_line] -= stick;
    return (table);
}

int play(int *table, int max_stick, int line)
{
    int play = 1;

    while (play) {
        print_game(table, line);
        if (detect_lose(table, 0))
            return (1);
        my_putstr("\nYour turn:\n");
        table = player_play(table, max_stick, line);
        print_game(table, line);
        if (detect_lose(table, 1))
            return (2);
        my_putstr("\nAI's turn...\n");
        table = ia_play(table, max_stick, line);
    }
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
    return (play(table, max_stick, line));
}
