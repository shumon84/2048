#include"include/2048lib.h"



int main(void)
{
  struct Screen scr;
  int board[16]={};
  int key=0;
  int score=0;
  int count=0;

  srand((unsigned)time(NULL));
  set_screen(&scr);
  initial_condition(board);
  
  board_print(board,score,count);

  while(key!='q')
    {
      key=getch();
      switch (key)
	{
	case 'w'       :
	case KEY_UP    : score+=up(board,&count);     break;
	case 's'       :
	case KEY_DOWN  : score+=down(board,&count);   break;
	case 'a'       :
	case KEY_LEFT  : score+=left(board,&count);   break;
	case 'd'       :
	case KEY_RIGHT : score+=right(board,&count);  break;
	case '['       : key=save(board,score,count); break;
	case ']'       : load(board,&score,&count);   break;
	case 'r'       : retry(board,&score,&count);  break;
	case 'q'       : key=quit(board,score,count); break;
	default        :                              break;
	}
      
      board_print(board,score,count);

      if(end_check(board))
	if(gameend(board,&score,&count))
	  key='q';
    }
  
  endwin();
  return 0;
}
