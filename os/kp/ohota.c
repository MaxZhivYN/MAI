#include "ohota.h"


const float RAND_MAX_F = RAND_MAX;

void game_print(Fox_item **fox_game_place)
{
    for (int i = 0; i < fox_row; i++) {
        for (int j = 0; j < fox_row; j++) {
            if (fox_game_place[i][j].is_fox)
                printf("F");
            else
                printf("%d", fox_game_place[i][j].number);
            printf(" ");
        }
        printf("\n");
    }
}

float get_rand() 
{
    return rand() / RAND_MAX_F;
}

float get_rand_range(const float min, const float max) 
{
    return get_rand() * (max - min) + min;
}

int col_find_fox(Fox_item **fox_game_place, int i, int j)
{
    int fox_find_count = 0;
    for (int k = 0; k < fox_row; k++) {
        if (k != i && fox_game_place[k][j].is_fox)
            fox_find_count++;
    }
    return fox_find_count;
}

int row_find_fox(Fox_item **fox_game_place, int i, int j)
{
    int fox_find_count = 0;
    for (int k = 0; k < fox_row; k++) {
        if (k != j && fox_game_place[i][k].is_fox)
            fox_find_count++;
    }
    return fox_find_count;
}

bool is_normal_limit(int row, int col)
{
    return 0 <= row && row < fox_row && 0 <= col && col < fox_row;
}

int horizontal_find_fox(Fox_item **fox_game_place, int i, int j)
{
    int fox_find_count = 0;
    int row = i, col = j;
    while (is_normal_limit(row + 1, col + 1)) {
        if (fox_game_place[++row][++col].is_fox)
            fox_find_count++;
    }
    row = i;
    col = j;
    while (is_normal_limit(row + 1, col - 1)) {
        if (fox_game_place[++row][--col].is_fox)
            fox_find_count++;
    }
    row = i;
    col = j;
    while (is_normal_limit(row - 1, col - 1)) {
        if (fox_game_place[--row][--col].is_fox)
            fox_find_count++;
    }
    row = i;
    col = j;
    while (is_normal_limit(row - 1, col + 1)) {
        if (fox_game_place[--row][++col].is_fox)
            fox_find_count++;
    }
    return fox_find_count;
}

int find_fox_number(Fox_item **fox_game_place, int i, int j)
{
    return (horizontal_find_fox(fox_game_place, i, j) + row_find_fox(fox_game_place, i, j) + col_find_fox(fox_game_place, i, j));
}

Fox_item** fox_game_place_create() 
{
    Fox_item **fox_game_place = (Fox_item**)malloc(fox_row * sizeof(Fox_item*));
    for (int i = 0; i < fox_row; i++) {
        fox_game_place[i] = (Fox_item*)malloc(fox_row * sizeof(Fox_item));
        for (int j = 0; j < fox_row; j++) {
            fox_game_place[i][j].is_fox = false;
            fox_game_place[i][j].is_visible = false;
            //fox_game_place[i][j].number = 0;
        }
    }

    srand(time(NULL));
    int fox_count = 0, i, j;
    while (fox_count < fox_row) {
        i = get_rand_range(0, fox_row);
        j = get_rand_range(0, fox_row);
        if (!fox_game_place[i][j].is_fox) {
            fox_game_place[i][j].is_fox = true;
            fox_count++;
        } 
    }
    for (int i = 0; i < fox_row; i++) 
        for (int j = 0; j < fox_row; j++) 
            if (!fox_game_place[i][j].is_fox)
                fox_game_place[i][j].number = find_fox_number(fox_game_place, i, j);

    return fox_game_place;
}
