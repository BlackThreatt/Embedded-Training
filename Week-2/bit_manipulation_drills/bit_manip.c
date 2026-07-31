#include <stdint.h>
#include <stdio.h>

#define SET_BIT(reg, pos) ((reg) |= (1U << (pos)))
#define CLEAR_BIT(reg, pos) ((reg) &= ~(1U << (pos)))
#define TOGGLE_BIT(reg, pos) ((reg) ^= (1U << (pos)))
#define READ_BIT(reg, pos) (((reg) & (1U << (pos))) >> (pos))

#define SET_BITS_MASK(reg, pos, mask) ((reg) |= ((mask) << (pos)))
#define CLEAR_BITS_MASK(reg, pos, mask) ((reg) &= ~((mask) << (pos)))
#define TOGGLE_BITS_MASK(reg, pos, mask) ((reg) ^= ((mask) << (pos)))
#define READ_BITS_MASK(reg, pos, mask) (((reg) & ((mask) << (pos))) >> (pos))

int main() {
  uint8_t test = 0;
  SET_BIT(test, 4);
  printf("1) SET TEST = %u\n", test);
  CLEAR_BIT(test, 4);
  printf("2) CLEAR TEST = %u\n", test);
  TOGGLE_BIT(test, 4);
  printf("3) TOGGLE TEST = %u\n", test);
  uint8_t read_test = 0;
  read_test = READ_BIT(test, 4);
  printf("4) READ TEST = %u\n", read_test);
  // Masked version CT
  uint8_t test_mask = 0;
  SET_BITS_MASK(test_mask, 0, 15U);
  printf("5) SET WITH MASK TEST = %u\n", test_mask);
  CLEAR_BITS_MASK(test_mask, 0, 15U);
  printf("6) CLEAR WITH MASK TEST = %u\n", test_mask);
  TOGGLE_BITS_MASK(test_mask, 0, 15U);
  printf("7) TOGGLE WITH MASK TEST = %u\n", test_mask);
  uint8_t read_test_mask = 0;
  read_test_mask = READ_BITS_MASK(test_mask, 0, 15U);
  printf("8) READ WITH MASK TEST = %u\n", test_mask);

  return 0;
}
