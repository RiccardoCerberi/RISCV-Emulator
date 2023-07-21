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
    for dump_f in glob.glob('dump_files/*.dump'):
        print(f'Testing file: {dump_f}')
        executeTest(dump_f[dump_f.find('/')+1:].replace('.dump', '.bin'))
        with open(dump_f) as df, open(OUT_FILE) as out:
            s = df.read()
            output = out.read()
            ins_fail = findTargetInstruction(s, '<fail>:')
            print(f'fail instruction: {ins_fail}')
            ins_succ = findTargetInstruction(s, '<pass>:')
            print(f'success instruction: {ins_succ}')
            if output.rfind(ins_fail) != -1:
                print(f'FAILURE: {ins_fail} present')
                break
            if output.rfind(ins_succ) == -1:
                print(f'FAILURE: {ins_succ} not found')
                break
            print('SUCCESS')
        test_num += 1
    print(f'Success = {test_num-1}')
