All:
	arm-none-eabi-gcc -g -O0 -mcpu=cortex-m4 -std=gnu11 -IDrivers/Inc -E Drivers/Src/button.c
	arm-none-eabi-gcc -g -O0 -mcpu=cortex-m4 -std=gnu11 -IDrivers/Inc -E Drivers/Src/exti0.c
	arm-none-eabi-gcc -g -O0 -mcpu=cortex-m4 -std=gnu11 -IDrivers/Inc -E Drivers/Src/led.c
	arm-none-eabi-gcc -g -O0 -mcpu=cortex-m4 -std=gnu11 -IDrivers/Inc -E Drivers/Src/tim1.c
	arm-none-eabi-gcc -g -O0 -mcpu=cortex-m4 -std=gnu11 -IDrivers/Inc -E Drivers/Src/uart.c
	arm-none-eabi-gcc -g -O0 -mcpu=cortex-m4 -std=gnu11 -IDrivers/Inc -E Drivers/Src/dma.c
	arm-none-eabi-gcc -g -O0 -mcpu=cortex-m4 -std=gnu11 -IDrivers/Inc -c Drivers/Src/button.c -o build/button.o 
	arm-none-eabi-gcc -g -O0 -mcpu=cortex-m4 -std=gnu11 -IDrivers/Inc -c Drivers/Src/exti0.c -o build/exti0.o 
	arm-none-eabi-gcc -g -O0 -mcpu=cortex-m4 -std=gnu11 -IDrivers/Inc -c Drivers/Src/led.c -o build/led.o
	arm-none-eabi-gcc -g -O0 -mcpu=cortex-m4 -std=gnu11 -IDrivers/Inc -c Drivers/Src/tim1.c -o build/tim1.o
	arm-none-eabi-gcc -g -O0 -mcpu=cortex-m4 -std=gnu11 -IDrivers/Inc -c Drivers/Src/uart.c -o build/uart.o
	arm-none-eabi-gcc -g -O0 -mcpu=cortex-m4 -std=gnu11 -IDrivers/Inc -c Drivers/Src/dma.c -o build/dma.o
	arm-none-eabi-gcc -g -O0 -mcpu=cortex-m4 -std=gnu11 -IDrivers/Inc -c Core/main.c -o build/main.o
	arm-none-eabi-gcc -g -O0 -mcpu=cortex-m4 -std=gnu11 -IDrivers/Inc -c Core/syscalls.c -o build/syscalls.o
	arm-none-eabi-gcc -g -O0 -mcpu=cortex-m4 -std=gnu11 -c -x assembler-with-cpp Core/startup_stm32f411vetx.s -o build/startup.o
	arm-none-eabi-gcc -g -O0 -mcpu=cortex-m4 -std=gnu11 -T"STM32F411VETX_FLASH.ld" -Wl,-Map="build/output.map" -Wl,--gc-sections -static build/*.o -o build/firmware.elf
Clean:
	rm -rf build/*.o build/*.elf build/*.map
Load:
	STM32_Programmer_CLI -c port=SWD -e 0 -d build/firmware.elf -rst