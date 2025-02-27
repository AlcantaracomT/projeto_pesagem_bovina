#include "include/display.h"

uint x = 50, y = 40, boi = 0;

volatile uint32_t interrup = 0;
volatile bool statu_Boi = true;

//===
Boi bois[] = {
    {1, 500, 500}, // ID 1, peso inicial 500kg, peso atual 500kg
    {2, 600, 600}, // ID 2, peso inicial 600kg, peso atual 600kg
};
//===

// Função auxiliar para ler o ADC
uint16_t ler_adc(uint8_t canal) 
{
    adc_select_input(canal);
    return adc_read();
}


// Função que movimenta o cursor no display
void movimentar(uint16_t x_value, uint16_t y_value, ssd1306_t *ssd, bool cor)
{
    x_value = ler_adc(1);
    y_value = ler_adc(0); 

    if (x_value > ADC_MAX) 
    {
        x = (x + 10 > 110) ? 110 : x + 10;

    if (x == 40) 
    {
        interrupcao(false);
        if(boi == 2)
        {
            atualizar_peso(&bois[0], 450); 
            mostrar_boi(&bois[0], ssd);
        }
        if(boi == 3)
        {
            atualizar_peso(&bois[1], 650); 
            mostrar_boi(&bois[1], ssd);
        }
        
        sleep_ms(6000);
    }
        
        ssd1306_fill(ssd, false); 
    } 
    else if (x_value < ADC_MIN) 
    {
        x = (x - 10 < 5) ? 10 : x - 10;
        if (x < 5) x = 10;

        if (x == 30)
        {
            interrupcao(true);
        }
        ssd1306_fill(ssd, false); 
    }

    if (y_value > ADC_MAX) 
    {
        y = (y - 10 < 0) ? 0 : y - 10;
        
        if (y == 20 && x == 20) 
        {
           if (boi == 0) 
           { 
            x = 50; y = 20; 
           }
           else if (boi == 1) 
           { 
                x = 20; y = 40; 
           }
           boi++;
        }

        if (y == 30 && boi == 2 && x == 50) 
        { 
            x = 20; y = 20;
            boi++; 
        }

        if (y == 40 && boi == 3 && x == 50) 
            boi++;
        ssd1306_fill(ssd, false); 
    } 
    else if (y_value < ADC_MIN) 
    {
        y = (y + 10 > 54) ? 50 : y + 10;
        ssd1306_fill(ssd, false); 
    }
    
    movimentar_boi(ssd, cor);
    rect(ssd);
    desenho(ssd);
}


// função mostra dados do boi
void mostrar_boi(Boi *boi, ssd1306_t *ssd) {
    char buffer[50];
    ssd1306_fill(ssd, false); // Limpa o display

    // Exibe o ID do boi
    snprintf(buffer, sizeof(buffer), "boi %d", boi->id);
    ssd1306_draw_string(ssd, buffer, 10, 7);

    // Exibe o peso inicial

    ssd1306_draw_string(ssd, "peso", 10, 20);

    snprintf(buffer, sizeof(buffer), "inicial %d", boi->peso_inicial);
    ssd1306_draw_string(ssd, buffer, 10, 30);

    // Exibe o peso atual
    snprintf(buffer, sizeof(buffer), "atual %d", boi->peso_atual);
    ssd1306_draw_string(ssd, buffer, 10, 40);

    // Exibe a diferença de peso
    int diferenca = boi->peso_atual - boi->peso_inicial;

    if(diferenca >= 0)
    {
        snprintf(buffer, sizeof(buffer), "ganhou %d kg", diferenca);
        ssd1306_draw_string(ssd, buffer, 10, 54);
    }
    else
    {
        snprintf(buffer, sizeof(buffer), "perdeu %d kg", diferenca);
        ssd1306_draw_string(ssd, buffer, 10, 54);
    }
    ssd1306_send_data(ssd); // Envia os dados para o display
}


// Função para atualizar o peso do boi
void atualizar_peso(Boi *boi, uint16_t novo_peso) {
    boi->peso_atual = novo_peso;
}


// Função que movimenta o boi no display
void movimentar_boi(ssd1306_t *ssd, bool cor) {
    if (statu_Boi) {
        switch (boi) {
            case 0: 
                oled(x, y, ssd, cor); 
                oled(50, 20, ssd, cor); 
                break;
            case 1: 
                oled(20, 20, ssd, cor); 
                oled(x, y, ssd, cor); 
                break;
            case 2: 
                oled(20, 20, ssd, cor); 
                oled(20, 40, ssd, cor); 
                break;
            default: break;
        }
    } 
    else {
        switch (boi) {
            case 2: 
                gpio_put(LED_RED, 1); 
                oled(x, y, ssd, cor); 
                oled(20, 20, ssd, cor);
                break;
            case 3: 
                oled(50, 20, ssd, cor); 
                oled(x, y, ssd, cor); 
                break;
            case 4: 
                oled(50, 40, ssd, cor); 
                oled(50, 20, ssd, cor); 
                calcular_media_peso(ssd);
                break;
            default: break;
        }
    }
}

void calcular_media_peso(ssd1306_t *ssd) {
    char tota[50];
    int count = sizeof(bois) / sizeof(bois[0]);
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += bois[i].peso_atual;
    }

    total /= count;

    ssd1306_draw_string(ssd, "media", 60, 10);
    snprintf(tota, sizeof(tota), "%d kg", total);
    ssd1306_draw_string(ssd, tota, 60, 20);

}

// Callback para botões
void callba(uint gpio, uint32_t events) 
{
    uint32_t time_atual = time_us_32();
    if ((time_atual - interrup) < 2000) return; 
    interrup = time_atual;

    if (gpio == BOTTONA) {   
        gpio_put(LED_BLUE, 1);
        statu_Boi = !statu_Boi;
    } 
    else if (gpio == BOTTONB) {
        printf("\n=== Relatorio Mensal de Peso dos Bois ===\n\n");
    
        printf("BOI 1 (ID: 1)\n");
        printf("Semana 1: 500kg -> 520kg (+20kg)\n");
        printf("Semana 2: 520kg -> 535kg (+15kg)\n");
        printf("Semana 3: 535kg -> 550kg (+15kg)\n");
        printf("Semana 4: 550kg -> 570kg (+20kg)\n");
        printf("Ganho total: +70kg\n\n");
        printf("\n=====================================\n");
            
    }
}
//exibe quantidade que entrou e saiu no display
void oled(uint16_t x, uint16_t y, ssd1306_t *ssd, bool cor) 
{
    ssd1306_draw_string(ssd, ":", x, y);
    ssd1306_send_data(ssd);
}


//desenha um retangulo
void rect(ssd1306_t *ssd)
{
    ssd1306_rect(ssd, 0, 0, 128, 64, true, false);
    ssd1306_send_data(ssd);
}


//desenha uma linha
void desenho(ssd1306_t *ssd) 
{
    ssd1306_line(ssd, 40, 0, 40, 50, true);
    ssd1306_send_data(ssd);
}
