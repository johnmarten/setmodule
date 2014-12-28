#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include "SetModule.h"

#define BYTE 8

static unsigned int x, y; // Koordinater i bit-matrisen.

void my_assert(int i);

void my_assert(int i){
    assert((i >= 0) && (i < 512));
}

void setadd(Set *s, int e){
    my_assert(e);
    x = e % BYTE;
    y = e / BYTE;
    SET_BIT(s, x, y);
}

void setsub(Set *s, int e){
    my_assert(e);
    x = e % BYTE;
    y = e / BYTE;
    CLEAR_BIT(s, x, y);
}

Set setmake(int argc, ...){
    va_list ap;
    int i, j, e;
    Set *s = malloc(sizeof(Set));
    
    // Sätt alla bitar till 0
    for(i = 0; i < (X_SIZE / 8); i++){
	for(j = 0; j < Y_SIZE; j++){
	    s->bits[i][j] = 0;
	}
    }
    va_start(ap, argc);
    for(i = 0; i < argc; i++){
	e = va_arg(ap, int);
	my_assert(e);
	setadd(s, e);
    }
    
    return (*s);
}

int ismember(Set s, int e){
    my_assert(e);
    x = e % BYTE;
    y = e / BYTE;
    if(GET_BIT((&s), x, y) == 0)
	return 0;
    else 
	return 1;
}

void setprint(Set s){

    unsigned int result;
    
    for(x = 0; x < X_SIZE; x++){
	for(y = 0; y < Y_SIZE; y++){
	    if((GET_BIT((&s), x, y)) != 0){
		/* Nu måste vi få fram talet som bitpositionen representerar.
		   Detta görs genom att multiplicera y-koordinaten med 8.
		   Y-koordinaten motsvarar ju en rad i matrisen. Varje rad är en byte.
		   En byte är åtta bitar. T ex åttonde raden blir 64. Sedan adderar
		   man x-koordinaten, t ex 3. 64 + 3 = 67:e biten, d.v.s. talet 67.
		*/
		result = y * X_SIZE;
		result = result + x;
		printf("%d\n", result);
	    }
	}
    }
}

Set setintersection(Set s1, Set s2){
    Set *s = malloc(sizeof(Set));
    
    for(x = 0; x < X_SIZE; x++){
	for(y = 0; y < Y_SIZE; y++){
	    if((GET_BIT((&s1), x, y)) != 0 && (GET_BIT((&s2), x, y)) != 0){
		SET_BIT((s), x, y);
	    }
	}
    }
    return (*s);
}

/*int main(void){
    int i;
    Set s, s1, s2;

    s = setmake(5, 10, 503, 89, 77, 54);
    i = ismember(s, 54);
    printf("%d\n", i);
    setprint(s);
    printf("\n");
    setadd((&s), 53);
    setprint(s);
    setsub((&s), 54);
    printf("\n");
    setprint(s);
    printf("\n");
    i = ismember(s, 54);
    printf("%d\n", i);
    s1 = setmake(5, 11, 503, 88, 77, 54);
    s2 = setintersection(s, s1);
    setprint(s2);
    
    
    return 0;
    }*/
