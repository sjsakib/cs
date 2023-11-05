def result(jobs):
  return ' '.join(str(x[1]) for x in sorted(jobs))

jqs = []
for _ in range(int(input())):
  input()
  jobs = []
  for i in range(1, int(input()) + 1):
    T, S = map(int, input().split())
    jobs.append((T / S, i))
  jqs.append(jobs)

print('\n\n'.join(result(jobs) for jobs in jqs))
