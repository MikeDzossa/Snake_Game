#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "field.h"

void color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}

void gotoxy(int x, int y)
{
   HANDLE hConsoleOutput;
   COORD dwCursorPosition;
   //cout.flush();
   dwCursorPosition.X = x;
   dwCursorPosition.Y = y;
   hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

void cadre(int x1,int x2,int y1,int y2,int c1, int c2, int type)
{
    int i, police[32]={205,205,186,186,201,187,200,188,196,196,179,179,218,191,192,217,202,203,185,204,201,187,200,188,220,220,219,219,220,220,219,219};
    color(c1,c2);
    int a=type==0?0:type==1?8:type==2?16:24;
    for(i=x1;i<=x2;i++)
    {
        gotoxy(i,y1);
        printf("%c", police[a+0]);
        gotoxy(i,y2);
        printf("%c", police[a+1]);
    }
    for(i=y1;i<=y2;i++)
    {
        gotoxy(x1,i);
        printf("%c", police[a+2]);
        gotoxy(x2,i);
        printf("%c", police[a+3]);
    }
    gotoxy(x1,y1);printf("%c", police[a+4]);
    gotoxy(x2,y1);printf("%c", police[a+5]);
    gotoxy(x1,y2);printf("%c", police[a+6]);
    gotoxy(x2,y2);printf("%c", police[a+7]);

}

void Peinture(int x1, int x2, int y1, int y2, int c)
{
    color(c,c);
    for(int i=x1;i<=x2;i++)
        for(int j=y1;j<=y2;j++)
            {gotoxy(i,j); printf("%c",186);}
}


void Nettoyer_cadre(int x1, int x2, int y1, int y2, int bgc) //Permet de repeindre une selection de une couleur donnée
{
    int y, x;
    color(15,bgc);
    for(y=y1;y<=y2;y++)
    {
        for(x=x1;x<=x2;x++)
        {
           gotoxy(x,y); printf(" ");
        }
    }
}

void field(int x1,int x2, int y1, int y2)
{
    Peinture(x1,x2,y1,y2,INDIGO);
    sleeping(100);
    cadre(x1,x2,y1,y2,WHITE,INDIGO,PNT);
    //sleeping(300);
    cadre(x1+1,x2-1,y1+1,y2-1,WHITE,WHITE,FIN); //sleeping(300);
    Peinture(x1+2,x2-2,y1+2,y2-2,GREEN_F);
}
