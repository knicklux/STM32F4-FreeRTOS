# see https://gitlab.kamaro-engineering.de/KaMaRo-Etec/stm32_empty/blob/master/CMakeLists.txt
# Note: We handle the assembler for .s files differently and add CDEFS such as -DHSE_VALUE
# Also we set the CMAKE_tool variables for compiler and other tools like objdump
# Additionally we use other c and cpp dialects
# And cmake is called with cmake -DCMAKE_TOOLCHAIN_FILE="../toolchain.cmake" ..

INCLUDE(CMakeForceCompiler)  
SET(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/binary")
set(LDSCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/Link/stm32_flash.ld")
  
SET(CPREF arm-none-eabi)  
SET(CMAKE_C_COMPILER ${CPREF}-gcc)  
SET(CMAKE_CXX_COMPILER ${CPREF}-g++)  
SET(AS "arm-none-eabi-as")  
SET(AR ${CPREF}-ar)  
SET(LD ${CPREF}-ld)  
SET(NM ${CPREF}-nm)  
SET(OBJCOPY ${CPREF}-objcopy)  
SET(OBJDUMP ${CPREF}-objdump)  
SET(READELF ${CPREF}-readelf)  
  
CMAKE_FORCE_C_COMPILER(${CPREF}-gcc GNU)  
CMAKE_FORCE_CXX_COMPILER(${CPREF}-g++ GNU)  
  
# here is the target environment is located  
SET(CMAKE_FIND_ROOT_PATH  /usr/arm-none-eabi)  
  
# adjust the default behaviour of the FIND_XXX() commands:  
# search headers and libraries in the target environment, search   
# programs in the host environment  
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)  
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)  
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)  
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
  
SET(MCU cortex-m4)
set(CDEFS "-DUSE_STDPERIPH_DRIVER -DSTM32F4XX -DSTM32F40_41xxx -DHSE_VALUE=8000000 -D__FPU_PRESENT=1 -D__FPU_USED=1 -DARM_MATH_CM4")
SET(MCFLAGS "-mcpu=${MCU} -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -finline-functions -Wdouble-promotion")  
SET(CMAKE_ASM_FLAGS "")  
SET(CMAKE_C_FLAGS "${MCFLAGS} ${CDEFS} -ffunction-sections -std=gnu99 -fdata-sections -Wall")  
SET(CMAKE_CXX_FLAGS "${MCFLAGS} ${CDEFS} -ffunction-sections -std=c++14 -fno-builtin -fdata-sections -Wall -fno-rtti -fno-exceptions")  
  
SET(CMAKE_C_FLAGS_DEBUG "-O0 -g -gstabs+")  
SET(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -gstabs+")  
SET(CMAKE_ASM_FLAGS_DEBUG "-g -gstabs+")  
  
SET(CMAKE_C_FLAGS_RELEASE "-Os")  
SET(CMAKE_CXX_FLAGS_RELEASE "-Os")  
SET(CMAKE_ASM_FLAGS_RELEASE "")  

# Uncomment if you want to do profiling with gprof
# SET(CMAKE_CXX_FLAGS "-pg")
  
SET(CMAKE_EXE_LINKER_FLAGS "${MCFLAGS} -T${LDSCRIPT} -Wl,-Map=${CMAKE_PROJECT_NAME}.map,--cref,--no-warn-mismatch -Wl,--gc-sections -Wl,--defsym=malloc_getpagesize_P=0x1000,-specs=nosys.specs")  
SET(CMAKE_MODULE_LINKER_FLAGS "")  
SET(CMAKE_SHARED_LINKER_FLAGS "")

#set(CMAKE_ASM_COMPILER "arm-none-eabi-as" CACHE PATH "as" FORCE)
set(CMAKE_ASM_COMPILER ${AS} CACHE PATH "as" FORCE)

set(CMAKE_AR           "arm-none-eabi-ar"      CACHE PATH "ar"      FORCE)
set(CMAKE_LINKER           "arm-none-eabi-ld"      CACHE PATH "ld"      FORCE)
set(CMAKE_NM           "arm-none-eabi-nm"      CACHE PATH "nm"      FORCE)
set(CMAKE_OBJCOPY           "arm-none-eabi-objcopy"      CACHE PATH "objcopy"      FORCE)
set(CMAKE_OBJDUMP           "arm-none-eabi-objdump"      CACHE PATH "objdump"      FORCE)
set(CMAKE_STRIP           "arm-none-eabi-strip"      CACHE PATH "strip"      FORCE)
set(CMAKE_STRIP           "arm-none-eabi-ranlib"      CACHE PATH "ranlib"      FORCE)
