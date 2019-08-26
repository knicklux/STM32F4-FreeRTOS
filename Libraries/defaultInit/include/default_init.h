#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"
#include "stm32f4xx_usart.h"

// Macro to use CCM (Core Coupled Memory) in STM32F4
#define CCM_RAM __attribute__((section(".ccmram")))

#define FPU_TASK_STACK_SIZE 256

extern StackType_t fpuTaskStack[FPU_TASK_STACK_SIZE] CCM_RAM;  // Put task stack in CCM
extern StaticTask_t fpuTaskBuffer CCM_RAM;  // Put TCB in CCM
extern StackType_t ledTaskStack[FPU_TASK_STACK_SIZE] CCM_RAM;  // Put task stack in CCM
extern StaticTask_t ledTaskBuffer CCM_RAM;  // Put TCB in CCM

void setupAll(void);

void init_USART3(void);
