#!/usr/bin/env python3
import subprocess
import matplotlib.pyplot as plt
import glob
import time
import os
import sys

OUT_FILE = 'out.txt'

EXEC_PATH = '../bin/Release/riscv-emulator'

def executeTest(bin_file):
    subprocess.run(f'{EXEC_PATH} bin_files/{bin_file} > {OUT_FILE}',
                   shell=True)

def findTargetInstruction(s, target):
    beg_target = s.rfind(target)
    beg_ins = s[:beg_target].rfind('\n')+1
    return  s[beg_ins : beg_target-1]

# the file doesn't have fail or pass
non_test_file = [ 'dump_files/rv32ui-p-simple.dump']

def testPassed(dump_f):
    with open(dump_f) as df, open(OUT_FILE) as out:
        s = df.read()
        output = out.read()
        ins_fail = findTargetInstruction(s, '<fail>:')
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
    plt.title(f'Execution time for all {test_num-1} tests')
    plt.plot(x,y)
    plt.show()

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('No mode specified: executable from Release, otherwise rerun ' 
              'script passing Debug')
    else:
        EXEC_PATH = f'../bin/{sys.argv[1]}/riscv-emulator'
    x = []
    y = []
    test_label = []
    test_num = 1
    t = 0
    for dump_f in glob.glob('dump_files/*.dump'):
        if dump_f in non_test_file:
            continue
        test_label.append(dump_f[dump_f.rfind('-')+1:dump_f.rfind('.')])
        print(f'Testing file: {dump_f}')
        start = time.time()
        executeTest(dump_f[dump_f.find('/')+1:].replace('.dump', '.bin'))
        end = time.time()
        t += end - start
        try:
            testPassed(dump_f)
        except Exception as e:
            print('ERROR: ', e)
            sys.exit(1)
        x.append(test_num)
        y.append(end-start)
        test_num += 1
    print('SUCCESS: the emulator has passed all tests')
    displayStat(x,y, test_num)
