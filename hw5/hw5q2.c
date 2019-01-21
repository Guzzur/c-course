#include <stdio.h>
#define OK 0
#define FAIL 1
#define FALSE 0
#define TRUE 1
#define MAX_LENGTH 50
#define SEPARATOR ','
#define STR_LAST_INPUT "EZPZ"
#define ADD_LAST_INPUT "1337"
#define ASCII_NUM_OFFSET 48

int str_len(char str[])
{
  int i;
  /* as long as str[i] != 0, count chars */
  for (i = 0; str[i] && i < MAX_LENGTH; i++)
    ;
  return i;
}

void print_str_add(char str[], char add[])
{
  int i;
  for (i = 0; i < str_len(str) && i < str_len(add); i++)
  {
    putchar(str[i] + add[i] - ASCII_NUM_OFFSET);
  }
  putchar('\n'); /* TODO: Diff and check if it is needed */
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

void split_str(char orig[], char str_1[MAX_LENGTH], char str_2[MAX_LENGTH], char separator)
{
  int i, j;
  for (i = 0; orig[i] != separator; i++)
    str_1[i] = orig[i];
  str_1[i] = 0;

  j = i + 1;
  for (i = 0; orig[j + i]; i++)
    str_2[i] = orig[j + i];
  str_2[i] = 0;
}

int main()
{
  int done = FALSE;
  char currChar;
  char originalStr[MAX_LENGTH * 2 + 1]; /* Max size is: MAX_LENGTH, SEPARATOR, MAX_LENGTH */
  char str[MAX_LENGTH], add[MAX_LENGTH];

  do
  {
    /* Scan line */
    scanf("%s", originalStr);

    /* Split it into two parts, separated by SEPARATOR */
    split_str(originalStr, str, add, SEPARATOR);

    /* Check if it is the last line of input and set the `done` flag if true */
    if (!str_cmp(str, STR_LAST_INPUT) && !str_cmp(add, ADD_LAST_INPUT))
    {
      done = TRUE;
    }
    /* It is not the last input line, print using print_str_add function */
    else
    {
      /*
      TODO: Remove after running all inputs
      printf("%s\n", originalStr);
      printf("%s\n", str);
      printf("%s\n", add);
      */
      print_str_add(str, add);
    }
  } while (!done);

  return OK;
}
