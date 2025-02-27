#ifndef CONFIG_H
#define CONFIG_H

// Bibliotecas
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "ws2812.pio.h"
#include "pico/bootrom.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"
#include "include/ssd1306.h"
#include "hardware/timer.h"
#include "hardware/pio.h"

#include "include/font.h"
#include "include/matriz.h"

//botão
#define BOTTONA 5
#define BOTTONB 6

// definição de pinos coordenadas do oled
#define X 27   
#define Y 26

//Oled
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C

//matriz de leds
#define NUM_PIXELS 25
#define LED_RED 13
#define WS2812_PIN 7
#define IS_RGBW false

//buffer de LEDs
#define NUM_PIXELS 25

#define LED_BLUE 12
#define LED_RED 13
// Declaração da função

void iniciar();//inicializa os botões e o display
#endif