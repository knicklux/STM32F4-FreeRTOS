cmake_minimum_required(VERSION 3.0)

project(stm32f4-freertos-samples C CXX ASM)

IF(NOT CMAKE_CROSSCOMPILING)
  message(FATAL_ERROR "Cross compiling only. Please use -DCMAKE_TOOLCHAIN_FILE=/PATH/TO/TOOLCHAIN_FILE.")
ENDIF(NOT CMAKE_CROSSCOMPILING)

#add_definitions(-DSTM32F4)

set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/Utilities/stm32_flash.ld")
# ${CMAKE_SOURCE_DIR}/stm32f4-discovery.ld

set(NAME "FreeRTOS")

set(STM32F4_FLAGS "-mfloat-abi=hard -mfpu=fpv4-sp-d16 -mthumb -mcpu=cortex-m4 -fsingle-precision-constant -finline-functions -Wdouble-promotion -Wall -ffunction-sections -fdata-sections")

set(CDEFS "-DUSE_STDPERIPH_DRIVER -DSTM32F4XX -DSTM32F40_41xxx -DHSE_VALUE=8000000 -D__FPU_PRESENT=1 -D__FPU_USED=1 -DARM_MATH_CM4")

set(LDFLAGS "${MCUFLAGS} -u _scanf_float -u _printf_float -fno-exceptions -Wl,--gc-sections")
#,-T${LINKER_SCRIPT}-Map,${CMAKE_CURRENT_BINARY_DIR}/${Name}.map

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 ${STM32F4_FLAGS} ${CFLAGS} ${CDEFS}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++14 ${STM32F4_FLAGS} ${CFLAGS} ${CDEFS}")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LDFLAGS} -T${LINKER_SCRIPT} --specs=rdimon.specs")
# -nostartfiles

function(add_bin_from_elf bin elf)
  add_custom_target(${bin} ALL ${CMAKE_OBJCOPY} -Obinary ${elf} ${bin} DEPENDS ${elf})
endfunction(add_bin_from_elf)
#add_executable(button.elf button.c)
#target_link_libraries(button.elf m c gcc)
#add_bin_from_elf(button.bin button.elf)

#set_source_files_properties(hardware/startup_stm32f4xx.s PROPERTIES COMPILE_FLAGS "-x assembler-with-cpp")

add_library(hardware
  hardware/startup_stm32f4xx.s
  hardware/stm32f4xx_it.c
  hardware/system_stm32f4xx.c
  Libraries/syscall/syscalls.c
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
  PUBLIC -lm 
  PUBLIC -lc 
  PUBLIC -lgcc
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
)
target_include_directories(FreeRTOS PUBLIC
  $<BUILD_INTERFACE:
    ${CMAKE_CURRENT_SOURCE_DIR}/FreeRTOS/include
    ${CMAKE_CURRENT_SOURCE_DIR}/FreeRTOS/portable/GCC/ARM_CM4F>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(FreeRTOS
  PUBLIC STM32F4xx_StdPeriph_Driver
)

add_executable(myexec.elf main.c)
target_link_libraries(myexec.elf FreeRTOS)
add_bin_from_elf(myexec.bin myexec.elf)
