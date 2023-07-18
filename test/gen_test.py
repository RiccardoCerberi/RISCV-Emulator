import os
import glob
import subprocess

if __name__ == 'main':
    if not os.isdir('bin_files'):
        os.mkdir('bin_files')
    for file in glob.glob('riscv-tests/isa/rv32ui-p-*'):
        if not file.endswith('.dump'):
            subprocess.run(f'riscv64-unknown-elf-objcopy -O binary {file} {file}.bin')
