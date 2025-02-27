#ifndef DISPLAY_H
#define DISPLAY_H

#include "config.h"
#define ADC_MAX 2100
#define ADC_MIN 1700


//===
typedef struct {
    uint16_t id;
    uint16_t peso_inicial;
    uint16_t peso_atual;
} Boi;

//===


// Declarações das funções
void oled(uint16_t x, uint16_t y, ssd1306_t *ssd, bool cor);//desenha no oled

void desenho(ssd1306_t *ssd);//desenha um desenho no display

void rect(ssd1306_t *ssd);//desenha um retangulo no display

void movimentar( uint16_t x_value, uint16_t y_value, ssd1306_t *ssd, bool cor);//movimenta o cursor no display

uint16_t ler_adc(uint8_t canal);//função auxiliar para ler o ADCs

void movimentar_boi(ssd1306_t *ssd, bool cor);//movimenta o boi no display

void callba(uint gpio, uint32_t events);//função de callback

void mostrar_boi(Boi *boi, ssd1306_t *ssd);//função que mostra o boi no display
void atualizar_peso(Boi *boi, uint16_t novo_peso);//função que atualiza o peso do boi
void calcular_media_peso(ssd1306_t *ssd);
#endif 