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
  if (a > 0)
  {
    multi(a / 10, b);
  }
  if (b > 0)
  {
    multi(a % 10, b / 10);
  }
  if (a > 0 && b > 0)
  {
    /*
    printf("a=%d, b=%d\n", a, b);

    printf("%d * %d = ", (a % 10), (b % 10));
    */
    printf("%d\n", (a % 10) * (b % 10));
  }
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