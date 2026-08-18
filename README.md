# STM32F446 RTOS

A from-scratch Cortex-M4 runtime and RTOS targeting the STM32F446RE.

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