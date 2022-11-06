#include "FreeRTOS.h"
#include "task.h"

#include "stm32f4xx.h"

// TASKS
void prvBlinkTask(void* pvParameters);

int main(void) {

    // init HW
    RCC->AHB1ENR |= (1 << 2); // GPIOC en
    GPIOC->MODER |= (1 << (13*2));
    GPIOC->OTYPER |= ( 1 << 13 ); // PC13-LED

    xTaskCreate(prvBlinkTask, "LED blink", configMINIMAL_STACK_SIZE, NULL, 2, NULL);

    vTaskStartScheduler();

    // should get here if no enough memory to create idle task
    return 0;     
}

#define BLINK_DELAY ( ( TickType_t ) 500 / portTICK_PERIOD_MS )
void prvBlinkTask(void* pvParameters) {
    while(1) {
        GPIOC->ODR ^= (1 << 13);
        vTaskDelay(BLINK_DELAY);
    }
}