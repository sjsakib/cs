import sys

n = int(input())
all_words = []

for i in range(n):
    all_words.append(input())


def match(idx):
    if idx == len(words):
        return True
    word = words[idx] # encrypted word

    for w in all_words:
        if len(word) != len(w):
            continue

        success = True
        added = set()
        for i, c in enumerate(word):
            if (c in mapping and mapping[c] != w[i]) or (c not in mapping and w[i] in mapped):
                for c in added:
                    mapped.remove(mapping[c])
                    del mapping[c]
                success = False
                break
            if c not in mapping:
                mapping[c] = w[i]
                mapped.add(w[i])
                added.add(c)
        if not success:
            continue

        if match(idx+1):
            return True
        else:
            for c in added:
                mapped.remove(mapping[c])
                del mapping[c]
    return False


for line in sys.stdin:
    words = line.split()
    mapping = {}
    mapped = set()
    found_match = match(0)

    for i, word in enumerate(words):
        for c in word:
            print(mapping[c] if found_match else '*', end='')
        if i != len(words)-1:
            print(' ', end='')
    print('')
