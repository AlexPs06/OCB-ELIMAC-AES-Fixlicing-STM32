################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/OCB3.c \
../Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/aes_encrypt.c \
../Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/aes_keyschedule.c \
../Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/aes_keyschedule_lut.c 

OBJS += \
./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/OCB3.o \
./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/aes_encrypt.o \
./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/aes_keyschedule.o \
./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/aes_keyschedule_lut.o 

C_DEPS += \
./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/OCB3.d \
./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/aes_encrypt.d \
./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/aes_keyschedule.d \
./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/aes_keyschedule_lut.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/%.o Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/%.su Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/%.cyclo: ../Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/%.c Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F756xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-EliMAC_OCBRA_fixlixing_AES-2f-fixslicing

clean-Core-2f-Src-2f-EliMAC_OCBRA_fixlixing_AES-2f-fixslicing:
	-$(RM) ./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/OCB3.cyclo ./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/OCB3.d ./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/OCB3.o ./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/OCB3.su ./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/aes_encrypt.cyclo ./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/aes_encrypt.d ./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/aes_encrypt.o ./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/aes_encrypt.su ./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/aes_keyschedule.cyclo ./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/aes_keyschedule.d ./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/aes_keyschedule.o ./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/aes_keyschedule.su ./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/aes_keyschedule_lut.cyclo ./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/aes_keyschedule_lut.d ./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/aes_keyschedule_lut.o ./Core/Src/EliMAC_OCBRA_fixlixing_AES/fixslicing/aes_keyschedule_lut.su

.PHONY: clean-Core-2f-Src-2f-EliMAC_OCBRA_fixlixing_AES-2f-fixslicing

