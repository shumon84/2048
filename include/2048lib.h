#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include<time.h>
#include<unistd.h>



/* カラーマクロ */
#define COLOR_GRAY     8	/*   灰色 */
#define COLOR_PURPLE  55	/*   紫色 */
#define COLOR_ORANGE 166	/*   橙色 */
#define COLOR_BEIGE  223	/* 薄茶色 */
#define COLOR_SKY    152	/*   空色 */
#define COLOR_BLAD    52	/* 血赤色 */
#define COLOR_MAD      9        /* 黄土色 */
#define COLOR_PIANO   15	/* 明白色 */
#define COLOR_PINK    13	/*   桃色 */



/* カラーペアマクロ */
#define BLACK          1	/*   黒文字 + 白背景 */
#define RED            2	/*   赤文字 + 白背景 */
#define GREEN          3	/*   緑文字 + 白背景 */
#define YELLOW         4	/*   黄文字 + 白背景 */
#define BLUE           5	/*   青文字 + 白背景 */
#define MAGENTA        6	/* 赤紫文字 + 白背景 */
#define CYAN           7	/* 青緑文字 + 白背景 */
#define GRAY           8	/*   灰文字 + 白背景 */
#define PURPLE         9	/* 　紫文字 + 白背景 */
#define ORANGE        10	/*   橙文字 + 白背景 */
#define BLAD          11	/* 血赤文字 + 黒背景 */
#define MAD           12	/* 黄土文字 + 黒背景 */
#define BEIGE         13	/* 薄茶文字 + 黒背景 */
#define SKY           14	/*   空文字 + 黒背景 */
#define PIANO         15	/* 明白文字 + 黒背景 */
#define PINK          16	/*   桃文字 + 黒背景 */



/* エラー文用カラーペアマクロ */
#define ERR_MSG      100	/*   白文字 + 赤背景 */



/* セーブデータ */
#define GAME_DATA  "dat/game_log.dat"
#define RANKING    "dat/ranking.dat"



/* ランキング情報を保持 */
struct Ranker
{
  int score;
  int count;
  int year;
  int month;
  int day;
  int hour;
  int min;
  int sec;
};



/* 画面サイズを保持 */
struct Screen
{
  int h; //縦
  int w; //横
};



int swap(int *a,int *b);	                    /* int型用スワップ */
int set_screen(struct Screen *scr);                 /* コンソールの準備 */
int tile_print(int x,int y,char t[]);               /* タイル単位の出力 */
int board_print(int board[16],int score,int count); /* 盤面状態の出力 */
int initial_condition(int board[16]);               /* 盤面状態の初期化 */
int up(int board[16],int *count);		    /* 上移動 */
int down(int board[16],int *count);	            /* 下移動 */
int left(int board[16],int *count);	            /* 左移動 */
int right(int board[16],int *count);	            /* 右移動 */
int space_justification(int tile[4][4]);            /* 盤面の空白詰め */
int generation(int board[16]);		            /* 新たなタイルを生成 */
int save(int board[16],int score,int count);	    /* ゲームデータのセーブ */
int load(int board[16],int *score,int *count);      /* ゲームデータをロード */
int retry(int board[16],int *score,int *count);     /* ゲームをリトライ */
int gameend(int board[16],int *score,int *count);   /* ゲーム終了処理 */
int end_check(int board[16]);                       /* ゲームオーバーの確認 */
int quit(int board[16],int score,int count);        /* ゲームの中断 */
