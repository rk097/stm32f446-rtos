cmake_minimum_required(VERSION 3.20)

project(stm32f446_rtos
    LANGUAGES C ASM
)

add_executable(firmware
    src/main.c
    platform/systick.c
    platform/nucleo.c
    platform/nvic.c
    drivers/uart.c
    drivers/gpio.c
    startup/startup.c
    kernel/task.c
    kernel/context.S
    kernel/pendsv.c
)

target_compile_options(firmware PRIVATE
    -mcpu=cortex-m4
    -mthumb
)

target_link_options(firmware PRIVATE
    -mcpu=cortex-m4
    -mthumb
    -nostartfiles
    -T${CMAKE_SOURCE_DIR}/linker/stm32f446re.ld
)

target_include_directories(firmware PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/drivers
    ${CMAKE_SOURCE_DIR}/platform
    ${CMAKE_SOURCE_DIR}/kernel
)