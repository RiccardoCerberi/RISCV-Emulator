import os
import glob
import subprocess

DIR_PATH = 'riscv-tests/isa'
BIN_FILES = 'bin_files'

if __name__ == '__main__':
    if not os.path.isdir(BIN_FILES):
        os.mkdir(BIN_FILES)
    for file in glob.glob(f'{DIR_PATH}/rv32ui-p-*'):
        if not file.endswith('.dump'):
            bin_file = file[file.find('rv32'):len(file)] + '.bin'
            print(f'Generating binary {bin_file} for executable {file}')
            subprocess.run(f'riscv64-unknown-elf-objcopy -O binary {file} \
                    {BIN_FILES}/{bin_file}', shell=True)
