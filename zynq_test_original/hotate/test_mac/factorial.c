int factorial(int n) {
  int result = 1;
  for (int i = 2; i <= n; i++) {
    result *= i;
  }
  return result;
}

int main() {
  factorial(10);
  for(;;) {}
  return 0;
}
