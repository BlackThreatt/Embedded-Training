#include <stdio.h>

void first_handler() { printf("first_handler\n"); }
void second_handler() { printf("second_handler\n"); }
void third_handler() { printf("third_handler\n"); }
void fourth_handler() { printf("fourth_handler\n"); }
void fifth_handler() { printf("fifth_handler\n"); }

int main() {
  typedef void (*handlers)();

  handlers dispatch_table[5] = {first_handler, second_handler, third_handler,
                                fourth_handler, fifth_handler

  };
  dispatch_table[4]();
  return 0;
}
