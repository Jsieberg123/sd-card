// /*
//  * main.c
//  *
//  *  Created on: Mar 4, 2017
//  *      Author: jacob
//  */

#define true 1
#define false 0

#define F_CPU 8000000UL

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>

#include "spi.h"
#include "uart.h"
#include "adc.h"
#include "carddefs.h"
#include "options.h"

static void TaskBlinkGreenLED(void *pvParameters);

static xSemaphoreHandle mut;

//-----------------------------------------------------------

int main() {
  uart_init();
  stdout = &uart_output;
  stdin = &uart_input;

  iobuffer[0] = CARD_TYPE;

  SetupSpi();

  SetupAdc();
  
  sei();

  mut = xSemaphoreCreateMutex();

  xTaskCreate(TaskBlinkGreenLED, (const portCHAR *)"GreenLED", 50, NULL, 3, NULL);

  #if CARD_TYPE == CARD_TYPE_MOTORMONT
    CreateReadAdcTask(1, 10, 100);
    CreateReadAdcTask(2, 12, 100);
    CreateReadAdcTask(3, 14, 100);
    CreateReadAdcTask(4, 16, 100);
    CreateReadAdcTask(5, 18, 100);
    CreateReadAdcTask(6, 20, 100);
  #endif

  vTaskStartScheduler();

  for (;;)
    ;
  ;

  return 0;
}

//-----------------------------------------------------------

// Main Green LED Flash
static void TaskBlinkGreenLED(void *pvParameters) {
  // set pin 5 of PORTB for output
  DDRD |= _BV(DDD7);

  TickType_t xLastWakeTime = xTaskGetTickCount();
  while (true) {
    // LED on
    PORTD |= _BV(PORTD7);
    // printf("ON\n");
    vTaskDelayUntil(&xLastWakeTime, (2000 / portTICK_PERIOD_MS));

    // LED off
    PORTD &= ~_BV(PORTD7);
    // printf("OFF\n");
    vTaskDelayUntil(&xLastWakeTime, (1000 / portTICK_PERIOD_MS));
  }

  vTaskDelete(NULL);
}

//-----------------------------------------------------------

void vApplicationStackOverflowHook(TaskHandle_t xTask, portCHAR *pcTaskName) {
  // main LED on
  DDRB |= _BV(DDB5);
  PORTB |= _BV(PORTB5);

  // die
  while (true) {
    PORTB |= _BV(PORTB5);
    _delay_ms(250);
    PORTB &= ~_BV(PORTB5);
    _delay_ms(250);
  }
}
