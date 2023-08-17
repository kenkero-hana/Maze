#include <stdio.h>
#include <stdlib.h>

//マップ幅
#define MapX (5)
#define MapY (5)

enum MazeKind {WALL, ROAD, START, GOAL};
enum MazeFlag {FALSE, TRUE};
enum MazeMove {UP, DOWN, LEFT, RIGHT, Invalib};

//マップ生成
typedef struct 
{
    enum MazeKind kind;
    enum MazeFlag flag;
}MazeBlok;

//プレーヤー位置情報
typedef struct
{
    int playX;
    int playY;
}MazePlayer;

//プレイヤー初期化
int MazePlayerInit(int *playerX, int *playerY, MazeBlok maze[MapX][MapY]){
    int i,j;

    for(i = 0; i < MapX; i++){
        for(j = 0; j < MapY; j++){
            if(maze[i][j].kind == START){
                *playerX = i;
                *playerY = j;
                return 0;
            }
        }
    }

    //スタート地点がなければ、プレイヤーを設定できず
    printf("スタートがありません\n");
    return -1;
}

void MazePlayerMove(int *playerX, int *playerY, MazeBlok maze[MapX][MapY]){
    char buf[100];
    int direction = -1;

    printf("%d:上", UP);
    printf("%d:下", DOWN);
    printf("%d:右", LEFT);
    printf("%d:左", RIGHT);
    printf("数字を入力してください：");

    fgets(buf, sizeof(buf), stdin); //1:文字列のポインタ、2:最大文字数、3:値を読みこみ
}

//マップ生成
void MazeDrop(int *playerX, int *playerY, MazeBlok maze[MapX][MapY]){
    int i,j;

    for(i = 0; i < MapX; i++){
        for(j = 0; j < MapY; j++){
            if(i == playerX && j == playerY){
                printf("P");
            }
            else if(maze[i][j].flag == FALSE){
                printf("?");
            }
            else{
                switch (maze[i][j].kind)
                {
                case WALL:
                    /* code */
                    printf("■");
                    break;
                case GOAL:
                    printf("G");
                    break;
                
                default:
                    printf(" ");
                    break;
                }
            }
        }
        printf("\n");
    }
}

//初期実行
int main(void){

    MazePlayer player;

    MazeBlok maze[MapX][MapY] = {
        { {START,TRUE},{ROAD,TRUE} ,{WALL,TRUE},{WALL,TRUE},{WALL,TRUE}},
        { {WALL,TRUE},{ROAD,TRUE} ,{ROAD,TRUE} ,{WALL,TRUE} ,{WALL,TRUE}},
        { {WALL,TRUE},{WALL,TRUE},{ROAD,TRUE} ,{ROAD,TRUE} ,{WALL,TRUE}},
        { {WALL,TRUE},{WALL,TRUE},{WALL,TRUE},{ROAD,TRUE} ,{WALL,TRUE}},
        { {WALL,TRUE},{WALL,TRUE},{WALL,TRUE},{ROAD,TRUE} ,{GOAL,TRUE}}
    };

    if(MazePlayerInit(&player.playX, &player.playY, maze) == -1){
        return 0;
    }

    MazeDrop(player.playX, player.playY, maze);

    return 0;
}