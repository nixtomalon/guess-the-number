#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

int startGame();

struct tempPlayer{
    char name[50];
    int tries;
    int min;
    int sec;
    int time;
};
struct topPlay{
    char name[50];
    int tries;
    int min;
    int sec;
    int time;
};
int getTopPlayers(struct topPlay * topPlayer,int i);
struct topPlay1{
    char name[50];
    int tries;
    int min;
    int sec;
    int time;
};
struct currPlayer{
    char name[50];
    int tries;
    int min;
    int sec;
    int time;
};

int main(){
    time_t start_time, end_time;
    int elapsed_seconds;
    struct currPlayer curr;
    struct topPlay topPlayer[5];
    struct topPlay1 topPlayer1[5];
    char ch;
    FILE * fp;
    int players,rank=0,i,j,z=0,k=0;

    players=getTopPlayers(topPlayer,rank);
    printf("\t\t ==================================\n");
    printf("\t\t  WELCOME TO GUESS THE NUMBER GAME\n");
    printf("\t\t ==================================\n");
    printf("\t\t\t [ TOP 5 PLAYERS ]\n\n");
    printf("    %-10s %6s %6s\n","Name","Try","Time");
    for(i=0;i<players;i++){
        printf("    %-1d. %-10s %-3d %3dmin:%02dsec\n",i+1,topPlayer[i].name,topPlayer[i].tries,topPlayer[i].min,topPlayer[i].sec);
    }

    printf("\nWhat is your name? ");
    scanf("%s",curr.name);
    printf("\nHello %s guess the number from 1 - 1000.\n",curr.name);
    printf("    Press ( Enter ) to start the game...");
    ch = getchar();

    start_time = time(NULL);
    curr.tries = startGame();
    end_time = time(NULL);

    curr.time = (int)(end_time - start_time);
    curr.min = curr.time / 60;
    curr.sec = curr.time % 60;

    printf("\n\t\t  Try\tTime\n");
    printf("\t\t  %d\t%dmin %dsec\n",curr.tries ,curr.min,curr.sec);

    if(players<5){
        strcpy(topPlayer[players].name,curr.name);
        topPlayer[players].tries = curr.tries;
        topPlayer[players].min = curr.min;
        topPlayer[players].sec = curr.sec;
        topPlayer[players].time = curr.time;

        for(i=0;i<players+1;i++){
            for(j=0;j<i;j++){
                if(topPlayer[i].time<topPlayer[j].time){

                    strcpy(curr.name,topPlayer[i].name);
                    curr.tries = topPlayer[i].tries;
                    curr.min = topPlayer[i].min;
                    curr.sec = topPlayer[i].sec;
                    curr.time = topPlayer[i].time;

                    strcpy(topPlayer[i].name,topPlayer[j].name);
                    topPlayer[i].tries=topPlayer[j].tries;
                    topPlayer[i].min=topPlayer[j].min;
                    topPlayer[i].sec=topPlayer[j].sec;
                    topPlayer[i].time=topPlayer[j].time;

                    strcpy(topPlayer[j].name,curr.name);
                    topPlayer[j].tries=curr.tries;
                    topPlayer[j].min=curr.min;
                    topPlayer[j].sec=curr.sec;
                    topPlayer[j].time=curr.time;
                }
            }
        }
        fp = fopen("game.txt","w");
        for(i=0;i<players+1;i++){
            fprintf(fp,"%s\t%d\t%d\t%d\t%d\n",topPlayer[i].name,topPlayer[i].tries,topPlayer[i].min,topPlayer[i].sec,topPlayer[i].time);
        }
    }
    else{
        for(i=0;i<players;i++){
            if(curr.time<topPlayer[i].time){
                printf("\t  Congrats %s Your In the Top %d now!!....\n\n\n",curr.name,i+1);
                for(j=i;j<players;j++){
                    strcpy(topPlayer1[k].name,topPlayer[j].name);
                    topPlayer1[k].tries=topPlayer[j].tries;
                    topPlayer1[k].min=topPlayer[j].min;
                    topPlayer1[k].sec=topPlayer[j].sec;
                    topPlayer1[k].time=topPlayer[j].time;
                    k++;
                }
                strcpy(topPlayer[i].name,curr.name);
                topPlayer[i].tries=curr.tries;
                topPlayer[i].min=curr.min;
                topPlayer[i].sec=curr.sec;
                topPlayer[i].time=curr.time;
                z=i+1;
                break;
            }
        }
        for(i=0;i<players;i++){
            if(i==z){
                for(j=0;j<k;j++){
                    strcpy(topPlayer[z].name,topPlayer1[j].name);
                    topPlayer[z].tries=topPlayer1[j].tries;
                    topPlayer[z].min=topPlayer1[j].min;
                    topPlayer[z].sec=topPlayer1[j].sec;
                    topPlayer[z].time=topPlayer1[j].time;
                    z++;
                }
            }
        }
        fp = fopen("game.txt","w");
        for(i=0;i<players;i++){
            fprintf(fp,"%s\t%d\t%d\t%d\t%d\n",topPlayer[i].name,topPlayer[i].tries,topPlayer[i].min,topPlayer[i].sec,topPlayer[i].time);
        }
    }
    fclose(fp);
    return 0;
}
int getTopPlayers(struct topPlay * topPlayer,int i){
    FILE * fp = fopen("game.txt","r");
    char name[50];
    int tries,min,sec,time;
    if(fp == NULL){
        printf("File not exist\n");
    }
    else{
        while(fscanf(fp,"%s%d%d%d%d",name,&tries,&min,&sec,&time)!=EOF){
                strcpy(topPlayer[i].name,name);
                topPlayer[i].tries=tries;
                topPlayer[i].min=min;
                topPlayer[i].sec=sec;
                topPlayer[i].time=time;
                i++;
            }
        }
    fclose(fp);
    return i;
}
int startGame(){
    int guess,Gplayer=0,playtry=1;
    srand(time(NULL));
    guess = (rand()%1000)+1;
    while(guess!=Gplayer){
        printf("\n\nWhat is your guess? ");
        scanf("%d",&Gplayer);
        if(Gplayer>guess){
            printf("\nLower....");
            playtry++;
		}else if(Gplayer<guess){
            printf("\nHigher...");
            playtry++;
		}
    }
    return playtry;
}

//TODO
int savePlayer(){
    return 0;
}
