import sys
from collections import deque


def line():
    return sys.stdin.readline()


class Candidate:
    def __init__(self, name, idx):
        self.name = name
        self.votes = 0
        self.idx = idx


nn = int(line())
line()

for ii in range(nn):
    n = int(line())
    candidates = {}
    for i in range(n):
        candidates[i+1] = Candidate(line().strip(), i+1)

    all_votes = []
    while True:
        votes = deque(map(int, line().split()))
        if not votes:
            break
        all_votes.append(votes)

    for votes in all_votes:
        if votes and votes[0] in candidates:
            candidates[votes[0]].votes += 1

    while True:
        sorted_candidates = sorted(candidates.values(), key=lambda c: c.votes, reverse=True)
        eliminated = [sorted_candidates.pop()]
        while sorted_candidates and sorted_candidates[-1].votes == eliminated[0].votes:
            eliminated.append(sorted_candidates.pop())

        for c in eliminated:
            for votes in all_votes:
                if votes[0] == c.idx:
                    votes.popleft()
                    while votes and votes[0] not in candidates:
                        votes.popleft()
                    if votes:
                        candidates[votes[0]].votes += 1
            del candidates[c.idx]
        if not candidates:
            for c in eliminated:
                print(c.name)
            break
        if sorted_candidates[0].votes * 2 > len(all_votes):
            print(sorted_candidates[0].name)
            break
    if ii != nn-1:
        print()
