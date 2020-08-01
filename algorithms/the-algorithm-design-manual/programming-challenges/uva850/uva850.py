import sys

n = int(input())
input()

phrase = 'the quick brown fox jumps over the lazy dog'


def match(line):
    if len(line) != len(phrase):
        return False

    for i, c in enumerate(line):
        if (c in mapping and mapping[c] != phrase[i]) or (c not in mapping and phrase[i] in mapped):
            return False
        if c not in mapping:
            mapping[c] = phrase[i]
            mapped.add(phrase[i])
    return True


for i in range(n):
    lines = []
    while True:
        try:
            line = input()
        except:
            break
        if (line):
            lines.append(line)
        else:
            break
    found_match = False
    for line in lines:
        mapping = {' ': ' '}
        mapped = set()
        found_match = match(line)
        if found_match:
            break

    if found_match:
        for line in lines:
            for c in line:
                print(mapping[c], end='')
            print('')
    else:
        print('No solution.')
    
    if i != n-1:
        print('')
