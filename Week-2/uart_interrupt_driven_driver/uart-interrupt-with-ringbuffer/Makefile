# Toolchain
CC = arm-none-eabi-gcc
AS = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size

# Target
TARGET = firmware
BUILD_DIR = build
LDSCRIPT = linker/STM32F429ZITX_FLASH.ld

# MCU Configuration
CPU = cortex-m4
FPU = fpv4-sp-d16
FLOAT_ABI = hard

MCU_FLAGS = \
				-mcpu=$(CPU) \
				-mthumb \
				-mfpu=$(FPU) \
				-mfloat-abi=$(FLOAT_ABI)

# Paths
SRC_DIRS = \
					 external/STM32F4xx_HAL_Driver/Src \
					 src \

INCLUDE_DIRS = \
							src/ \
							src/app \
							src/common \
							src/drivers \
							src/test \
							external/STM32F4xx_HAL_Driver/Inc \
							external/STM32F4xx_HAL_Driver/Inc/Legacy \
							external/CMSIS/Include \
							external/CMSIS/Device/ST/STM32F4xx/Include

# Source Discovery
C_SOURCES := $(shell find $(SRC_DIRS) -name '*.c')
ASM_SOURCES := $(shell find $(SRC_DIRS) -name '*.s')

# Object generation
OBJECTS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(C_SOURCES)) \
					$(patsubst %.s,$(BUILD_DIR)/%.o,$(ASM_SOURCES))

# Includes
INCLUDES = $(addprefix -I,$(INCLUDE_DIRS))

# Defines
DEFINES = \
					-DDEBUG \
					-DUSE_HAL_DRIVER \
					-DSTM32F429xx

# Compiler flags
CFLAGS= \
				$(MCU_FLAGS) \
				$(DEFINES) \
				$(INCLUDES) \
				-std=gnu11 \
				-O0 \
				-g3 \
				-Wall \
				-ffunction-sections \
				-fdata-sections \
				-fstack-usage

ASFLAGS = \
					$(MCU_FLAGS) \
					-g3 \
					-x assembler-with-cpp \
					--specs=nano.specs

# Linker Flags
LDFLAGS = \
					$(MCU_FLAGS) \
					-T"$(LDSCRIPT)" \
					--specs=nano.specs \
					--specs=nosys.specs \
					-Wl,-Map=$(BUILD_DIR)/$(TARGET).map \
					-Wl,--gc-sections \
					-static

LDLIBS = \
				 -lc \
				 -lm

# Build Rules
.PHONY: all
all : $(BUILD_DIR)/$(TARGET).elf

$(BUILD_DIR)/$(TARGET).elf : $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(OBJECTS) $(LDFLAGS) $(LDLIBS) -o $@
	$(SIZE) $@

$(BUILD_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -MMD -MP -MF $(@:.o=.d) $< -o $@

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -c -MMD -MP -MF $(@:.o=.d) $< -o $@

.PHONY: bin 
bin : $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $(BUILD_DIR)/$(TARGET).bin

.PHONY: hex 
hex : $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O ihex $< $(BUILD_DIR)/$(TARGET).hex

.PHONY: clean 
clean :
	rm -rf $(BUILD_DIR)

.PHONY: flash 
flash : $(BUILD_DIR)/$(TARGET).elf
	make
	@make bin
	st-flash write $(BUILD_DIR)/$(TARGET).bin 0x08000000
