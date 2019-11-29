#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <inttypes.h>
#include <stdbool.h>
#include "ohota.h"

#define STR_SIZE 256

typedef double ID;

/*
typedef struct _Fox_item {
    int number;
    bool is_fox;
    bool is_visible;
} Fox_item;
*/

typedef struct _msg {
    ID client;
    int sum;
    int action;
    ID receiverClient;
    void *requester;
    char message[STR_SIZE];
    char fileName[STR_SIZE];
    //Fox_item **fox_game_place;
} MsgData;

#endif