#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

/* Definição dos Pinos dos LED's */
#define LED_1 4
#define LED_2 5
#define LED_3 6
#define LED_4 7

/* Definição das Funções de Controle de Tempo */
#define Delay_ms vTaskDelay
#define DELAY_500_MILISECCONDS 500

// Funções
void Fase1(void);
void Resetar_Leds(void);
void Fase2(void);
void Fase2_setarLeds(int led_num, int state);

void app_main() 
{
  gpio_reset_pin(LED_1);
  gpio_reset_pin(LED_2);
  gpio_reset_pin(LED_3);
  gpio_reset_pin(LED_4);

  gpio_set_direction(LED_1, GPIO_MODE_OUTPUT);
  gpio_set_direction(LED_2, GPIO_MODE_OUTPUT);
  gpio_set_direction(LED_3, GPIO_MODE_OUTPUT);
  gpio_set_direction(LED_4, GPIO_MODE_OUTPUT);

  while (true) 
  {
    Fase1();

    Delay_ms(DELAY_500_MILISECCONDS / portTICK_PERIOD_MS);
    Resetar_Leds();
    Fase2();
    Delay_ms(DELAY_500_MILISECCONDS / portTICK_PERIOD_MS);
  }
}

void Fase1(void) 
{
    for (int i = 0; i < 16; i++) 
    {
        gpio_set_level(LED_1, (i >> 0) & 0x01);  
        gpio_set_level(LED_2, (i >> 1) & 0x01);  
        gpio_set_level(LED_3, (i >> 2) & 0x01); 
        gpio_set_level(LED_4, (i >> 3) & 0x01); 

        Delay_ms(DELAY_500_MILISECCONDS / portTICK_PERIOD_MS); 
    }
}

void Fase2(void)
{
  for (int i = 1; i <= 4; i++) 
  {
      Fase2_setarLeds(i, 1);
      Delay_ms(DELAY_500_MILISECCONDS / portTICK_PERIOD_MS);
      Fase2_setarLeds(i, 0);
  }
  for (int i = 4; i >= 1; i--) 
  {
    Fase2_setarLeds(i, 1);
    Delay_ms(DELAY_500_MILISECCONDS / portTICK_PERIOD_MS);
    Fase2_setarLeds(i, 0);
  }
}

void Fase2_setarLeds(int led_num, int state) 
{
    switch (led_num) 
    {
        case 1: gpio_set_level(LED_1, state); break;
        case 2: gpio_set_level(LED_2, state); break;
        case 3: gpio_set_level(LED_3, state); break;
        case 4: gpio_set_level(LED_4, state); break;
    }
}

void Resetar_Leds(void)
{
  gpio_set_level(LED_1, 0);
  gpio_set_level(LED_2, 0);
  gpio_set_level(LED_3, 0);
  gpio_set_level(LED_4, 0);
}


