#include <stdio.h>
//#include <stdlib.h>

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

void MazePlayerMove(int *playerX, int *playerY, MazeBlok maze[MapX][MapY]){
    char buf[100];
    int direction = -1;

    printf("%d:上", UP);
    printf("%d:下", DOWN);
    printf("%d:右", LEFT);
    printf("%d:左", RIGHT);
    printf("\n");
    printf("数字を入力してください：");

    fgets(buf, sizeof(buf), stdin); //1:文字列のポインタ、2:最大文字数、3:値を読みこみ
    sscanf(buf, "%d", &direction);

    while(direction < 0 || direction > (Invalib -1)){
        printf("入力が不正です。再入力してください：");
        fgets(buf, sizeof(buf), stdin); //1:文字列のポインタ、2:最大文字数、3:値を読みこみ
        sscanf(buf, "%d", &direction);
    }
    switch (direction)
    {
    case UP:
    {
        if(*playerX -1 >= 0){ //迷宮の範囲内でないことを確認する
            maze[*playerX-1][*playerY].flag = TRUE; //ブロックの種類を判別
            if(maze[*playerX -1][*playerY].kind != WALL){
                *playerX -= 1; //移動
                printf("\n上に移動しました\n");
            }
            else{
                printf("\n壁です\n");
            }
        }
        else{
            printf("\n範囲外です\n");
        }
    }
        break;

    case DOWN:
    {
        if(*playerX + 1 < MapX){ //迷宮の範囲内でないことを確認する
            maze[*playerX + 1][*playerY].flag = TRUE; //ブロックの種類を判別
            if(maze[*playerX + 1][*playerY].kind != WALL){
                *playerX += 1; //移動
                printf("\n下に移動しました\n");
            }
            else{
                printf("\n壁です\n");
            }
        }
        else{
            printf("\n範囲外です\n");
        }
    }
        break;
    
    case LEFT:
    {
        if(*playerY - 1 >= 0){
            maze[*playerX][*playerY - 1].flag = TRUE;
            if(maze[*playerX][*playerY -1].kind != WALL){
                *playerY -= 1;
                printf("\n左に移動しました\n");
            }
            else{
                printf("\n壁です\n");
            }
        }
        else{
            printf("\n範囲外です\n");
        }
    }
        break;

    case RIGHT:
    {
        if(*playerY + 1 >= MapY){
            maze[*playerX][*playerY + 1].flag = TRUE;
            if(maze[*playerX][*playerY + 1].kind != WALL){
                *playerY += 1;
                printf("\n左に移動しました\n");
            }
            else{
                printf("\n壁です\n");
            }
        }
        else{
            printf("\n範囲外です\n");
        }
    }
        break;
    default:
        break;
    }
}

//ゴール判定
int MazeGoalCheak(int *playerX, int *playerY, MazeBlok maze[MapX][MapY]){
    if(maze[*playerX][*playerY].kind == GOAL){
        printf("ゴール！\n");
        return 1;
    }
    return 0;
}

//初期実行
int main(void){

    MazePlayer player;

    MazeBlok maze[MapX][MapY] = {
        { {START,TRUE},{ROAD,FALSE} ,{WALL,FALSE},{WALL,FALSE},{WALL,FALSE}},
        { {ROAD,FALSE},{ROAD,FALSE} ,{ROAD,FALSE} ,{WALL,FALSE} ,{WALL,FALSE}},
        { {WALL,FALSE},{WALL,FALSE},{ROAD,FALSE} ,{ROAD,FALSE} ,{WALL,FALSE}},
        { {WALL,FALSE},{WALL,FALSE},{WALL,FALSE},{ROAD,FALSE} ,{WALL,FALSE}},
        { {WALL,FALSE},{WALL,FALSE},{WALL,FALSE},{ROAD,FALSE} ,{GOAL,TRUE}}
    };

    if(MazePlayerInit(&player.playX, &player.playY, maze) == -1){
        return 0;
    }

    while(MazeGoalCheak(&player.playX, &player.playY, maze) != 1){
        //迷路表示
        MazeDrop(player.playX, player.playY, maze);
        //プレイヤー移動
        MazePlayerMove(&player.playX, &player.playY, maze);
    }

    MazeDrop(player.playX, player.playY, maze);

    return 0;
}