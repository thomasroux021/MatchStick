/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** include
*/

#ifndef MY_H
#define MY_H

#include <stdio.h>
#include "../src/lib/my/lib.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

int *player_play_matches(int *table, int max_stick, int line, int line_put);
int *print_error_msg(int error, int max_stick, int *table, int line);
void print_player_move(int stick, int line);
int play(int *table, int max_stick, int line);
int *ia_play(int *table, int max_stick);
int *player_play(int *table, int max_stick, int line);
int detect_lose(int *table, int player);
void print_game(int *table, int line);
int *generate_table(int line);
void print_last_line(int line);
void print_ia_move(int stick, int line);
#endif
