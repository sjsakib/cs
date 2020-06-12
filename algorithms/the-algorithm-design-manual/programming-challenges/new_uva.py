#!/usr/bin/python3
import sys
import os

if len(sys.argv) != 2:
    raise Exception('Invalid arguments')

name = sys.argv[1]

num, title = name.split(' - ')

short_name = f'uva{num}'

with open('README.md', 'a') as f:
    print(f'\n* [UVa {name}](./uva{num})', file=f)

os.mkdir(short_name)

with open(f'./{short_name}/README.md', 'w') as f:
    print(f'# UVa {name}', file=f)
    print(
        f'[Python solution](https://github.com/sjsakib/cs/blob/master/algorithms/the-algorithm-design-manual/programming-challenges/{short_name}/{short_name}.py)', file=f)

open(f'./{short_name}/{short_name}.py', 'w').close()

os.system(f'code ./{short_name}/{short_name}.py')
