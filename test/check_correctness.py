#!/usr/bin/env python3

import subprocess
import matplotlib.pyplot as plt
import glob
import time
import os
import sys

OUT_FILE = 'out.txt'

EXEC_DIR = os.path.join('..', 'bin')

EXEC_NAME = 'riscv-emulator'

BIN_DIR = 'bin_files'

def removeExtension(f):
    f_nodir =  os.path.basename(f)
    return os.path.splitext(f_nodir)[0]

def findTargetInstruction(s, target):
    beg_target = s.rfind(target)
    beg_ins = s[:beg_target].rfind('\n')+1
    return  s[beg_ins : beg_target-1]

# the file doesn't have fail or pass
non_test_file = ['rv32ui-p-simple']

def testPassed(dump_f):
    with open(dump_f) as df, open(OUT_FILE) as out:
        s = df.read()
        output = out.read()
        ins_fail = findTargetInstruction(s, 'fail>:')
        ins_succ = findTargetInstruction(s, '<pass>:')
        if output.rfind(ins_fail) != -1:
            raise Exception(f'<fail> instruction at {ins_fail} is reached.')
        if output.rfind(ins_succ) == -1:
            raise Exception('<pass> instruction misses. '
                    'The emulator terminates prematurely: errors occured.')

def displayStat(x,y, test_num):
    plt.figure(figsize=(15,15))
    plt.xticks(x, test_label, rotation = 'vertical')
    plt.vlines(x, min(y) ,y, linestyle="dashed")
    plt.xlim(0, test_num)
    plt.ylim(min(y), max(y))
    plt.xlabel('Tests')
    plt.ylabel('Time')
    plt.title(f'Execution time for all {test_num} tests')
    plt.plot(x,y)
    plt.show()

def getExecMode():
    available_modes = ('Release', 'Debug')
    mode = available_modes[0]
    if len(sys.argv) >= 2:
        if sys.argv[1] in available_modes:
            mode = sys.argv[1]
        else:
            raise Exception('Invalid mode')
    return mode

if __name__ == '__main__':
    if not os.path.isdir(BIN_DIR):
        print(f'Directory {BIN_DIR} not found, please run get_test.py')
        sys.exit(1)

    try:
        exec_path = os.path.join(EXEC_DIR, getExecMode(), EXEC_NAME)
    except Exception as e:
        print('ERROR: ', e)
        sys.exit(1)

    x = []
    y = []
    test_label = []
    test_num = 0
    t = 0
    for df in glob.glob(os.path.join('riscv-tests', 'isa', 'rv32ui-p-*')):
        if not df.endswith('.dump'): # it's not a dump file
            continue
        fnoext = removeExtension(df)
        if fnoext in non_test_file:
            continue
        bf = fnoext + '.bin'
        test_label.append(fnoext)
        print(f'Testing file: {bf}')
        start = time.time()
        bin_path = os.path.join(BIN_DIR, bf);
        subprocess.run(f'{exec_path} {bin_path} > {OUT_FILE}', shell=True)
        end = time.time()
        t += end - start
        try:
            testPassed(df)
        except Exception as e:
            print(f'Test number {test_num + 1} not passed, error: ', e)
            print(f'Test passed {test_num}')
            sys.exit(1)
        x.append(test_num)
        y.append(end-start)
        test_num += 1

    print(f'SUCCESS: the emulator passed {test_num} tests')
    displayStat(x,y, test_num)
