#include <stdint.h>
#include <stdio.h>

void *mem_cpy(void *dest, const void *src, uint32_t size);
void *mem_set(void *s, int c, size_t n);
char *str_cpy(char *dest, const char *src);

int main(void) {
  char *a = "Test\n";
  char *b;

  mem_cpy(&b, &a, 6);
  printf("%s\n", b);

  mem_set(&b, 68, 2);
  printf("%s\n", a);

  char c[20];
  str_cpy(c, a);
  printf("%s", c);

  return 0;
}
char *str_cpy(char *dest, const char *src) {
  const char *src_ptr = src;
  char *dest_ptr = dest;

  if (dest == NULL)
    return NULL;

  while (*src_ptr != '\0')
    *dest_ptr++ = *src_ptr++;
  return dest;
}

void *mem_set(void *s, int c, size_t n) {
  unsigned char *s_ptr = s;

  while (n--)
    *s_ptr++ = (unsigned char)c;

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
