#include <stdint.h>
#include <stdio.h>

void *mem_cpy(void *dest, const void *src, uint32_t size);
void *mem_set(void *s, int c, size_t n);

int main(void) {
  char *a = "Test\n";
  char *b;

  mem_cpy(&b, &a, 6);
  printf("%s\n", b);

  mem_set(&b, 68, 2);
  printf("%s\n", a);

  return 0;
}

void *mem_set(void *s, int c, size_t n) {
  unsigned char *s_ptr = s;
  unsigned char t = (unsigned char)c;

  for (uint32_t iter = 0; iter < n; iter++) {
    s_ptr[iter] = t;
  }
  return s;
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
