/*
 * function_songs.c
 *
 * Created: 11/04/2022 11:43:31
 *  Author: Ana Carolina Souza
 */ 

#include "function_songs.h"
#include <asf.h>

volatile int pause = 0;
volatile int count = 0;
volatile int meter = 100;
volatile char start_flag = 0;
volatile char selecao_flag = 0;

void set_buzzer();
void clear_buzzer();
void set_led();
void clear_led();

/**
 * freq: Frequencia em Hz
 * time: Tempo em ms que o tom deve ser gerado
 
 *Como fazer? O melhor jeito é contar quantos pulsos (freq)
 *existem dentro de um tempo (time) e então fazer um loop que gere
 *a quantidade de pulsos (na frequência certa).
 */
void tone(int freq, int time){
	double period = 1.0/freq;
	double duration = (time*1000/(period*1000000));
	double delay = period*1000000/2;
	
	for (int i = 0; i <=duration; i++){
		set_buzzer();
		clear_led();
		delay_us(delay);
		clear_buzzer();
		set_led();
		delay_us(delay);
	}	
}

void song(musica musica1){

	// this calculates the duration of a whole note in ms
	int wholenote = (60000 * 4) / musica1.tempo;

	int divider = 0, noteDuration = 0;
	
	int inc;
	
	if(musica1.notes/100 > 0){
		inc = musica1.notes/100;
	} else{
		inc = 100/musica1.notes;
	}
	int meter = 100;
	
	for (int thisNote = pause; thisNote < musica1.notes * 2; thisNote = thisNote + 2) {

		// calculates the duration of each note
		divider = musica1.melody[thisNote + 1];
		if (divider > 0) {
			noteDuration = (wholenote) / abs(divider);
		} else{
			noteDuration = (wholenote) / abs(divider);
			noteDuration *= 1.5; // increases the duration in half for dotted notes
		}
	
		// we only play the note for 90% of the duration, leaving 10% as a pause
		tone(musica1.melody[thisNote], noteDuration * 0.9);
		delay_ms(noteDuration*0.1);
	
		if(start_flag == 1){
			pause = thisNote;
			break;
		} else if(selecao_flag == 1){
			pause = 0;
			count = 0;
			break;
		}
		
		if(count%inc == 0){
			if(meter - 1 > 0){
				meter = meter - 1;
			} else{
				meter = 0;
			}
			gfx_mono_generic_draw_filled_rect(10,20,100,10, 0);
			gfx_mono_generic_draw_filled_rect(10,20,meter,10, 1);
		}
		count++;
  }
}
