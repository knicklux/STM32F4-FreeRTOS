#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOS_initializations.h"
#include "syscalls.c"

void test_FPU_test(void* p);

void blink_LED(void *p);

int main(void) {

  // Configure USART3(PB10, PB11) to redirect printf data to host PC.
  setupAll();

  // Write all tasks running on this CPU as separate functions and create the
  // tasks here with the FreeRTOS API as shown below.
  // Additional initialization of hardware and variables can be done here.

  // Create a task
  // Stack and TCB are placed in CCM of STM32F4
  // The CCM block is connected directly to the core, which leads to zero wait states
  xTaskCreateStatic(test_FPU_test, "FPU", FPU_TASK_STACK_SIZE, NULL, 1, fpuTaskStack, &fpuTaskBuffer);
  xTaskCreateStatic(blink_LED, "LED", FPU_TASK_STACK_SIZE, NULL, 1, ledTaskStack, &ledTaskBuffer);

  vTaskStartScheduler();  // should never return

  for (;;);
}

void test_FPU_test(void* p) {
  float ff = 1.0f;
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  printf("Start FPU test task.\r\n");
  for (;;) {
    float s = sinf(ff);
    ff += s;

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }

  vTaskDelete(NULL);
}

void blink_LED(void *p) {
  printf("Blink LED task.\r\n");
  
  //Enable the GPIOD Clock
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
  
  // GPIOD Configuration
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStruct);
  
  GPIO_SetBits(GPIOD, GPIO_Pin_12);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  for (;;) {
    GPIO_ResetBits(GPIOD, GPIO_Pin_12);
    GPIO_SetBits(GPIOD, GPIO_Pin_13);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    GPIO_ResetBits(GPIOD, GPIO_Pin_13);
    GPIO_SetBits(GPIOD, GPIO_Pin_14);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    GPIO_ResetBits(GPIOD, GPIO_Pin_14);
    GPIO_SetBits(GPIOD, GPIO_Pin_15);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    GPIO_ResetBits(GPIOD, GPIO_Pin_15);
    GPIO_SetBits(GPIOD, GPIO_Pin_12);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }

  vTaskDelete(NULL);
}
