#include <stdint.h>
#include <stdio.h>

void *mem_cpy(void *dest, const void *src, uint32_t size);

int main(void) {
  char *a = "Test\n";
  char *b;

  mem_cpy(&b, &a, 6);

  printf("%s\n", b);

  return 0;
}

void *mem_cpy(void *dest, const void *src, uint32_t size) {
  char *d = (char *)dest;
  const char *s = (char *)src;

  if (dest == NULL)
    return NULL;

  for (uint32_t iter = 0; iter < size; iter++) {
    d[iter] = s[iter];
  }
  return dest;
}
