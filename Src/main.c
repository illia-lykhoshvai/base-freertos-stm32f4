#include "FreeRTOS.h"
#include "task.h"

#include "stm32f4xx.h"

// TASKS
static void prvBlinkTask(void* pvParameters);

int main(void) {

    // init HW
    RCC->AHB1ENR |= (1 << 2); // GPIOC en
    GPIOC->MODER |= (1 << (13*2));
    GPIOC->OTYPER |= ( 1 << 13 ); // PC13-LED

    xTaskCreate(prvBlinkTask, "LED", configMINIMAL_STACK_SIZE, NULL, configMAX_PRIORITIES-1, NULL);

    vTaskStartScheduler();

    // should get here if no enough memory to create idle task
    return 0;
}

#define BLINK_DELAY ( ( TickType_t ) 1000 / portTICK_PERIOD_MS )
static void prvBlinkTask(void* pvParameters) {
    for(;;) {
        GPIOC->ODR ^= (1 << 13);
        vTaskDelay(BLINK_DELAY);
    }
}