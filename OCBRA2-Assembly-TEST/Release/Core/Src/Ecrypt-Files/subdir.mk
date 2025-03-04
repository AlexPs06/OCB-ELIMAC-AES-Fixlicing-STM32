################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Src/Ecrypt-Files/aes_encrypt.s \
../Core/Src/Ecrypt-Files/aes_keyschedule_lut.s 

C_SRCS += \
../Core/Src/Ecrypt-Files/OCBRA.c 

S_UPPER_SRCS += \
../Core/Src/Ecrypt-Files/aes_keyschedule.S 

OBJS += \
./Core/Src/Ecrypt-Files/OCBRA.o \
./Core/Src/Ecrypt-Files/aes_encrypt.o \
./Core/Src/Ecrypt-Files/aes_keyschedule.o \
./Core/Src/Ecrypt-Files/aes_keyschedule_lut.o 

S_DEPS += \
./Core/Src/Ecrypt-Files/aes_encrypt.d \
./Core/Src/Ecrypt-Files/aes_keyschedule_lut.d 

S_UPPER_DEPS += \
./Core/Src/Ecrypt-Files/aes_keyschedule.d 

C_DEPS += \
./Core/Src/Ecrypt-Files/OCBRA.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Ecrypt-Files/%.o Core/Src/Ecrypt-Files/%.su Core/Src/Ecrypt-Files/%.cyclo: ../Core/Src/Ecrypt-Files/%.c Core/Src/Ecrypt-Files/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F756xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/Ecrypt-Files/%.o: ../Core/Src/Ecrypt-Files/%.s Core/Src/Ecrypt-Files/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
Core/Src/Ecrypt-Files/%.o: ../Core/Src/Ecrypt-Files/%.S Core/Src/Ecrypt-Files/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Src-2f-Ecrypt-2d-Files

clean-Core-2f-Src-2f-Ecrypt-2d-Files:
	-$(RM) ./Core/Src/Ecrypt-Files/OCBRA.cyclo ./Core/Src/Ecrypt-Files/OCBRA.d ./Core/Src/Ecrypt-Files/OCBRA.o ./Core/Src/Ecrypt-Files/OCBRA.su ./Core/Src/Ecrypt-Files/aes_encrypt.d ./Core/Src/Ecrypt-Files/aes_encrypt.o ./Core/Src/Ecrypt-Files/aes_keyschedule.d ./Core/Src/Ecrypt-Files/aes_keyschedule.o ./Core/Src/Ecrypt-Files/aes_keyschedule_lut.d ./Core/Src/Ecrypt-Files/aes_keyschedule_lut.o

.PHONY: clean-Core-2f-Src-2f-Ecrypt-2d-Files

