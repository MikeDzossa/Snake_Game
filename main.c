#include <stdio.h>
#include <windows.h>
#include "field.h"
#include <time.h>
#include "partie.h"
#include "snake.h"
Player P;

int main()
{
    system("mode con: LINES=16 COLS=25");
    system("color f0");
    system("setvol unmute");
    system("setvol 17");
    int choix;

    srand(time(NULL));
    do
    {
        system("start cmdmp3win Loading.wav");
        sleeping(400);
        choix=menu_deroulant(1,23,0,15);
        switch(choix)
        {
            case 0:
                Game(1,89,0,34);
                break;
            case 1:
                High_scores(1,23,0,15);
                break;
            case 2:
                Help(1,79,0,19);
                break;
            case 3:
                system("cls");
                color(WHITE,WHITE);
                exit(0);
                break;
        }

    }
    while(choix!=3);

   return 0;
}
