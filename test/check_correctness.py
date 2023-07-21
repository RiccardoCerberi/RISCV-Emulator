#!/usr/bin/env python3
import subprocess
import glob

# Enable test for emulator.
# For each binaries it checks the presence of  jump instruction to <pass> and the absence of any jump to <fail>
EXEC_PATH = '../bin/Debug/riscv-emulator'

OUT_FILE = 'out.txt'

def executeTest(bin_file):
    subprocess.run(f'{EXEC_PATH} bin_files/{bin_file} > {OUT_FILE}',
                   shell=True)

def findTargetInstruction(s, target):
    beg_target = s.rfind(target)
    beg_ins = s[:beg_target].rfind('\n')+1
    return  s[beg_ins : beg_target-1]

if __name__ == '__main__':
    test_num = 1
    with open(OUT_FILE) as out:
        for dump_f in glob.glob('dump_files/*.dump'):
            print(f'Testing file: {dump_f}')
            #remove dump_files and .dump from file passed to executeTest
            #function
            executeTest(dump_f[dump_f.find('/')+1:].replace('.dump', '.bin'))
            with open(dump_f) as df:
                s = df.read()
                ins_fail = findTargetInstruction(s, '<fail>:')
                print(f'fail instruction: {ins_fail}')
                ins_succ = findTargetInstruction(s, '<pass>:')
                print(f'fail instruction: {ins_succ}')
                if (out.read().find(ins_fail) == -1 
                    and out.read().find(ins_succ) != -1):
                    print('SUCESS')
                else:
                    print('FAILURE')
                    break
                if (out.read().find(fail_ins) != -1):
                    print(f"FAILED on test {test_num}")
                    break
            test_num += 1
