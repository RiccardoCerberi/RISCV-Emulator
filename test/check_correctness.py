#!/usr/bin/env python3

import subprocess
import glob

# Enable test for emulator.
# For each binaries it checks the presence of  jump instruction to <pass> and the absence of any jump to <fail>
TARGET = '<fail>:'

EXEC_PATH = '../bin/Debug/riscv-emulator'

OUT_FILE = 'out.txt'

def executeTest(bin_file):
    subprocess.run(f'{EXEC_PATH} test/bin_files/{bin_file} > {OUT_FILE}',
                   shell=True)

if __name__ == '__main__':
    test_num = 1
    with open(OUT_FILE) as out:
        for dump_f in glob.glob('dump_files/*.dump'):
            print(f'Testing file: {dump_f}')
            executeTest(dump_f.replace('.dump', '.bin'))
            with open(dump_f) as df:
                s = df.read()
                beg_target = s.rfind(TARGET)
                beg_line = s[:beg_target].rfind('\n')+1
                fail_ins = s[beg_line: beg_target-1]
                if (out.read().find(fail_ins) != -1):
                    print(f"FAILED on test {test_num}")
                    break
            test_num += 1
