#ifndef SETMODULE_H
#define SETMODULE_H

#define MINIMAL
#define X_SIZE 8 // 8 bitar i x-led
#define Y_SIZE 64 // 64 bitar i y-led, 8 multiplicerat med 64 är ju 512

typedef char bitmap[X_SIZE / 8][Y_SIZE]; // X_SIZE / 8 = 8 bitar per byte
typedef struct set{
    bitmap bits;
} Set;

#define SET_BIT(s,x,y) s->bits[(x)/8][y] |= (0x80 >> ((x) % 8))
#define GET_BIT(s,x,y) s->bits[(x)/8][y] & (0x80 >> ((x) % 8))
#define CLEAR_BIT(s,x,y) s->bits[(x)/8][y] ^=(0x80 >> ((x) % 8)) 

void setadd(Set *s, int e);
void setsub(Set *s, int e);
Set setmake(int argc, ...);
int ismember(Set s, int e);
void setprint(Set s);
Set setintersection(Set s1, Set s2);

#endif
