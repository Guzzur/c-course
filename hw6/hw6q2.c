#include <stdio.h>
#define MAX_SIZE 1000
void multi(int a, int b);

int main()
{
  int a, b;
  scanf("%d %d", &a, &b);
  multi(a, b);
  return 0;
}

void multi(int a, int b)
{
  if (a < 10 && b < 10)
    printf("%d\n", a * b);
  if (a > 9)
    multi(a / 10, b);
  if (b > 9)
    multi(a, b / 10);
}

/*
123 465
4
6
5
8
12
10
12
18
15

*/