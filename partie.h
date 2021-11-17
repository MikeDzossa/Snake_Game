#ifndef PARTIE_H_INCLUDED
#define PARTIE_H_INCLUDED
#define LINE_MENU 16
#define COL_MENU 25
#define LINE_SCORE
#define COL_SCORE
#define LINE_HELP
#define COL_HELP

#define X1 19
#define X2 70
#define Y1 12
#define Y2 33





int menu_deroulant(int x1, int x2, int y1, int y2);

void load(int x1, int x2, int y1, int y2);

void sleeping(int ms);

void load2(int x1, int x2, int y1, int y2);

void High_scores(int x1, int x2, int y1, int y2);

void RESET(int x1, int y1);

void Record_score(int Pts, int x, int y, char *nom);

int nb_chiffres(int nb);

void Help(int x1, int x2, int y1, int y2);

void Game(int x1, int x2, int y1, int y2);

void logo(int x1, int x2, int y1, int y2, int c1, int c2);

void s(int x1, int x2, int y1, int y2, int c1, int c2);

void N(int x1, int x2, int y1, int y2, int c1, int c2);

void A(int x1, int x2, int y1, int y2, int c1, int c2);

void K(int x1, int x2, int y1, int y2, int c1, int c2);

void G(int x1, int x2, int y1, int y2, int c1, int c2);

void E(int x1, int x2, int y1, int y2, int c1, int c2);

void M(int x1, int x2, int y1, int y2, int c1, int c2);

void O(int x1, int x2, int y1, int y2, int c1, int c2);

void Score_board(int x1, int x2, int y3, int y2);

void V(int x1, int x2, int y1, int y2, int c1, int c2);

void R(int x1, int x2, int y1, int y2, int c1, int c2);

void Gameover(int x1, int y1, int c1, int c2);

#endif // PARTIE_H_INCLUDED
