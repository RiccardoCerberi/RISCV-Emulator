gen_ex:
	riscv64-unknown-elf-gcc -Wl,-Ttext=0x0 -nostdlib -march=rv64i -mabi=lp64 -o test test.s
gen_bin: gen_ex
	riscv64-unknown-elf-objcopy -O binary test test.bin
all: gen_bin