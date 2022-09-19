int fib(int n) {
  if(n <= 1) return 1;
  return fib(n-1) + fib(n-2);
}

int main() {
  fib(9);
  for(;;) {
  }
  return 0;
}