#include <asf.h>
#include "function_songs.h"
#include <math.h>

#include "NGGYU.h"
#include "MII.h"
#include "SOS.h"
#include "notes.h"

#define BUZZER_PIO PIOC
#define BUZZER_PIO_ID ID_PIOC
#define BUZZER_PIO_IDX 13
#define BUZZER_PIO_IDX_MASK (1 << BUZZER_PIO_IDX)

#define START_PIO	PIOD
#define START_PIO_ID ID_PIOD
#define START_PIO_IDX 28
#define START_PIO_IDX_MASK (1u << START_PIO_IDX) // esse já está pronto.

#define SELECAO_PIO	PIOC
#define SELECAO_PIO_ID ID_PIOC
#define SELECAO_PIO_IDX 31
#define SELECAO_PIO_IDX_MASK (1u << SELECAO_PIO_IDX) // esse já está pronto.

//Configuracoes dos LEDs do display
#define LED_ONE PIOA
#define LED_ONE_ID ID_PIOA
#define LED_ONE_IDX 0
#define LED_ONE_IDX_MASK (1u << LED_ONE_IDX)


void start_callback(){
	if(start_flag == 0){
		start_flag = 1; 
	} else{
		start_flag = 0;
	}
}

void selecao_callback(){
	if(!pio_get(SELECAO_PIO,PIO_INPUT,SELECAO_PIO_IDX_MASK)){
		selecao_flag = 0;
	} else{
		selecao_flag = 1;
	}
}

void init(void){

	// Desativa WatchDog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;

	// Configura led
	pmc_enable_periph_clk(LED_ONE_ID);
	pio_configure(LED_ONE, PIO_OUTPUT_1, LED_ONE_IDX_MASK, PIO_DEFAULT);
	
	pmc_enable_periph_clk(BUZZER_PIO_ID);
	pmc_enable_periph_clk(START_PIO_ID);
	pmc_enable_periph_clk(SELECAO_PIO_ID);
	
	pio_configure(BUZZER_PIO, PIO_INPUT, BUZZER_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_configure(BUZZER_PIO, PIO_INPUT, BUZZER_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	
	pio_set_output(BUZZER_PIO, BUZZER_PIO_IDX_MASK, 0, 0, 0);
	pio_set_input(START_PIO, START_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	pio_set_input(SELECAO_PIO, SELECAO_PIO_IDX_MASK, PIO_PULLUP | PIO_DEBOUNCE);
	
	pio_handler_set(START_PIO,
	START_PIO_ID,
	START_PIO_IDX_MASK,
	PIO_IT_FALL_EDGE,
	start_callback);
	
	pio_handler_set(SELECAO_PIO,
	SELECAO_PIO_ID,
	SELECAO_PIO_IDX_MASK,
	PIO_IT_EDGE,
	selecao_callback);
	
	pio_enable_interrupt(START_PIO,START_PIO_IDX_MASK);
	pio_get_interrupt_status(START_PIO);
	pio_enable_interrupt(SELECAO_PIO,SELECAO_PIO_IDX_MASK);
	pio_get_interrupt_status(SELECAO_PIO);
	
	NVIC_EnableIRQ(START_PIO_ID);
	NVIC_SetPriority(START_PIO_ID,4);
	NVIC_EnableIRQ(SELECAO_PIO_ID);
	NVIC_SetPriority(SELECAO_PIO_ID,4);
}

void set_buzzer(){
	pio_set(PIOC, BUZZER_PIO_IDX_MASK);
}

void clear_buzzer(){
	pio_clear(PIOC, BUZZER_PIO_IDX_MASK);
}

void set_led(){
	pio_set(LED_ONE, LED_ONE_IDX_MASK);
}

void clear_led(){
	pio_clear(LED_ONE, LED_ONE_IDX_MASK);
}

int get_startstop(){
	if (!pio_get(START_PIO,PIO_INPUT,START_PIO_IDX_MASK)){
		return 1;
	} else if(pio_get(START_PIO,PIO_INPUT,START_PIO_IDX_MASK)){
		return 0;
	}
}

int get_selecao(){
	if (!pio_get(SELECAO_PIO,PIO_INPUT,SELECAO_PIO_IDX_MASK)){
		return 1;
		} else if(pio_get(SELECAO_PIO,PIO_INPUT,SELECAO_PIO_IDX_MASK)){
		return 0;
	}
}

int main (void)
{
	pmusica = &musica1;
	pmusica-> tempo = tempo1;
	pmusica-> melody = &melody1[0];
	pmusica-> name = name1;
	pmusica ->notes = sizeof(melody1) / sizeof(melody1[0]) / 2;
	
	pmusica = &musica2;
	pmusica-> tempo = tempo2;
	pmusica-> melody = &melody2[0];
	pmusica-> name = name2;
	pmusica ->notes = sizeof(melody2) / sizeof(melody2[0]) / 2;
	
	pmusica = &musica3;
	pmusica-> tempo = tempo3;
	pmusica-> melody = &melody3[0];
	pmusica-> name = name3;
	pmusica ->notes = sizeof(melody3) / sizeof(melody3[0]) / 2;
		
	int escolha = 1;
	
	struct musica playlist[] = {musica1, musica2, musica3};
	
	board_init();
	sysclk_init();
	delay_init();
	init();
	gfx_mono_ssd1306_init();

	gfx_mono_draw_string(playlist[escolha].name, 0, 0, &sysfont);

  /* Insert application code here, after the board has been initialized. */
	while(1) {
		if(selecao_flag == 1){
			if(escolha == 0){
				escolha = 1;
			} else if(escolha == 1){
				escolha = 2;
			} else if(escolha == 2){
				escolha = 0;
			}
			selecao_flag = 0;
		}
		
		gfx_mono_ssd1306_init();
		gfx_mono_draw_string(playlist[escolha].name, 0, 0, &sysfont);
		
		if(start_flag == 0){
			song(playlist[escolha]);
		}
	}
}
