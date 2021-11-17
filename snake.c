#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include "field.h"
#include "partie.h"
#include "snake.h"
#include <time.h>
#include <conio.h>
#include<ctype.h>
#include <process.h>
#include <unistd.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77


extern Player P;
Snakes S;
char c;

void Info(int x1, int x2, int y1, int y2)
{
    int i=0;
    char c=5, nom[16];
    color(0,15);
    char header[]={"Entrez votre pseudonyme"};
    color(WHITE,INDIGO);
    gotoxy(x1+6,y1+2); system("start cmdmp3win Pseudo.wav");
    while(header[i]!='\0')
    {
       sleeping(100);
       printf("%c",header[i]);
       i++;
    }
    cadre(x1+7,x1+27,y1+5,y1+7,WHITE,INDIGO,FIN);
    gotoxy(x1+10,y1+6); i=0;
    while(1)
    {
       c=getch();
       if(i<15 && c!=8)
       {
         nom[i]=c;
        system("start cmdmp3win Type.wav");
         i++;
         printf("%c",c);
       }
       if(c==8 && i>0)
       {
          i--;
          gotoxy(x1+10+i,y1+6); printf(" "); gotoxy(x1+10+i,y1+6);
          system("start cmdmp3win Type1.wav");
       }
       if(c==13 && i!=0)  break;
    }
    system("start cmdmp3win Choice.wav"); sleeping(200);
    P.length=i;
    for(int j=0;j<i;j++)
        P.name[j]=nom[j];
}

void Move(int x1, int x2, int y1, int y2)
{

    char opposite=0;
    int x,y,a,b, food=0;
    int i=0, j=0, pos, wait;
    S.lifes=3;  P.score=0;

    while(S.lifes)
    {
                a=rand()%(x2-x1-1)+x1+1;
                b=rand()%(y2-y1-1)+y1+1;
        Snake_Init(x1,y1);
        c=RIGHT;
        opposite=0;
        while(1)
        {
          if(kbhit())
            c=getch();
        if(c==opposite) c=(opposite==UP)?DOWN:(opposite==DOWN)?UP:(opposite==LEFT)?RIGHT:(opposite==RIGHT)?LEFT:opposite;
        if(c!=opposite)
        {
            i=(c==LEFT)?-1:(c==RIGHT)?1:0; j=(c==UP)?-1:(c==DOWN)?1:0;
           if(Die(S.P[S.head].x+i,S.P[S.head].y+j))
            {
               S.lifes--; pos=(S.lifes==2)?2:(S.lifes==1)?1:0;
               gotoxy(36+pos*2,9); color(WHITE,INDIGO); printf(" ");
               system("start cmdmp3win Die.wav");
                for(int i=0;i<=5;i++)
                {
                  for(int j=0;j<=S.length;j++)
                  {
                      gotoxy(S.P[j].x,S.P[j].y);
                     if(i%2!=0) (S.head==j)?color(GREEN_F,RED_F):color(GREEN_F,BLACK);
                     else color(GREEN_F,GREEN_F);
                     printf(" ");
                  }
                  sleeping(200);
                }

               break;
            }

            if(a==S.P[S.head].x+i && b==S.P[S.head].y+j)
            {
                system("start cmdmp3win Bleep.wav");
                do
                {
                    a=rand()%(x2-x1-1)+x1+1;
                    b=rand()%(y2-y1-1)+y1+1;
                }
                while(Body(a,b));
                food++;
                P.score+=5; gotoxy(55,9); color(WHITE,INDIGO);
                if(food) printf("%d",P.score);

            }
            gotoxy(a,b); color(RED,GREEN_F); printf("%c",4);

                if (c==UP)
                {
                   if(S.P[S.head].y-1!=y1)
                   {
                       x=S.P[S.head].x; y=S.P[S.head].y-1;
                       if (!food) Simple(x,y);
                       else Complex(x,y);
                   }

                }
                else if (c==DOWN)
                {
                    if(S.P[S.head].y+1!=y2)
                    {
                       x=S.P[S.head].x; y=S.P[S.head].y+1;
                       if (!food) Simple(x,y);
                       else Complex(x,y);
                    }
                }
                else if (c==LEFT)
                {
                    if(S.P[S.head].x-1!=x1)
                    {
                       x=S.P[S.head].x-1; y=S.P[S.head].y;
                       if (!food) Simple(x,y);
                       else Complex(x,y);
                    }
                }
                else if (c==RIGHT)
                {
                    if(S.P[S.head].x+1!=x2)
                    {
                       x=S.P[S.head].x+1; y=S.P[S.head].y;
                       if (!food) Simple(x,y);
                       else Complex(x,y);
                    }
                }
                opposite=(c==UP)?DOWN:(c==DOWN)?UP:(c==LEFT)?RIGHT:(c==RIGHT)?LEFT:opposite;
            }
            food=0;
            if(P.score<=280)
            {
                if(c==LEFT || c==RIGHT)
                wait=100-10*(P.score/40)-15;
                else   wait=100-10*(P.score/40);
            }
            else wait=(c==LEFT || c==RIGHT)?55:70;
            //gotoxy(4,4); printf("%d",wait);
            sleeping(wait);
               food=0;
        }

    }
}


void Simple(int x, int y)
{
    gotoxy(S.P[S.head].x,S.P[S.head].y);  color(GREEN_F,BLACK); printf(" ");
    gotoxy(S.P[S.tail].x,S.P[S.tail].y);  color(GREEN_F,GREEN_F); printf(" ");
    S.head=S.tail; S.tail=(S.tail==S.length)?0:S.tail+1;
    S.P[S.head].x=x; S.P[S.head].y=y;
    gotoxy(S.P[S.head].x,S.P[S.head].y);  color(GREEN_F,RED_F); printf(" ");
}

void Complex(int x, int y)
{
    gotoxy(S.P[S.head].x,S.P[S.head].y);  color(GREEN_F,BLACK); printf(" ");
    S.length++;
    for(int i=S.length-1;i>=S.tail;i--)
    {
       S.P[i+1].x=S.P[i].x;
       S.P[i+1].y=S.P[i].y;
    }
    S.head=S.tail; S.tail=S.tail+1;
    S.P[S.head].x=x; S.P[S.head].y=y;
    gotoxy(S.P[S.head].x,S.P[S.head].y);  color(GREEN_F,RED_F); printf(" ");
}

void Snake_Init(int x1, int y1)
{
    Peinture(X1+1,X2-1,Y1+1,Y2-1,GREEN_F);
    c=RIGHT;
    S.head=1; S.length=1; S.tail=0;
    S.P[S.head].y=y1+10; S.P[S.head].x=x1+1; S.P[S.tail].x=x1+1; S.P[S.tail].y=y1+10;

}

int Die(int x, int y)
{

    if(x==X1 || x==X2 || y==Y1 || y==Y2) return 1;
    if(x==S.P[S.head].x && y==S.P[S.head].y) return 0;
    for(int i=0;i<=S.length;i++)
      if(x==S.P[i].x && y==S.P[i].y) return 1;
      return 0;

}

void Your_Score()
{
    system("start cmdmp3win Score.wav");
   system("cls");
   char text[]={"YOUR SCORE"}, ch=1;
   int i=0;
   cadre(20+3,60+3,12,20,WHITE,INDIGO,DBLE);
   gotoxy(35+3,15); color(WHITE,INDIGO);
   while(text[i]!='\0')
    {
       sleeping(100);
       printf("%c",text[i]);
       i++;
    }
    gotoxy(33+3,17);
    for(int j=0;j<P.length;j++)
        printf("%c",P.name[j]);
     gotoxy(33+3+P.length,17); printf(" : %d",P.score);
     gotoxy(30+5,22); color(GREEN_F,INDIGO);
     printf("Press ENTER KEY");
     while(ch!=13)
        ch=getch();
     system("start cmdmp3win Choice.wav"); sleeping(600);

}

int Body(int a, int b)
{
    for(int i=0;i<=S.length;i++)
      if(a==S.P[i].x && b==S.P[i].y) return 1;
      return 0;
}

//powershell -c (New-Object Media.SoundPlayer 'C:\Users\MIKE\Downloads\Music\thunder2.wav').PlaySync();
