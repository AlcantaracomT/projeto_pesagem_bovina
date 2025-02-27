#include "include/matriz.h"

// Variável global para o buffer de LEDs
bool led_buffer[NUM_PIXELS];

int numeral = 0;

// Função única para tratar ambos os botões
void interrupcao(bool status_boi) 
{
    // Verifica qual botão foi pressionado
    if (status_boi) 
    { 
        numeral = (numeral + 1) % 10;
    } 
    else if(status_boi == 0)
    { 
        numeral = (numeral - 1 + 10) % 10;
    }

    // Atualiza a matriz de LEDs
    contador(numeral);
    set_one_led(10, 0, 10, 0.5);
}


// Enviar dados para o LED
static inline void put_pixel(uint32_t pixel_grb) 
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}



// Reorganizar RGB para GRB no WS2812
static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) 
{
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}



// Percorre o buffer e marca 1 ligado e 0 desligado
void set_one_led(uint8_t r, uint8_t g, uint8_t b, double inten) 
{
    // Intensidade 
    r *= inten;
    g *= inten;
    b *= inten;

    // Define a cor com base nos parâmetros fornecidos
    uint32_t color = urgb_u32(r, g, b);

    for (int i = 0; i < NUM_PIXELS; i++) {
        if (led_buffer[i]) {
            put_pixel(color); 
        } else {
            put_pixel(0); 
        }
    }
}



// Função que imprime os números na matriz de LEDs
void contador(int contar)
{
    bool numeros[10][NUM_PIXELS] = {
        {   0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0,  0, 1, 0, 1, 0, 0, 1, 1, 1, 0}, // 0

        {   0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0}, // 1

        {   0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0,  0, 1, 1, 1, 0},  // 2

        {   0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0}, //3

        {   0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0}, //4

        {   0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0,  0, 1, 1, 1, 0}, //5
        
        {   0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0}, //6

        {   0, 1, 0, 0, 0, 0, 0, 0, 1, 0,  0, 1, 0, 0, 0,  0, 0, 0, 1, 0,  0, 1, 1, 1, 0}, //7

        {   0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0,  0, 1, 0, 1, 0, 0, 1, 1, 1, 0}, //8

        {   0, 1, 0, 0, 0,  0, 0, 0, 1, 0,  0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0} //9   
    };

    memcpy(led_buffer, numeros[contar], NUM_PIXELS * sizeof(bool));//copia no array global
    set_one_led(0, 0, 10, 1);
}