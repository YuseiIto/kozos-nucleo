rm -rf obj
mkdir -p obj
arm-none-eabi-as -c targets/STM32F303K8/startup.s -o obj/startup.o -g
arm-none-eabi-gcc -c main.c -o obj/main.o -mcpu=cortex-m4 -O0 -g
arm-none-eabi-ld -T targets/STM32F303K8/ldscript.ld obj/main.o obj/startup.o -o kernel.out -g

arm-none-eabi-objcopy kernel.out -I ihex -O binary kernel.bin 
st-flash write kernel.bin 0x8000000
