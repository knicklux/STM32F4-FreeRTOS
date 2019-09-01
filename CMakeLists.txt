cmake_minimum_required(VERSION 3.0)

SET(PROJECT_NAME stm32f4-freertos-exec)

INCLUDE(toolchain.cmake)

project(${PROJECT_NAME} C CXX ASM)

ENABLE_LANGUAGE(ASM)

IF(NOT CMAKE_CROSSCOMPILING)
  message(FATAL_ERROR "Cross compiling only. Please use -DCMAKE_TOOLCHAIN_FILE=/PATH/TO/TOOLCHAIN_FILE.")
ENDIF(NOT CMAKE_CROSSCOMPILING)

function(add_bin_from_elf bin elf)
  add_custom_target(${bin} ALL ${CMAKE_OBJCOPY} -Obinary ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${elf} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${bin} DEPENDS ${elf})
endfunction(add_bin_from_elf)
#add_executable(button.elf button.c)
#target_link_libraries(button.elf m c gcc)
#add_bin_from_elf(button.bin button.elf)

set_source_files_properties(hardware/startup_stm32f4xx.s PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp")

add_library(hardware
  hardware/startup_stm32f4xx.s
  hardware/stm32f4xx_it.c
  hardware/system_stm32f4xx.c
)
target_include_directories(hardware PUBLIC
  $<BUILD_INTERFACE:
    ${CMAKE_CURRENT_SOURCE_DIR}/hardware
    ${CMAKE_CURRENT_SOURCE_DIR}/config
    ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/CMSIS/Device/ST/STM32F4xx/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/STM32F4xx_StdPeriph_Driver/inc>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(hardware
  PUBLIC m
  PUBLIC c
  PUBLIC gcc
)

add_library(STM32F4xx_StdPeriph_Driver
  Libraries/STM32F4xx_StdPeriph_Driver/src/misc.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cec.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma2d.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dsi.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash_ramfunc.c
#  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fmc.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fmpi2c.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_lptim.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_ltdc.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_qspi.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sai.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spdifrx.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c
  Libraries/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c
)
target_include_directories(STM32F4xx_StdPeriph_Driver PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Libraries/STM32F4xx_StdPeriph_Driver/inc>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(STM32F4xx_StdPeriph_Driver
  PUBLIC hardware
)

add_library(FreeRTOS
  FreeRTOS/croutine.c
  FreeRTOS/event_groups.c
  FreeRTOS/list.c
  FreeRTOS/queue.c
  FreeRTOS/tasks.c
  FreeRTOS/timers.c
  FreeRTOS/portable/GCC/ARM_CM4F/port.c
  FreeRTOS/portable/MemMang/heap_4.c
  Libraries/defaultInit/src/default_init.c
  #Libraries/defaultInit/src/hooks.c
)
target_include_directories(FreeRTOS PUBLIC
  $<BUILD_INTERFACE:
    ${CMAKE_CURRENT_SOURCE_DIR}/FreeRTOS/include
    ${CMAKE_CURRENT_SOURCE_DIR}/FreeRTOS/portable/GCC/ARM_CM4F
    ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/defaultInit/include>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(FreeRTOS
  PUBLIC STM32F4xx_StdPeriph_Driver
)

add_executable(${CMAKE_PROJECT_NAME}.elf main.c)
target_include_directories(${CMAKE_PROJECT_NAME}.elf PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Libraries/syscall>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(${CMAKE_PROJECT_NAME}.elf FreeRTOS)
add_bin_from_elf(${CMAKE_PROJECT_NAME}.bin ${CMAKE_PROJECT_NAME}.elf)
