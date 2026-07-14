#include <stdint.h>
#include <stdio.h>

int main() {

  // 1st Example
  uint8_t a = 200, b = 200;
  uint8_t sum = a + b;

  printf("Example 1\n-----------------\n%d\n", sum);
  //  1100 1000
  // +
  //  1100 1000
  //  ---------
  //  1001 0000 ==> 144
  // FIX: explici cast int on 'a' and 'b'
  printf("1) Fixed: %u\n-----------------\n", (int)a + (int)b);
  // 2nd Example: unsigned to signed value trap
  uint16_t x = 0xFFFF;
  // BUG:  computed in int, overflows, then converted to uint32_t
  uint32_t y = x * x;
  printf("Example 2\n-----------------\nBad=%d\n", y);
  // FIX: computed correctly in 32-bit unsigned, no overflow
  uint32_t y2 = (uint32_t)x * x;
  printf("2) Fixed: %u\n", y2);
  // 3rd Example: mixed sign comparison trap
  unsigned int c = 6;
  int d = -20;
  // BUG: d is implicilty promoted to unsigned int ==> d=4294967276
  // FIX:: cast (int) on c so the comparison becomes valid
  if (d < c) {
    printf("True!\n");
  } else {
    printf("Wrong! trap triggered!");
  }
  return 0;
}
