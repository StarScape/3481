#include <stdio.h>

int f1(int *);

int main()
{
  int x = 0x12345678;
  printf("Val of x: %x\n", x);
  int *p = &x;
  x++;
  int y = *p;
  printf("Val of x: %x\n", x);
  printf("Val of y: %x\n", y);
  printf("Val of p: %x\n", *p);
}

int f1(int *p)
{
  (*p)++;
}
