TOOLCHAIN_PREFIX ?= riscv64-unknown-elf-
RESET_VECTOR ?= 0
FLASH_ADDR ?= 0x0

# Define source directory
SRC_DIR = src

# Rule for compiling a .S or .c file into a .elf
# This will match any file with the .elf extension
%.elf: $(SRC_DIR)/%.o
	$(TOOLCHAIN_PREFIX)gcc -nostartfiles -march=rv32im_zicsr -mabi=ilp32 -Ttools/link.ld -o $@ $^

# Rule for compiling .S (assembly) files into .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.S
	$(TOOLCHAIN_PREFIX)gcc -c -nostartfiles -march=rv32im_zicsr -mabi=ilp32 -o $@ $<

# Rule for compiling .c (C) files into .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(TOOLCHAIN_PREFIX)gcc -c -nostartfiles -march=rv32im_zicsr -mabi=ilp32 -o $@ $<

# Additional rules for converting ELF to other formats (optional)
%.vh: %.bin
	python3 tools/makehex.py $< > $@

%.bin: %.elf
	$(TOOLCHAIN_PREFIX)objcopy -O binary $< $@

%.ihex: %.elf
	$(TOOLCHAIN_PREFIX)objcopy -O ihex $< $@

%.ub: %.bin
	mkimage \
	-A riscv \
	-C none \
	-T standalone \
	-a 0x0 \
	-e $(RESET_VECTOR) \
	-n '$@' \
	-d $< \
	$@

%.ubvh: %.ub
	objcopy --change-addresses $(FLASH_ADDR) -I binary -O verilog $< $@

clean:
	rm -f $(SRC_DIR)/*.o *.elf *.bin *.vh
