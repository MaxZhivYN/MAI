#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <pthread.h>


#include "zmq.h"
#include "ohota.h"
//#include "message.h"



void menuUser()
{
    printf("1) Connect to game solo\n");
    printf("2) \n");
    printf("3) \n");
    printf("4) \n");
    printf("5) EXIT\n");
}

int user_registration(void *sendSocket, int id_game, int id_client)
{

    MsgData *md = (MsgData*) malloc(sizeof(MsgData));
    md->id_game = id_game;
    md->id_client = id_client;

    zmq_msg_t message;
    zmq_msg_init_size(&message, sizeof(MsgData));
    memcpy(zmq_msg_data(&message), md, sizeof(MsgData));
    zmq_msg_send(&message, sendSocket, 0);                  
    zmq_msg_close(&message);

    zmq_msg_init(&message);
    zmq_msg_recv(&message, sendSocket, 0);                  
    int *id = (int*) zmq_msg_data(&message);
    zmq_msg_close(&message);

    printf("Registration sucsess!\nYour id: %d\n", *id);
    return *id;
}   


void *SendRecv(void *arg)
{
    MsgData *md = (MsgData*) arg;
    zmq_msg_t message;
    zmq_msg_init_size(&message, sizeof(MsgData));
    memcpy(zmq_msg_data(&message), md, sizeof(MsgData));
    //zmq_msg_send(&message, md->requester, 0);                  

    zmq_msg_init(&message);
    //zmq_msg_recv(&message, md->requester, 0);                   
    md = (MsgData *) zmq_msg_data(&message);
    //printf("%s\n", md->message);
    zmq_msg_close(&message);
    pthread_exit(NULL);
    return 0;
}

int main(int argc, char **argv)
{
    void *context = zmq_ctx_new();
    char adress[25] = "tcp://localhost:4040";
    void *sendSocket = zmq_socket(context, ZMQ_REQ);
    zmq_connect(sendSocket, adress);

    Fox_item **fox_game_place = (Fox_item**) malloc(sizeof(Fox_item*));
    for (int i = 0; i < fox_row; i++) {
        fox_game_place[i] = (Fox_item*) malloc(sizeof(Fox_item));
        for (int j = 0; j < fox_row; j++)
            fox_game_place[i][j].is_visible = false;
    }

    MsgData *md = (MsgData*) malloc(sizeof(MsgData));
    md->id_client = 0;
    md->id_game = 0;

    md->id_client = user_registration(sendSocket, md->id_game, md->id_client);
    
    int act = 0, sum = 0;
    

    menuUser();
    do {
        scanf("%d", &act);
        //md.action = act;
        //md.id_client = client;
        switch (act) {
            case 1: {
                zmq_msg_t message;
                zmq_msg_init_size(&message, sizeof(MsgData));
                memcpy(zmq_msg_data(&message), md, sizeof(MsgData));
                zmq_msg_send(&message, sendSocket, 0);                  
                zmq_msg_close(&message);
            
                zmq_msg_init(&message);
                zmq_msg_recv(&message, sendSocket, 0);             
                Game_place_conect *game_place_conect = (Game_place_conect*) zmq_msg_data(&message);
                zmq_msg_close(&message);

                fox_game_place = game_place_conect->fox_game_place;
                md->id_game = game_place_conect->id_game;
                //printf("%d", );
                //game_print(fox_game_place);

                break;
            }
            case 2: {
                printf("Enter the sum: ");
                scanf("%d", &sum);
                //md.sum = sum;
                pthread_t th;
                //md.requester = sendSocket;
                pthread_create(&th, NULL, SendRecv, &md);
                pthread_detach(th);
                break;
            }
            case 3: {
                int receiverClient;
                printf("Enter receiver id: ");
                scanf("%d", &receiverClient);
                printf("Enter the sum: ");
                scanf("%d", &sum);
                //md.sum = sum;
                //md.receiverClient = receiverClient;
                pthread_t th;
                //md.requester = sendSocket;
                pthread_create(&th, NULL, SendRecv, &md);
                pthread_detach(th);
                break;
            }
            case 4: {
                pthread_t th;
                //md.requester = sendSocket;
                pthread_create(&th, NULL, SendRecv, &md);
                pthread_detach(th);
                break;
            }
            case 5:
                break;
            default: {
                printf("Inccorect command\n");
                break;
            }
        }
    } while (act != 5);

    zmq_close(sendSocket);
    zmq_ctx_destroy(context);

    return 0;
}