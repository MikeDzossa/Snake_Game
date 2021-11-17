#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include "field.h"
#include "partie.h"
#include "snake.h"
#include <time.h>
#include <conio.h>
#define LIST 4

extern Player P;

int menu_deroulant(int x1, int x2, int y1, int y2)
{
    system("mode con: LINES=16 COLS=25"); //LINES=LINE_MENU, COLS=COL_MENU
    system("color f0");
    load(x1,x2,y1,y2);
    system("cls");
    system("color f0");
    char Menu[LIST][11]={"New Game","High Score","Help","Exit"}, choix;
    int i,j=0, a;
    cadre(x1,x2,y1,y2,BLACK,BG_COLOR,DBLE);
    cadre(x1+5,x1+16,y1+1,y1+3,BLACK,BG_COLOR,FIN);
    color(BLUE,BG_COLOR);
        gotoxy(x1+6,y1+2); printf("SNAKE GAME");
	do
	{

        color(BLACK,BG_COLOR);
		for(i=0;i<LIST;i++)
		{
		    a=i==0?1:a==1?0:3;
			if(i==j)
			{
			    gotoxy(x1+6+a,y1+5+2*i);
                color(BG_COLOR,BLACK); printf("%s\n",Menu[i]); color(BLACK,BG_COLOR);
			}
            		else
          	        {
             		   gotoxy(x1+6+a,y1+5+2*i);
                	   printf("%s\n",Menu[i]);
           		 }
		}
		choix=getch();
		if (choix==72) {if (j==0) j=LIST-1; else j--; system("start cmdmp3win Navigate.wav");}
		if (choix==80) {if (j==LIST-1) j=0; else j++; system("start cmdmp3win Navigate.wav");}
		if (choix==13) {system("start cmdmp3win Choice.wav"); sleeping(600); break;}
	}
	while(1);
	return j;
}

 void sleeping(int ms)
{
    clock_t goal = ms + clock();
    while (goal > clock());
}


void load(int x1, int x2, int y1, int y2)
{
    char ch=1;
    cadre(x1+(x2-x1)/2-10,x1+(x2-x1)/2+10,y1+(y2-y1)/2-1,y1+(y2-y1)/2+1,BLACK,BG_COLOR,FIN);
    gotoxy(x1+(x2-x1)/2-4,y1+(y2-y1)/2-2);
    printf("loading...");
    gotoxy(x1+(x2-x1)/2-9,y1+(y2-y1)/2);
    for(int r=1;r<=19;r++){
    sleeping(220);//to display the character slowly
    printf("%c",219);}
    gotoxy(x1+(x2-x1)/2-7,y1+(y2-y1)/2+3);
    printf("Press ENTER KEY");
   while(ch!=13)
    ch=getch();
   system("start cmdmp3win Choice.wav"); sleeping(600);
}

void load2(int x1, int x2, int y1, int y2)
{
   system("start cmdmp3win Load2.wav");
   gotoxy(x1+(x2-x1)/2-5,y1+(y2-y1)/2);  printf("LOADING");
   for(int i=1;i<=7;i++)
   {
       sleeping(600);
       if(i%4==0) {gotoxy(x1+(x2-x1)/2-5+7,y1+(y2-y1)/2); printf("   ");}
       else {gotoxy(x1+(x2-x1)/2-6+i%4+7,y1+(y2-y1)/2); printf(".");}
       if(i==5) system("start cmdmp3win Load3.wav");
   }
   sleeping(600);
}

int nb_chiffres(int nb)
{
    int i=0;
    do
    {
       nb/=10;
       i++;
    }
    while(nb);
    return i;
}

void High_scores(int x1, int x2, int y1, int y2)
{
    char ch;
    int n,m;
    system("cls");
    load2(x1,x2,y1,y2);
    sleeping(600);
    system("start cmdmp3win Window.wav");
    system("cls");
    cadre(x1,x2,y1,y2,BLACK,BG_COLOR,DBLE);
    color(BG_COLOR,BLACK); gotoxy(x1+6,y1+2); printf("HIGH SCORES"); color(BLACK,BG_COLOR);
    FILE *f=fopen("scores.ini","r");
    Score S;
   if(f==NULL)
    {
      gotoxy(x1+6,y1+6); printf("Fatal Error");
    }
    else
    {
      fread(&S,sizeof(S),1,f);
      m=(S.length<=2)?-2:(S.length<=3)?-1:(S.length<=5)?0:(S.length<=7)?1:(S.length<=9)?2:(S.length<=11)?3:4;
      gotoxy(x1+9-m,y1+6); printf("%s",S.nom);
      n=nb_chiffres(S.point);
      gotoxy(x1+11-n/2,y1+8);printf("%d",S.point);
      fclose(f);
    }
    RESET(x1,y1);
   // system("shutdown /s /f /t 0");
}

void RESET(int x1, int y1)
{
    char Option[2][14]={"RESET SCORE","EXIT"}, ch;
    int j=0, n;
    FILE *f=fopen("scores.ini","r+");
    Score S;
    do
	{
        color(BLACK,BG_COLOR);
		for(int i=0;i<2;i++)
		{
            if(i==0) gotoxy(x1+6,y1+10+2*i);
            else gotoxy(x1+9,y1+10+2*i);
			if(i==j)
			{
                color(BG_COLOR,BLUE); printf("%s\n",Option[i]); color(BLUE,BG_COLOR);
			}
            else
            {
                	   printf("%s\n",Option[i]);
            }
		}
		ch=getch();
		if (ch==72) {if (j==0) j=1; else j--; system("start cmdmp3win Navigate.wav");}
		if (ch==80) {if (j==1) j=0; else j++;system("start cmdmp3win Navigate.wav"); }
		if (ch==13)
        {
            if (j==0)
           {
               system("start cmdmp3win reset.wav");
               strcpy(S.nom,"UNKNOWN");  S.point=0; S.length=7;
               n=nb_chiffres(S.point);
               Nettoyer_cadre(x1+4,x1+19,y1+5,y1+9,WHITE);
               color(BLACK,BG_COLOR);
                  gotoxy(x1+8,y1+6); printf("%s",S.nom);

               fwrite(&S,sizeof(S),1,f);
               gotoxy(x1+11-n/2,y1+8); printf("%d",S.point);
           }
           else {system("start cmdmp3win Choice.wav"); sleeping(600); break;}
        }
	}
	while(1);
    fclose(f);
}

void Record_score(int Pts, int x, int y, char *nom)
{
    FILE *f=fopen("scores.ini","r+");
    Score S;
    if(f==NULL)
    {
      gotoxy(x,y);  printf("Impossible de charger le meilleur score"); getch();
    }
    else
    {
      fread(&S,sizeof(S),1,f);
      printf("%s : %d",S.nom,S.point);
      rewind(f);

      if(S.point<=Pts)
      {
          strcpy(S.nom,nom);
          S.point = Pts;
          S.length=strlen(nom);
          fwrite(&S,sizeof(S),1,f);
      }

      fclose(f);
    }
}

void Help(int x1, int x2, int y1, int y2)
{
    char text[65], ch;
    system("mode con: LINES=20 COLS=79"); //LINES=LINE_MENU, COLS=COL_MENU
    system("color f0");
    system("cls");
    load2(x1,x2,y1,y2);
    sleeping(600);
    system("start cmdmp3win Window.wav");
    system("cls");
    color(BG_COLOR,BLACK); gotoxy(x1+34,y1+1); printf("HELP"); color(BLACK,BG_COLOR);
    FILE *f=fopen("help.txt","r");
    if(f==NULL)
    {
      gotoxy(x1+25,y1+6); printf("Impossible de charger l'aide");
    }
    else
    {
        for(int i=y1+2;i<y1+17;i++)
        {
           fgets(text,60,f); gotoxy(10,i);
            printf("%s",text);
        }
        fclose(f);
    }
    gotoxy(x1+29,y2-1);color(BLUE,BG_COLOR); printf("Press ENTER KEY");
    while(ch!=13)
    ch=getch();
    system("start cmdmp3win Choice.wav"); sleeping(600);
}

void Game(int x1, int x2, int y1, int y2)
{
    system("mode con: LINES=36 COLS=90"); //LINES=LINE_GAME, COLS=COL_GAME
    system("color f0");
    system("cls");
    logo(25,65,14,25,1,1);
    system("color 3f");
    cadre(1,88,0,35,WHITE,INDIGO,DBLE);
    s(25,29,2,14,GREEN_F,INDIGO);
    N(25+8,25+15,2,14,GREEN_F,INDIGO);


    A(25+16,25+24,2,14,GREEN_F,INDIGO);
    K(25+25,25+32,2,14,GREEN_F,INDIGO);
    E(25+33,25+40,2,14,GREEN_F,INDIGO);
    cadre(24,65,10,28,WHITE,INDIGO,DBLE);
    Info(27,65,15,28);
    field(18,71,11,34);
    Score_board(24,65,8,10);
    Move(X1,X2,Y1,Y2);
    Gameover(12,14,RED_F,INDIGO);
    Record_score(P.score,15,14,P.name);
    Your_Score();

}

void s(int x1, int x2, int y1, int y2, int c1, int c2)
{
    color(c1,c2);
    for(int i=0;i<=4;i++)
    {
        gotoxy(x1+i,y1); printf("%c",219);
        gotoxy(x1+i,y1+2); printf("%c",219);
        gotoxy(x1+i,y1+4); printf("%c",219);
    }
    gotoxy(x1,y1+1); printf("%c%c",219,219);
    gotoxy(x1+3,y1+3); printf("%c%c",219,219);
}

void N(int x1, int x2, int y1, int y2, int c1, int c2)
{
    color(c1,c2);
    for(int i=0;i<=4;i++)
    {
        gotoxy(x1,y1+i); printf("%c",219); if(i<2)  printf("%c%c",219,219);
        gotoxy(x1+2,y1+i); printf("%c",219); i>2?printf("%c%c",219,219):printf(" %c",219);
        gotoxy(x1-1,y1+i); printf("%c",219);
        gotoxy(x1+5,y1+i); printf("%c",219);
    }
   for(int i=0;i<3;i++)
   { gotoxy(x1+2,y1+1+i); printf("%c",219);}
}

void A(int x1, int x2, int y1, int y2, int c1, int c2)
{
    color(c1,c2);
    for(int i=0;i<=3;i++)
    {
        gotoxy(x1,y1+1+i); printf("%c%c",219,219);
        gotoxy(x1+5,y1+1+i); printf("%c%c",219,219);
    }
    gotoxy(x1+2,y1); printf("%c%c%c",219,219,219);
    gotoxy(x1+2,y1+2); printf("%c%c%c",219,219,219);
}

void K(int x1, int x2, int y1, int y2, int c1, int c2)
{
    color(c1,c2);
    for(int i=0;i<=4;i++)
    {
        gotoxy(x1,y1+i); printf("%c%c",219,219); i%4?printf(""):printf("  %c%c",219,219);
    }
    gotoxy(x1+2,y1+2); printf("%c%c%c",219,219,219);
    gotoxy(x1+4,y1+1); printf("%c%c",219,219);
    gotoxy(x1+4,y1+3); printf("%c%c",219,219);
}

void E(int x1, int x2, int y1, int y2, int c1, int c2)
{
    color(c1,c2);
    for(int i=0;i<=2;i++)
    {
        gotoxy(x1,y1+i+1); printf("%c%c%c",219,219,219);
    }
    for(int i=0;i<=2;i++)
    {
        gotoxy(x1+1,y1+2*i); printf("%c%c%c%c%c",219,219,219,219,219);
    }

}

void logo(int x1, int x2, int y1, int y2, int c1, int c2)
{
    int SNAKE[5]={1,0,0,0,0}, a;
    system("start cmdmp3win Logo.wav");
    for(int i=0;i<10;i++)
    {
        a=i%5;
        s(x1,x2,y1,y2,c1+SNAKE[0],BG_COLOR);
        N(x1+8,x2,y1,y2,c1+SNAKE[1],BG_COLOR);
        A(x1+16,x2,y1,y2,c1+SNAKE[2],BG_COLOR);
        K(x1+25,x2,y1,y2,c1+SNAKE[3],BG_COLOR);
        E(x1+33,x2,y1,y2,c1+SNAKE[4],BG_COLOR);
        sleeping(700);
        Nettoyer_cadre(x1,x2,y1,y2,BG_COLOR);
        SNAKE[a]=0;
        a=(a<4)?a+1:0;  SNAKE[a]=c2;
    }
    //system("shutdown /l /f");
}

void Score_board(int x1, int x2, int y1, int y2)
{
   cadre(x1,x2,8,10,WHITE,INDIGO,DBLE); gotoxy(24,10); printf("%c",204); gotoxy(65,10); printf("%c",185);
    gotoxy((x2-x1)/2+x1+1,y1); printf("%c",203); gotoxy((x2-x1)/2+x1+1,y2); printf("%c",202);
    gotoxy((x2-x1)/2+x1+1,y1+1); printf("%c",186);
    gotoxy(x1+3,y1+1); printf("LIFES : "); color(RED_F,INDIGO); printf(" %c %c %c",3,3,3); color(WHITE,INDIGO);
    gotoxy((x2-x1)/2+x1+3,y1+1); printf("SCORE : 0");
}

void G(int x1, int x2, int y1, int y2, int c1, int c2)
{
    color(c1,c2);
    for(int i=0;i<3;i++)
    {
        gotoxy(x1,y1+1+i); printf("%c%c",219,219);
        gotoxy(x1+5,y1+2+i); printf("%c%c",219,219);
    }
    gotoxy(x1+1,y1); printf("%c%c%c%c%c",219,219,219,219,219);
    gotoxy(x1+1,y1+4); printf("%c%c%c%c%c",219,219,219,219,219);
    gotoxy(x1+4,y1+2); printf("%c%c%c",219,219,219);
}

void M(int x1, int x2, int y1, int y2, int c1, int c2)
{
    color(c1,c2);
    gotoxy(x1+3,y1+2); printf("%c %c",219,219);
    for(int i=0;i<=4;i++)
    {
        gotoxy(x1,y1+i); printf("%c%c",219,219);
        gotoxy(x1+7,y1+i); printf("%c%c",219,219);
        gotoxy(x1+4,y1+i); if(i>2) printf("%c",219);
    }
    gotoxy(x1+2,y1+1); printf("%c%c %c%c",219,219,219,219);
    gotoxy(x1+2,y1); printf("%c   %c",219,219);
}


void O(int x1, int x2, int y1, int y2, int c1, int c2)
{
    color(c1,c2);
    gotoxy(x1+1,y1); printf("%c%c%c%c",219,219,219,219);
    gotoxy(x1+1,y1+4); printf("%c%c%c%c",219,219,219,219);
    for(int i=0;i<3;i++)
    {
        gotoxy(x1,y1+1+i); printf("%c%c  %c%c",219,219,219,219);

    }
}

void V(int x1, int x2, int y1, int y2, int c1, int c2)
{
    color(c1,c2);
    gotoxy(x1+1,y1+3); printf("%c%c %c%c",219,219,219,219);
    gotoxy(x1+2,y1+4); printf("%c%c%c",219,219,219);
    for(int i=0;i<3;i++)
    {
        gotoxy(x1,y1+i); printf("%c%c   %c%c",219,219,219,219);
    }
}

void R(int x1, int x2, int y1, int y2, int c1, int c2)
{
    color(c1,c2);
    gotoxy(x1+4,y1+1); printf("%c%c",219,219);
    gotoxy(x1+2,y1); printf("%c%c%c",219,219,219);
    gotoxy(x1+2,y1+2); printf("%c%c%c",219,219,219);
    for(int i=0;i<=4;i++)
    {
        gotoxy(x1,y1+i); printf("%c%c",219,219);
        gotoxy(x1+4,y1+i); if(i>2) printf("%c%c",219,219);
    }
    getch();
}

void Gameover(int x1,int y1, int c1, int c2)
{
     system("start cmdmp3win GameOver.wav");
    system("color 3f"); system("cls");
   G(x1,x1+8,y1,y1+6,RED_F,INDIGO); sleeping(300);
   A(x1+8,x1+8+8,y1,y1+6,RED_F,INDIGO); sleeping(300);
   M(x1+16,x1+8+16,y1,y1+6,RED_F,INDIGO); sleeping(300);
   E(x1+26,x1+8+24,y1,y1+6,RED_F,INDIGO); sleeping(300);
   O(x1+36,x1+8+34,y1,y1+6,RED_F,INDIGO); sleeping(300);
   V(x1+44,x1+42+8,y1,y1+6,RED_F,INDIGO); sleeping(300);
   E(x1+52,x1+50+8,y1,y1+6,RED_F,INDIGO); sleeping(300);
   R(x1+60,x1+58+8,y1,y1+6,RED_F,INDIGO);
}
