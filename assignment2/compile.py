# USEFUL THINGS
# Windows:
# >> doskey compile=python compile.py $*
# Not Windows:
# >> alias compile="python3 compile.py"


import os
import sys

test = False


compile_normal = 'dcc --leak-check -o pokedex main.c pokedex.c pokemon.c'
compile_test = 'dcc --leak-check -o test_pokedex test_pokedex.c pokedex.c pokemon.c'
run_normal = './pokedex'
run_test = './test_pokedex'

isOnWindows = os.name == 'nt'

def run_cmd(cmd):
    print('running:', cmd)
    os.system(cmd)

if isOnWindows:
    compile_normal = 'gcc -o pokedex.exe main.c pokedex.c pokemon.c'
    compile_test = 'gcc -o test_pokedex.exe test_pokedex.c pokedex.c pokemon.c'
    run_normal = 'pokedex.exe'
    run_test = 'test_pokedex.exe'

if 'test' in sys.argv:
    test = True
    run_cmd(compile_test)
else:
    run_cmd(compile_normal)

if 'run' in sys.argv:
    os.system(run_test if test else run_normal)

        
