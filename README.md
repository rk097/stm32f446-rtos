# STM32F446 RTOS

A from-scratch Cortex-M4 runtime and RTOS targeting the STM32F446RE.

### Architecture Diagram

![Diagram](/docs/diagram.png)

### Feature List

per-task stacks, SysTick scheduling, PendSV context switching, sleep/blocking, binary semaphores, UART driver, idle task, SysTick system delay

### Key Learnings

- Toolchain/environment setup for baremetal development of STM32 without CubeMX. (Used VS Code with C/C++ Intellisense, CMake, Ninja, and the open source ST-Link)
- Compilation and linkage from command line for baremetal target using arm-none-eabi-gcc, simple linker script based on RAM/FLASH size of STM32F446RE, and Reset_Handler with custom vector table ordered according to ARM Cortex-M4 spec and STM32F446 datasheet
- Developing baremetal drivers for GPIO and UART using register operations (register write, register read-and-writeback depending on the register)
- Interrupt-driven UART with async transmit/receive via ringbuffers on both ends, enabling interrupt both in STM32 register and NVIC
- Usage of PSP vs MSP; Thread vs Handler mode; manually toggling CONTROL.SPSEL vs taking advantage of EXEC_RETURN; context switching using PendSV as per ARM Cortex-M4's specifications
- Cooperative yielding vs preemption using SysTick interrupt; task sleeps; task scheduling using states, and task management with task stacks and stack pointers in an RTOS style
- Implementation of a binary semaphore; disabling IRQs to allow for critical paths in code

## Important References

[STM32F446 Reference Manual](https://www.st.com/en/microcontrollers-microprocessors/stm32f446/documentation.html#)
[STM32F446 Datasheet](https://www.st.com/resource/en/datasheet/stm32f446ze.pdf)
[Nucleo64 User Manual](https://www.st.com/resource/en/user_manual/um1724-stm32-nucleo64-boards-mb1136-stmicroelectronics.pdf)
Arm Cortex-M4 Technical Reference Manual
The Definitive Guide to ARM Cortex-M3 and Cortex-M4 Processors

## Building

Run once, and whenever build settings change:

```shell
cmake -S . -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE="cmake/arm-none-eabi-gcc.cmake"
```

Run on every build:

```shell
cmake --build build
```

## Flashing

```shell
st-info --probe
arm-none-eabi-objcopy -O binary build/firmware build/firmware.bin
st-flash write build/firmware.bin 0x08000000
```

## Debug

```shell
cmake -S . -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE="cmake/arm-none-eabi-gcc.cmake" -DCMAKE_BUILD_TYPE=Debug
cmake --build build
st-util
arm-none-eabi-gdb build/firmware
target extended-remote localhost:4242
load
```

## Target

- MCU: STM32F446RE
- Core: ARM Cortex-M4F
- Board: NUCLEO-F446RE

## Toolchain

- ARM GNU Toolchain
- CMake
- Ninja
- stlink v1.7