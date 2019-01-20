#include <stdio.h>
#define OK 0
#define FAIL 1
#define MAX_LENGTH 50

int main()
{
  char currChar;
  char str[MAX_LENGTH], add[MAX_LENGTH];

  while ((currChar = getchar()) != ',')
  {
  }

  return OK;
}

void print_str_add(char str[], char add[])
{
  int i;
  for (i = 0; i < str_len(str) && i < str_len(add); i++)
  {
    putchar(str[i] + add[i]);
  }
}

int str_len(char str[])
{
  int i;
  /* as long as str[i] != 0 */
  for (i = 0; str[i] && i < MAX_LENGTH; i++)
    ;
  return i;
}