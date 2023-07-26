/*
 * Opis: Przykładowy kod w Pythonie z różną funkcjonalnością.
 */
fib_mem = [1] * 2
def fill_fib(n):
  global fib_mem
  while len(fib_mem) <= n:
    fib_mem.append(fib_mem[-2] + fib_mem[-1])
def main():
  # Write here. Use PyPy. Don't use list of list -- use instead 1D list with indices i + m * j.
  # Use a // b instead of a / b. Don't use recursive functions (rec limit is approx 1000).
  assert list(range(3, 6)) == [3, 4, 5]
  s = set()
  s.add(5)
  for x in s:
    print(x)
  s = [2 * x for x in s]
  print(eval("s[0] + 10"))
  m = {}
  m[5] = 6
  assert 5 in m
  assert list(m) == [5] # only keys!
  line_list = list(map(int, input().split())) # gets a list of integers in the line
  print(line_list)
  print(' '.join(["a", "b", str(5)]))
  while True:
    try:
      line_int = int(input())
    except Exception as e:
      break
main()
