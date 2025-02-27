#include "include/config.h"
#include "include/display.h"
#include "include/matriz.h"


ssd1306_t ssd;


int main() 
{
    stdio_init_all(); 

    iniciar();
    srand(time(NULL));

    bool cor = true;
    uint16_t x_value;
    uint16_t y_value;

    //matriz de leds
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);
    set_one_led(10, 0, 10, 0.1);
 

    gpio_set_irq_enabled_with_callback(BOTTONA, GPIO_IRQ_EDGE_FALL, true, &callba);
    gpio_set_irq_enabled_with_callback(BOTTONB, GPIO_IRQ_EDGE_FALL, true, &callba);

    while (true) {
        
        movimentar(x_value, y_value, &ssd, cor);//movimenta o cursor no display
        sleep_ms(100);  
    }
    return 0;
}