#include <stdio.h>
#define OK 0
#define FAIL 1
#define MAX_LENGTH 50

int str_len(char str[])
{
  int i;
  /* as long as str[i] != 0 */
  for (i = 0; str[i] && i < MAX_LENGTH; i++)
    ;
  return i;
}

void print_str_add(char str[], char add[])
{
  int i;
  for (i = 0; i < str_len(str) && i < str_len(add); i++)
  {
    putchar(str[i] + add[i]);
  }
}

int str_cmp(char str_1[], char str_2[])
{
  int i = 0;
  char c1, c2;
  do
  {
    c1 = str_1[i];
    c2 = str_2[i];
    if (c1 == '\0')
      return c1 - c2;
  } while (c1 == c2 && ++i < MAX_LENGTH);
  return c1 - c2;
}

int main()
{
  char currChar;
  char str[MAX_LENGTH], add[MAX_LENGTH];

  scanf("%s,%s", &str, &add);

  print_str_add(str, add);

  return OK;
}
