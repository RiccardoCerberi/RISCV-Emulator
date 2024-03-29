#!/usr/bin/env python3

import os
import glob
import subprocess

DIR_PATH = os.path.join('riscv-tests','isa')
BIN_FILES = 'bin_files'
DUMP_FILES = 'dump_files'
OUT_FILE = 'out.txt'

def makeDir(dir_name):
    if not os.path.isdir(dir_name):
        os.mkdir(dir_name)
        return True
    return False

def generateBinFiles():
    for f in glob.glob(os.path.join(DIR_PATH,'rv32ui-p-*')): #only 32 integers user instructions
        if not f.endswith('.dump'):
            bf = os.path.split(f)[1] + '.bin' # get file without dirs
            bin_path = os.path.join(BIN_FILES, bf)
            subprocess.run(f'riscv64-unknown-elf-objcopy -O binary {f} {bin_path}', shell=True)

if __name__ == '__main__':
    if (makeDir(BIN_FILES)):
        generateBinFiles()
