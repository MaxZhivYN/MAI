#ifndef _BANK_H_
#define _BANK_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define fox_row 10
#define STR_SIZE 256

typedef struct _Fox_item {
    int number;
    bool is_fox;
    bool is_visible;
} Fox_item;

typedef struct _Game_place {
    Fox_item **fox_game_place;
    int number_of_players;
    
} Game_place;

typedef struct _Game_place_conect {
    Fox_item **fox_game_place;
    int id_game;
} Game_place_conect;

typedef struct _Turn {
    int row;
    int col;
} Turn; 

typedef struct _msg {
    Turn turn;
    int id_game;
    int id_client;
} MsgData;


void game_print(Fox_item **fox_game_place);
float get_rand();
float get_rand_range(const float min, const float max);
int col_find_fox(Fox_item **fox_game_place, int i, int j);
int row_find_fox(Fox_item **fox_game_place, int i, int j);
bool is_normal_limit(int row, int col);
int horizontal_find_fox(Fox_item **fox_game_place, int i, int j);
int find_fox_number(Fox_item **fox_game_place, int i, int j);
Fox_item** fox_game_place_create();




#endif