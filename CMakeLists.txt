cmake_minimum_required(VERSION 3.20)

project(stm32f446_rtos
    LANGUAGES C ASM
)

add_executable(firmware
    src/main.c
    startup/startup.c
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
)