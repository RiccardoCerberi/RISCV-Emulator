#!/usr/bin/env python3
import subprocess
import matplotlib.pyplot as plt
import glob
import time
import os

# Enable test for emulator.
# For each binaries it checks the presence of a jump to instruction marked as <pass> and the absence of any jump to instruction marked as <fail> 
EXEC_PATH = '../bin/Release/riscv-emulator'

OUT_FILE = 'out.txt'

def executeTest(bin_file):
    subprocess.run(f'{EXEC_PATH} bin_files/{bin_file} > {OUT_FILE}',
                   shell=True)

def findTargetInstruction(s, target):
    beg_target = s.rfind(target)
    beg_ins = s[:beg_target].rfind('\n')+1
    return  s[beg_ins : beg_target-1]

# the file doesn't have fail or pass
check_later = [ 'dump_files/rv32ui-p-simple.dump']

if __name__ == '__main__':
    x = []
    y = []
    test_label = []
    test_num = 1
    t = 0
    for dump_f in glob.glob('dump_files/*.dump'):
        if dump_f in check_later:
            continue
        test_label.append(dump_f[dump_f.rfind('-')+1:dump_f.rfind('.')])
        print(f'Testing file: {dump_f}')
        start = time.time()
        executeTest(dump_f[dump_f.find('/')+1:].replace('.dump', '.bin'))
        end = time.time()
        t += end - start
        with open(dump_f) as df, open(OUT_FILE) as out:
            s = df.read()
            output = out.read()
            ins_fail = findTargetInstruction(s, '<fail>:')
            print(f'fail instruction: {ins_fail}')
            ins_succ = findTargetInstruction(s, '<pass>:')
            print(f'success instruction: {ins_succ}')
            if output.rfind(ins_fail) != -1:
                print(f'FAILURE: {ins_fail} present')
                os.abort()
            if output.rfind(ins_succ) == -1:
                print(f'FAILURE: {ins_succ} not found')
                os.abort()
            print(f'SUCCESS. Execution time: {t}')
        x.append(test_num)
        y.append(end-start)
        test_num += 1
    print(f'Success = {test_num-1}')
    print(f'Execution time (total): {t}')
    plt.figure(figsize=(15,15))
    plt.xticks(x, test_label, rotation = 'vertical')
    plt.vlines(x, min(y) ,y, linestyle="dashed")
    plt.xlim(0, test_num)
    plt.ylim(min(y), max(y))
    plt.xlabel('Tests')
    plt.ylabel('Time')
    plt.title(f'Execution time for all {test_num-1} tests')
    plt.plot(x,y)
    plt.show()
