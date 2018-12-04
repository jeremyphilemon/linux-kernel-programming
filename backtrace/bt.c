#include <stdio.h>
#include <stdlib.h>

extern unsigned long *retaddress();
extern void backtrack();
unsigned long bound;
unsigned int loop = 0;
unsigned int count;

void print_main(int (*main)()) { printf("\nMain: %p", main); }

void get_bound(unsigned char *main) {
  while (*main != (unsigned char)0xc3) {
    main++;
  }
  bound = (unsigned long)main;
}

void print_backtrace(int acount) {
  count = acount;
  while (count > 0) {
    loop++;
    unsigned long address = (unsigned long)retaddress();
    if (address >= bound) {
      break;
    }
    printf("0x%llx\n", address);
    backtrack();
    count--;
  }
}

int foo2(int x) {
  print_backtrace(10);
  return x;
}

int foo(int number) {
  int a = 5;
  int b = 3;
  int sum = a + b + foo2(5);
  return sum;
}

int main() {
  unsigned char *mainaddr = (unsigned char *)&main;
  get_bound(mainaddr);
  int something = foo(10);
  return 0;
}