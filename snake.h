#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#define AREA 200
typedef struct _Score_
{
    char nom[15];
    int point;
    int length;
}
Score;

typedef struct _Player_
{
    char name[16];
    int score;
    int length;
}
Player;


typedef struct _Position_
{
   int x,y;
}
Position;

typedef struct _Snakes_
{
    Position P[AREA];
    int  lifes, length;
    int head, tail;
}
Snakes;


void Info(int x1, int x2, int y1, int y2);

void field(int x1,int x2, int y1, int y2);

void Move(int x1, int x2, int y1, int y2);

void Simple(int x, int y);

void Snake_Init();

void Complex(int x, int y);

int Die(int x, int y);

int Body(int a, int b);

void Your_Score();

#endif // SNAKE_H_INCLUDED
