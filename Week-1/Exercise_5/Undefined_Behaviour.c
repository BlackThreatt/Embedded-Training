#include <stdint.h>
#include <stdio.h>

int main() {
  // signed overflow test
  int a = 0xFFFFFFFE;
  int b = 0xFFFFFFFF;
  int sum = a + b;
  if (sum < a) {
    printf("Undefined behavior occured.\n");
  }
  /* Compilation with -O0 flag yields no error compared to compilation with -O2
  which prints the message indicating the UB occured. */
  // Null pointer derefrence test
  int *ptr = (void *)0;
  int val = *ptr;
  // printf("%d\n", val);
  /* Both compilations resulted in segmentation fault */
  // out of bounds test
  int c[2] = {0, 1};
  printf("%d\n", c[-1]);
  /* Compilation with -02 flags yields no errors, the value printed is '0',
   * whereas with -00, segmentation fault occured */
  return 0;
}
