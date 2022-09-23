/*
 * function_songs.h
 *
 * Created: 17/03/2022 13:36:23
 *  Author: Ana Carolina Souza
 */ 


#ifndef FUNCTION_SONGS_H_
#define FUNCTION_SONGS_H_

#include <asf.h>
#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

extern volatile int pause;
extern volatile int count;
extern volatile int meter;
extern volatile char start_flag;
extern volatile char selecao_flag;
extern int escolha;

typedef struct musica {
	int tempo;
	int *melody;
	char *name;
	int notes;
} musica;

struct musica *pmusica, musica1, musica2, musica3;

void tone(int freq, int time);
void song(musica cancao);

#endif /* FUNCTION_SONGS_H_ */