#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stropts.h>
#include <signal.h>

#include "zmq.h"
#include "ohota.h"




int main(void)
{
    void *context = zmq_ctx_new();
    void *responsSocket = zmq_socket(context, ZMQ_REP);
    char adress[25] = "tcp://*:4040";
    zmq_bind(responsSocket, adress);

    int free_id_client = 1;
    int free_id_game = 1;
    

    while (1) {
        zmq_msg_t message;
        zmq_msg_init(&message);
        zmq_msg_recv(&message, responsSocket, 0);
        MsgData *md = (MsgData *) zmq_msg_data(&message);
        zmq_msg_close(&message);

        if (md->id_client == 0) {
            int *id_client = &free_id_client;
            
            zmq_msg_init_size(&message, sizeof(int));
            memcpy(zmq_msg_data(&message), id_client, sizeof(int));
            zmq_msg_send(&message, responsSocket, 0);
            zmq_msg_close(&message);
            free_id_client++;
        }
        else 
        if (md->id_game == 0) {
            Game_place_conect *local_place = (Game_place_conect*) malloc(sizeof(Game_place_conect));
            local_place->fox_game_place = (Fox_item**) malloc(sizeof(Fox_item*));
            for (int i = 0; i < fox_row; i++)
                local_place->fox_game_place[i] = (Fox_item*) malloc(sizeof(Fox_item));
            local_place->fox_game_place = fox_game_place_create();
            //Fox_item **fox_game_place = fox_game_place_create();
            //local_place->fox_game_place = fox_game_place;
            game_print(local_place->fox_game_place);
            local_place->id_game = free_id_game;
            free_id_game++;
            

            zmq_msg_init_size(&message, sizeof(Game_place_conect) + sizeof(Fox_item) * 100);
            memcpy(zmq_msg_data(&message), local_place, sizeof(Game_place_conect));
            zmq_msg_send(&message, responsSocket, 0);
            zmq_msg_close(&message);
        }
            
        
        /*
        switch (1) {
        case 1: {
            //printf("Put money into the account id: %f\n", md->client);
            //MoneyPut(md->client, md->sum, clientBase);
            //ClientDBPrint(clientBase);
            strcpy(info, "Operation was completed successfully\0");
            memcpy(md->message, info, strlen(info) + 1);
            zmq_msg_init_size(&message, sizeof(MsgData));
            memcpy(zmq_msg_data(&message), md, sizeof(MsgData));
            zmq_msg_send(&message, responsSocket, 0);
            zmq_msg_close(&message);
            break;
        }

        case 2: {
            printf("Get money from the account id: %f\n", md->client);

            //code = MoneyGet(md->client, md->sum, clientBase);
            
            if (code == SUCCESS) {
                printf("Success\n");
                ClientDBPrint(clientBase);
                strcpy(info, "Operation was completed successfully\0");
            } else if (code == NOT_ENOUGH_MONEY) {
                printf("Not enough money\n");
                strcpy(info, "You not enough money\0");
            } else {
                printf("Not bank client\n");
                strcpy(info, "You aren't a client of bank\0");
            }
            
            memcpy(md->message, info, strlen(info) + 1);
            zmq_msg_init_size(&message, sizeof(MsgData));
            memcpy(zmq_msg_data(&message), md, sizeof(MsgData));
            zmq_msg_send(&message, responsSocket, 0);
            zmq_msg_close(&message);

            break;
        }

        case 3: {
            
            printf("Send money from account id: %f to account if: %f\n", md->client, md->receiverClient);
            code = MoneySend(md->client, md->receiverClient, md->sum, clientBase);
            if (code == SUCCESS) {
                printf("Success\n");
                ClientDBPrint(clientBase);
                strcpy(info, "Operation was completed successfully\0");
            } else if (code == NOT_ENOUGH_MONEY) {
                printf("Not enought money\n");
                strcpy(info, "You not enough money");
            } else if (code == RECEIVER_NOT_CLIENT) {
                printf("Receiver not bank client\n");
                strcpy(info, "Receiver is not a client of bank\0");
            }
            
            memcpy(md->message, info, strlen(info) + 1);
            zmq_msg_init_size(&message, sizeof(MsgData));
            memcpy(zmq_msg_data(&message), md, sizeof(MsgData));
            zmq_msg_send(&message, responsSocket, 0);
            zmq_msg_close(&message);
            break;
        }
        case 4: {
            
            printf("Check account id: %f\n", md->client);
            code = CheckAccount(md->client, clientBase);
                if (code == NOT_CLIENT) {
                    printf("Not bank client\n");
                    strcpy(info, "You aren't client of bank\0");
                } else {
                    printf("Client sum is %d\n", code);
                    ClientDBPrint(clientBase);
                    sprintf(info, "%s%d%c", "Your account is ", code, '\0');
                }
                memcpy(md->message, info, strlen(info) + 1);
                
                zmq_msg_init_size(&message, sizeof(MsgData));
                memcpy(zmq_msg_data(&message), md, sizeof(MsgData));
                zmq_msg_send(&message, responsSocket, 0);
                zmq_msg_close(&message);
                break;
        }
        }*/
        zmq_msg_close(&message);
    }

    zmq_close(responsSocket);
    zmq_ctx_destroy(context);

    //ClientDBDestroy(&clientBase);

    return 0;
}