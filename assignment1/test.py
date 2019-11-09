import os
import sys

mode = sys.argv[1]
if mode == 'upto':
    max_test = int(sys.argv[2])
    for test in range(max_test + 1):
        os.system(f"1511 autotest-stage {str(test).rjust(2, '0')} cs_paint")
elif mode == 'only':
    tests = sys.argv[2:]
    for test in tests:
        os.system(f"1511 autotest-stage {test.rjust(2, '0')} cs_paint")
