#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

static void blinkTask(void){
	while(1){
		GPIOD->ODR ^= GPIO_ODR_ODR_13;
		vTaskDelay(200);
	}
}

extern void init_LED(){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	GPIOD->MODER |= GPIO_MODER_MODER13_0 | GPIO_MODER_MODER14_0 | GPIO_MODER_MODER15_0;

	xTaskCreate(blinkTask,
		(const signed char *)"blinkTask",
		configMINIMAL_STACK_SIZE,
		NULL,                 // pvParameters
		tskIDLE_PRIORITY + 1, // uxPriority
		NULL              ); // pvCreatedTask

}
