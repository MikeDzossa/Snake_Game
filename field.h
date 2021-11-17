#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED
#define BG_COLOR 15
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define  RED 4
#define VIOLET 5
#define YELLOW 6
#define  GREY 8
#define  WHITE 15
#define GREEN_F 10
#define INDIGO 3
#define RED_F 12

#define FIN 1
#define DBLE 0
#define PNT 2
#define CONT 3


void color(int couleurDuTexte,int couleurDeFond);

void gotoxy(int x, int y);

void cadre(int x1,int x2,int y1,int y2,int c1, int c2, int type);

void Nettoyer_cadre(int x1, int x2, int y1, int y2, int bgc);

void Mouvement(int x1, int x2, int y1, int y2);

void cadre_fin(int x1,int x2,int y1,int y2,int c1, int c2);

void Peinture(int x1, int x2, int y1, int y2, int c);

void field(int x1,int x2, int y1, int y2);

#endif // FIELD_H_INCLUDED
