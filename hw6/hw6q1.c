#include <stdio.h>
#define MAX_SIZE 1000

int max_sum(int a[], int n);
int max(int a, int b);

int main()
{
  int i, size_array, array[MAX_SIZE];
  scanf("%d", &size_array);

  for (i = 0; i < size_array; i++)
    scanf("%d", &array[i]);

  printf("%d", max_sum(array, size_array));
  return 0;
}

int max(int a, int b)
{
  return a > b ? a : b;
}

int max_sum(int a[], int n)
{
  if (n == 2)
  {
    return a[0] + a[1];
  }
  if (n > 2)
  {
    return max(max(max_sum(a + 1, n - 1),
                   a[0] + max_sum(a + 4, n - 4)),
               a[0] + a[1] + max_sum(a + 5, n - 5));
  }
  return 0;
}

/*

5
4 1 7 1 4
8

10
1 2 5 4 2 7 8 9 8 1
26

7
3 4 5 2 7 6 5
18

*/
