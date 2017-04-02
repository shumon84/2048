#include"include/2048lib.h"



int swap(int *a,int *b)
{
  int temp=*a;
  *a=*b;
  *b=temp;
  return 0;
}



int set_screen(struct Screen *scr)
{
  initscr();
  getmaxyx(stdscr,scr->h,scr->w);
  noecho();
  cbreak();
  keypad(stdscr,TRUE);
  mousemask( BUTTON1_PRESSED | BUTTON2_PRESSED | REPORT_MOUSE_POSITION ,NULL);

  /* カラーペアの準備 */
  start_color();
  init_pair( BLACK   , COLOR_BLACK   , COLOR_WHITE );
  init_pair( RED     , COLOR_RED     , COLOR_WHITE );
  init_pair( GREEN   , COLOR_GREEN   , COLOR_WHITE );
  init_pair( YELLOW  , COLOR_YELLOW  , COLOR_WHITE );
  init_pair( BLUE    , COLOR_BLUE    , COLOR_WHITE );
  init_pair( MAGENTA , COLOR_MAGENTA , COLOR_WHITE );
  init_pair( CYAN    , COLOR_CYAN    , COLOR_WHITE );
  init_pair( GRAY    , COLOR_GRAY    , COLOR_WHITE );
  init_pair( PURPLE  , COLOR_PURPLE  , COLOR_WHITE );
  init_pair( ORANGE  , COLOR_ORANGE  , COLOR_WHITE );
  init_pair( BLAD    , COLOR_BLAD    , COLOR_WHITE );
  init_pair( MAD     , COLOR_MAD     , COLOR_BLACK );
  init_pair( BEIGE   , COLOR_BEIGE   , COLOR_BLACK );
  init_pair( SKY     , COLOR_SKY     , COLOR_BLACK );
  init_pair( PIANO   , COLOR_PIANO   , COLOR_BLACK );
  init_pair( PINK    , COLOR_PINK    , COLOR_BLACK );

  init_pair( ERR_MSG , COLOR_WHITE   , COLOR_RED   );

  return 0;
}



int tile_print(int x,int y,char t[])
{
  move(y-1,x); addstr("       ");
  move(y  ,x); addstr(    t    );
  move(y+1,x); addstr("       ");
  return 0;
}



int board_print(int board[16],int score,int count)
{
  int i=0;
  int x,y;
  int new=-1;
  char scr[32];
  char cnt[32];
  move(2,0);
  attrset( COLOR_PAIR(BLACK) | A_REVERSE );
  addstr(
"     +-----------------------------------------+     +--------------------+\n"
"     | +-------+ +-------+ +-------+ +-------+ |     | +----------------+ |\n"
"     | |       | |       | |       | |       | |     | |                | |\n"
"     | |       | |       | |       | |       | |     | |      2048      | |\n"
"     | |       | |       | |       | |       | |     | |                | |\n"
"     | +-------+ +-------+ +-------+ +-------+ |     | +----------------+ |\n"
"     | +-------+ +-------+ +-------+ +-------+ |     | +----------------+ |\n"
"     | |       | |       | |       | |       | |     | |                | |\n"
"     | |       | |       | |       | |       | |     | | score          | |\n"
"     | |       | |       | |       | |       | |     | |                | |\n"
"     | +-------+ +-------+ +-------+ +-------+ |     | +----------------+ |\n"
"     | +-------+ +-------+ +-------+ +-------+ |     | +----------------+ |\n"
"     | |       | |       | |       | |       | |     | |                | |\n"
"     | |       | |       | |       | |       | |     | | count          | |\n"
"     | |       | |       | |       | |       | |     | |                | |\n"
"     | +-------+ +-------+ +-------+ +-------+ |     | +----------------+ |\n"
"     | +-------+ +-------+ +-------+ +-------+ |     | +----------------+ |\n"
"     | |       | |       | |       | |       | |     | |                | |\n"
"     | |       | |       | |       | |       | |     | |                | |\n"
"     | |       | |       | |       | |       | |     | |                | |\n"
"     | +-------+ +-------+ +-------+ +-------+ |     | +----------------+ |\n"
"     +-----------------------------------------+     +--------------------+\n"
	  );
  sprintf(scr,"%07d",score);
  sprintf(cnt,"%07d",count);
  move(10,64); addstr(scr);
  move(15,64); addstr(cnt);

	    
  char t0[]    ="       ";
  char t2[]    ="   2   ";
  char t4[]    ="   4   ";
  char t8[]    ="   8   ";
  char t16[]   ="  16   ";
  char t32[]   ="  32   ";
  char t64[]   ="  64   ";
  char t128[]  ="  128  ";
  char t256[]  ="  256  ";
  char t512[]  ="  512  ";
  char t1024[] =" 1024  ";
  char t2048[] =" 2048  ";
  char t4096[] =" 4096  ";
  char t8192[] =" 8192  ";
  char t16384[]=" 16384 ";
  
  for(i=0;i<16;i++)
    {
      if(board[i]<0)
	{
	  board[i]*=-1;
	  new=i;
	  continue;
	}
      y=5+(i/4)*5;
      x=8+(i%4)*10;
      attrset( COLOR_PAIR(board[i]+1) | A_REVERSE | A_BOLD );
      switch(board[i])
	{
	case  0 : tile_print(x,y,t0    ); break;
	case  1 : tile_print(x,y,t2    ); break; 
	case  2 : tile_print(x,y,t4    ); break;
	case  3 : tile_print(x,y,t8    ); break;
	case  4 : tile_print(x,y,t16   ); break;
	case  5 : tile_print(x,y,t32   ); break;
	case  6 : tile_print(x,y,t64   ); break;
	case  7 : tile_print(x,y,t128  ); break;
	case  8 : tile_print(x,y,t256  ); break;
	case  9 : tile_print(x,y,t512  ); break;
	case 10 : tile_print(x,y,t1024 ); break;
	case 11 : tile_print(x,y,t2048 ); break;
	case 12 : tile_print(x,y,t4096 ); break;
	case 13 : tile_print(x,y,t8192 ); break;
	case 14 : tile_print(x,y,t16384); break;
	}
    }

  move(0,0);
  refresh();

  if(new!=-1)
    {
      usleep(100000); //0.1秒待機
      y=5+(new/4)*5;
      x=8+(new%4)*10;
      attrset( COLOR_PAIR(board[new]+1) | A_REVERSE | A_BOLD );
      if(board[new]==1)
	tile_print(x,y,t2);
      else
	tile_print(x,y,t4);
  
      move(0,0);
    }
  
  return 0;
}



int initial_condition(int board[16])
{
  int a,b;
  a=rand()%16;
  while((b=rand()%16)==a);
  
  rand()%10?board[a]=1:(board[a]=2);
  rand()%10?board[b]=1:(board[b]=2);

  return 0;
}



int up(int board[16],int *count)
{
  int tile[4][4];
  int i,j;
  int score=0;
  int judge=0;

  for(i=0;i<4;i++)
    for(j=0;j<4;j++)
      tile[i][j]=board[i*4+j];

  space_justification(tile);

  for(j=0;j<4;j++)
    {
      if(tile[0][j]==tile[1][j] && tile[0][j]!=0)
	{
	  tile[0][j]++;
	  tile[1][j]=0;
	  score+=1<<tile[0][j];
	  if(tile[2][j]==tile[3][j] && tile[2][j]!=0)
	    {
	      tile[2][j]++;
	      tile[3][j]=0;
	      score+=1<<tile[2][j];
	    }
	}
      else if(tile[1][j]==tile[2][j] && tile[1][j]!=0)
	{
	  tile[1][j]++;
	  tile[2][j]=0;
	  score+=1<<tile[1][j];
	}
      else if(tile[2][j]==tile[3][j] && tile[2][j]!=0)
	{
	  tile[2][j]++;
	  tile[3][j]=0;
	  score+=1<<tile[2][j];
	};
    }

  space_justification(tile);

  for(i=0;i<4;i++)
    for(j=0;j<4;j++)
      if(board[i*4+j]!=tile[i][j])
	{
	  board[i*4+j]=tile[i][j];
	  judge++;
	}

  if(judge==0)
    return 0;
  
  generation(board);
  (*count)++;
  
  return score;
}



int down(int board[16],int *count)
{
  int tile[4][4];
  int i,j;
  int score=0;
  int judge=0;
  
  for(i=0;i<4;i++)
    for(j=0;j<4;j++)
      tile[3-i][j]=board[i*4+j];

  space_justification(tile);
  
  for(j=0;j<4;j++)
    {
      if(tile[0][j]==tile[1][j] && tile[0][j]!=0)
	{
	  tile[0][j]++;
	  tile[1][j]=0;
	  score+=1<<tile[0][j];
	  if(tile[2][j]==tile[3][j] && tile[2][j]!=0)
	    {
	      tile[2][j]++;
	      tile[3][j]=0;
	      score+=1<<tile[2][j];
	    }
	}
      else if(tile[1][j]==tile[2][j] && tile[1][j]!=0)
	{
	  tile[1][j]++;
	  tile[2][j]=0;
	  score+=1<<tile[1][j];
	}
      else if(tile[2][j]==tile[3][j] && tile[2][j]!=0)
	{
	  tile[2][j]++;
	  tile[3][j]=0;
	  score+=1<<tile[2][j];
	}
    }

  space_justification(tile);

  for(i=0;i<4;i++)
    for(j=0;j<4;j++)
      if(board[i*4+j]!=tile[3-i][j])
	{
	  board[i*4+j]=tile[3-i][j];
	  judge++;
	}

  if(judge==0)
    return 0;
  
  generation(board);
  (*count)++;
  
  return score;
}



int left(int board[16],int *count)
{
  int tile[4][4];
  int i,j;
  int score=0;
  int judge=0;

  for(i=0;i<4;i++)
    for(j=0;j<4;j++)
      tile[j][3-i]=board[i*4+j];

  space_justification(tile);

  for(j=0;j<4;j++)
    {
      if(tile[0][j]==tile[1][j] && tile[0][j]!=0)
	{
	  tile[0][j]++;
	  tile[1][j]=0;
	  score+=1<<tile[0][j];
	  if(tile[2][j]==tile[3][j] && tile[2][j]!=0)
	    {
	      tile[2][j]++;
	      tile[3][j]=0;
	      score+=1<<tile[2][j];
	    }
	}
      else if(tile[1][j]==tile[2][j] && tile[1][j]!=0)
	{
	  tile[1][j]++;
	  tile[2][j]=0;
	  score+=1<<tile[1][j];
	}
      else if(tile[2][j]==tile[3][j] && tile[2][j]!=0)
	{
	  tile[2][j]++;
	  tile[3][j]=0;
	  score+=1<<tile[2][j];
	}
    }

  space_justification(tile);
  
  for(i=0;i<4;i++)
    for(j=0;j<4;j++)
      if(board[i*4+j]!=tile[j][3-i])
	{
	  board[i*4+j]=tile[j][3-i];
	  judge++;
	}

  if(judge==0)
    return 0;
  
  generation(board);
  (*count)++;
  
  return score;
}



int right(int board[16],int *count)
{
  int tile[4][4];
  int i,j;
  int score=0;
  int judge=0;

  for(i=0;i<4;i++)
    for(j=0;j<4;j++)
      tile[3-j][i]=board[i*4+j];

  space_justification(tile);
  
  for(j=0;j<4;j++)
    {
      if(tile[0][j]==tile[1][j] && tile[0][j]!=0)
	{
	  tile[0][j]++;
	  tile[1][j]=0;
	  score+=1<<tile[0][j];    
	  if(tile[2][j]==tile[3][j] && tile[2][j]!=0)
	    {
	      tile[2][j]++;
	      tile[3][j]=0;
	      score+=1<<tile[2][j];
	    }
	}
      else if(tile[1][j]==tile[2][j] && tile[1][j]!=0)
	{
	  tile[1][j]++;
	  tile[2][j]=0;
	  score+=1<<tile[1][j];
	}
      else if(tile[2][j]==tile[3][j] && tile[2][j]!=0)
	{
	  tile[2][j]++;
	  tile[3][j]=0;
	  score+=1<<tile[2][j];
	}
    }

  space_justification(tile);
  
  for(i=0;i<4;i++)
    for(j=0;j<4;j++)
      if(board[i*4+j]!=tile[3-j][i])
	{
	  board[i*4+j]=tile[3-j][i];
	  judge++;
	}

  if(judge==0)
    return 0;
  
  generation(board);
  (*count)++;
  
  return score;
}



int space_justification(int tile[4][4])
{
  int i,j,k;

  for(k=0;k<3;k++)
    for(i=0;i<3;i++)
      for(j=0;j<4;j++)
	if(tile[i][j]==0)
	  swap(&tile[i][j],&tile[i+1][j]);

  return 0;
}



int generation(int board[16])
{
  int new;
  int judge=0;
  int i;

  for(i=0;i<16;i++)
    if(board[i]==0)
      {
	judge=1;
	break;
      }
  if(judge)
    {
      while(board[new=rand()%16]);
      rand()%10?board[new]=-1:(board[new]=-2);
    }
    
  return judge;
}



int save(int board[16],int score,int count)
{
  FILE *fp=fopen(GAME_DATA,"w");
  MEVENT event;
  time_t t=time(NULL);
  int ret;
  int i;

  if(fp==NULL)
    {
      move(25,5);
      insdelln(1);
      attrset( COLOR_PAIR(ERR_MSG) );
      addstr("It failed in saving the game data");
      ret=0;
    }
  else
    {
      for(i=0;i<16;i++)
	fprintf(fp,"%d ",board[i]);
      fprintf(fp,"%d ",score);
      fprintf(fp,"%d",count);
      
      fclose(fp);
      
      move(25,5);
      insdelln(1);
      attrset( COLOR_PAIR(BLACK) | A_REVERSE );
      addstr("It succeeded in saving the game data");
      
      attrset( COLOR_PAIR(ERR_MSG) );
      move( 8,15);addstr("                                        ");
      move( 9,15);addstr("        It leaves from the 2048         ");
      move(10,15);addstr("                                        ");
      move(11,15);addstr("               +--------+               ");
      move(12,15);addstr("               |        |               ");
      move(13,15);addstr("               |   OK   |               ");
      move(14,15);addstr("               |        |               ");
      move(15,15);addstr("               +--------+               ");
      move(16,15);addstr("                                        ");

      while((ret=getch())!='q')
	{
	  if(ret==KEY_MOUSE)
	    {
	      getmouse(&event);
	      if(11<=event.y && event.y<=15)
		{
		  if(30<=event.x && event.x<=39)
		    ret='q';
		}
	    }
	}
    }
  return ret;
}



int load(int board[16],int *score,int *count)
{
  int i;
  FILE *fp=fopen(GAME_DATA,"r");

  if(fp==NULL)
    {
      move(25,5);
      insdelln(1);
      attrset( COLOR_PAIR(ERR_MSG) );
      addstr("It failed in loading the game data");
      return 1;
    }

  for(i=0;i<16;i++)
    fscanf(fp,"%d",&board[i]);
  fscanf(fp,"%d",score);
  fscanf(fp,"%d",count);

  fclose(fp);
  
  remove(GAME_DATA);
  
  move(25,5);
  insdelln(1);
  attrset( COLOR_PAIR(BLACK) | A_REVERSE );
  addstr("It succeeded in loading the game data");

  return 0;
}



int retry(int board[16],int *score,int *count)
{
  int i;
  int select;
  int ret;
  MEVENT event;
  
  attrset( COLOR_PAIR(ERR_MSG) );
  move( 8,15);addstr("                                        ");
  move( 9,15);addstr("         Do you retry the game?         ");
  move(10,15);addstr("                                        ");
  move(11,15);addstr("       +--------+      +--------+       ");
  move(12,15);addstr("       |        |      |        |       ");
  move(13,15);addstr("       |   Yes  |      |   No   |       ");
  move(14,15);addstr("       |        |      |        |       ");
  move(15,15);addstr("       +--------+      +--------+       ");
  move(16,15);addstr("                                        ");
  
  while((select=getch())!='y' && select!='n')
    if(select==KEY_MOUSE)
      {
	getmouse(&event);
	if(11<=event.y && event.y<=15)
	  {
	    if(22<=event.x && event.x<=31)
	      {
		select='y';
		break;
	      }
	    else if(38<=event.x && event.x<=47)
	      {
		select='n';
		break;
	      }
	  }
      }
  
  if(select=='y')
    {
      for(i=0;i<16;i++)
	board[i]=0;
      *score=0;
      *count=0;

      initial_condition(board);
      board_print(board,*score,*count);
      
      move(25,5);
      insdelln(1);
      attrset( COLOR_PAIR(BLACK) | A_REVERSE );
      addstr("The game was retried");
    
      ret=0;
    }
  else
    ret=1;

  return ret;
}



int gameend(int board[16],int *score,int *count)
{  
  struct Ranker you;
  struct Ranker top[10]={};
  int i=0;
  int result=11;
  int ret;
  char str[BUFSIZ];
  time_t t=time(NULL);
  struct tm *now=localtime(&t);
  FILE *fp;

  attrset( COLOR_PAIR(ERR_MSG) | A_BOLD | A_BLINK );
  move(20,58);addstr("GAME OVER!");
  
  while(getch()!='q');

  if((fp=fopen(RANKING,"r"))!=NULL)
    {
      for(i=0;i<10;i++)
	fscanf(fp,"%d %d %d %d %d %d %d %d",
	       &top[i].score,
	       &top[i].count,
	       &top[i].year,
	       &top[i].month,
	       &top[i].day,
	       &top[i].hour,
	       &top[i].min,
	       &top[i].sec);

      fclose(fp);
    }
      
  you.score = *score;
  you.count = *count;
  you.year  = now->tm_year+1900;
  you.month = now->tm_mon+1;
  you.day   = now->tm_mday;
  you.hour  = now->tm_hour;
  you.min   = now->tm_min;
  you.sec   = now->tm_sec;
  
  for(i=0;i<10;i++)
    if(you.score>top[i].score)
      {
	result=i;
	for(i=9;i>result;i--)
	  top[i]=top[i-1];
	top[result]=you;
	break;
      }
      
  erase();
  
  attrset( COLOR_PAIR(BLACK) | A_REVERSE );
  move(2,29);
  addstr("TOP 10 RANKING");

  for(i=0;i<10;i++)
    {
      if(top[i].year)
	sprintf(str,"%2d : %7d (%4d/%2d/%2d %02d:%02d)",
		i+1,
		top[i].score,
		top[i].year,
		top[i].month,
		top[i].day,
		top[i].hour,
		top[i].min);
      else
	sprintf(str,"%2d : NO DATA",i+1);
	  
      if(result==i)
	{
	  attrset( COLOR_PAIR(SKY) | A_BLINK | A_BOLD );
	  move(4+i,16);
	  addstr("NEW");
	  attrset( COLOR_PAIR(BLACK) | A_REVERSE);
	}

      move(4+i,20);
      addstr(str);

    }
      
  move(5+i,13);addstr("---------------------------------------------");
  
  sprintf(str,"YOU : %7d (%4d/%2d/%2d %02d:%02d)",
	  you.score,
	  you.year,
	  you.month,
	  you.day,
	  you.hour,
	  you.min);
  
  move(7+i,19);addstr(str);
  
  fp=fopen(RANKING,"w");
  
  for(i=0;i<10;i++)
    fprintf(fp,"%d %d %d %d %d %d %d %d\n",
	    top[i].score,
	    top[i].count,
	    top[i].year,
	    top[i].month,
	    top[i].day,
	    top[i].hour,
	    top[i].min,
	    top[i].sec);
  
  fclose(fp);

  getch();

  ret=retry(board,score,count);
  
  return ret;
}



int end_check(int board[16])
{
  int i,j,k;
  int ret=1;

  for(i=0;i<16;i++)
    if(board[i]==0)
      ret=0;

  for(i=0;i<4;i++)
    for(j=0;j<3;j++)
      {
	if(board[i+j*4]==board[i+(j+1)*4])
	  ret=0;
	if(board[i*4+j]==board[i*4+j+1])
	  ret=0;
      }

  return ret;
}



int quit(int board[16],int score,int count)
{
  int i;
  int select;
  int ret=0;
  MEVENT event;
  
  attrset( COLOR_PAIR(ERR_MSG) );
  
  move( 8,15);addstr("                                        ");
  move( 9,15);addstr("   Without saving is the game quited?   ");
  move(10,15);addstr("                                        ");
  move(11,15);addstr("    +--------+ +--------+ +--------+    ");
  move(12,15);addstr("    |        | |        | |        |    ");
  move(13,15);addstr("    |  Save  | |  Quit  | | Resume |    ");
  move(14,15);addstr("    |        | |        | |        |    ");
  move(15,15);addstr("    +--------+ +--------+ +--------+    ");
  move(16,15);addstr("                                        ");

  while((select=getch())!='s' && select!='q' && select!='r')
    if(select==KEY_MOUSE)
      {
	getmouse(&event);
	if(11<=event.y && event.y<=15)
	  {
	    if(19<=event.x && event.x<=28)
	      {
		select='s';
		break;
	      }
	    else if(30<=event.x && event.x<=39)
	      {
		select='q';
		break;
	      }
	    else if(41<=event.x && event.x<=50)
	      {
		select='r';
		break;
	      }
	  }
      }
      
  switch(select)
    {
    case 'q': ret='q';break;
    case 's': save(board,score,count);ret='q';break;
    case 'r': break;
    }
  
  return ret;
}
