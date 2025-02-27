#ifndef MATRIZ_H
#define MATRIZ_H

#include "include/config.h"

// Declarações das funções

void set_one_led(uint8_t r, uint8_t g, uint8_t b, double inten); // Percorre o buffer e marca 1 ligado e 0 desligado

void contador(int contar);//imprime os números na matriz de LEDs

static inline void put_pixel(uint32_t pixel_grb);//enviar dados para o LED

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b);//reorganizar RGB para GRB no WS2812

void interrupcao(bool status_boi);//interrupção para matriz

#endif 